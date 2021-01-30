#include "launchgame.h"

LaunchGame::LaunchGame()
{
}

LaunchGame::~LaunchGame()
{
}

/* Execute and start the game */
bool LaunchGame::start(const LaunchConfig &launchConfig)
{
  // Check required files that they are configured
  if(!launchConfig.isZandronumBinaryValid())
  {
    qWarning("Zandronum filepath is not valid");
    return false;
  }
  else if(!launchConfig.isDoomBinaryValid())
  {
    qWarning("Doom WAD filepath is not valid");
    return false;
  }

  // Proceed with setting up the process
  QStringList arguments;

  arguments.append("-iwad");
  arguments.append(launchConfig.getDoomBinaryFilepath());

  if(launchConfig.isModBinaryValid())
  {
    arguments.append("-file");
    arguments.append(launchConfig.getModBinaryFilepath());
  }

  if(launchConfig.isModConfigValid())
  {
    arguments.append("-config");
    arguments.append(launchConfig.getModConfigFilepath());
  }

  QProcess::startDetached(launchConfig.getZandronumBinaryFilepath(), arguments);
  return true;
}
