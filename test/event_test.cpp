#include <iostream>
#include "thread_base.hpp"
#include "event.hpp"

class CThread : public varlib::thread_base {
public:
    int run() {
        std::cout << "[" << __FILE__ << ":" << __LINE__ << "][" << __PRETTY_FUNCTION__ << "]" << std::endl;
        ex.wait(-5000);
    }

private:
    varlib::event ex;
};

int main(int argc, char *argv[]) {
    CThread ct;
    ct.start();
    ct.join();
    return 0;
};
