#ifndef LAUNCHGAME_H
#define LAUNCHGAME_H

#include <QProcess>

#include "config/launchconfig.h"

class LaunchGame
{
public:
  LaunchGame();
  ~LaunchGame();

public:
  /* Execute and start the game */
  bool start(const LaunchConfig &launchConfig);
};

#endif // LAUNCHGAME_H
