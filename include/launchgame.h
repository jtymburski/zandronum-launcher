#ifndef LAUNCHGAME_H
#define LAUNCHGAME_H

#include <QCoreApplication>
#include <QFile>
#include <QProcess>
#include <QTimer>

class LaunchGame
{
public:
  LaunchGame();
  ~LaunchGame();

private:
  /* Resource base directory, relative to the binary */
  const static QString kRESOURCE_DIRECTORY;

private:
  /* Returns the base executable directory */
  QString baseExecutableDir();

public:
  /* Execute and start the game */
  void start();
};

#endif // LAUNCHGAME_H
