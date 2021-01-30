#include "launchgame.h"

/* Constant Implementation - see header file for descriptions */
const QString LaunchGame::kRESOURCE_DIRECTORY = "/../Resources/";

LaunchGame::LaunchGame()
{
}

LaunchGame::~LaunchGame()
{
}

/* Returns the base executable directory */
QString LaunchGame::baseExecutableDir()
{
  return QCoreApplication::applicationDirPath() + kRESOURCE_DIRECTORY;
}

/* Execute and start the game */
void LaunchGame::start()
{
  QString binary = baseExecutableDir() + "Zandronum.app/Contents/MacOS/zandronum";

  QStringList arguments;

  arguments.append("-iwad");
  arguments.append(baseExecutableDir() + "doom.wad");

  QFile mod_pk3(baseExecutableDir() + "mod.pk3");
  if(mod_pk3.exists())
  {
    arguments.append("-file");
    arguments.append(mod_pk3.fileName());
  }

  QFile mod_config(baseExecutableDir() + "mod.ini");
  if(mod_config.exists())
  {
    arguments.append("-config");
    arguments.append(mod_config.fileName());
  }

  QProcess::startDetached(binary, arguments);
}
