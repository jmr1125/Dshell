#include"style.h"
style::style(WINDOW *win,int t){
  this->t=t;
  this->win=win;
  t&=A_ATTRIBUTES;
}
void style::on()const{
  wattron(win,t);
}
void style::off()const{
  wattroff(win,t);
}
