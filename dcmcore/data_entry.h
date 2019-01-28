#pragma once

// Data dictionary entry.

#include "dcmcore/defs.h"
#include "dcmcore/vr.h"

namespace dcmcore {

class DataEntry {
  public:
  std::uint32_t tag;
  VR::Type vr_type;
  std::string keyword;
  std::string description;
};

} // namespace dcmcore