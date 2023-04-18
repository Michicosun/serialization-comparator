#include <boost/log/trivial.hpp>

#include <worker/udp-server/multicast_listener.hpp>

namespace worker::server {

namespace _detail {

udp::socket CreateMulticastSocket(boost::asio::io_context& io_context, std::string& multicast_ip, uint32_t port) {
  udp::socket socket(io_context);

  socket.open(boost::asio::ip::udp::v4());
  socket.set_option(udp::socket::reuse_address(true));
  socket.bind(udp::endpoint(boost::asio::ip::address_v4::any(), port));

  boost::asio::ip::address address = boost::asio::ip::address::from_string(multicast_ip);
  socket.set_option(boost::asio::ip::multicast::join_group(address));

  return socket;
}

}  // _detail

MulticastListener::MulticastListener(
    boost::asio::io_context& io_context, std::string multicast_ip, uint32_t port,
    boost::asio::thread_pool& pool, serialization::SerializationMethodStorage& storage, uint32_t datagram_len)
  : BaseListener(
      _detail::CreateMulticastSocket(io_context, multicast_ip, port), pool, storage, datagram_len)
  {
    BOOST_LOG_TRIVIAL(info) << "using multicast listener: " << multicast_ip << ":" << port;
    StartReceive();
  }
}
