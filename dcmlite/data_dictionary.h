#pragma once

// Data dictionary singleton.

#include "dcmlite/data_entry.h"
#include "dcmlite/tag.h"

namespace dcmlite {

class DataDictionary {
public:
    static DataDictionary& Get();

    ~DataDictionary() = default;

    const DataEntry* FindEntry(Tag tag) const;

private:
    DataDictionary() = default;
};

} // namespace dcmlite