/**
 * @class Argument
 *
 * Argument that can be passed to zandronum to modify the configuration of the launched
 * application.
 */
#include "model/argument.h"

/**
 * Create the key-value pair for the argument which returns the immutable object.
 * @param key argument key string
 * @param value argument value string
 */
Argument::Argument(QString key, QString value)
{
  this->key = key;
  this->value = value;
}

/**
 * Returns the stored immutable key, tied to the {@link #getValue()}.
 * @return key string
 */
QString Argument::getKey()
{
  return key;
}

/**
 * Returns the stored immutable value, tied to the {@link #getKey()}.
 * @return value string
 */
QString Argument::getValue()
{
  return value;
}
