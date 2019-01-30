#pragma once
#include "dcmcore/buffer.h"
#include <memory>
#include <stdint.h>

namespace dcmcore::img {
class IImage {
  public:
  inline IImage(const uint32_t width, const uint32_t height,
      const uint8_t bpp)
      : m_width(width)
      , m_height(height)
      , m_bpp(bpp)
  {
  }

  inline uint32_t GetWidth() const
  {
    return m_width;
  }

  inline uint32_t GetHeight() const
  {
    return m_height;
  }

  inline uint8_t GetBitsPerPixel() const
  {
    return m_bpp;
  }

  virtual inline uint8_t GetStorageBitsPerPixel() const = 0;

  inline uint8_t GetStorageBytesPerPixel() const
  {
    return GetStorageBitsPerPixel() / 8;
  }

  inline uint32_t GetTotalSize() const
  {
    return GetStorageBytesPerPixel() * m_width * m_height;
  }

  inline const Buffer& GetBuffer() const
  {
    return m_buffer;
  }

  inline void SetBuffer(const Buffer& buffer)
  {
    m_buffer = buffer;
  }

  protected:
  Buffer m_buffer;
  uint32_t m_width;
  uint32_t m_height;
  uint8_t m_bpp;
};

template <class T>
class Image final : public IImage {
  public:
  inline Image(uint32_t width, uint32_t height,
      uint8_t bpp)
      : IImage(width, height, bpp)
  {
    m_buffer.resize(width * height * GetStorageBitsPerPixel());
  }

  inline uint8_t GetStorageBitsPerPixel() const override
  {
    return sizeof(T) * 8;
  }

  inline const T* GetData() const
  {
    return reinterpret_cast<const T*>(m_buffer.data());
  }

  inline const T& GetPixel(uint32_t c, uint32_t r) const
  {
    uint32_t index = (r * m_width + c);
    return GetData()[index];
  }
};
}