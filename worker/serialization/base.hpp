#pragma once

#include <cmath>
#include <cstdint>
#include <ctime>
#include <map>
#include <vector>

#include <fmt/core.h>


namespace worker::serialization {

template <class Func>
uint64_t CalcExecutionTime(Func func) {
  clock_t start_time = clock();
  func();
  double ticks = static_cast<double>(clock() - start_time);

  return std::round(ticks / CLOCKS_PER_SEC * 1e9);  // nanosecs
}

class ISerializationMethod {
 public:
  struct TestTime {
    TestTime(uint64_t s_time, uint64_t d_time)
      : s_time_(s_time)
      , d_time_(d_time) {}

    uint64_t s_time_;
    uint64_t d_time_;
  };

  virtual ~ISerializationMethod() = default;

  std::string MakeResponse(std::string method_name) {
    auto object_size = GetSerializedObjectSize();
    auto test_time = CalcTestTime();

    return fmt::format(
      "{} - {}b - {}ns - {}ns\n",
      method_name, object_size, test_time.s_time_, test_time.d_time_
    );
  }

  struct BaseObject {
    void FillDefault() {
      str = "hello world!";
      array = {1, 2, 3, 4, 5};
      map = {{"str_1", 1}, {"str_2", 2}};
      number = 42;
      floating_number = 84.84;
      boolean = false;
    };

    std::string str;
    std::vector<uint64_t> array;
    std::map<std::string, uint64_t> map;
    uint64_t number;
    double floating_number;
    bool boolean;
  };

 protected:
  virtual uint64_t ItersCnt() = 0;
  virtual uint64_t GetSerializedObjectSize() = 0;
  virtual void Serialize() = 0;
  virtual void Deserialize() = 0;

 private:
  TestTime CalcTestTime() {
    uint64_t s_time = 0;
    uint64_t d_time = 0;

    auto s_func = [this](){Serialize();};
    auto d_func = [this](){Deserialize();};

    uint64_t kRunCount = ItersCnt();

    for (uint64_t i = 0; i < kRunCount; ++i) {
      s_time += CalcExecutionTime(s_func);
      d_time += CalcExecutionTime(d_func);
    }

    return TestTime(s_time / kRunCount , d_time / kRunCount);
  }
};

}
