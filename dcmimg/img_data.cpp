#include "img_data.h"
#include "charls/charls.h"
#include "transfer_syntax.h"

#include <iostream>

// Dimensions
constexpr dcmcore::Tag kRows(0x0028, 0x0010);
constexpr dcmcore::Tag kColumns(0x0028, 0x0011);

// Pixeldata
constexpr dcmcore::Tag kPixelData(0x7FE0, 0x0010);

dcmcore::img::ImageData::ImageData()
{
}

bool dcmcore::img::ImageData::LoadFromDataSet(const DataSet& dataset)
{
  if (!dataset.GetUint16(kColumns, m_columns)) {
    std::cout << "No width specified" << std::endl;
    return false;
  }

  if (!dataset.GetUint16(kRows, m_rows)) {
    std::cout << "No height specified" << std::endl;
    return false;
  }

  TransferSyntax syntax;
  if (!TransferSyntaxUtil::GetSyntax(dataset, syntax)) {
    std::cout << "No transfersyntax specified" << std::endl;
    return false;
  }

  Buffer buffer;
  size_t length = 0;
  if (!dataset.GetBuffer(kPixelData, buffer, length)) {
    std::cout << "No image data found" << std::endl;
    return false;
  }

  switch (syntax)
  {
    case TransferSyntax::EXPLICIT_VR_LE:
      /* code */
      break;

    case TransferSyntax::EXPLICIT_VR_BE:
      break;
  
    default:
      // Not implemented yet
      break;
  }
}

bool dcmcore::img::ImageData::LoadJpegLs(const dcmcore::Buffer& buffer)
{
  JlsParameters params {};

  std::error_code error = JpegLsReadHeader(buffer.data(), buffer.size(), &params, nullptr);
  if (error) {
    auto msg = charls_get_error_message(error.value());
    return false;
  }

  auto width = params.width;
  auto height = params.height;
}