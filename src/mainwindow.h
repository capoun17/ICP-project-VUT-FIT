#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/* 
    Autoři:  Adam František Čapka xcapka06
            Filip Janoušek xjanou24
            
*/

/* 
    Definice pro mainwindow.cpp
*/

#include "qgraphicsscene.h"
#include "qtimer.h"
#include <QMainWindow>
#include <QtMath>
#include <QtWidgets>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

    // funkce v MainWindow
    private slots:
        void simulationUpdate();
        void addRobot();
        void addObstacle();
        void deleteRobot();
        void deleteObstacle();
        void stop();
        void go();
        void rotateC();
        void rotateCC();
        void animStop();
        void animRes();
        void exportScene();
        void importScene();
        void toggleImportButtons();
        void saveScene();
        void loadScene();
        bool isRobotSelected();


    private:
        void saveSceneToJson(const QString &filename);
        void addRobot1(qreal x, qreal y, qreal startingAngle, bool clockwise, qreal speed, qreal collisionAngle, qreal visionDistance);
        void addObstacle1(qreal x, qreal y, qreal size, qreal rotation);
        bool importButtonsVisible;

        // deklarace proměnných pro práci v MainWindow
        Ui::MainWindow *ui;
        QTimer timer;
        QGraphicsScene *scene;
        QGraphicsView *view;
        QList<QGraphicsItem*> addedRobots;
        QList<QGraphicsItem*> addedObstacles;

};
#endif // MAINWINDOW_H
