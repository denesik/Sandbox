// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#include "Timer.h"
#include <GLFW\glfw3.h>



Timer::Timer()
{
  Start();
}


Timer::~Timer()
{
}

void Timer::Start()
{
  mTime = glfwGetTime();
}

unsigned int Timer::Elapsed() const
{
  return static_cast<unsigned int>((glfwGetTime() - mTime) * 1000);
}
