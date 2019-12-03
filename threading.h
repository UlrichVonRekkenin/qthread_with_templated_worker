#ifndef THREADING_H
#define THREADING_H

#include <type_traits>
#include <QThread>


namespace impl {

  /*!
  \brief A templated wrapper for an incapsulating of `Worker` class.
  \details Because an instantaion of `Worker` class fields in the heap should happend in
    another thread to have appropriated affinity use template parameter `OnThreadStartSlot`
    on constructor of `ThreadedWorker` which is connected with `QThread::started` signal.
    So, `Workers`'s constructor should take only variadic pack `Args...` of configuration parameters.

    Usage:
  \code
      ThreadedWorker<Worker1> thw1(&Worker1::someSlot);
      ThreadedWorker<Worker2> thw2(&Worker2::anotherSlot, foo, bar, zab, baz);

      thw1.start();
      thw2.start();
  \endcode
  */
  template <typename Worker>
  struct ThreadedWorker final {
      Worker* worker = nullptr;

      ThreadedWorker(const ThreadedWorker &) = delete;
      ThreadedWorker(const ThreadedWorker &&) = delete;
      ThreadedWorker &operator=(const ThreadedWorker &) = delete;
      ThreadedWorker &operator=(const ThreadedWorker &&) = delete;

      template<typename OnThreadStartSlot, typename ...Args>
      explicit ThreadedWorker(OnThreadStartSlot slot, Args...args) :
        worker(new Worker(std::forward<Args>(args)...))
      {
        static_assert(std::is_base_of<QObject, Worker>::value, "Template parameter `Worker` must be derived from QOject.");
        QObject::connect(&thread, &QThread::started, worker, slot);
        QObject::connect(&thread, &QThread::finished, worker, &QObject::deleteLater);
        worker->moveToThread(&thread);
      }

      ~ThreadedWorker()
      {
        thread.quit();
        thread.wait();
      }

      void start(QThread::Priority priority = QThread::HighPriority)
      {
        thread.start(priority);
      }

    private:
      QThread thread;
  };

}

#endif // THREADING_H
