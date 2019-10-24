#include "Profiler.h"

#ifdef MX_PLATFORM_WINDOWS_X64
  #include "windows.h"
#elif MX_PLATFORM_UNIX_X64
  #include "sys/types.h"
  #include "sys/sysinfo.h"
#endif

namespace MX
{
  unsigned int Profiler::get_tvm()
  {
#ifdef MX_PLATFORM_WINDOWS_X64

    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&memInfo);

    return memInfo.ullTotalPageFile;

#elif MX_PLATFORM_UNIX_X64

    struct sysinfo memInfo;

    sysinfo(&memInfo);
    long long totalVirtualMem = memInfo.totalram;
    // add other values in next statement to avoid int overflow on right hand side
    totalVirtualMem += memInfo.totalswap;
    totalVirtualMem *= memInfo.mem_unit;

    return totoalVirtualMem

#endif
  }

  unsigned int Profiler::get_cvm()
  {
#ifdef MX_PLATFORM_WINDOWS_X64

    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&memInfo);

    return memInfo.ullTotalPageFile - memInfo.ullAvailPageFile;

#elif MX_PLATFORM_UNIX_X64

    long long virtualMemUsed = memInfo.totalram - memInfo.freeram;
    // add other values in next statement to avoid int overflow on right hand side
    virtualMemUsed += memInfo.totalswap - memInfo.freeswap;
    virtualMemUsed *= memInfo.mem_unit;

    return virtualMemUsed;

#endif
  }
}