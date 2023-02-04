#include "incfile.cpp"
#include "shell_runner.h"
int main() {
  int input[2], output[2];
  promise<pid_t> pid;
  auto pidd=pid.get_future();
  future<int> fut =
    std::async(start, "bash", input, output, move(pid));
  
  sleep(2);
  printf("pid: %d\n",pidd.get());
  sleep(2);
  fut.wait();
  // int stat=fut.get();
  // printf("status: %d\n",stat);
}
