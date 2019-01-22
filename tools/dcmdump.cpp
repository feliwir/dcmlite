#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

#include "cxxopts.hpp"

#include "dcmlite/dcmlite.h"

std::string EndianToString(dcmlite::Endian endian)
{
    if (endian == dcmlite::kLittleEndian) {
        return "Little Endian";
    } else {
        return "Big Endian";
    }
}

void DumpDicomFile(const std::string& file_path)
{
    dcmlite::DumpReadHandler read_handler;
    dcmlite::DicomReader reader(&read_handler);
    reader.ReadFile(file_path);

    std::cout << std::endl;
}

int main(int argc, char* argv[])
{
    cxxopts::Options options("dcmdump", "Dump the tags of a DICOM file.");
    options.add_options("General")
    ("d,debug", "Enable debug mode")
    ("h,help",  "Print help")
    ("i,input", "Input file to dump", cxxopts::value<std::string>());

    options.parse_positional({ "input" });

    auto result = options.parse(argc, argv);

    if (result.count("help") || result.count("input")==0)
    {
        std::cout << options.help({}) << std::endl;
        return 0;
    }

    auto file_path = result["input"].as<std::string>();
    std::cout << "file path: " << file_path << std::endl;
    std::cout << std::endl;

    DumpDicomFile(file_path);

    return 0;
}
