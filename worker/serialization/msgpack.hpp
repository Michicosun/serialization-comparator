#include <fmt/core.h>

#include <catch2/catch.hpp>
#include <msgpack/msgpack.hpp>

#include <worker/serialization/base.hpp>


namespace worker::serialization {

class MessagePack : public ISerializationMethod {
 public:
  MessagePack() {
    object_.FillDefault();
  }

  ~MessagePack() = default;

  uint64_t GetSerializedObjectSize() override {
    Serialize();
    uint64_t size = bytes_.size();
    Deserialize();
    return size;
  }

  void Serialize() override {
    bytes_ = msgpack::pack(object_);
  }

  void Deserialize() override {
    object_ = msgpack::unpack<Object>(bytes_);
  }

  uint64_t ItersCnt() override {
    return 100000;
  }

 private:
  struct Object: public BaseObject {
    template<class T>
    void pack(T &pack) {
      pack(str, array, map, number, floating_number, boolean);
    }
  };

 private:
  Object object_;
  std::vector<uint8_t> bytes_;
};

}
