#include "config/launchconfig.h"

/* Default file names, used by the default config */
const QString LaunchConfig::DEFAULT_DOOM_FILENAME = "doom2.wad";
const QString LaunchConfig::DEFAULT_INI_FILENAME = "mod.ini";
const QString LaunchConfig::DEFAULT_PK3_FILENAME = "mod.pk3";

/* Destructor function */
LaunchConfig::~LaunchConfig()
{
}

/* Returns the file reference to the doom WAD implementation */
QString LaunchConfig::getDoomBinaryFilepath() const
{
  return getBaseExecutableDirectory() + DEFAULT_DOOM_FILENAME;
}

/* Returns the file reference to the compiled mod (pk3) */
QString LaunchConfig::getModBinaryFilepath() const
{
  return getBaseExecutableDirectory() + DEFAULT_PK3_FILENAME;
}

/* Returns the file reference to the mod configuration (ini) */
QString LaunchConfig::getModConfigFilepath() const
{
  return getBaseExecutableDirectory() + DEFAULT_INI_FILENAME;
}

/* Returns the server IPv4 address for connecting as a client */
QString LaunchConfig::getServerAddress() const
{
  return server_address;
}

/* Returns the server connection limits for clients when hosting */
uint LaunchConfig::getServerConnectionLimit() const
{
  return server_connection_limit;
}

/* Returns if the doom binary path is a valid file */
bool LaunchConfig::isDoomBinaryValid() const
{
  return QFile(getDoomBinaryFilepath()).exists();
}

/* Returns if the mod binary path is a valid file */
bool LaunchConfig::isModBinaryValid() const
{
  return QFile(getModBinaryFilepath()).exists();
}

/* Returns if the mod configuration path is a valid file */
bool LaunchConfig::isModConfigValid() const
{
  return QFile(getModConfigFilepath()).exists();
}

/* Returns if the server IPv4 address for connecting as a client is set */
bool LaunchConfig::isServerAddressSet() const
{
  // TODO: Replace with IPv4 regex
  return !server_address.isEmpty();
}

/* Returns if the server connection limit for clients is set */
bool LaunchConfig::isServerConnectionLimitSet() const
{
  return server_connection_limit_set;
}

/* Returns if the zandronum path is a valid file */
bool LaunchConfig::isZandronumBinaryValid() const
{
  return QFile(getZandronumBinaryFilepath()).exists();
}

/* Sets the server IPv4 address for connecting as a client */
void LaunchConfig::setServerAddress(QString address)
{
  server_address = address;
}

/* Sets the server connection limits for clients when hosting */
void LaunchConfig::setServerConnectionLimit(uint limit)
{
  server_connection_limit = limit;
  server_connection_limit_set = true;
}
