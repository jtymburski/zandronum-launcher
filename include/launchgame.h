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
  /* Set up standard arguments */
  QStringList createStandardArguments(const LaunchConfig &launch_config);

  /* Check if the config is valid and can be used */
  bool isValidConfig(const LaunchConfig &launch_config);

  /* Start the process */
  bool startProcess(const LaunchConfig &launch_config, const QStringList &arguments, bool detached);

public:
  /* Checks if the process exists, has been created and is being managed by this launcher */
  bool isProcessCreated();

  /* Execute and start the game, in normal start-up mode */
  bool start(const LaunchConfig &launch_config, bool detached = false);

  /* Execute and start a multiplayer client */
  bool startClient(const LaunchConfig &launch_config, bool detached = false);

  /* Execute and start a multiplayer server */
  bool startServer(const LaunchConfig &launch_config, bool detached = false);

  /* Stop any embedded process */
  bool stop();
};

#endif // LAUNCHGAME_H
