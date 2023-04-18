#pragma once

#include <api/Specific.hh>
#include <api/Stream.hh>

#include <worker/serialization/base.hpp>
#include <worker/serialization/avro/object.hh>

namespace worker::serialization {

class Avro : public ISerializationMethod {
 public:
  Avro()
    : encoder_{avro::binaryEncoder()}
    , decoder_{avro::binaryDecoder()}
  {
    FillDefault();
  }

  ~Avro() = default;

  uint64_t GetSerializedObjectSize() override {
    Serialize();
    uint64_t size = out_->byteCount();
    Deserialize();
    return size;
  }

  void Serialize() override {
    out_ = avro::memoryOutputStream();
    encoder_->init(*out_);

    avro::encode(*encoder_, object_);
    encoder_->flush();
  }

  void Deserialize() override {
    in_ = avro::memoryInputStream(*out_);
    decoder_->init(*in_);

    avro::decode(*decoder_, object_);
  }

  uint64_t ItersCnt() override {
    return 100000;
  }

 private:
  void FillDefault() {
    object_.str = "hello world!";
    object_.array = {1, 2, 3, 4, 5};
    object_.map = {{"str_1", 1}, {"str_2", 2}};
    object_.number = 42;
    object_.floating_number = 84.84;
    object_.boolean = false;
  }

  void Clear() {
    object_.str = {};
    object_.array = {};
    object_.map = {};
    object_.number = {};
    object_.floating_number = {};
    object_.boolean = {};
  }

 private:
  avro_serialization::Object object_;

  avro::OutputStreamPtr out_;
  avro::InputStreamPtr in_;

  avro::EncoderPtr encoder_;
  avro::DecoderPtr decoder_;
};

}
