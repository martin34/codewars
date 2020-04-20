#pragma once

#include <string>
#include <type_traits>

namespace templates {

constexpr char kNotSupportedOutput[] = "Not supported type";

template <class T>
typename std::enable_if<!std::is_integral<T>::value, std::string>::type
to_string(T) {
  return {kNotSupportedOutput};
}

template <class T>
typename std::enable_if<std::is_integral<T>::value, std::string>::type
to_string(T v) {
  return std::to_string(v);
}

template <> std::string to_string(double);
} // namespace templates