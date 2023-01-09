#include"incfile.cpp"
class style{
 public:
  style() = delete;
  style(WINDOW *win,int t=A_NORMAL);
  void on()const;
  void off()const;
 private:
  int t;
  WINDOW *win;
};
