#ifndef NETWORKINFO_H
#define NETWORKINFO_H

#include <QNetworkInterface>
#include <QString>

class NetworkInfo
{
public:
  /* Determines the local network address, expected in IPv4 format */
  QString localAddress();
};

#endif // NETWORKINFO_H
