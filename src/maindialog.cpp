#include "maindialog.h"

/* Constant Implementation - see header file for descriptions */
const QString MainDialog::kBACKGROUND_PATH = ":/resource/background.png";

MainDialog::MainDialog(QWidget *parent)
  : QDialog(parent)
{
  // Only the close button should be enabled
  setWindowFlags( Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint );

  // Fix the window size to the background
  QImage background_image(kBACKGROUND_PATH);
  setFixedSize(background_image.width(), background_image.height());
  setStyleSheet("QDialog {background-image: url(" + kBACKGROUND_PATH + ");}");

  QGridLayout* layout = new QGridLayout(this);
  layout->setRowStretch(0, 1);
  layout->setColumnStretch(0, 1);
  layout->setMargin(45);

  // Launch button configuration
  QPushButton* launch_button = new QPushButton("Launch", this);
  launch_button->setFocusPolicy(Qt::FocusPolicy::NoFocus);
  connect(launch_button, SIGNAL(clicked()), this, SLOT(onLaunchClick()));
  layout->addWidget(launch_button, 1, 1);
}

MainDialog::~MainDialog()
{
}

/**
 * Launch button click in the dialog. Expected to start the application.
 */
void MainDialog::onLaunchClick()
{
  launch_game.start();
  close();
}
