#pragma once
#include"incfile.cpp"
#include"pos.h"
#include"style.h"

class wOut{
 public:
  wOut() = delete;
  wOut(WINDOW*);
  ~wOut() = default;
  wOut& operator << (const long long&);
  wOut& operator << (char);
  wOut& operator << (const char*);
  wOut& operator << (const curpos&);
  wOut& operator << (const style&);
private:
  WINDOW *win;
  style now;
};
