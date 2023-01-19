#pragma once
#include"incfile.cpp"
#include"evtlistener.h"

class form{
 public:
  form()=delete;
  form(int,int,int,int);
  ~form();
  virtual void show();
  bool OnMouse(int,int);
  pair<int,int> Mousexy(int,int);
  virtual string process(const evtlistener::res_t*);
  WINDOW* getwin();
  chtype border[8];
    /* 122222223
       4       5
       4       5
       677777778
    */
 protected:
  WINDOW *win;
};
