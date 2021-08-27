/**
 * @class Argument
 *
 * Argument that can be passed to zandronum to modify the configuration of the launched
 * application.
 */
#ifndef ARGUMENT_H
#define ARGUMENT_H

#include <QString>

class Argument
{
public:
  /* Constructor, for KV pair */
  Argument(QString key, QString value);

private:
  /* Key name of the argument */
  QString key;

  /* Value of the argument */
  QString value;

public:
  /* Returns the key name of the argument */
  QString getKey();

  /* Returns the value name of the argument */
  QString getValue();
};

#endif // ARGUMENT_H
