#include "Core.hpp"


// test comment
int main(int argc, char* argv[]) {
  Core core;

  if (!core.init()) {
    return -1;
  }

  core.mainloop();

  return 0;
}
