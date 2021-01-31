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
  setObjectName("mainDialog");
  setStyleSheet("QDialog#mainDialog {background-image: url(" + kBACKGROUND_PATH + ");}");

  QGridLayout* layout = new QGridLayout(this);
  layout->setRowStretch(0, 1);
  layout->setColumnStretch(0, 1);
  layout->setMargin(25);

  QVBoxLayout* button_layout = new QVBoxLayout();

  // Server label
  server_addr_label = new QLabel("", this);
  server_addr_label->setAlignment(Qt::AlignCenter);
  server_addr_label->setStyleSheet("QLabel { font-size: 15px; font-weight: bold; color : green; }");
  button_layout->addWidget(server_addr_label);

  // Launch button configuration
  server_button = new QPushButton("Host Server", this);
  server_button->setFocusPolicy(Qt::FocusPolicy::NoFocus);
  connect(server_button, SIGNAL(clicked()), this, SLOT(onServerClick()));
  button_layout->addWidget(server_button);

  QPushButton* client_button = new QPushButton("Connect to Server", this);
  client_button->setFocusPolicy(Qt::FocusPolicy::NoFocus);
  connect(client_button, SIGNAL(clicked()), this, SLOT(onClientClick()));
  button_layout->addWidget(client_button);

  QPushButton* launch_button = new QPushButton("Launch Game", this);
  launch_button->setFocusPolicy(Qt::FocusPolicy::NoFocus);
  connect(launch_button, SIGNAL(clicked()), this, SLOT(onLaunchClick()));
  button_layout->addWidget(launch_button);

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
  bool ok;
  QString addr = QInputDialog::getText(this, tr("Server Address"),
                                       tr("Running server IP address:"), QLineEdit::Normal,
                                       "127.0.0.1", &ok);
  if(ok && !addr.isEmpty())
  {
    launch_config->setServerAddress(addr);
    launch_game.startClient(*launch_config, true);
  }

  delete launch_config;
}

/**
 * Launch button click in the dialog. Expected to start the application.
 */
void MainDialog::onLaunchClick()
{
  LaunchConfig* launch_config = createLaunchConfig();

  // Start the game
  bool success = launch_game.start(*launch_config, true);
  if(success && !launch_game.isProcessCreated())
  {
    // Delay closure of the app till game start
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
  // TODO: Swap to use process slots for both updating the status text and state mgmt
  if(launch_game.isProcessCreated())
  {
    launch_game.stop();
    server_addr_label->setText(QString());
    server_button->setText("Host Server");
  }
  else
  {
    LaunchConfig* launch_config = createLaunchConfig();
    launch_config->setServerConnectionLimit(2);

    QString local_address = network_info.localAddress();
    qInfo() << "[INFO] Starting server at address:" << local_address;

    if(launch_game.startServer(*launch_config))
    {
      server_addr_label->setText(local_address);
      server_button->setText("Stop Server");
    }
    else
    {
      qWarning() << "Failed to start the server";
    }

    delete launch_config;
  }
}
