// main.cpp
#include <QApplication>
#include "App.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    App application;
    application.init();

    return app.exec();
}