#include "event.hpp"
#include "thread_base.hpp"
#include <gtest/gtest.h>
#include <iostream>

class CThread : public varlib::thread_base {
public:
  int run() {
    std::cout << "[" << __FILE__ << ":" << __LINE__ << "]["
              << __PRETTY_FUNCTION__ << "]" << std::endl;
    ex.wait(-5000);
    return 0;
  }

private:
  varlib::event ex;
};

TEST(EVENT, USAGE) {

  CThread ct;
  ct.start();
  ct.join();
};
