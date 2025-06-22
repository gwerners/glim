#pragma once
#ifdef USING_QT
#include <QObject>
#endif

class Task
#ifdef USING_QT
    : public QObject
#endif
{
#ifdef USING_QT
  Q_OBJECT
#endif
 public:
  Task(
#ifdef USING_QT
      QObject* parent = 0
#endif
  );
  void setArgs(int argc, char** argv);
#ifdef USING_QT
 public slots:
#endif
  int run();
#ifdef USING_QT
 signals:
  void finished();
#endif
 private:
  int _argc;
  char** _argv;
};
