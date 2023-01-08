#include"incfile.cpp"
class evtlistener{
public:
  evtlistener()=delete;
  evtlistener(WINDOW*);
  ~evtlistener();
  struct res_t{
    MEVENT evt;
    int ch;
  }res;
private:
  mmask_t mouse;
  WINDOW *win;
  atomic<bool> stop;
  thread *th;
  void listen();
};
