#include "transfer_syntax.h"
#include <map>

// Transfer syntax
constexpr dcmcore::Tag kTransferSyntax(0x0002, 0x0010);

std::map<std::string, dcmcore::img::TransferSyntax> kTransferSyntaxMap = {
  { "1.2.840.10008.1.2", dcmcore::img::TransferSyntax::IMPLICIT_VR },
  { "1.2.840.10008.1.2.1", dcmcore::img::TransferSyntax::EXPLICIT_VR_LE },
  { "1.2.840.10008.1.2.2", dcmcore::img::TransferSyntax::EXPLICIT_VR_BE },
};

bool dcmcore::img::TransferSyntaxUtil::GetSyntax(const DataSet& dataset, TransferSyntax& syntax)
{
  std::string syntaxStr;
  if (!dataset.GetString(kTransferSyntax, syntaxStr)) {
    // Transfer syntax doesn't exist
    return false;
  }

  auto syntaxIt = kTransferSyntaxMap.find(syntaxStr.c_str());
  if (syntaxIt == kTransferSyntaxMap.end()) {
    // Not handled yet
    return false;
  }

  syntax = syntaxIt->second;

  return true;
}