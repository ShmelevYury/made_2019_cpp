#ifndef SERIALIZER_05_SERIALIZER_H
#define SERIALIZER_05_SERIALIZER_H

#include <ostream>
#include <istream>

enum class Error {
  NoError,
  CorruptedArchive,
  CorruptedData
};

class Serializer {
 public:
  explicit Serializer(std::ostream& out);

  template <class T>
  Error Save(T& obj);

  template <class... ArgsT>
  Error operator()(ArgsT&&... args);

 private:
  static constexpr char Separator = ' ';
  std::ostream& out_;

  template <class T>
  Error Process(T&& val);

  template <class T, class... ArgsT>
  Error Process(T&& val, ArgsT&&... args);
};

class DeSerializer {
 public:
  explicit DeSerializer(std::istream& in);

  template <class T>
  Error Load(T& obj);

  template <class... ArgsT>
  Error operator()(ArgsT&&... args);

 private:
  std::istream& in_;

  template <class T>
  Error Process(T&& val);

  template <class T, class... ArgsT>
  Error Process(T&& val, ArgsT&&... args);
};

//Template realisation

template <class T>
Error Serializer::Save(T& obj) {
  return obj.Serialize(*this);
}

template <class T>
Error ToString(T& val, std::ostream& out) {
  return Error::CorruptedData;
}

template <>
Error ToString<uint64_t>(uint64_t& val, std::ostream& out) {
  out << val << ' ';
  return Error::NoError;
}

template <>
Error ToString<bool>(bool& val, std::ostream& out) {
  if (val) {
    out << "true ";
  } else {
    out << "false ";
  }
  return Error::NoError;
}

template <class T>
Error Serializer::Process(T&& val) {
  return ToString(val, out_);
}

template <class T, class... ArgsT>
Error Serializer::Process(T&& val, ArgsT&&... args) {
  if (ToString(val, out_) == Error::CorruptedData) {
    return Error::CorruptedData;
  } else {
    return Serializer::Process(std::forward<ArgsT>(args)...);
  }
}

template <class... ArgsT>
Error Serializer::operator()(ArgsT&&... args) {
  return Serializer::Process(std::forward<ArgsT>(args)...);
}

template <class T>
Error DeSerializer::Load(T &obj) {
  return obj.Serialize(*this);
}

template <class T>
Error FromString(T& val, std::istream& in) {
  return Error::CorruptedData;
}

template <>
Error FromString<uint64_t>(uint64_t& val, std::istream& in) {
  in >> val;
  return Error::NoError;
}

template <>
Error FromString<bool>(bool& val, std::istream& in) {
  std::string text;
  in >> text;

  if (text == "true") {
    val = true;
  } else if (text == "false") {
    val = false;
  } else {
    return Error::CorruptedArchive;
  }
  return Error::NoError;
}

template <class T>
Error DeSerializer::Process(T&& val) {
  return FromString(val, in_);
}

template <class T, class... ArgsT>
Error DeSerializer::Process(T&& val, ArgsT&&... args) {
  if (FromString(val, in_) == Error::CorruptedArchive) {
    return Error::CorruptedArchive;
  } else {
    return DeSerializer::Process(std::forward<ArgsT>(args)...);
  }
}

template <class... ArgsT>
Error DeSerializer::operator()(ArgsT&&... args) {
  DeSerializer::Process(std::forward<ArgsT>(args)...);
}

Serializer::Serializer(std::ostream &out) : out_(out) {};

DeSerializer::DeSerializer(std::istream &in) : in_(in) {}

#endif //SERIALIZER_05_SERIALIZER_H
