#pragma once
#include"incfile.cpp"
#include"evtlistener.h"
class wIn{
public:
  wIn(WINDOW *);
  ~wIn();
  const wIn& operator >> (long long&)const;
  const wIn& operator >> (string&)const;
  const wIn& operator >> (char&)const;
  string getline()const;
  void setecho(bool);
private:
  void callecho()const;
  bool isecho=false;
  WINDOW *win;
};
