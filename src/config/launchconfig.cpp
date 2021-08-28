#include "config/launchconfig.h"

/* Default file names, used by the default config */
const QString LaunchConfig::DEFAULT_DOOM_FILENAME = "doom2.wad";
const QString LaunchConfig::DEFAULT_INI_FILENAME = "mod.ini";
const QString LaunchConfig::DEFAULT_PK3_FILENAME = "mod.pk3";

/* Parameter names for the config */
const QString LaunchConfig::PARAM_CONFIG_INI = "-config";
const QString LaunchConfig::PARAM_CONNECTION_LIMIT = "-host";
const QString LaunchConfig::PARAM_BASE_WAD = "-iwad";
const QString LaunchConfig::PARAM_MOD_PK3 = "-file";
const QString LaunchConfig::PARAM_SERVER_ADDR = "-connect";

/* Destructor function */
LaunchConfig::~LaunchConfig()
{
}

/**
 * Returns the base mapping of arguments, common for all game types. It will only include
 * valid arguments, if they are optional.
 */
QMap<QString, Argument> LaunchConfig::getArgumentsMap() const
{
  QMap<QString, Argument> arguments;

  arguments.insert(PARAM_BASE_WAD, Argument(PARAM_BASE_WAD, getDoomBinaryFilepath()));
  if(isModBinaryValid())
    arguments.insert(PARAM_MOD_PK3, Argument(PARAM_MOD_PK3, getModBinaryFilepath()));
  if(isModConfigValid())
    arguments.insert(PARAM_CONFIG_INI, Argument(PARAM_CONFIG_INI, getModConfigFilepath()));

  return arguments;
}

/**
 * Returns the file reference to the doom WAD binary. This is required in order to start
 * a Zandronum instance.
 */
QString LaunchConfig::getDoomBinaryFilepath() const
{
  return getBaseExecutableDirectory() + DEFAULT_DOOM_FILENAME;
}

/**
 * Returns the file reference to the main mod PK3 binary. This is optional. If it is not
 * provided or valid, it will just request a stock doom game.
 */
QString LaunchConfig::getModBinaryFilepath() const
{
  return getBaseExecutableDirectory() + DEFAULT_PK3_FILENAME;
}

/**
 * Returns the file reference to the mod configuration ini file.
 */
QString LaunchConfig::getModConfigFilepath() const
{
  return getBaseExecutableDirectory() + DEFAULT_INI_FILENAME;
}

/**
 * Returns the server IPv4 address for connecting as a client.
 */
QString LaunchConfig::getServerAddress() const
{
  return server_address;
}

/**
 * Returns the server connection limits for clients when hosting.
 */
uint LaunchConfig::getServerConnectionLimit() const
{
  return server_connection_limit;
}

/**
 * Returns if the doom binary path is a valid file. This is testing the
 * {@link #getDoomBinaryFilepath()} return path.
 */
bool LaunchConfig::isDoomBinaryValid() const
{
  return FileReader::isValid(getDoomBinaryFilepath());
}

/**
 * Returns if the mod binary path is a valid file. This is testing the
 * {@link #getModBinaryFilepath()} return path.
 */
bool LaunchConfig::isModBinaryValid() const
{
  return FileReader::isValid(getModBinaryFilepath());
}

/**
 * Returns if the mod configuration path is a valid file. This is testing the
 * {@link #getModConfigFilepath()} return path.
 */
bool LaunchConfig::isModConfigValid() const
{
  return FileReader::isValid(getModConfigFilepath());
}

/**
 * Returns if the server IPv4 address for connecting as a client is set and valid.
 */
bool LaunchConfig::isServerAddressSet() const
{
  // TODO: Replace with IPv4 regex
  return !server_address.isEmpty();
}

/**
 * Returns if the server connection limit for clients is set to a valid number.
 */
bool LaunchConfig::isServerConnectionLimitSet() const
{
  return server_connection_limit > 0;
}

/**
 * Returns if the zandronum path is a valid file. This is testing the
 * {@link #getZandronumBinaryFilepath()} return path.
 */
bool LaunchConfig::isZandronumBinaryValid() const
{
  return FileReader::isValid(getZandronumBinaryFilepath());
}

/**
 * Validates the base arguments in the config, common for all game types, is set or will throw
 * an exception. This is testing the arguments in {@link #getArgumentsMap}.
 * @throws std::invalid_parameter if the base arguments are missing or misconfigured
 */
void LaunchConfig::validateArgumentsOrThrow() const
{
  if(!isZandronumBinaryValid())
    throw std::invalid_argument("Zandronum filepath is not valid");
  if(!isDoomBinaryValid())
    throw std::invalid_argument("Doom WAD filepath is not valid");
}

/**
 * Validates the client specific arguments in the config is set or will throw an exception.
 * @throws std::invalid_parameter if the client arguments are missing or misconfigured
 */
void LaunchConfig::validateClientArgumentsOrThrow() const
{
  validateArgumentsOrThrow();

  if(!isServerAddressSet())
    throw std::invalid_argument("Server address is not set but required for client connection");
}

/**
 * Validates the server specific arguments in the config is set or will throw an exception.
 * @throws std::invalid_parameter if the server arguments are missing or misconfigured
 */
void LaunchConfig::validateServerArgumentsOrThrow() const
{
  validateArgumentsOrThrow();

  if(!isServerConnectionLimitSet())
    throw std::invalid_argument("Server connection limit is not set");
}

/* ---- PUBLIC FUNCTIONS ---- */

/**
 * Returns a list of all arguments to start a client game.
 */
QList<Argument> LaunchConfig::getClientArguments() const
{
  validateClientArgumentsOrThrow();

  QMap<QString, Argument> arguments = getArgumentsMap();

  arguments.insert(PARAM_SERVER_ADDR, Argument(PARAM_SERVER_ADDR, getServerAddress()));

  return arguments.values();
}

/**
 * Returns a list of all arguments to start an offline game.
 */
QList<Argument> LaunchConfig::getOfflineArguments() const
{
  validateArgumentsOrThrow();
  return getArgumentsMap().values();
}

/**
 * Returns a list of all arguments to start a server.
 */
QList<Argument> LaunchConfig::getServerArguments() const
{
  validateServerArgumentsOrThrow();

  QMap<QString, Argument> arguments = getArgumentsMap();

  arguments.insert(PARAM_CONNECTION_LIMIT,
                   Argument(PARAM_CONNECTION_LIMIT, QString::number(getServerConnectionLimit())));

  return arguments.values();
}

/**
 * Sets the server IPv4 {@param address} for connecting as a client.
 */
void LaunchConfig::setServerAddress(QString address)
{
  server_address = address;
}

/**
 * Sets the server connection {@param limit} for clients when hosting. This is the maximum
 * connections that will be allowed.
 */
void LaunchConfig::setServerConnectionLimit(uint limit)
{
  server_connection_limit = limit;
}
