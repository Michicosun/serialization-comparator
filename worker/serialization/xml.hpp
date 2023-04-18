#pragma once

#include "fmt/os.h"
#include <array>
#include <boost/archive/basic_archive.hpp>
#include <cstdint>
#include <sstream>
#include <worker/serialization/base.hpp>

#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/vector.hpp>

#include <fmt/core.h>


namespace worker::serialization {

class Xml : public ISerializationMethod {
  using RawDataBuffer = std::string;

 public:
  Xml() {
    object_.FillDefault();
  }

  ~Xml() = default;

  uint64_t GetSerializedObjectSize() override {
    Serialize();
    uint64_t size = bytes_.size();
    Deserialize();
    return size;
  }

  void Serialize() override {
    std::stringstream ss;
    boost::archive::xml_oarchive o_xml(ss, boost::archive::no_header);

    o_xml << BOOST_SERIALIZATION_NVP(object_);

    bytes_ = ss.str();
  }

  void Deserialize() override {
    std::stringstream ss(bytes_);
    boost::archive::xml_iarchive i_xml(ss, boost::archive::no_header);

    i_xml >> BOOST_SERIALIZATION_NVP(object_);
  }

  uint64_t ItersCnt() override {
    return 10000;
  }

 private:
  struct Object : public BaseObject {
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & BOOST_SERIALIZATION_NVP(str);
        ar & BOOST_SERIALIZATION_NVP(array);
        ar & BOOST_SERIALIZATION_NVP(map);
        ar & BOOST_SERIALIZATION_NVP(number);
        ar & BOOST_SERIALIZATION_NVP(floating_number);
        ar & BOOST_SERIALIZATION_NVP(boolean);
    }
  };

 private:
  Object object_;
  RawDataBuffer bytes_;
};

}
