#include"ow.h"
wOut::wOut(WINDOW *win):
  now(win)
{
  now.on();
  this->win=win;
}
void wOut::Clear(){
  wclear(win);
}
void wOut::Clrtobot(){
  wclrtobot(win);
}
void wOut::Clrtoeol(){
  wclrtoeol(win);
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
  return *this;
}
wOut& wOut::operator << (const curpos &rsh){
  wmove(win,rsh.y,rsh.x);
  wrefresh(win);
  return *this;
}
wOut& wOut::operator << (const style & rsh){
  now.off();
  rsh.on();
  now=rsh;
  return *this;
}
