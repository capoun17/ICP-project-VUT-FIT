/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QPushButton *importButton;
    QPushButton *addObstacleButton;
    QPushButton *goButton;
    QTextEdit *textEdit;
    QGraphicsView *graphicsView;
    QPushButton *exportButton;
    QPushButton *rotateCCButton;
    QPushButton *animStopButton;
    QPushButton *rotateCButton;
    QPushButton *stopButton;
    QPushButton *loadImportButton;
    QPushButton *deleteLastObstacleButton;
    QPushButton *saveImportButton;
    QPushButton *addRobotButton;
    QPushButton *animResButton;
    QPushButton *deleteLastRobotButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->setEnabled(true);
        MainWindow->resize(1061, 602);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        importButton = new QPushButton(centralwidget);
        importButton->setObjectName(QString::fromUtf8("importButton"));

        gridLayout->addWidget(importButton, 9, 0, 1, 1);

        addObstacleButton = new QPushButton(centralwidget);
        addObstacleButton->setObjectName(QString::fromUtf8("addObstacleButton"));

        gridLayout->addWidget(addObstacleButton, 2, 0, 1, 1);

        goButton = new QPushButton(centralwidget);
        goButton->setObjectName(QString::fromUtf8("goButton"));
        goButton->setEnabled(true);

        gridLayout->addWidget(goButton, 1, 1, 1, 1);

        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        QSizePolicy sizePolicy(QSizePolicy::Ignored, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(textEdit->sizePolicy().hasHeightForWidth());
        textEdit->setSizePolicy(sizePolicy);
        textEdit->setMaximumSize(QSize(578, 16777215));

        gridLayout->addWidget(textEdit, 19, 0, 17, 1);

        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));

        gridLayout->addWidget(graphicsView, 2, 1, 34, 4);

        exportButton = new QPushButton(centralwidget);
        exportButton->setObjectName(QString::fromUtf8("exportButton"));

        gridLayout->addWidget(exportButton, 10, 0, 1, 1);

        rotateCCButton = new QPushButton(centralwidget);
        rotateCCButton->setObjectName(QString::fromUtf8("rotateCCButton"));

        gridLayout->addWidget(rotateCCButton, 1, 4, 1, 1);

        animStopButton = new QPushButton(centralwidget);
        animStopButton->setObjectName(QString::fromUtf8("animStopButton"));

        gridLayout->addWidget(animStopButton, 7, 0, 1, 1);

        rotateCButton = new QPushButton(centralwidget);
        rotateCButton->setObjectName(QString::fromUtf8("rotateCButton"));
        rotateCButton->setEnabled(true);

        gridLayout->addWidget(rotateCButton, 1, 3, 1, 1);

        stopButton = new QPushButton(centralwidget);
        stopButton->setObjectName(QString::fromUtf8("stopButton"));

        gridLayout->addWidget(stopButton, 1, 2, 1, 1);

        loadImportButton = new QPushButton(centralwidget);
        loadImportButton->setObjectName(QString::fromUtf8("loadImportButton"));

        gridLayout->addWidget(loadImportButton, 18, 0, 1, 1);

        deleteLastObstacleButton = new QPushButton(centralwidget);
        deleteLastObstacleButton->setObjectName(QString::fromUtf8("deleteLastObstacleButton"));

        gridLayout->addWidget(deleteLastObstacleButton, 4, 0, 1, 1);

        saveImportButton = new QPushButton(centralwidget);
        saveImportButton->setObjectName(QString::fromUtf8("saveImportButton"));

        gridLayout->addWidget(saveImportButton, 17, 0, 1, 1);

        addRobotButton = new QPushButton(centralwidget);
        addRobotButton->setObjectName(QString::fromUtf8("addRobotButton"));

        gridLayout->addWidget(addRobotButton, 1, 0, 1, 1);

        animResButton = new QPushButton(centralwidget);
        animResButton->setObjectName(QString::fromUtf8("animResButton"));

        gridLayout->addWidget(animResButton, 8, 0, 1, 1);

        deleteLastRobotButton = new QPushButton(centralwidget);
        deleteLastRobotButton->setObjectName(QString::fromUtf8("deleteLastRobotButton"));

        gridLayout->addWidget(deleteLastRobotButton, 3, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1061, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        importButton->setText(QCoreApplication::translate("MainWindow", "Import", nullptr));
        addObstacleButton->setText(QCoreApplication::translate("MainWindow", "Add Obstacle", nullptr));
        goButton->setText(QCoreApplication::translate("MainWindow", "Go", nullptr));
        exportButton->setText(QCoreApplication::translate("MainWindow", "Export", nullptr));
        rotateCCButton->setText(QCoreApplication::translate("MainWindow", "Rotate Left", nullptr));
        animStopButton->setText(QCoreApplication::translate("MainWindow", "Stop Animation", nullptr));
        rotateCButton->setText(QCoreApplication::translate("MainWindow", "Rotate Right", nullptr));
        stopButton->setText(QCoreApplication::translate("MainWindow", "Stop", nullptr));
        loadImportButton->setText(QCoreApplication::translate("MainWindow", "Load Scene", nullptr));
        deleteLastObstacleButton->setText(QCoreApplication::translate("MainWindow", "Delete Last Obstacle", nullptr));
        saveImportButton->setText(QCoreApplication::translate("MainWindow", "Save import", nullptr));
        addRobotButton->setText(QCoreApplication::translate("MainWindow", "Add Robot", nullptr));
        animResButton->setText(QCoreApplication::translate("MainWindow", "Resume Animation", nullptr));
        deleteLastRobotButton->setText(QCoreApplication::translate("MainWindow", "Delete selected Robot", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
