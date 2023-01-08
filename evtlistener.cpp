#include"evtlistener.h"

void evtlistener::listen(){
  while(!stop){
    if(stop)continue;
    res.ch=wgetch(win);
    if(res.ch==KEY_MOUSE){
      if(getmouse(&res.evt)==OK){
      }
    }
  }
}

evtlistener::evtlistener(WINDOW *win){
  this->win=win;
  mousemask(ALL_MOUSE_EVENTS,NULL);
  th=new thread([this](){listen();});
}
evtlistener::~evtlistener(){
  stop=true;
  th->join();
}
