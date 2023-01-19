#pragma once
#include"incfile.cpp"
#include"dshell.h"				
// #define sig_null (0)
// #define sig_next (1)
// #define sig_stop (2)
class evtlistener{
public:
  evtlistener()=delete;
  evtlistener(WINDOW*);
  ~evtlistener();
  struct res_t{
    MEVENT evt;
    int ch;
  }res;
  atomic<int> sig;
  void listen();
private:
  mmask_t mouse;
  WINDOW *win;
  // thread *th;
};
