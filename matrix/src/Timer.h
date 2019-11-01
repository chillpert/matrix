#ifndef TIMER_H
#define TIMER_H

#include "stdafx.h"

namespace MX
{
  class Timer
  {
  public:
    Timer();
    ~Timer() = default;

    Timer(const Timer&) = default;
    Timer &operator=(const Timer&) = default;

    void start();
    void stop();
    void pause();
    void unpause();

    Uint32 get_ticks();

    bool is_started();
    bool is_paused();

  private:
    Uint32 m_start_ticks;
    Uint32 m_paused_ticks;

    bool m_paused;
    bool m_started;
  };
}

#endif // TIMER_H