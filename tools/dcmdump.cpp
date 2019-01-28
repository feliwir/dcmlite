#include <fstream>
#include <iomanip>
#include <iostream>
#include <string_view>

#include "cxxopts.hpp"
#include "dcmcore/dcmcore.h"

void DumpDicomFile(std::string_view file_path)
{
  dcmcore::DumpReadHandler read_handler;
  dcmcore::DicomReader reader(&read_handler);
  reader.ReadFile(file_path);

  std::cout << std::endl;
}

int main(int argc, char* argv[])
{
  cxxopts::Options options("dcmdump", "Dump the tags of a DICOM file.");
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

  if (result.count("help") || result.count("input") == 0) {
    std::cout << options.help({}) << std::endl;
    return 0;
  }

  auto file_path = result["input"].as<std::string>();
  std::cout << "Filepath: " << file_path << std::endl;
  std::cout << std::endl;

  DumpDicomFile(file_path);

  return 0;
}
