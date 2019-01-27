#include "dcmlite/dcmlite.h"
#include "gtest/gtest.h"
#include <filesystem>
#include <iostream>

void testFile(std::string_view path)
{
  std::cout << "Testing file: " << path << std::endl;
  dcmlite::DataSet data_set;
  dcmlite::FullReadHandler read_handler(&data_set);
  dcmlite::DicomReader reader(&read_handler);

  // Try to open one of my CR datasets
  EXPECT_TRUE(reader.ReadFile(path));

  // Retrieve the patient name
  std::string patient_name;
  EXPECT_TRUE(data_set.GetString(dcmlite::Tag(0x0010, 0x0010), patient_name));
  EXPECT_EQ(patient_name, "Vedder^Stephan");
}

TEST(LoadDicom, CR)
{
  for (auto& p : std::filesystem::directory_iterator("./data/CR")) {
    testFile("./data/CR/" + p.path().filename().string());
  }
}
