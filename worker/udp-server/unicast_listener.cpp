#include <boost/log/trivial.hpp>

#include <worker/udp-server/unicast_listener.hpp>


namespace worker::server {

namespace _detail {

udp::socket CreateUnicastSocket(boost::asio::io_context& io_context, uint32_t port) {
  udp::socket socket(io_context, udp::endpoint(udp::v4(), port));
  socket.set_option(udp::socket::reuse_address(true));
  return socket;
}

}  // detail

UnicastListener::UnicastListener(
    boost::asio::io_context& io_context, uint32_t port, boost::asio::thread_pool& pool,
    serialization::SerializationMethodStorage& storage, uint32_t datagram_len)
  : BaseListener(_detail::CreateUnicastSocket(io_context, port), pool, storage, datagram_len)
{
  BOOST_LOG_TRIVIAL(info) << "using unicast listener on port " << port;
  StartReceive();
}

}  // worker::server
