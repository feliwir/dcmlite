#include "img_data.h"
#include "charls/charls.h"

#include <iostream>

dcmlite::img::ImageData::ImageData()
{
}

bool dcmlite::img::ImageData::LoadFromDataSet(const DataSet& dataset)
{
  Buffer buffer;
  size_t length = 0;
  if (!dataset.GetBuffer({ 0x7FE0, 0x0010 }, buffer, length)) {
    std::cout << "No image data found" << std::endl;
    return false;
  }

  std::cout << "Image data found" << std::endl;

  JlsParameters params{};

  std::error_code error = JpegLsReadHeader(buffer.get(), length, &params, nullptr);
  if (error) {
    auto msg = charls_get_error_message(error.value());
    return false;
  }

  auto width = params.width;
  auto height = params.height;
}