#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "dcmcore/data_element.h"
#include "dcmcore/defs.h"

namespace dcmcore {

class Visitor;

class DataSet : public DataElement {
  public:
  // NOTE:
  // The data set will be nested (SQ) if the tag is not empty.
  // The VR (UNKNOWN or SQ) is determined by if the tag is empty or not.
  DataSet(Tag tag = Tag(), Endian endian = kLittleEndian);

  virtual ~DataSet();

  // TODO: const?
  virtual void Accept(Visitor& visitor) override;

  Endian endian() const
  {
    return endian_;
  }
  void set_endian(Endian endian)
  {
    endian_ = endian;
  }

  bool explicit_vr() const
  {
    return explicit_vr_;
  }
  void set_explicit_vr(bool explicit_vr)
  {
    explicit_vr_ = explicit_vr;
  }

  // Get the number of child elements.
  inline std::size_t GetSize() const
  {
    return m_elements.size();
  }

  // Get the element at the given index.
  DataElement* operator[](std::size_t index);

  // Get the element at the given index.
  const DataElement* operator[](std::size_t index) const;

  // Get the element at the given index.
  // Return nullptr if out of index (
  const DataElement* At(std::size_t index) const;

  void AddElement(DataElement* element);

  const DataElement* GetElement(Tag tag) const;

  // Clear data elements, reset endian type, etc.
  void Clear();

  // Get raw buffer (binary data).
  bool GetBuffer(Tag tag,
      Buffer& buffer,
      std::size_t& length) const;

  bool GetString(Tag tag, std::string& value) const;

  template <class T>
  inline bool Get(Tag tag, T& value) const
  {
    const DataElement* element = GetElement(tag);
    if (element != nullptr) {
      return element->Get<T>(value);
    }

    return false;
  }

  private:
  bool explicit_vr_;

  // Child elements.
  std::vector<DataElement*> m_elements;
};

} // namespace dcmcore