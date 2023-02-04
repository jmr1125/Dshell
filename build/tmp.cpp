// future example
#include <iostream>       // std::cout
#include <sys/unistd.h>
#include <atomic>
#include <future>
int f(){
    sleep(1);
    return 10;
}
int main ()
{
    auto fut=std::async(f);
    std::cout<<fut.get();
  return 0;
}
