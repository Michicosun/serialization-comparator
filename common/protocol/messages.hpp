#pragma once

#include <nlohmann/json.hpp>
#include <string>
#include <vector>


namespace common::messages {

enum class MessageType {
  Undefined,
  GetResult,
  GetResultAll,
  WorkerRequest,
  WorkerResponse,
};

// {"method":"get_result", "params": ["json"]}
// {"method":"get_result_all", "params": []}
struct Message {
  std::string method;
  std::vector<std::string> params;

  MessageType GetMessageType();
};

void to_json(nlohmann::json& j, const Message& obj);
void from_json(const nlohmann::json& j, Message& obj);

std::string MessageTypeToString(MessageType);
std::optional<Message> ParseMessageFromString(std::string text);

}
