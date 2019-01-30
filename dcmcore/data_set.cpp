#include "dcmcore/data_set.h"
#include "dcmcore/visitor.h"
#include <algorithm>
#include <cassert>
#include <iostream>

namespace dcmcore {

DataSet::DataSet(Tag tag, Endian endian)
    : DataElement(tag, tag.IsEmpty() ? VR::UNKNOWN : VR::SQ, endian)
    , explicit_vr_(true)
{
}

DataSet::~DataSet()
{
  Clear();
}

void DataSet::Accept(Visitor& visitor)
{
  visitor.VisitDataSet(this);
}

DataElement* DataSet::operator[](std::size_t index)
{
  assert(index < m_elements.size());
  return m_elements[index];
}

const DataElement* DataSet::operator[](std::size_t index) const
{
  assert(index < m_elements.size());
  return m_elements[index];
}

const DataElement* DataSet::At(std::size_t index) const
{
  if (index < m_elements.size()) {
    return m_elements[index];
  }
  return nullptr;
}

void DataSet::AddElement(DataElement* element)
{
  m_elements.emplace_back(element);
}

const DataElement* DataSet::GetElement(Tag tag) const
{
  auto element = std::find_if(m_elements.begin(), m_elements.end(), [&tag](DataElement* el) {
    return el->tag() == tag;
  });

  if (element == m_elements.end())
    return nullptr;

  return *element;
}

void DataSet::Clear()
{
  endian_ = kLittleEndian;
  explicit_vr_ = true;

  for (DataElement* element : m_elements) {
    delete element;
  }
  m_elements.clear();
}

bool DataSet::GetBuffer(Tag tag,
    Buffer& buffer,
    std::size_t& length) const
{
  const DataElement* element = GetElement(tag);
  if (element != nullptr) {
    buffer = element->buffer();
    length = element->length();
    return true;
  }
  return false;
}

bool DataSet::GetString(Tag tag, std::string& value) const
{
  const DataElement* element = GetElement(tag);
  if (element != nullptr) {
    return element->GetString(value);
  }

  return false;
}

} // namespace dcmcore
