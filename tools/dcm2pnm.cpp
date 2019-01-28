#include <fstream>
#include <iomanip>
#include <iostream>
#include <string_view>

#include "cxxopts.hpp"
#include "dcmimg/img_data.h"
#include "dcmcore/dcmcore.h"

int main(int argc, char* argv[])
{
  cxxopts::Options options("dcm2pnm", 
  "Save the pixeldata of the DICOM file as an image file");

  options
      .positional_help("[optional args]")
      .show_positional_help();

  options.add_options("General")
  ("d,debug", "Enable debug mode")
  ("h,help", "Print help")
  ("i,input", "Input file to dump", cxxopts::value<std::string>())
  ("positional", "Positional arguments", cxxopts::value<std::vector<std::string>>());

  options.parse_positional({ "input", "positional" });

  auto result = options.parse(argc, argv);

  if (result.count("help") || (result.count("input") == 0)) {
    std::cout << options.help({}) << std::endl;
    return 0;
  }

  auto file_path = result["input"].as<std::string>();
  std::cout << "Filepath: " << file_path << std::endl;
  std::cout << std::endl;

  dcmcore::DataSet data_set;
  dcmcore::FullReadHandler read_handler(&data_set);

  dcmcore::DicomReader reader(&read_handler);
  reader.ReadFile(file_path);

  dcmcore::img::ImageData img_data;
  img_data.LoadFromDataSet(data_set);

  return 0;
}
