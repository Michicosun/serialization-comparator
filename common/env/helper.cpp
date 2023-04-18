#include <common/env/helper.hpp>

namespace common::env {

std::pair<std::vector<std::string>, bool> GetAll(std::vector<std::string> names) {
  std::vector<std::string> ans;

  for (const auto& env_name : names) {
    char* env_var = std::getenv(env_name.c_str());
    if (!env_var) {
      return {{}, false};
    }
    ans.emplace_back(env_var);
  }

  return {ans, true};
}

}
