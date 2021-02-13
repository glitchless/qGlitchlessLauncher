#include "ui/mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow window;
    app.setStyleSheet("MainWindow {border-image: url(:/internal/img/background.png) 0 0 0 0 stretch stretch;}");
    window.show();
    return app.exec();
}
