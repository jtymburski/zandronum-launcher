#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>
#include <QGridLayout>
#include <QInputDialog>
#include <QLabel>
#include <QPushButton>
#include <QTimer>

#include "config/maclaunchconfig.h"
#include "config/winlaunchconfig.h"
#include "launchgame.h"
#include "network/networkinfo.h"

class MainDialog : public QDialog
{
  Q_OBJECT

public:
  MainDialog(QWidget *parent = nullptr);
  ~MainDialog();

private:
  /* Launcher implementation */
  LaunchGame launch_game;

  /* Network info access implementation */
  NetworkInfo network_info;

  /* Server widgets */
  QLabel* server_addr_label;
  QPushButton* server_button;

  /* Background image resource path */
  const static QString kBACKGROUND_PATH;

private:
  /* Create base config */
  LaunchConfig* createLaunchConfig();

private slots:
  /* Client button click */
  void onClientClick();

  /* Launch button click */
  void onLaunchClick();

  /* Server button click */
  void onServerClick();
};
#endif // MAINDIALOG_H
