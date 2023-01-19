#include"inputbox.h"
inputbox::inputbox(int h,int w,int x,int y)
  :form(h,w,x,y),bos(0),curs(0){}
string inputbox::get_value(){
  return value;
}
void inputbox::set_value(string value){
  this->value=value;
}
void inputbox::show(){
  //wclear(win);
  wborder(win,border[3],border[4],border[1],border[6],border[0],border[2],border[5],border[7]);
  //werase(win);
  //waddstr(win, value.substr(bos,std::min(int(getmaxx(win)-2)*(getmaxy(win)-2),(int)value.size()-bos)).c_str());
  wmove(win,1,1);
  waddstr(win, value.substr(bos,std::min(int(getmaxx(win)-2)*(getmaxy(win)-2),(int)value.size()-bos)).c_str());
  //mvwaddstr(win,getbegy(win)+1,getbegx(win)+1,"hello");
  //waddstr(win,"hello");
  wrefresh(win);
}
string inputbox::process(const evtlistener::res_t*evt){
  if(evt->ch==KEY_MOUSE){
    if(OnMouse(evt->evt.x,evt->evt.y)){
      if(evt->evt.bstate&BUTTON1_PRESSED){
	auto [mx,my]=this->Mousexy(evt->evt.x, evt->evt.y); //clang will warn decomposition declarations except let CMAKE_CXX_STANDARD:string=17
	curs=std::max(decltype(curs)(my-1)*(getmaxx(win)-2)+mx,decltype(curs)(0));
	bos=std::max(curs-3,decltype(curs) (0));
	return "clicked";
      }else{
	return "move";
      }
    }else if(evt->ch==KEY_HOME){
      curs=bos=0;
    }else if(evt->ch==KEY_END){
      curs=bos=value.size()-1;
    }else {
      value.insert(value.begin(), evt->ch);
    }
  }
  return "";
}
