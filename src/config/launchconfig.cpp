#include "config/launchconfig.h"

/* Default file names, used by the default config */
const QString LaunchConfig::DEFAULT_DOOM_FILENAME = "doom.wad";
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

/* Returns if the zandronum path is a valid file */
bool LaunchConfig::isZandronumBinaryValid() const
{
  return QFile(getZandronumBinaryFilepath()).exists();
}
