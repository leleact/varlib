#include <mutex/Mutex.hpp>
#include <thread/Thread.hpp>
#include <unistd.h>
typedef struct {
  long element;
  varlib::Mutex lock;
} Data;

class MyThread1 : public varlib::Thread {
public:
  MyThread1(Data *ptData) : m_pt_data(ptData){};
  long run() override {
    while (1) {
      usleep(5000);
      m_pt_data->lock.lock();
      m_pt_data->element--;
      if (m_pt_data->element <= 0) {
        m_pt_data->lock.unlock();
        break;
      }
      std::cout << "Thread: [" << GetThreadId() << "] element: ["
                << m_pt_data->element << "]" << std::endl;
      m_pt_data->lock.unlock();
    }
    return 0;
  }

private:
  Data *m_pt_data;
};

class MyThread2 : public varlib::Thread {
public:
  long run() override {
    while (1) {
      usleep(5000);
      std::cout << "Thread: [" << GetThreadId() << "], " << m_loopcout++
                << std::endl;
    }
    return 0;
  }

private:
  unsigned long m_loopcout;
};
int main() {
  Data data;
  data.element = 100;
  MyThread1 thread1(&data);
  thread1.start();
  thread1.start();
  thread1.wait_stop();
  return 0;
}
