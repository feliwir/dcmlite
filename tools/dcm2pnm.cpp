#include <fstream>
#include <iomanip>
#include <iostream>
#include <string_view>

#include "cxxopts.hpp"
#include "dcmcore/dcmcore.h"
#include "dcmimg/image.h"
#include "dcmimg/img_data.h"
#include "pnm.hpp"

int main(int argc, char* argv[])
{
  cxxopts::Options options("dcm2pnm",
      "Save the pixeldata of the DICOM file as an image file");

  options
      .positional_help("[optional args]")
      .show_positional_help();

  options.add_options("General")("d,debug", "Enable debug mode")("h,help", "Print help")("i,input", "Input file to dump", cxxopts::value<std::string>())("positional", "Positional arguments", cxxopts::value<std::vector<std::string>>());

  options.parse_positional({ "input", "positional" });

  auto result = options.parse(argc, argv);

  if (result.count("help") || (result.count("input") == 0)) {
    std::cout << options.help({}) << std::endl;
    return 0;
  }

  auto file_path = result["input"].as<std::string>();

  dcmcore::DataSet data_set;
  dcmcore::FullReadHandler read_handler(&data_set);

  dcmcore::DicomReader reader(&read_handler);
  reader.ReadFile(file_path);

  dcmcore::img::ImageData img_data;
  if (!img_data.LoadFromDataSet(data_set)) {
    std::cout << "Failed to load imagedata!" << std::endl;
    return -1;
  }

  auto image = img_data.GetImage();
  pnm::pgm_image pgm(image->GetWidth(), image->GetHeight());

  for (size_t r = 0; r < pgm.height(); ++r) {
    for (size_t c = 0; c < pgm.width(); ++c) {
      uint8_t val = 0;
      if (image->GetBitsPerPixel() > 8) {
        int n = image->GetStorageBitsPerPixel() - image->GetBitsPerPixel();
        auto img = dynamic_cast<const dcmcore::img::Image<uint16_t>*>(image);
        val = std::numeric_limits<uint8_t>::max() - (img->GetPixel(c, r) >> n);
      } else {
        auto img = dynamic_cast<const dcmcore::img::Image<uint8_t>*>(image);
        val = std::numeric_limits<uint8_t>::max() - img->GetPixel(c, r);
      }

      pgm[r][c] = val;
    }
  }

  pnm::write("test.pgm", pgm, pnm::format::binary);

  return 0;
}
