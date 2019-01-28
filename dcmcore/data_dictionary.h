#pragma once

// Data dictionary singleton.

#include "dcmcore/data_entry.h"
#include "dcmcore/tag.h"

namespace dcmcore {

class DataDictionary {
  public:
  static DataDictionary& Get();

  ~DataDictionary() = default;

  const DataEntry* FindEntry(Tag tag) const;

  private:
  DataDictionary() = default;
};

} // namespace dcmcore