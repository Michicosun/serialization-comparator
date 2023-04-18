#include <boost/asio/ip/address_v4.hpp>
#include <boost/log/trivial.hpp>

#include <boost/algorithm/string.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/ip/udp.hpp>
#include <boost/asio/post.hpp>

#include <nlohmann/json.hpp>

#include <fmt/core.h>

#include <common/protocol/messages.hpp>

#include <proxy/udp/listener.hpp>
#include <stdexcept>
#include <string>


namespace proxy::server {

namespace _detail {

udp::socket CreateSocket(boost::asio::io_context& io_context, uint32_t port) {
  udp::socket socket(io_context, udp::endpoint(udp::v4(), port));
  socket.set_option(udp::socket::reuse_address(true));
  return socket;
}

}

Listener::Listener(boost::asio::io_context& io_context, uint32_t listening_port, uint32_t worker_port, uint32_t datagram_len)
  : worker_port{worker_port}
  , socket_(_detail::CreateSocket(io_context, listening_port))
  , resolver_(io_context)
  , recv_buffer_(datagram_len, 0)
{
  BOOST_LOG_TRIVIAL(info) << "proxy listening on port " << listening_port;
  StartReceive();
}

std::optional<udp::endpoint> Listener::ResolveWorker(std::string host, uint32_t port) {
  BOOST_LOG_TRIVIAL(info) << "trying to resolve " << host << ":" << port;

  try {
    udp::resolver::query query(boost::asio::ip::udp::v4(), host, std::to_string(port));
    auto endpoint = resolver_.resolve(query).begin()->endpoint();
    BOOST_LOG_TRIVIAL(info) << host << ":" << port << " resolved to " << endpoint.address().to_string() << ":" << endpoint.port();
    return endpoint;
  } catch (std::exception& e) {
    return {};
  }
}

void Listener::UseMulticast(std::vector<std::string> multicast_setting) {
  multicast_endpoint = udp::endpoint(boost::asio::ip::address::from_string(multicast_setting[0]), std::stoi(multicast_setting[1]));
  BOOST_LOG_TRIVIAL(info) << fmt::format(
    "using multicast dispatch to {}:{}", multicast_endpoint->address().to_string(), multicast_endpoint->port()
  );
}

void Listener::StartReceive() {
  socket_.async_receive_from(
      boost::asio::buffer(recv_buffer_),
      remote_endpoint_,
      boost::bind(&Listener::HandleReceive, this,
        boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred)
  );
}

std::pair<std::string, udp::endpoint> Listener::ProcessMessage(common::messages::Message msg) {
  BOOST_LOG_TRIVIAL(info) << "processing message: " << msg.method;
  switch (msg.GetMessageType()) {
    case common::messages::MessageType::GetResult: {
      if (msg.params.size() != 1) {
        BOOST_LOG_TRIVIAL(error) << "incorrect query len(params) != 1, method: " << msg.method;
        return {"incorrect query len(params) != 1", remote_endpoint_};
      }

      auto endpoint = ResolveWorker(msg.params[0], worker_port);
      if (!endpoint.has_value()) {
        return {fmt::format("undefined serialization method: {}", msg.params[0]), remote_endpoint_};
      }

      common::messages::Message new_msg;
      new_msg.method = msg.method;
      new_msg.params = {remote_endpoint_.address().to_string(), std::to_string(remote_endpoint_.port())};

      nlohmann::json jnew_msg = new_msg;
      auto text = nlohmann::to_string(jnew_msg);

      return {std::move(text), std::move(*endpoint)};
    }
    case common::messages::MessageType::GetResultAll: {
      if (multicast_endpoint.has_value()) {
        common::messages::Message new_msg;
        new_msg.method = msg.method;
        new_msg.params = {remote_endpoint_.address().to_string(), std::to_string(remote_endpoint_.port())};

        nlohmann::json jnew_msg = new_msg;
        auto text = nlohmann::to_string(jnew_msg);

        return {std::move(text), *multicast_endpoint};
      } else {
        BOOST_LOG_TRIVIAL(error) << "multicast is not configured";
        return {"multicast is not configured", remote_endpoint_};
      }
    }
    case common::messages::MessageType::WorkerResponse: {
      auto text = msg.params[0];

      auto user_ip = msg.params[1];
      auto user_port = std::stoi(msg.params[2]);
      auto endpoint = udp::endpoint(boost::asio::ip::address::from_string(user_ip), user_port);

      return {std::move(text), std::move(endpoint)};
    }
    default: {
      BOOST_LOG_TRIVIAL(error) << "unexpected message: " << msg.method;
      return {"unexpected message", remote_endpoint_};
    }
  }
}

void Listener::HandleReceive(const boost::system::error_code& error, std::size_t bytes_received) {
  if (!error) {
    std::string data(recv_buffer_.begin(), recv_buffer_.begin() + bytes_received);
    boost::algorithm::trim(data);

    auto msg_opt = common::messages::ParseMessageFromString(std::move(data));
    if (msg_opt.has_value()) {
      auto msg = msg_opt.value();
      BOOST_LOG_TRIVIAL(info) << "received msg with method: " << msg.method << ", len(params): " << msg.params.size();

      auto [msg_to_send, endpoint_to_send] = ProcessMessage(std::move(msg));

      socket_.async_send_to(boost::asio::buffer(std::move(msg_to_send)), endpoint_to_send,
        boost::bind(&Listener::HandleSend, this,
          endpoint_to_send,
          boost::asio::placeholders::error,
          boost::asio::placeholders::bytes_transferred)
      );
    } else {
      socket_.async_send_to(boost::asio::buffer("parse error"), remote_endpoint_,
        boost::bind(&Listener::HandleSend, this,
          remote_endpoint_,
          boost::asio::placeholders::error,
          boost::asio::placeholders::bytes_transferred)
      );
    }

    StartReceive();
  } else {
    BOOST_LOG_TRIVIAL(info) << "receive error: " << error.message();
  }
}

void Listener::HandleSend(udp::endpoint remote_endpoint, const boost::system::error_code& error, std::size_t bytes_sent) {
  if (!error) {
    BOOST_LOG_TRIVIAL(info)
      << "successfully sent " << bytes_sent << " bytes to "
      << remote_endpoint.address().to_string() << ":" << remote_endpoint.port();
  } else {
    BOOST_LOG_TRIVIAL(info) << "send error: " << error.message();
  }
}

}
