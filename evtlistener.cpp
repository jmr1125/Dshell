#include"evtlistener.h"

void evtlistener::listen(){
  while(true){
    while(sig==sig_null);
    if(sig==sig_stop)break;
    res.ch=wgetch(win);
    if(res.ch==KEY_MOUSE){
      wprintw(win,"receive mouse");
      if(getmouse(&res.evt)==OK){
	//continue;
      }else{
	wprintw(win,"mouse error !!!");
      }
    }
    sig=sig_null;
  }
}

evtlistener::evtlistener(WINDOW *win){
  this->win=win;
  sig=sig_null;//sig_next?
  mousemask(ALL_MOUSE_EVENTS|REPORT_MOUSE_POSITION,NULL);
  th=new thread ([this](){listen();});
}
evtlistener::~evtlistener(){
  sig=sig_stop;
  th->join();
}
