#include "launchgame.h"

LaunchGame::LaunchGame()
{
}

LaunchGame::~LaunchGame()
{
  stop();
}

/**
 * Convert the list of arguments into a process compatible string list. For example, add "-"
 * to the prefix of each argument.
 */
QStringList LaunchGame::argumentsToStringList(const QList<Argument> &arguments) const {
  QStringList argumentStringList;

  for(Argument arg : arguments)
  {
    argumentStringList.append("-" + arg.getKey());
    argumentStringList.append(arg.getValue());
  }

  return argumentStringList;
}

/**
 * Start the process.
 */
void LaunchGame::startProcess(const LaunchConfig &launch_config, const QList<Argument> &arguments,
                              bool detached)
{
  QStringList argumentStringList = argumentsToStringList(arguments);
  if(detached)
  {
    if(!QProcess::startDetached(launch_config.getZandronumBinaryFilepath(), argumentStringList))
      throw std::runtime_error("Game process failed to detach and start");
  }
  else if(stop())
  {
    process = new QProcess();
    process->start(launch_config.getZandronumBinaryFilepath(), argumentStringList);
  }
}

/* ---- PUBLIC FUNCTIONS ---- */

/**
 * Checks if the process exists, has been created and is being managed by this launcher.
 */
bool LaunchGame::isProcessCreated()
{
  // TODO: Replace with better current state definition
  return process != nullptr;
}

/**
 * Execute and start the game.
 * @throws std::invalid_parameter if the launch config is misconfigured
 */
void LaunchGame::start(const LaunchConfig &launch_config, bool detached)
{
  startProcess(launch_config, launch_config.getOfflineArguments(), detached);
}

/**
 * Execute and start a multiplayer client.
 * @throws std::invalid_parameter if the launch config is misconfigured
 */
void LaunchGame::startClient(const LaunchConfig &launch_config, bool detached)
{
  startProcess(launch_config, launch_config.getClientArguments(), detached);
}

/**
 * Execute and start a multiplayer server.
 * @throws std::invalid_parameter if the launch config is misconfigured
 */
void LaunchGame::startServer(const LaunchConfig &launch_config, bool detached)
{
  startProcess(launch_config, launch_config.getServerArguments(), detached);
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
