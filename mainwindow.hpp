#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "TreeView.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow()
    {
        console.close();
        process.terminate();
    }

    void processOutput(){
        auto buffer = process.readLine();
        while(buffer.size() != 0){
            qDebug().noquote().nospace() << QTextEdit(buffer).toPlainText();
            console.insertPlainText(buffer);
            buffer = process.readLine();
        }
    }

    void closeEvent(QCloseEvent *event) override{
        console.close();
        event->accept();
    }

private:
    Ui::MainWindow *ui;
    QProcess process;
    QPlainTextEdit console;
    QString client{R"(C:\Users\alrondprime\CLionProjects\GraduateWork\cmake-build-debug\Client.exe)"};
    QString workingDir{R"(C:\Users\alrondprime\CLionProjects\GraduateWork\cmake-build-debug)"};
    QString cmd{"checkIntegrity \"\"\n"};
};
#endif // MAINWINDOW_HPP
