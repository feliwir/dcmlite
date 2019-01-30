#include "dcmcore/dcmcore.h"
#include "dcmimg/img_data.h"
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

void testImage(std::string_view path, int width, int height)
{
  dcmcore::DataSet data_set;
  dcmcore::FullReadHandler read_handler(&data_set);
  dcmcore::DicomReader reader(&read_handler);

  // Try to open one of my CR datasets
  reader.ReadFile(path);
  dcmcore::img::ImageData img_data;

  // Try to open one of my CR datasets
  EXPECT_TRUE(img_data.LoadFromDataSet(data_set));

  auto image = img_data.GetImage();
  EXPECT_EQ(image->GetWidth(), width);
  EXPECT_EQ(image->GetHeight(), height);
}

TEST(LoadDicom, CR)
{
  for (auto& p : std::filesystem::directory_iterator("./data/CR")) {
    testFile("./data/CR/" + p.path().filename().string());
  }
}

TEST(LoadImageData, CR)
{
  testImage("./data/CR/0000.dcm", 2364, 2868);
  testImage("./data/CR/0001.dcm", 1419, 2247);
  testImage("./data/CR/0002.dcm", 1089, 1941);
}
