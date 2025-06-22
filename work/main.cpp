#ifdef USING_QT
#include <QCoreApplication>
#include <QtCore>
#endif
#include <cstdio>
#include "Task.h"

int main(int argc, char** argv) {
  setbuf(stdout, nullptr);
#ifdef USING_QT
  QCoreApplication a(argc, argv);
  Task* task = new Task(&a);
  task->setArgs(argc, argv);
#else
  Task task;
  task.setArgs(argc, argv);
  return task.run();
#endif
#ifdef USING_QT
  QObject::connect(task, SIGNAL(finished()), &a, SLOT(quit()));
  QTimer::singleShot(0, task, SLOT(run()));
  return a.exec();
#endif
}
