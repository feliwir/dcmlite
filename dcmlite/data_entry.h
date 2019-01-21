#pragma once

// Data dictionary entry.

#include "dcmlite/defs.h"
#include "dcmlite/vr.h"

namespace dcmlite {

class DataEntry {
public:
    std::uint32_t tag;
    VR::Type vr_type;
    std::string keyword;
    std::string description;
};

} // namespace dcmlite