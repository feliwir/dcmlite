#pragma once

#include <fstream>
#include <stdint.h>
#include <string>
#include <string_view>

#include "dcmcore/data_set.h"
#include "image.h"

namespace dcmcore::img {

class ImageData final {
  public:
  ImageData();

  bool LoadFromDataSet(const DataSet& dataset);

  inline const IImage* GetImage()
  {
    return m_image.get();
  }

  private:
  bool CreateImage(const DataSet& dataset);

  bool LoadJpegLs(const Buffer& buffer);
  bool LoadUncompressedLE(const Buffer& buffer);

  std::unique_ptr<IImage> m_image;
};

}