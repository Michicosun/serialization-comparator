#pragma once

#include <cstdint>
#include <vector>

#include <boost/asio/ip/udp.hpp>
#include <boost/asio/thread_pool.hpp>
#include <boost/bind/bind.hpp>
#include <boost/asio.hpp>

#include <common/protocol/messages.hpp>


namespace proxy::server {

using boost::asio::ip::udp;

class Listener {
 public:
  Listener(boost::asio::io_context& io_context, uint32_t listening_port, uint32_t worker_port, uint32_t datagram_len = 512);

  void UseMulticast(std::vector<std::string> multicast_setting);

 protected:
  void StartReceive();

 private:
  void HandleReceive(const boost::system::error_code& error, std::size_t bytes_transferred);

  void HandleSend(udp::endpoint, const boost::system::error_code&, std::size_t);

  std::optional<udp::endpoint> ResolveWorker(std::string host, uint32_t port);

  std::pair<std::string, udp::endpoint> ProcessMessage(common::messages::Message msg);

 private:
  uint32_t worker_port;
  std::optional<udp::endpoint> multicast_endpoint;

  udp::socket socket_;
  udp::resolver resolver_;
  udp::endpoint remote_endpoint_;
  std::vector<char> recv_buffer_;
};

}
