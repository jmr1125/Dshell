#include"ow.h"
#define printmac(form)				\
  if(tgpos){					\
    mvprintw(y,x,form,rsh);			\
    tgpos=false;				\
  }else{					\
    printw(form,rsh);				\
  }						\
  refresh();					\
wOut& operator << (wOut&,const long long& rsh){
  printmac("%lld");
}
wOut& operator << (wOut&,char rsh){
  printmac("%c");
}
wOut& operator << (wOut&,const char* rsh){
  printmac("%s");
}
wOut& operator << (wOut&,const rsh&){
  cur=rsh;
  tgpos=true;
}