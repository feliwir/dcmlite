#pragma once

#include <fstream>
#include <stdint.h>
#include <string>
#include <string_view>

#include "dcmcore/data_set.h"

namespace dcmcore::img {

class ImageData final {
  public:
  ImageData();

  bool LoadFromDataSet(const DataSet& dataset);

  private:
  bool LoadJpegLs(const Buffer& buffer);

  uint16_t m_columns;
  uint16_t m_rows;
};

}