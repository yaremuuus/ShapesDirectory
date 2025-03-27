#include <QApplication>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QWidget>
#include <string>
#include <iostream>
#include <QCoreApplication>
#include <string>
#include <QObject>
#include <QString>


#include"lab_9.h"



int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow window;
    //window.setFixedSize(1200, 800);
    window.show();
    return app.exec();
}
