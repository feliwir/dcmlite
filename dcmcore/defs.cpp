#include "dcmcore/defs.h"

namespace dcmcore {

static union {
  char c[4];
  unsigned long mylong;
} endian_test = { { 'l', '?', '?', 'b' } };

#define ENDIANNESS ((char)endian_test.mylong)

Endian PlatformEndian()
{
  static Endian endian = (ENDIANNESS == 'l') ? kLittleEndian : kBigEndian;
  return endian;
}

} // namespace dcmcore
