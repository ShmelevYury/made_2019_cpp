#define CATCH_CONFIG_MAIN

#include "../catch2/catch.hpp"
#include "serializer.h"
#include <cctype>

struct Data {
  uint64_t a;
  bool b;
  uint64_t c;

  template <class SerializerT>
  Error Serialize(SerializerT& serializer) {
    return serializer(a, b, c);
  }
};

template <class T1, class T2, class T3>
struct WrongData {
  T1 a;
  T2 b;
  T3 c;

  template <class SerializerT>
  Error Serialize(SerializerT& serializer) {
    return serializer(a, b, c);
  }
};

TEST_CASE("Lesson example") {
  Data x{1, true, 2};

  std::stringstream stream;
  Serializer serializer(stream);
  auto err = serializer.Save(x);
  REQUIRE(err == Error::NoError);

  Data y{0, false, 0};

  DeSerializer deserializer(stream);
  err = deserializer.Load(y);

  REQUIRE(err == Error::NoError);
  REQUIRE(x.a == y.a);
  REQUIRE(x.b == y.b);
  REQUIRE(x.c == y.c);
}

TEST_CASE("Wrong data") {
  std::stringstream stream;
  Serializer serializer(stream);
  WrongData<int, bool, int> x{1, true, 2};
  REQUIRE(serializer.Save(x) == Error::CorruptedData);

  WrongData<uint64_t, bool, int> y{1, true, 2};
  REQUIRE(serializer.Save(y) == Error::CorruptedData);

  WrongData<uint64_t, int, uint64_t > z{1, true, 2};
  REQUIRE(serializer.Save(z) == Error::CorruptedData);
}

TEST_CASE("Corrupted Archive") {
  std::stringstream stream_x{"1 lol 2"};
  DeSerializer deserializer_x(stream_x);
  Data x{};
  REQUIRE(deserializer_x.Load(x) == Error::CorruptedArchive);

  std::stringstream streamy{"true 356.7 2"};
  DeSerializer deserializer_y(streamy);
  Data y{};
  REQUIRE(deserializer_y.Load(y) == Error::CorruptedArchive);
}