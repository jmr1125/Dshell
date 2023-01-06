#pragma once
#include"incfile.cpp"
#include"pos.h"

class wOut{
 public:
  wOut();
  ~wOut();
 private:
  pos cur;
  bool tgpos=false;
};
wOut& operator << (wOut&,const long long&);
wOut& operator << (wOut&,char);
wOut& operator << (wOut&,const char*);
wOut& operator << (wOut&,const pos&);
