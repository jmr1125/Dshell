#include "incfile.cpp"
#include "evtlistener.h"
#include "form.h"

class inputbox : public form {
 public:
  inputbox() = delete;
  inputbox(int,int,int,int);
  string get_value();
  void set_value(string);
  virtual void show()override;
  virtual string process(const evtlistener::res_t*)override;
  bool editable;
  int bos;//begin of string to show
  int curs;
 private:
  string value;
};
