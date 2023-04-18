#pragma once

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>

#include <worker/serialization/base.hpp>

#include <fmt/core.h>


namespace worker::serialization {

class SerializationMethodStorage {
  using Constructor = std::function<std::unique_ptr<ISerializationMethod>(void)>;
 public:
  SerializationMethodStorage(std::string using_method)
    : using_method_{std::move(using_method)} {}

  template<class Method>
  void RegisterMethod(std::string name) {
    methods_[name] = []() { return std::make_unique<Method>(); };
  }

  std::unique_ptr<ISerializationMethod> GetMethod() {
    auto it = methods_.find(using_method_);
    if (it == methods_.end()) {
      return nullptr;
    }
    return it->second();
  }

  std::string GetMethodName() {
    return using_method_;
  }

 private:
  std::string using_method_;
  std::unordered_map<std::string, Constructor> methods_;
};

}
