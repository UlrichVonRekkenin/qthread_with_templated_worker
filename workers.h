#ifndef WORKERS_H
#define WORKERS_H

#include <QObject>
#include <QDebug>


namespace worker {

  class Worker1 : public QObject {
      Q_OBJECT
    public:
      Worker1() = default;
      ~Worker1() = default;

    public slots:
      void someSlot()
      {
        qInfo() << Q_FUNC_INFO;
      }
  };

  class Worker2 : public QObject {
      Q_OBJECT
    public:
      Worker2() = default;
      ~Worker2() = default;

    public slots:
      void anotherSlot()
      {
        qInfo() << Q_FUNC_INFO;
      }
  };

}

#endif // WORKERS_H
