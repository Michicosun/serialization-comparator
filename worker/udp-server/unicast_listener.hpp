#pragma once

#include <boost/asio/ip/udp.hpp>

#include <worker/udp-server/base_listener.hpp>
#include <worker/serialization/storage.hpp>


namespace worker::server {

class UnicastListener : public BaseListener {
 public:
  UnicastListener(
    boost::asio::io_context& io_context, uint32_t port, boost::asio::thread_pool& pool,
    serialization::SerializationMethodStorage& storage, uint32_t datagram_len = 512);

  ~UnicastListener() = default;
};

}
