#pragma once

#include <array>
#include <chrono>
#include <cstring>
#include <worker/serialization/base.hpp>


namespace worker::serialization {

class Native : public ISerializationMethod {
 public:
  Native() {
    object_.FillDefault();
  }

  ~Native() = default;

  uint64_t GetSerializedObjectSize() override {
    Serialize();
    uint64_t size = bytes_.size();
    Deserialize();
    return size;
  }

  void Serialize() override {
    memcpy(bytes_.data(), &object_, sizeof(Object));
  }

  void Deserialize() override {
    object_ = *reinterpret_cast<Object*>(bytes_.data());
  }

  uint64_t ItersCnt() override {
    return 100000;
  }

 private:
  struct Object: public BaseObject {};

 private:
  Object object_;
  std::array<uint8_t, sizeof(Object)> bytes_;
};

}
