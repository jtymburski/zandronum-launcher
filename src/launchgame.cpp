#include "launchgame.h"

LaunchGame::LaunchGame()
{
}

LaunchGame::~LaunchGame()
{
  stop();
}

/**
 * Set up standard arguments.
 */
QStringList LaunchGame::createStandardArguments(const LaunchConfig &launch_config)
{
  QStringList arguments;

  arguments.append("-iwad");
  arguments.append(launch_config.getDoomBinaryFilepath());

  if(launch_config.isModBinaryValid())
  {
    arguments.append("-file");
    arguments.append(launch_config.getModBinaryFilepath());
  }

  if(launch_config.isModConfigValid())
  {
    arguments.append("-config");
    arguments.append(launch_config.getModConfigFilepath());
  }

  return arguments;
}

/**
 * Check if the config is valid and can be used.
 */
bool LaunchGame::isValidConfig(const LaunchConfig &launch_config)
{
  if(!launch_config.isZandronumBinaryValid())
  {
    qWarning("Zandronum filepath is not valid");
    return false;
  }
  else if(!launch_config.isDoomBinaryValid())
  {
    qWarning("Doom WAD filepath is not valid");
    return false;
  }
  return true;
}

/**
 * Start the process.
 */
bool LaunchGame::startProcess(const LaunchConfig &launch_config, const QStringList &arguments,
                              bool detached)
{
  if(detached)
  {
    return QProcess::startDetached(launch_config.getZandronumBinaryFilepath(), arguments);
  }
  else if(stop())
  {
    process = new QProcess();
    process->start(launch_config.getZandronumBinaryFilepath(), arguments);
    return true;
  }
  return false;
}

/**
 * Execute and start the game.
 */
bool LaunchGame::start(const LaunchConfig &launch_config, bool detached)
{
  if(!isValidConfig(launch_config))
    return false;

  QStringList arguments = createStandardArguments(launch_config);

  return startProcess(launch_config, arguments, detached);
}

/**
 * Execute and start a multiplayer client.
 */
bool LaunchGame::startClient(const LaunchConfig &launch_config, bool detached)
{
  if(!isValidConfig(launch_config))
    return false;
  else if(!launch_config.isServerAddressSet())
  {
    qWarning("Server address is not set but required for client connection");
    return false;
  }

  QStringList arguments = createStandardArguments(launch_config);

  arguments.append("-connect");
  arguments.append(launch_config.getServerAddress());

  return startProcess(launch_config, arguments, detached);
}

/**
 * Execute and start a multiplayer server.
 */
bool LaunchGame::startServer(const LaunchConfig &launch_config, bool detached)
{
  if(!isValidConfig(launch_config))
    return false;
  else if(!launch_config.isServerConnectionLimitSet())
  {
    qWarning("Server connection limit is not set");
    return false;
  }

  QStringList arguments = createStandardArguments(launch_config);

  arguments.append("-host");
  arguments.append(QString::number(launch_config.getServerConnectionLimit()));

  return startProcess(launch_config, arguments, detached);
}

/**
 * Stop any embedded process.
 */
bool LaunchGame::stop()
{
  if(process != nullptr)
  {
    process->kill();
    delete process;
    process = nullptr;
  }
  return true;
}
