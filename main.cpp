#include <QCoreApplication>

#include "threading.h"
#include "workers.h"


int main(int argc, char* argv[])
{
  using namespace impl;
  using namespace worker;

  QCoreApplication a(argc, argv);

  ThreadedWorker<Worker1> thw1(&Worker1::someSlot);
  ThreadedWorker<Worker2> thw2(&Worker2::anotherSlot);

  thw1.start();
  thw2.start();

  return a.exec();
}
