#include "Task.h"
#include <sys/wait.h>
#include "Core.h"

Task::Task(
#ifdef USING_QT
    QObject* parent
#endif
    )
#ifdef USING_QT
    : QObject(parent)
#endif
{
}
void Task::setArgs(int argc, char** argv) {
  _argc = argc;
  _argv = argv;
}

static void func(int) {
  wait(NULL);
}

int Task::run() {
  signal(SIGCHLD, func);
  Core core;
  core.run(_argc, _argv);
#ifdef USING_QT
  emit finished();
#endif
  return 0;
}
