#include"inputbox.h"
inputbox::inputbox(int h,int w,int x,int y)
  :form(h,w,x,y),bos(0),curs(0){}
string inputbox::get_value(){
  return value;
}
void inputbox::set_value(string value){
  this->value=value;
}
inline string substring(size_t a,size_t b,string s){//a -> b include a and b
  using std::max;
  using std::min;
  a=max(a,decltype(a)(0)),a=min(a,s.size());
  b=max(a,b),b=min(b,s.size());
  return s.substr(a, b-a);
}
void inputbox::show(){
  wclear(win);
  wborder(win,border[3],border[4],border[1],border[6],border[0],border[2],border[5],border[7]);
  wmove(win,1,1);
  //waddstr(win, value.substr(bos,std::min(int(getmaxx(win)-2)*(getmaxy(win)-2),(int)value.size()-bos)).c_str());
  waddstr(win,substring(bos,bos+(getmaxx(win)-2)*(getmaxy(win)-2),value).c_str());
  wrefresh(win);
}
string inputbox::process(const evtlistener::res_t*evt){
  if(evt->ch==KEY_MOUSE){
    if(OnMouse(evt->evt.x,evt->evt.y)){
      if(evt->evt.bstate&BUTTON1_PRESSED){
	auto [mx,my]=this->Mousexy(evt->evt.x, evt->evt.y);
	my=std::max(1,my);
	my=std::min(getmaxy(win)-2,my);
	auto nowpos=mx-1+(my-1)*(getmaxx(win)-2);
	//curs=nowpos+bos;
	curs=nowpos;
	bos+=nowpos-(getmaxx(win)-2)*(getmaxy(win)-2)/2;
	using std::min;
	using std::max;
	curs=max(0,curs);
	bos=max(0,bos);
	bos=min(decltype(bos)(value.size())-1,bos);
	return "clicked";
      }else{
	return "move";
      }
    }else if(evt->ch==KEY_HOME){
      curs=bos=0;
      return "toBeg";
    }else if(evt->ch==KEY_END){
      curs=bos=value.size()-1;
      return "toEnd";
    }else {
      if(isalnum(evt->ch)){
	value.insert(value.begin()+curs, evt->ch);
	return "inserted";
      }
    }
  }
  return "";
}
