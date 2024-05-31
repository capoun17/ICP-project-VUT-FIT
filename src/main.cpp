/* 
    Autoři:  Adam František Čapka xcapka06
            Filip Janoušek xjanou24
            
*/

/*
    Celkové spuštění aplikace
*/

#include <QtMath>
#include <QtWidgets>
#include "mainwindow.h"


int main(int argc, char **argv)
{

    QApplication app(argc, argv);


    MainWindow w;
    // spuštení na celou obrazovku
    w.showMaximized();
    return app.exec();
}
