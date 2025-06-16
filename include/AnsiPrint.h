
#ifndef _ANSIPRINT_H
#define _ANSIPRINT_H

#include <string>
#include "unit.h"

std::string AnsiPrint(const char* str,
                      Color fg = NOCHANGE,
                      Color bg = NOCHANGE,
                      bool hi = false,
                      bool blinking = false);

std::string AnsiPrint(const char* str,
                      bool hi = false,
                      bool blinking = false);

#endif  // _ANSIPRINT_H
