#pragma once

#include <vector>

#include <boost/asio/ip/udp.hpp>
#include <boost/asio/thread_pool.hpp>
#include <boost/bind/bind.hpp>
#include <boost/asio.hpp>

#include <fmt/core.h>

#include <worker/serialization/storage.hpp>


namespace worker::server {

using boost::asio::ip::udp;

class BaseListener {
 public:
  BaseListener(udp::socket, boost::asio::thread_pool&, serialization::SerializationMethodStorage&, uint32_t = 512);

 protected:
  void StartReceive();

 private:
  void HandleReceive(const boost::system::error_code& error, std::size_t bytes_transferred);

  void HandleSend(udp::endpoint, const boost::system::error_code&, std::size_t);

 private:
  void CalcResult(std::string data, udp::endpoint remote_endpoint);

  void TriggerAsyncWrite(std::string response, udp::endpoint remote_endpoint);

 private:
  udp::socket socket_;
  udp::endpoint remote_endpoint_;
  std::vector<char> recv_buffer_;
  boost::asio::thread_pool& pool_;
  serialization::SerializationMethodStorage& storage_;
};

}
