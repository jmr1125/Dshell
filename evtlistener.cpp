#include"evtlistener.h"

void evtlistener::listen(){
  res.ch=wgetch(win);
}

evtlistener::evtlistener(WINDOW *win){
  this->win=win;
  mousemask(ALL_MOUSE_EVENTS|REPORT_MOUSE_POSITION,NULL);
}
evtlistener::~evtlistener(){
}