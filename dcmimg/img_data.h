#pragma once

#include <fstream>
#include <stdint.h>
#include <string>
#include <string_view>

#include "dcmlite/data_set.h"

namespace dcmlite::img {

class ImageData final {
  public:
  ImageData();

  bool LoadFromDataSet(const DataSet& dataset);
};

}