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
  layout->setMargin(25);

  QVBoxLayout* button_layout = new QVBoxLayout(this);

  // Launch button configuration
  QPushButton* launch_button = new QPushButton("Launch Game", this);
  launch_button->setFocusPolicy(Qt::FocusPolicy::NoFocus);
  connect(launch_button, SIGNAL(clicked()), this, SLOT(onLaunchClick()));
  button_layout->addWidget(launch_button);

  QPushButton* server_button = new QPushButton("Host Server", this);
  server_button->setFocusPolicy(Qt::FocusPolicy::NoFocus);
  connect(server_button, SIGNAL(clicked()), this, SLOT(onServerClick()));
  button_layout->addWidget(server_button);

  QPushButton* client_button = new QPushButton("Connect to Server", this);
  client_button->setFocusPolicy(Qt::FocusPolicy::NoFocus);
  connect(client_button, SIGNAL(clicked()), this, SLOT(onClientClick()));
  button_layout->addWidget(client_button);

  layout->addLayout(button_layout, 1, 1);
}

MainDialog::~MainDialog()
{
}

/**
 * Create base config.
 */
LaunchConfig* MainDialog::createLaunchConfig()
{
  LaunchConfig* launch_config;

#ifdef _WIN32
  launch_config = new WinLaunchConfig();
#elif __APPLE__
  launch_config = new MacLaunchConfig();
#endif

  return launch_config;
}

/**
 * Client button click.
 */
void MainDialog::onClientClick()
{
  LaunchConfig* launch_config = createLaunchConfig();

  // TODO: Fetch from dialog
  launch_config->setServerAddress("127.0.0.1");

  launch_game.startClient(*launch_config, true);
}

/**
 * Launch button click in the dialog. Expected to start the application.
 */
void MainDialog::onLaunchClick()
{
  LaunchConfig* launch_config = createLaunchConfig();

  // Start the game
  bool success = launch_game.start(*launch_config, true);
  if(success)
  {
    // Delay closure of the app till game start
    // TODO: This should only shutdown if a server is not running
    QTimer *timer = new QTimer(this);
    timer->setSingleShot(true);
    connect(timer, SIGNAL(timeout()), this, SLOT(close()));
    timer->start(5000);
  }

  delete launch_config;
}

/**
 * Server button click.
 */
void MainDialog::onServerClick()
{
  LaunchConfig* launch_config = createLaunchConfig();
  launch_config->setServerConnectionLimit(2);

  launch_game.startServer(*launch_config);
}
