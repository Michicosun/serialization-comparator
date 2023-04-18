#pragma once

#include <vector>
#include <string>

namespace common::env {

std::pair<std::vector<std::string>, bool> GetAll(std::vector<std::string> names);

}
