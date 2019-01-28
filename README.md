# dcmcore

A lightweight C++ DICOM library for reading and writing DICOM files.

## Usage

### Read Full Data Set

```cpp
dcmcore::DataSet data_set;
dcmcore::FullReadHandler read_handler(&data_set);
dcmcore::DicomReader reader(&read_handler);
reader.ReadFile("path/to/some/dcm");
```

With the data set, you can get tags.

Read string:
```cpp
std::string transfer_syntax_uid;
if (data_set.GetString(dcmcore::Tag(0x0002, 0x0010), &transfer_syntax_uid)) {
  std::cout << "Transfer Syntax UID: " << transfer_syntax_uid << std::endl;
}

std::string patient_name;
if (data_set.GetString(dcmcore::Tag(0x0010, 0x0010), &patient_name)) {
  std::cout << "Patient Name: " << patient_name << std::endl;
}
```

Read integer:
```cpp
std::uint16_t samples_per_pixel;
if (data_set.GetUint16(dcmcore::Tag(0x0028, 0x0002), &samples_per_pixel)) {
  std::cout << "Samples Per Pixel: " << samples_per_pixel << std::endl;
}
```

### Read Specific Tags

Much less memory allocation thus much faster.

```cpp
dcmcore::DataSet data_set;
dcmcore::TagsReadHandler read_handler(&data_set);

// Add tags to read.
read_handler.AddTag(dcmcore::Tag(0x0002, 0x0010)).
    AddTag(dcmcore::Tag(0x0010, 0x0010)).
    AddTag(dcmcore::Tag(0x0028, 0x0002));

dcmcore::DicomReader reader(&read_handler);
reader.ReadFile("path/to/some/dcm")

// Get value from data set.
// ...
```

## Write

Write a data set to a file:
```cpp
  dcmcore::BinaryFile file;
  if (!file.Open("output.dcm", dcmcore::BinaryFile::Mode::WRITE)) {
    std::cerr << "Failed to open output file.\n";
    return;
  }

  dcmcore::WriteVisitor visitor(&file);
  data_set.Accept(visitor);
```
