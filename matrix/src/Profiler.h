#ifndef PROFILER_H
#define PROFILER_H

#include "stdafx.h"

namespace MX
{
  class Profiler
  {
  public:
    // total virtual memory (installed RAM + SWAP file)
    unsigned int get_tvm();
    // current virtual memory
    unsigned int get_cvm();
  };

}

#endif // PROFILER_H