/*
 * Author: Jwalant Patel
 * Date: 2024-02-02
 * Description: main class where it creates a QApplication object and initializes the mainWindow of the application
 *              displaying it and starting the event loop
 *   
 */

#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
