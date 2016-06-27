#include <pthread.h>
#include <iostream>
#include <cstdlib>
#include <unistd.h>

// TODO: MyThread implementáció

class MyThread
{
public:
  MyThread() {}
  virtual ~MyThread() { join(); }
  
  void start();
  void join();
  
protected:
  virtual void on_run() = 0;
  
private:
  static void* thread_entry(void* pobj);
  
protected:
  pthread_t _th;
};

void MyThread::start()
{
  // TODO
}

void* MyThread::thread_entry(void* pobj)
{
  // TODO
  return NULL;
}

void MyThread::join()
{
  // TODO
}

///////////////////////////////////

class TestThread : public MyThread
{
protected:
  virtual void on_run();
};

void TestThread::on_run()
{
  for(int i = 0; i < 20; i++)
  {
    std::cout << i << std::endl;
    sleep(1);
  }
}

//////////////////////////////////

int main()
{
  TestThread a;
  TestThread b;
  a.start();
  b.start();
  a.join();
  b.join();
  
  return 0;
}
