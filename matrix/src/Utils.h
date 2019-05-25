#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

namespace MX
{
  std::string parseFile(const std::string &path);
  std::string tokenizeLine(const std::string &delimiter);

  const int initial_window_width = 1200;
  const int initial_window_height = 600;
}

#endif // UTILS_H