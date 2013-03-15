#include "MainWindow.h"
#include <QApplication>
#include <dialog.h>
#include <QSplashScreen>
#include <X11/Xlib.h>
#include <iostream>
#include <QTextCodec>

int main(int argc, char *argv[]){
    //Allows concurrent threads to make Xlib calls.
    //std::cout << XInitThreads() << std::endl;
    std::cout << std::endl;

    //résouds les problèmes d'accents
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

    //Q_INIT_RESOURCE(img);
    QApplication a(argc, argv);

    a.setOrganizationName("ABS");
    a.setApplicationName("FishTube");
    MainWindow w;
    w.show();
    return a.exec();
}

