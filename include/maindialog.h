#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>

class MainDialog : public QDialog
{
  Q_OBJECT

public:
  MainDialog(QWidget *parent = nullptr);
  ~MainDialog();
};
#endif // MAINDIALOG_H
