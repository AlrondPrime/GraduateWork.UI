#include "mainwindow.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Client App");

    QTreeView *tree = new TreeView(this);
    this->setCentralWidget(tree);

    QPushButton *add_btn = new QPushButton("Add", this);
    QPushButton *update_btn = new QPushButton("Update", this);
    QPushButton *restore_btn = new QPushButton("Restore", this);
    QPushButton *check_btn = new QPushButton("Check Integrity", this);
    QPushButton *terminate_btn = new QPushButton("Terminate child", this);
    QPushButton *console_btn = new QPushButton("Toggle console", this);
    connect(terminate_btn, &QPushButton::clicked, this, [&](){process.kill();});
    connect(console_btn, &QPushButton::clicked, this, [&](){console.setHidden(!console.isHidden());});

    QToolBar *toolbar = new QToolBar();
    QSplitter *splitter = new QSplitter(Qt::Horizontal);
    splitter->showMaximized();
    toolbar->addWidget(add_btn);
    toolbar->addWidget(update_btn);
    toolbar->addWidget(restore_btn);
    toolbar->addWidget(check_btn);
    toolbar->addWidget(terminate_btn);
    toolbar->addWidget(splitter);
    toolbar->addWidget(console_btn);
    toolbar->setMovable(false);
    this->addToolBar(toolbar);

    console.setReadOnly(true);
    console.setWindowTitle("App log");

    connect(&process, &QProcess::readyReadStandardOutput, this, &MainWindow::processOutput);
    process.setWorkingDirectory(workingDir);
    process.setProcessChannelMode(QProcess::MergedChannels);
//    process.start(client);
//    if(!process.waitForStarted())
//    {
//        qDebug() << "Child process was not started";
//        exit(1);
//    }

//    process.write(cmd.toLocal8Bit());
//    process.waitForBytesWritten();
}


