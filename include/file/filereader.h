/**
 * @class FileReader
 *
 * Interface to handle any file processing and abstract out the implementation details.
 */
#ifndef FILEREADER_H
#define FILEREADER_H

#include <QFile>

class FileReader
{
public:
  /* Returns if the path is a valid file that can be read */
  static bool isValid(QString path);
};

#endif // FILEREADER_H
