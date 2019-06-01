#include "matrix/src/controller/InputMap.h"

namespace MX 
{
  float speed = 2.0f;
  
  bool key_w = 0;
  bool key_a = 0;
  bool key_s = 0;
  bool key_d = 0;
  bool key_c = 0;
  bool key_space = 0;

  void disable_all_keys()
  {
    speed = 2.0f;

    key_w = 0;
    key_a = 0;
    key_s = 0;
    key_d = 0;
    key_c = 0;
    key_space = 0;
  }
}