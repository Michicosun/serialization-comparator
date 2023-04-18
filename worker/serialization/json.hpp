#pragma once

#include <nlohmann/json.hpp>

#include <worker/serialization/base.hpp>


namespace worker::serialization {

namespace _detail {

class Object : public worker::serialization::ISerializationMethod::BaseObject {};

inline void to_json(nlohmann::json& j, const Object& obj) {
  j = nlohmann::json{
    {"str", obj.str},
    {"array", obj.array},
    {"map", obj.map},
    {"number", obj.number},
    {"floating_number", obj.floating_number},
    {"boolean", obj.boolean}
  };
}

inline void from_json(const nlohmann::json& j, Object& obj) {
  j.at("str").get_to(obj.str);
  j.at("array").get_to(obj.array);
  j.at("map").get_to(obj.map);
  j.at("number").get_to(obj.number);
  j.at("floating_number").get_to(obj.floating_number);
  j.at("boolean").get_to(obj.boolean);
}

};  // namespace _detail

class Json : public ISerializationMethod {
 public:
  Json() {
    object_.FillDefault();
  }

  ~Json() = default;

  uint64_t GetSerializedObjectSize() override {
    Serialize();
    uint64_t size = nlohmann::to_string(json_).size();
    Deserialize();
    return size;
  }

  void Serialize() override {
    json_ = object_;
  }

  void Deserialize() override {
    object_ = json_.get<_detail::Object>();
  }

  uint64_t ItersCnt() override {
    return 10000;
  }

 private:
  _detail::Object object_;
  nlohmann::json json_;
};

}
