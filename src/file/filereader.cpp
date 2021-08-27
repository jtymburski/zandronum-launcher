/**
 * @class FileReader
 *
 * Interface to handle any file processing and abstract out the implementation details.
 */
#include "file/filereader.h"

/**
 * Returns if the path is a valid file that can be read.
 * @param path a direct or relative file url
 * @return TRUE if the file is valid and could be read. FALSE otherwise
 */
bool FileReader::isValid(QString path)
{
  return QFile(path).exists();
}
