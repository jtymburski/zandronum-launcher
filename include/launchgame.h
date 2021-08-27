#ifndef LAUNCHGAME_H
#define LAUNCHGAME_H

#include <QProcess>

#include "config/launchconfig.h"

class LaunchGame
{
public:
  LaunchGame();
  ~LaunchGame();

private:
  /* Internal process, for last launched client, if it wasn't detached */
  QProcess *process = nullptr;

private:
  /* Convert the list of arguments into a process compatible string list */
  QStringList argumentsToStringList(const QList<Argument> &arguments) const;

  /* Start the process */
  void startProcess(const LaunchConfig &launch_config, const QList<Argument> &arguments,
                    bool detached);

public:
  /* Checks if the process exists, has been created and is being managed by this launcher */
  bool isProcessCreated();

  /* Execute and start the game, in normal start-up mode */
  void start(const LaunchConfig &launch_config, bool detached = false);

  /* Execute and start a multiplayer client */
  void startClient(const LaunchConfig &launch_config, bool detached = false);

  /* Execute and start a multiplayer server */
  void startServer(const LaunchConfig &launch_config, bool detached = false);

  /* Stop any embedded process */
  bool stop();
};

#endif // LAUNCHGAME_H
