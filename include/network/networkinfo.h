#ifndef NETWORKINFO_H
#define NETWORKINFO_H

#include <QNetworkInterface>
#include <QString>

class NetworkInfo
{
public:
  /* Returns if the address is a valid IPv4 format */
  bool isValidAddress(QString address);

  /* Fetches the local network address, expected in IPv4 format */
  QString localAddress();
};

#endif // NETWORKINFO_H
