// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#pragma once
#ifndef Timer_h__
#define Timer_h__


class Timer
{
public:
  Timer();
  ~Timer();

  void Start();

  /// Прошло времени в мс.
  unsigned int Elapsed() const;

private:

  double mTime;

};



#endif // Timer_h__
