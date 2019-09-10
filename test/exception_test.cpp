

#include "exception.hpp"
#include <iostream>

void f1() { throw varlib::exception(); }

void f2() { throw varlib::exception("lala"); }

void f3() { throw varlib::exception(__FILE__, __LINE__); }

void f4() { throw varlib::exception(__FILE__, __LINE__, __PRETTY_FUNCTION__); }

void f5() {
  throw varlib::exception(__FILE__, __LINE__, __PRETTY_FUNCTION__, "hehe");
}

int main(int argc, char *argv[]) {
  try {
    f1();
  } catch (varlib::exception ex) {
    std::cout << ex.what() << std::endl;
  }

  try {
    f2();
  } catch (varlib::exception ex) {
    std::cout << ex.what() << std::endl;
  }

  try {
    f3();
  } catch (varlib::exception ex) {
    std::cout << ex.what() << std::endl;
  }

  try {
    f4();
  } catch (varlib::exception ex) {
    std::cout << ex.what() << std::endl;
  }

  try {
    f5();
  } catch (varlib::exception &ex) {
    std::cout << ex.what() << std::endl;
  }

  try {
    f5();
  } catch (std::exception &ex) {
    std::cout << ex.what() << std::endl;
  }
}
