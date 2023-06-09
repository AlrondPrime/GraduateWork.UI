#ifndef CONSOLEWIDGET_HPP
#define CONSOLEWIDGET_HPP

class ConsoleWidget : public QPlainTextEdit{

    Q_OBJECT

public:
    ConsoleWidget(){
        setReadOnly(true);
        setWindowTitle("App log");
    }

    void toggleVisibility(){
        setHidden(!isHidden());
    }

};

#endif // CONSOLEWIDGET_HPP
