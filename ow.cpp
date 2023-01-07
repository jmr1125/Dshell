#include"ow.h"
wOut::wOut(WINDOW *win){
  this->win=win;
}
wOut& wOut::operator << (const long long& rsh){
  wprintw(win,"%lld",rsh);
  wrefresh(win);
  return *this;
}
wOut& wOut::operator << (char rsh){
  waddch(win,rsh);
  wrefresh(win);
  return *this;
}
wOut& wOut::operator << (const char* rsh){
  waddstr(win,rsh);
  wrefresh(win);
  //printf("str");
  //printf("%s",rsh);
  return *this;
}
wOut& wOut::operator << (const curpos &rsh){
  //printf("move");
  wmove(win,rsh.y,rsh.x);
  wrefresh(win);
  return *this;
}
