#include "dcmcore/dcmcore.h"
#include "gtest/gtest.h"
#include <filesystem>
#include <iostream>

void testFile(std::string_view path)
{
  std::cout << "Testing file: " << path << std::endl;
  dcmcore::DataSet data_set;
  dcmcore::FullReadHandler read_handler(&data_set);
  dcmcore::DicomReader reader(&read_handler);

  // Try to open one of my CR datasets
  EXPECT_TRUE(reader.ReadFile(path));

  // Retrieve the patient name
  std::string patient_name;
  EXPECT_TRUE(data_set.GetString(dcmcore::Tag(0x0010, 0x0010), patient_name));
  EXPECT_EQ(patient_name, "Vedder^Stephan");
}

TEST(LoadDicom, CR)
{
  for (auto& p : std::filesystem::directory_iterator("./data/CR")) {
    testFile("./data/CR/" + p.path().filename().string());
  }
}
