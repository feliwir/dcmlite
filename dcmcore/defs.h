#pragma once

#include <cstdint>
#include <string>

namespace dcmcore {

enum Endian {
  kLittleEndian,
  kBigEndian,
};

// Return the endian type of the current platform.
Endian PlatformEndian();

const std::uint32_t kUndefinedLength = 0xFFFFFFFF;

typedef float float32_t;
typedef double float64_t;

template <typename T>
T byteswap(T value);

template <>
inline uint16_t byteswap<std::uint16_t>(std::uint16_t value)
{
  return (value >> 8) | (value << 8);
}

template <>
inline int16_t byteswap<std::int16_t>(std::int16_t value)
{
  return (value >> 8) | (value << 8);
}

template <>
inline uint32_t byteswap<uint32_t>(uint32_t value)
{
  return std::uint32_t(byteswap<uint16_t>(value) << 16) | byteswap<uint16_t>(value >> 16);
}

template <>
inline int32_t byteswap<int32_t>(int32_t value)
{
  return std::int32_t(byteswap<int16_t>(value) << 16) | byteswap<int16_t>(value >> 16);
}

template <>
inline uint64_t byteswap<uint64_t>(uint64_t value)
{
  return std::uint64_t((unsigned long long)byteswap<uint32_t>(value) << 32LL) | byteswap<uint32_t>(value >> 32LL);
}

template <typename T>
inline void byteswap(void* src)
{
  T* p = (T*)src;
  *p = byteswap(*p);
}

template <>
inline void byteswap<float64_t>(void* src)
{
  uint64_t* p = (uint64_t*)src;
  *p = byteswap(*p);
}

template <>
inline void byteswap<float32_t>(void* src)
{
  uint32_t* p = (uint32_t*)src;
  *p = byteswap(*p);
}

} // namespace dcmcore