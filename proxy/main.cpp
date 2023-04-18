#include <boost/log/trivial.hpp>

#include <common/env/helper.hpp>

#include <proxy/udp/listener.hpp>

int main(int argc, char** argv) {
  auto [settings, is_correct_env] = common::env::GetAll({"PROXY_PORT", "WORKER_PORT"});

  if (!is_correct_env) {
    BOOST_LOG_TRIVIAL(error) << "incorrect environment variables, required {PROXY_PORT, WORKER_PORT}";
    return 1;
  }

  uint32_t proxy_port = std::stoi(settings[0]);
  uint32_t worker_port = std::stoi(settings[1]);

  auto [multicast_settings, using_multicast] = common::env::GetAll({"MULTICAST_IP", "MULTICAST_PORT"});

  try {
    boost::asio::io_context io_context;
    proxy::server::Listener listener(io_context, proxy_port, worker_port);
    if (using_multicast) {
      listener.UseMulticast(std::move(multicast_settings));
    }
    io_context.run();
  } catch (std::exception& e) {
    BOOST_LOG_TRIVIAL(info) << "ERROR: " << e.what();
  }
  return 0;
}
