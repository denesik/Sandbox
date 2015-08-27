// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#include "RenderErrorChecker.h"


#include <stdio.h>

void RenderCheckErrors()
{
  while(unsigned int openGLError = glGetError())
  {
    printf("ogl error: %i\n", openGLError);
  };
}

