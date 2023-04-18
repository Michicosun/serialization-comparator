#include <exception>

#include <boost/log/trivial.hpp>

#include <common/protocol/messages.hpp>


namespace common::messages {

static std::string UndefinedType = "undefined";
static std::string GetResultType = "get_result";
static std::string GetResultAllType = "get_result_all";
static std::string WorkerRequestType = "work-request";
static std::string WorkerResponseType = "work-response";

MessageType Message::GetMessageType() {
  if (method == GetResultType) {
    return MessageType::GetResult;
  }
  if (method == GetResultAllType) {
    return MessageType::GetResultAll;
  }
  if (method == WorkerRequestType) {
    return MessageType::WorkerRequest;
  }
  if (method == WorkerResponseType) {
    return MessageType::WorkerResponse;
  }
  BOOST_LOG_TRIVIAL(error) << "unknown message method: " << method;
  return MessageType::Undefined;
}

std::string MessageTypeToString(MessageType type) {
  switch (type) {
  case MessageType::GetResult:
    return GetResultType;
  case MessageType::GetResultAll:
    return GetResultAllType;
  case MessageType::WorkerRequest:
    return WorkerRequestType;
  case MessageType::WorkerResponse:
    return WorkerResponseType;
  default:
    return UndefinedType;
  }
}

void from_json(const nlohmann::json& j, Message& obj) {
  j.at("method").get_to(obj.method);
  j.at("params").get_to(obj.params);
}

void to_json(nlohmann::json& j, const Message& obj) {
  j = nlohmann::json{
    {"method", obj.method},
    {"params", obj.params},
  };
}

std::optional<Message> ParseMessageFromString(std::string text) {
  try {
    return nlohmann::json::parse(text).get<common::messages::Message>();
  } catch (std::exception& e) {
    BOOST_LOG_TRIVIAL(error) << "parse error: " << e.what();
    return {};
  }
}

}
