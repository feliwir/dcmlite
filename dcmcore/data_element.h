#pragma once

#include <cstdint>
#include <iosfwd>
#include <memory>
#include <vector>

#include "dcmcore/buffer.h"
#include "dcmcore/tag.h"
#include "dcmcore/vr.h"

namespace dcmcore {

class Visitor;

class DataElement {
  public:
  DataElement(Tag tag, VR::Type vr_type, Endian endian);

  virtual ~DataElement()
  {
  }

  Tag tag() const
  {
    return tag_;
  }

  // NOTE: VR is not allowed to change after construction.
  VR::Type vr_type() const
  {
    return vr_type_;
  }

  // Get the value length.
  std::size_t length() const
  {
    return buffer_.size();
  }

  // NOTE: SetBuffer will also set length.
  void set_length(std::size_t length)
  {
    //buffer_.resize(length);
  }

  // Get the value buffer.
  // NOTE: No set_buffer() is provided; see SetBuffer().
  const Buffer& buffer() const
  {
    return buffer_;
  }

  // Set value buffer and length together.
  // The length must be even (2, 4, 8, etc.).
  // Always set buffer and length together to ensure data consistency.
  void SetBuffer(Buffer buffer);

  // TODO: Add applicable VR types as comments.
  bool GetString(std::string& value) const;

  template <class T>
  inline bool Get(T& value) const
  {
    if (GetNumber<T>(value)) {
      AdjustBytes<T>(&value);
      return true;
    }
    return false;
  }

  // Print value to an output stream.
  void PrintValue(std::ostream& os) const;

  // Print value to a string.
  void PrintValue(std::string& str) const;

  // Visitor design pattern.
  virtual void Accept(Visitor& visitor);

  protected:
  // Get number value.
  template <typename T>
  bool GetNumber(T& value) const
  {
    if (!buffer_.empty() && buffer_.size() == sizeof(T)) {
      value = *reinterpret_cast<const T*>(buffer_.data());
      return true;
    }
    return false;
  }

  template <class T>
  inline void AdjustBytes(void* value) const
  {
    if (endian_ != PlatformEndian()) {
      byteswap<T>(&value);
    }
  }

  protected:
  Tag tag_;
  VR::Type vr_type_;

  // Big endian or little endian.
  Endian endian_;

  // Value buffer.
  Buffer buffer_;
};

std::ostream& operator<<(std::ostream& os, const DataElement& element);

} // namespace dcmcore