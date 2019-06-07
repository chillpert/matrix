#include "matrix/src/Utils.h"
#include "matrix/src/Logger.h"

#include <sstream>
#include <fstream> 

namespace MX
{
	std::chrono::time_point<std::chrono::steady_clock> current_time;

  std::string parseFile(const std::string& path)
  {
    std::ifstream stream(path);
	  std::string line;
	  std::stringstream ss[1];
  
	  while (getline(stream, line))
    {
	  	ss[0] << line << '\n';
	  }     
	  return ss[0].str();
  }

	std::string tokenizeLine(const std::string &delimiter)
	{
		return "";
	}
}

