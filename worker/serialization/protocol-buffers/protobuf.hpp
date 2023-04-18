#pragma once

#include <fmt/core.h>

#include <worker/serialization/base.hpp>
#include <worker/serialization/protocol-buffers/object.pb.h>

namespace worker::serialization {

class Protobuf : public ISerializationMethod {
 public:
  Protobuf() {
    FillDefault();
  }

  ~Protobuf() = default;

  uint64_t GetSerializedObjectSize() override {
    Serialize();
    uint64_t size = bytes_.size();
    Deserialize();
    return size;
  }

  void Serialize() override {
    object_.SerializeToString(&bytes_);
  }

  void Deserialize() override {
    object_.ParseFromString(bytes_);
  }

  uint64_t ItersCnt() override {
    return 100000;
  }

 private:
  void FillDefault() {
    object_.Clear();
    object_.set_str("hello world!");
    for (size_t i = 1; i <= 5; ++i) {
      object_.add_array(i);
    }
    auto& map = *object_.mutable_map();
    map["str_1"] = 1;
    map["str_2"] = 2;
    object_.set_number(42);
    object_.set_floating_number(84.84);
    object_.set_boolean(false);
  }

 private:
  protobuf_serialization::Object object_;
  std::string bytes_;
};

}
