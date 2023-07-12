#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    // Create a QApplication object
    QApplication a(argc, argv);

    // Create an instance of MainWindow
    MainWindow w;

    // Show the MainWindow
    w.show();

    // Start the application event loop
    return a.exec();
}
