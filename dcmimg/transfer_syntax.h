#pragma once
#include "dcmcore/data_set.h"

namespace dcmcore::img {

enum class TransferSyntax {
  IMPLICIT_VR,
  EXPLICIT_VR_LE,
  EXPLICIT_VR_BE,
};

class TransferSyntaxUtil {
  public:
  static bool GetSyntax(const DataSet& dataset, TransferSyntax& syntax);
};

}