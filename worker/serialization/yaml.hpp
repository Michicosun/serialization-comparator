#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

#include <fmt/core.h>

#include <yaml-cpp/yaml.h>

#include <worker/serialization/base.hpp>

namespace worker::serialization {


class Yaml : public ISerializationMethod {
 public:
  Yaml() {
    object_.FillDefault();
  }

  ~Yaml() = default;

  uint64_t GetSerializedObjectSize() override {
    Serialize();
    YAML::Emitter emmiter;
    emmiter << node_;
    size_t size = emmiter.size();
    Deserialize();
    return size;
  }

  void Serialize() override {
    node_ = object_;
  }

  void Deserialize() override {
    object_ = node_.as<Object>();
  }

  uint64_t ItersCnt() override {
    return 10000;
  }

 struct Object : public BaseObject {};

 private:
  Object object_;
  YAML::Node node_;
};

};

namespace YAML {

template<>
struct convert<worker::serialization::Yaml::Object> {
  static Node encode(const worker::serialization::Yaml::Object& rhs) {
    Node node;
    node["str"] = rhs.str;
    node["array"] = rhs.array;
    node["map"] = rhs.map;
    node["number"] = rhs.number;
    node["floating_number"] = rhs.floating_number;
    node["boolean"] = rhs.boolean;
    return node;
  }

  static bool decode(const Node& node, worker::serialization::Yaml::Object& rhs) {
    rhs.str = node["str"].as<std::string>();
    rhs.array = node["array"].as<std::vector<uint64_t>>();
    rhs.map = node["map"].as<std::map<std::string, uint64_t>>();
    rhs.number = node["number"].as<uint64_t>();
    rhs.floating_number = node["floating_number"].as<double>();
    rhs.boolean = node["boolean"].as<bool>();
    return true;
  }
};

}
