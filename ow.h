#pragma once
#include"incfile.cpp"
#include"pos.h"

class wOut{
 public:
  wOut() = delete;
  wOut(WINDOW*);
  ~wOut() = default;
  wOut& operator << (const long long&);
  wOut& operator << (char);
  wOut& operator << (const char*);
  wOut& operator << (const curpos&);
private:
  WINDOW *win;
};
