#include "img_data.h"
#include "charls/charls.h"
#include "transfer_syntax.h"

#include <iostream>

// Dimensions
constexpr dcmcore::Tag kRows(0x0028, 0x0010);
constexpr dcmcore::Tag kColumns(0x0028, 0x0011);

// Bits per pixel
constexpr dcmcore::Tag kBitsAllocated(0x0028, 0x0100);
constexpr dcmcore::Tag kBitsStored(0x0028, 0x0101);

// Pixeldata
constexpr dcmcore::Tag kPixelData(0x7FE0, 0x0010);

dcmcore::img::ImageData::ImageData()
{
}

bool dcmcore::img::ImageData::CreateImage(const DataSet& dataset)
{
  uint16_t columns, rows, abpp, bpp;

  if (!dataset.Get<uint16_t>(kColumns, columns)) {
    std::cout << "No width specified" << std::endl;
    return false;
  }

  if (!dataset.Get<uint16_t>(kRows, rows)) {
    std::cout << "No height specified" << std::endl;
    return false;
  }

  if (!dataset.Get<uint16_t>(kBitsAllocated, abpp)) {
    std::cout << "No allocated bits per pixel specified" << std::endl;
    return false;
  }

  if (!dataset.Get<uint16_t>(kBitsStored, bpp)) {
    std::cout << "No stored bits per pixel specified" << std::endl;
    return false;
  }

  switch (abpp) {
  case 8:
    m_image = std::make_unique<Image<uint8_t>>(columns, rows, bpp);
    break;
  case 16:
    m_image = std::make_unique<Image<uint16_t>>(columns, rows, bpp);
    break;
  default:
    break;
  }

  return true;
}

bool dcmcore::img::ImageData::LoadFromDataSet(const DataSet& dataset)
{
  if (!CreateImage(dataset)) {
    std::cout << "Missing required image tags" << std::endl;
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

  switch (syntax) {
  case TransferSyntax::EXPLICIT_VR_LE:
    return LoadUncompressedLE(buffer);

  case TransferSyntax::EXPLICIT_VR_BE:
    break;

  default:
    // Not implemented yet
    break;
  }

  return false;
}

bool dcmcore::img::ImageData::LoadJpegLs(const dcmcore::Buffer& buffer)
{
  JlsParameters params {};

  std::error_code error = JpegLsReadHeader(buffer.data(), buffer.size(), &params, nullptr);
  if (error) {
    auto msg = charls_get_error_message(error.value());
    return false;
  }

  return true;
}

bool dcmcore::img::ImageData::LoadUncompressedLE(const Buffer& buffer)
{
  if (m_image->GetTotalSize() != buffer.size()) {
    std::cout << "Image data size doesn't match expected size" << std::endl;
    return false;
  }

  m_image->SetBuffer(buffer);
  return true;
}