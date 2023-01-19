#include"button.h"

button::button(int h,int w,int x,int y):form(h,w,x,y){};
void button::set_lable(const char*str){
  wclear(win);
  mvwprintw(win, (getbegy(win)+getmaxy(win))/2, (getbegx(win)+getmaxx(win))/2, "%s", str);
  show();
}
string button::process(const evtlistener::res_t* res){
  if(OnMouse(res->evt.x,res->evt.y)){
    if(res->evt.bstate&BUTTON1_PRESSED){
      return "clicked";
    }
  }else{
    return "";
  }
  return "";
}
