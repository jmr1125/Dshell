#include"evtlistener.h"

void evtlistener::listen(){
  while(!stop){
    res.ch=wgetch(win);
    if(exit_cond(res.ch)){
      return;
    }
    if(res.ch==KEY_MOUSE){
      if(getmouse(&res.evt)==OK){
      }else{
	wprintw(win,"mouse error !!!");
      }
    }
  }
}

evtlistener::evtlistener(WINDOW *win){
  this->win=win;
  mousemask(ALL_MOUSE_EVENTS|REPORT_MOUSE_POSITION,NULL);
  th=new thread ([this](){listen();});
}
evtlistener::~evtlistener(){
  stop=true;
  th->join();
}
