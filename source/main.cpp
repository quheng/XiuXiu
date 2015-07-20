#include "mainwindow.h"
#include "dialog.h"
#include <QApplication>
#include <App/App.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    App<MainWindow> app(&w);
    app.Initialize();
    w.show();

    QFile styleFile(":/qss/interface.qss");
    styleFile.open(QIODevice::ReadOnly);
    QString setStyleSheet(styleFile.readAll());;
    a.setStyleSheet(setStyleSheet);

    return a.exec();
}
