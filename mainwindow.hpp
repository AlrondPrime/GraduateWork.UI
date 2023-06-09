#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "TreeView.hpp"
#include "ConsoleWidget.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr)
        : QMainWindow(parent)
    {
        setWindowTitle("Client App");

        tree = new TreeView(this);
        this->setCentralWidget(tree);

        QToolBar *toolbar = new QToolBar();
        this->addToolBar(toolbar);
        toolbar->setMovable(false);
        QSplitter *splitter = new QSplitter(Qt::Horizontal);
        splitter->showMaximized();

        QPushButton *add_btn = new QPushButton("Add", this);
        toolbar->addWidget(add_btn);
        connect(add_btn, &QPushButton::clicked, this, [&](){add();});

        QPushButton *update_btn = new QPushButton("Update", this);
        toolbar->addWidget(update_btn);
        connect(add_btn, &QPushButton::clicked, this, [&](){update();});

        QPushButton *restore_btn = new QPushButton("Restore", this);
        toolbar->addWidget(restore_btn);
        connect(add_btn, &QPushButton::clicked, this, [&](){restore();});

        QPushButton *check_btn = new QPushButton("Check Integrity", this);
        toolbar->addWidget(check_btn);
        connect(add_btn, &QPushButton::clicked, this, [&](){checkIntegrity();});

        QPushButton *console_btn = new QPushButton("Toggle console", this);
        toolbar->addWidget(splitter);
        connect(console_btn, &QPushButton::clicked, this, [&](){console.toggleVisibility();});

        toolbar->addWidget(console_btn);
        this->addToolBar(toolbar);

        // Child process
        connect(&process, &QProcess::readyReadStandardOutput, this, &MainWindow::processOutput);
        process.setWorkingDirectory(workingDir);
        process.setProcessChannelMode(QProcess::MergedChannels);
        process.start(client);
        if(!process.waitForStarted())
        {
            qDebug() << "Child process was not started";
            exit(-1);
        }

        resize(QSize(700, 400));
    }

    ~MainWindow()
    {
        console.close();
        process.terminate();
    }

    void add()
    {
        QString path {tree->currentPath()};
        if (path.isEmpty())
            return;

        QString cmd{"add "};
        cmd += path;

        write(cmd);
    }

    void update()
    {
        QString path {tree->currentPath()};
        if (path.isEmpty())
            return;

        QString cmd{"update "};
        cmd += path;

        write(cmd);
    }

    void restore()
    {
        QString path {tree->currentPath()};
        if (path.isEmpty())
            return;

        QString cmd{"restore "};
        cmd += path;

        write(cmd);
    }

    void addObservable()
    {
        QString path {tree->currentPath()};
        if (path.isEmpty())
            return;

        QString cmd{"addObservable "};
        cmd += path;

        write(cmd);
    }

    void checkIntegrity()
    {
        QString path {tree->currentPath()};
        if (path.isEmpty())
            return;

        QString cmd{"checkIntegrity "};
        cmd += path;

        write(cmd);
    }

    void processOutput(){
        auto buffer = process.readLine();
        while(buffer.size() != 0){
            qDebug().noquote().nospace() << QTextEdit(buffer).toPlainText();
            console.insertPlainText(buffer);
            buffer = process.readLine();
        }
    }

    void write(QString cmd)
    {
        cmd.append('\n');
        process.write(cmd.toLocal8Bit());
        process.waitForBytesWritten();
    }

    void closeEvent(QCloseEvent *event) override{
        if(process.Running){
            process.close();
            process.waitForFinished();
        }
        console.close();
        event->accept();
    }

private:
//    Ui::MainWindow *ui;
    QProcess process;
    ConsoleWidget console;
    TreeView *tree;
    QString client{R"(C:\Users\alrondprime\CLionProjects\GraduateWork\cmake-build-debug\Client.exe)"};
    QString workingDir{R"(C:\Users\alrondprime\CLionProjects\GraduateWork\cmake-build-debug)"};
};

#endif // MAINWINDOW_HPP
