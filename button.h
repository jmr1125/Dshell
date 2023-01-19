#include "form.h"
class button : public form {
 public:
  button()=delete;
  button(int,int,int,int);
  void set_lable(const char*);
  virtual string process(const evtlistener::res_t*);
};
