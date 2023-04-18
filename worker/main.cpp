#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

#include <common/env/helper.hpp>

#include <string>
#include <worker/udp-server/unicast_listener.hpp>
#include <worker/udp-server/multicast_listener.hpp>

#include <worker/serialization/storage.hpp>
#include <worker/serialization/native.hpp>
#include <worker/serialization/xml.hpp>
#include <worker/serialization/json.hpp>
#include <worker/serialization/yaml.hpp>
#include <worker/serialization/msgpack.hpp>
#include <worker/serialization/protocol-buffers/protobuf.hpp>
#include <worker/serialization/avro/avro.hpp>


int main(int argc, char** argv) {
  auto [worker_settings, correct_env] = common::env::GetAll({"PORT", "METHOD"});
  if (!correct_env) {
    BOOST_LOG_TRIVIAL(error) << "incorrect environment variables, required {PORT, METHOD}";
    return 1;
  }

  auto unicast_port = std::stoi(worker_settings[0]);
  auto using_method = worker_settings[1];

  auto [multicast_settings, use_multicast] = common::env::GetAll({"MULTICAST_IP", "MULTICAST_PORT"});

  worker::serialization::SerializationMethodStorage storage(std::move(using_method));
  storage.RegisterMethod<worker::serialization::Native>("native");
  storage.RegisterMethod<worker::serialization::Xml>("xml");
  storage.RegisterMethod<worker::serialization::Json>("json");
  storage.RegisterMethod<worker::serialization::Yaml>("yaml");
  storage.RegisterMethod<worker::serialization::MessagePack>("msgpack");
  storage.RegisterMethod<worker::serialization::Protobuf>("protobuf");
  storage.RegisterMethod<worker::serialization::Avro>("avro");

  boost::asio::thread_pool pool(std::thread::hardware_concurrency());

  try {
    boost::asio::io_context io_context;
    worker::server::UnicastListener unicast_listener(io_context, unicast_port, pool, storage);
    if (use_multicast) {
      auto multicast_ip = multicast_settings[0];
      auto multicast_port = std::stoi(multicast_settings[1]);
      worker::server::MulticastListener multicast_listener(io_context, multicast_ip, multicast_port, pool, storage);
      io_context.run();
    }
    io_context.run();
  } catch (std::exception& e) {
    BOOST_LOG_TRIVIAL(info) << "ERROR: " << e.what();
  }
  return 0;
}
