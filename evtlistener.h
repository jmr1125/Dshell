#include"incfile.cpp"
#include"dshell.h"
class evtlistener{
public:
  evtlistener()=delete;
  evtlistener(WINDOW*);
  ~evtlistener();
  void listen();
  struct res_t{
    MEVENT evt;
    int ch;
  }res;
private:
  mmask_t mouse;
  WINDOW *win;
  thread *th;
  atomic<bool> stop;
};
