#include "Timer.h"

Timer* Timer::static_instance = NULL;
Timer* Timer::instance() {
  if(static_instance == NULL)
    static_instance = new Timer();
  
  return static_instance;
}

void Timer::release() {
  delete static_instance;
  static_instance = NULL;
}

Timer::Timer() {
  reset();
  time_scale = 1.0f;
}

Timer::~Timer() {
  
}

void Timer::reset() {
  start_ticks = SDL_GetTicks();
  elapsed_ticks = 0;
  delta_time = 0.0f;
}

float Timer::deltaTime() {
  return delta_time;
}

void Timer::timeScale(float t) {
  time_scale = t;
}

float Timer::timeScale() {
  return time_scale;
}

void Timer::update() {
  elapsed_ticks = SDL_GetTicks() - start_ticks;

  /* Convert to seconds */
  delta_time = elapsed_ticks * 0.001f;
}
