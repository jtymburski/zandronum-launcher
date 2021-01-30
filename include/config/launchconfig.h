#ifndef LAUNCHCONFIG_H
#define LAUNCHCONFIG_H

#include <QFile>
#include <QString>

class LaunchConfig
{
public:
  /* Destructor function of the implementation */
  virtual ~LaunchConfig();

private:
  /* Default file names, used by the default config */
  const static QString DEFAULT_DOOM_FILENAME;
  const static QString DEFAULT_INI_FILENAME;
  const static QString DEFAULT_PK3_FILENAME;

private:
  /* Returns the base executable directory */
  virtual QString getBaseExecutableDirectory() const = 0;

public:
  /* Returns the file reference to the doom WAD implementation */
  QString getDoomBinaryFilepath() const;

  /* Returns the file reference to the compiled mod (pk3) */
  QString getModBinaryFilepath() const;

  /* Returns the file reference to the mod configuration (ini) */
  QString getModConfigFilepath() const;

  /* Returns the file reference to the zandronum binary */
  virtual QString getZandronumBinaryFilepath() const = 0;

  /* Returns if the doom binary path is a valid file */
  bool isDoomBinaryValid() const;

  /* Returns if the mod binary path is a valid file */
  bool isModBinaryValid() const;

  /* Returns if the mod configuration path is a valid file */
  bool isModConfigValid() const;

  /* Returns if the zandronum path is a valid file */
  bool isZandronumBinaryValid() const;
};

#endif // LAUNCHCONFIG_H
