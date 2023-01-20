#include"incfile.cpp"
#include"iow.h"
#include"evtlistener.h"
#include"shell_runner.h"
#include"form.h"
#include"button.h"
#include"inputbox.h"
regex command(R"(^((?:".+")|(?:[^"][^ ]+[^"])|(?:[\w^ ]+))(.*)$)");
string tohex(long long x){
  char s[64];
  sprintf(s,"%.8llx",x);
  return s;
}
void dshell(){
  form main_f(getmaxy(stdscr),getmaxx(stdscr),0,0);
  wbkgd(main_f.getwin(), COLOR_PAIR(1));
  main_f.show();
  keypad(main_f.getwin(),TRUE);
  wOut ost(main_f.getwin());
  wIn ist(main_f.getwin());
  evtlistener el(main_f.getwin());
  printf("\033[?1003h\n"); // Makes the terminal report mouse movement events
  mouseinterval(10);
  form subform(3,10,3,10);
  button but1(2,15,12,15);
  inputbox inb1(3,15,29,13);
  wbkgd(subform.getwin(), COLOR_PAIR(1));
  wbkgd(but1.getwin(), COLOR_PAIR(1));
  wbkgd(inb1.getwin(), COLOR_PAIR(1));
  //inb1.set_value("hello");
  while(true){
    inb1.set_value("abcdefghijklmnopqrst");
    main_f.show();
    subform.show();
    but1.show();
    inb1.show();
    el.listen();
    ost<<curpos(3,3)<<"ch: "<<(long long)el.res.ch;
    if(el.res.ch==KEY_MOUSE){
      ost<<curpos(3,5)<<(long long)el.res.evt.x<<' '<<(long long)el.res.evt.y;
      ost<<curpos(3,6)<<tohex(el.res.evt.bstate).c_str()<<' '<<(long long)el.res.evt.id;
      ost<<curpos(3,7)<<(long long)subform.OnMouse(el.res.evt.x, el.res.evt.y);
      auto trans=subform.Mousexy(el.res.evt.x, el.res.evt.y);
      ost<<curpos(3,8)<<(long long)trans.first<<" "<<(long long)trans.second<<' ';
      ost<<curpos(3,9)<<(but1.process(&el.res)).c_str()<<"       ";

      ost<<curpos(15,3)<<(inb1.process(&el.res)).c_str()<<"         ";
      ost<<curpos(15,4)<<(long long)inb1.curs<<' '<<(long long)inb1.bos<<"      ";
      ost<<curpos(15,5)<<(long long)(getmaxx(inb1.getwin())-2)*(getmaxy(inb1.getwin())-2)<<"    ";
    }else if(el.res.ch=='l'){
      wclear(main_f.getwin());
    }else if(el.res.ch=='q'){
      break;
    }
  }
  printf("\033[?1003l\n");
}
