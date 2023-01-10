#include"iw.h"
wIn::wIn(WINDOW *win){
  this->win=win;
}
wIn::~wIn(){}
const wIn& wIn::operator << (long long& x)const{
  callecho();
  wscanw(win,"%lld",&x);
  return *this;
}
const wIn& wIn::operator << (string& x)const{
  callecho();
  char str[256];
  //wscanw(win,"%s",str);
  wgetnstr(win,str,256);
  x=str;
  
  return *this;
}
const wIn& wIn::operator << (char& x)const{
  callecho();
  x=wgetch(win);
  return *this;
}
string wIn::getline()const{
  callecho();
  string s;
  return s;
}
static bool oncecall=false;
void wIn::callecho()const{
  if(oncecall){
    return;
  }
  oncecall=true;
  if(isecho){
    echo();
  }else{
    noecho();
  }
}
void wIn::setecho(bool t){
  if(isecho==t){
    return;
  }else{
    oncecall=false;
    isecho=t;
  }
}
