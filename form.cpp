#include"form.h"
form::form(int h,int w,int x,int y){
  win=newwin(h,w,y,x);//bef xy
  //box(win,x,y);
  //wborder(win,'|','|','-','-','+','+','+','+');
  //memcpy(border,"+-+||+-+a",8);
  border[0]='+',border[1]='-',border[2]='+',border[3]='|',border[4]='|',border[5]='+',border[6]='-',border[7]='+';
  show();
}
form::~form(){
  wborder(win,' ',' ',' ',' ',' ',' ',' ',' ');
  wrefresh(win);
  delwin(win);
}
void form::show(){
  wborder(win,border[3],border[4],border[1],border[6],border[0],border[2],border[5],border[7]);
  wrefresh(win);
}
bool form::OnMouse(int x,int y){
  return wenclose(win,y,x);
}
WINDOW* form::getwin(){
  return win;
}
string form::process(const evtlistener::res_t*){return "";};
pair<int,int> form::Mousexy(int x,int y){
  // int t_x;
  // int t_y;
  // wmouse_trafo(win, &t_y, &t_x, true);
  // return make_pair(t_x, t_y);
  // // if(wmouse_trafo(win, &t_y, &t_x, false)){
  // //   return make_pair(t_x,t_y);
  // // }else{
  // //   return make_pair(-1,-1);
  // // }
  if(OnMouse(x, y)){
    return make_pair(x-getbegx(win), y-getbegy(win));
  }else{
    return make_pair(-1, -1);
  }
}
