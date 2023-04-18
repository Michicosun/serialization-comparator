#include <boost/log/trivial.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/post.hpp>

#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>

#include <fmt/core.h>

#include <common/protocol/messages.hpp>

#include <worker/udp-server/base_listener.hpp>


namespace worker::server {

BaseListener::BaseListener(
    udp::socket socket,
    boost::asio::thread_pool& pool,
    serialization::SerializationMethodStorage& storage,
    uint32_t datagram_len)
  : socket_{std::move(socket)}
  , recv_buffer_(datagram_len, 0)
  , pool_{pool}
  , storage_{storage} {}

void BaseListener::StartReceive() {
  socket_.async_receive_from(
      boost::asio::buffer(recv_buffer_),
      remote_endpoint_,
      boost::bind(&BaseListener::HandleReceive, this,
        boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred)
  );
}

void BaseListener::TriggerAsyncWrite(std::string response, udp::endpoint remote_endpoint) {
  socket_.async_send_to(boost::asio::buffer(std::move(response)), remote_endpoint,
    boost::bind(&BaseListener::HandleSend, this,
      remote_endpoint,
      boost::asio::placeholders::error,
      boost::asio::placeholders::bytes_transferred)
  );
}

void BaseListener::CalcResult(std::string data, udp::endpoint remote_endpoint) {
  auto msg = common::messages::ParseMessageFromString(data);

  if (!msg.has_value()) {
    BOOST_LOG_TRIVIAL(info) << "incorrect format, skipping request: " << data;
    common::messages::Message new_msg;
    new_msg.method = common::messages::MessageTypeToString(common::messages::MessageType::WorkerResponse);
    new_msg.params.push_back("incorrect format");
    new_msg.params.insert(new_msg.params.end(), msg->params.begin(), msg->params.end());

    nlohmann::json jnew_msg = new_msg;
    TriggerAsyncWrite(nlohmann::to_string(jnew_msg), std::move(remote_endpoint_));
    return;
  }

  auto method = storage_.GetMethod();
  if (!method) {
    BOOST_LOG_TRIVIAL(info) << fmt::format("unknown method {}, skipping request: {}", storage_.GetMethodName(), data);

    common::messages::Message new_msg;
    new_msg.method = common::messages::MessageTypeToString(common::messages::MessageType::WorkerResponse);
    new_msg.params.push_back(fmt::format("unknown method: {}", storage_.GetMethodName()));
    new_msg.params.insert(new_msg.params.end(), msg->params.begin(), msg->params.end());

    nlohmann::json jnew_msg = new_msg;
    TriggerAsyncWrite(nlohmann::to_string(jnew_msg), std::move(remote_endpoint_));
    return;
  }

  common::messages::Message new_msg;
  new_msg.method = common::messages::MessageTypeToString(common::messages::MessageType::WorkerResponse);
  new_msg.params.push_back(method->MakeResponse(storage_.GetMethodName()));
  new_msg.params.insert(new_msg.params.end(), msg->params.begin(), msg->params.end());

  nlohmann::json jnew_msg = new_msg;
  TriggerAsyncWrite(nlohmann::to_string(jnew_msg), std::move(remote_endpoint_));
}

void BaseListener::HandleReceive(const boost::system::error_code& error, std::size_t bytes_received) {
  if (!error) {
    std::string data(recv_buffer_.begin(), recv_buffer_.begin() + bytes_received);
    boost::algorithm::trim(data);

    BOOST_LOG_TRIVIAL(info) << "received: " << data;

    boost::asio::post(pool_, [this, data = std::move(data)]() {
      CalcResult(std::move(data), std::move(remote_endpoint_));
    });

    StartReceive();
  } else {
    BOOST_LOG_TRIVIAL(info) << "receive error: " << error.message();
  }
}

void BaseListener::HandleSend(udp::endpoint remote_endpoint, const boost::system::error_code& error, std::size_t bytes_sent) {
  if (!error) {
    BOOST_LOG_TRIVIAL(info)
      << "successfully sent " << bytes_sent << " bytes to "
      << remote_endpoint.address().to_string() << ":" << remote_endpoint.port();
  } else {
    BOOST_LOG_TRIVIAL(info) << "send error: " << error.message();
  }
}

}
