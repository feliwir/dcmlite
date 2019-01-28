#pragma once

// Data Element Tag:
// A unique identifier for a Data Element composed of an ordered pair of numbers
// (a Group Number followed by an Element Number).
// See DICOM Part 3 / 3.8 or Part 5 / 3.10.

#include <cstdint>
#include <iosfwd>

#include "dcmcore/defs.h"

namespace dcmcore {

class Tag;

extern const Tag kSeqEndTag; // (0xFFFE, 0xE0DD)
extern const Tag kSeqItemEndTag; // (0xFFFE, 0xE00D)
extern const Tag kSeqItemPrefixTag; // (0xFFFE, 0xE000)

// Usage Hint:
//   Since the size of a tag is only 4-bytes, feel free to pass and
//   return by value.
class Tag {
  public:
  Tag() = default;
  Tag(const Tag& rhs) = default;
  Tag& operator=(const Tag& rhs) = default;

  constexpr Tag(const std::uint16_t group, const std::uint16_t element)
      : group_(group)
      , element_(element)
  {
  }

  constexpr Tag(const std::uint32_t tag_key)
      : group_((tag_key >> 16) & 0xFFFF)
      , element_(tag_key & 0xFFFF)
  {
  }

  inline std::uint16_t group() const
  {
    return group_;
  }

  inline void set_group(std::uint16_t group)
  {
    group_ = group;
  }

  inline std::uint16_t element() const
  {
    return element_;
  }

  inline void set_element(std::uint16_t element)
  {
    element_ = element;
  }

  inline bool IsEmpty() const
  {
    return group_ == 0 && element_ == 0;
  }

  inline Tag SwapBytes() const
  {
    return Tag(byteswap<uint16_t>(group_), byteswap<uint16_t>(element_));
  }

  // Convert to a 4-byte unsigned integer.
  // Group in high two bytes, element in low two bytes.
  inline std::uint32_t ToUint32() const
  {
    return (group_ << 16) + element_;
  }

  private:
  std::uint16_t group_;
  std::uint16_t element_;
};

inline bool operator==(Tag lhs, Tag rhs)
{
  return (lhs.group() == rhs.group() && lhs.element() == rhs.element());
}

inline bool operator!=(Tag lhs, Tag rhs)
{
  return !(lhs == rhs);
}

inline bool operator<(Tag lhs, Tag rhs)
{
  return lhs.ToUint32() < rhs.ToUint32();
}

inline bool operator>(Tag lhs, Tag rhs)
{
  return lhs.ToUint32() > rhs.ToUint32();
}

inline bool operator<=(Tag lhs, Tag rhs)
{
  return lhs.ToUint32() <= rhs.ToUint32();
}

inline bool operator>=(Tag lhs, Tag rhs)
{
  return lhs.ToUint32() >= rhs.ToUint32();
}

std::ostream& operator<<(std::ostream& os, Tag tag);

} // namespace dcmcore