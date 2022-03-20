#ifndef _TIMER_H_SUB
#define _TIMER_H_SUB

#include <SDL2/SDL.h>

class Timer {
  private:
    static Timer* static_instance;
    unsigned int start_ticks;
    unsigned int elapsed_ticks;
    float delta_time;
    float time_scale;
    
  public:
    static Timer* instance();
    static void release();

    void reset();
    float deltaTime();
    
    void timeScale(float t);
    float timeScale();
    
    void update();

  private:
    Timer();
    ~Timer();
};

#endif
