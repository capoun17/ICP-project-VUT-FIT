/*
    Autoři:     Adam František Čapka xcapka06
                Filip Janoušek xjanou24
            
*/

/*
    Kod pro vytvoreni prostredi, menu, robotu a zdi

    Funkcionality jsou ze zadani vsechny od vytvareni robotu az po import/export souboru
*/

#include <QtWidgets>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QTextStream>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "robot.h"
#include "wall.h"
#include <QDebug>


std::list<Robot*> Robot::robots;
std::vector<std::pair<double, double>> getRectangleVertices();
std::list<Wall*> Wall::walls;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(ui->graphicsView);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    //! [1]

    //walls
    const qreal rectWidth = 1000;
    const qreal rectHeight = 1000;
    const qreal borderWidth = 20;

    scene->setSceneRect(-(rectWidth/2 + borderWidth), -(rectHeight/2 + borderWidth), rectWidth + 2*borderWidth, rectHeight + 2*borderWidth);
    //! [1] //! [2]
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);



    Wall *wallCustom = new Wall;
    Wall::walls.push_back(wallCustom);
    wallCustom->setX(-510);
    wallCustom->setY(0);
    wallCustom->setWidth(20);
    wallCustom->setLength(1000);

    scene->addItem(wallCustom);

    wallCustom = new Wall;
    Wall::walls.push_back(wallCustom);

    wallCustom->setX(510);
    wallCustom->setY(0);
    wallCustom->setWidth(20);
    wallCustom->setLength(1000);

    scene->addItem(wallCustom);

    wallCustom = new Wall;
    Wall::walls.push_back(wallCustom);


    wallCustom->setX(0);
    wallCustom->setY(-510);
    wallCustom->setWidth(1001);
    wallCustom->setLength(20);

    scene->addItem(wallCustom);

    wallCustom = new Wall;
    Wall::walls.push_back(wallCustom);
    wallCustom->setX(0);
    wallCustom->setY(510);
    wallCustom->setWidth(1000);
    wallCustom->setLength(20);

    scene->addItem(wallCustom);
    //! [4] //! [5]

    ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground);
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
    //! [5] //! [6]
    //
    setWindowTitle("Roboti");
    ui->graphicsView->show();


    QObject::connect(&timer, SIGNAL(timeout()), this, SLOT(simulationUpdate()));
    timer.start(1000 / 33);  // určuje plynulost simulace

    // připojení tlačítek GUI
    connect(ui->addRobotButton, &QPushButton::clicked, this, &MainWindow::addRobot);
    connect(ui->addObstacleButton, &QPushButton::clicked, this, &MainWindow::addObstacle);
    connect(ui->deleteLastRobotButton, &QPushButton::clicked, this, &MainWindow::deleteRobot);
    connect(ui->deleteLastObstacleButton, &QPushButton::clicked, this, &MainWindow::deleteObstacle);

    connect(ui->goButton, &QPushButton::clicked, this, &MainWindow::go);
    connect(ui->stopButton, &QPushButton::clicked, this, &MainWindow::stop);
    connect(ui->rotateCButton, &QPushButton::clicked, this, &MainWindow::rotateC);
    connect(ui->rotateCCButton, &QPushButton::clicked, this, &MainWindow::rotateCC);


    connect(ui->animStopButton, &QPushButton::clicked, this, &MainWindow::animStop);
    connect(ui->animResButton, &QPushButton::clicked, this, &MainWindow::animRes);


    // počátecní nastavení tlačítek
    ui->goButton->setEnabled(false);
    ui->goButton->setStyleSheet("background-color: gray");
    ui->stopButton->setEnabled(false);
    ui->stopButton->setStyleSheet("background-color: gray");
    ui->rotateCButton->setEnabled(false);
    ui->rotateCButton->setStyleSheet("background-color: gray");
    ui->rotateCCButton->setEnabled(false);
    ui->rotateCCButton->setStyleSheet("background-color: gray");
    ui->deleteLastRobotButton->setEnabled(false);
    ui->deleteLastRobotButton->setStyleSheet("background-color: gray");
    ui->deleteLastObstacleButton->setEnabled(false);
    ui->deleteLastObstacleButton->setStyleSheet("background-color: gray");
    ui->animStopButton->setEnabled(false);
    ui->animStopButton->setStyleSheet("background-color: gray");
    ui->animResButton->setEnabled(false);
    ui->animResButton->setStyleSheet("background-color: gray");

    // připojení ostatních tlačítek GUI
    connect(ui->exportButton, &QPushButton::clicked, this, &MainWindow::exportScene);
    connect(ui->importButton, &QPushButton::clicked, this, &MainWindow::toggleImportButtons);
    connect(ui->saveImportButton, &QPushButton::clicked, this, &MainWindow::saveScene);
    connect(ui->loadImportButton, &QPushButton::clicked, this, &MainWindow::loadScene);

    // skrytí zatím nepotřebných tlačítek
    ui->saveImportButton->hide();
    ui->loadImportButton->hide();
    ui->textEdit->hide();
    importButtonsVisible = false;
}

// funkce pro vracení hodnoty true, když se vybere robot
bool MainWindow::isRobotSelected() {
    QList<QGraphicsItem*> selectedItems = scene->selectedItems();
    foreach (QGraphicsItem *item, selectedItems) {
        if (Robot *robot = dynamic_cast<Robot*>(item)) {
            // pokud vybereme robota, vrať true
            return true;
        }
    }
    // jinak vrať false
    return false;
}

// mění viditelnost určitých tlačítek v GUI podle potřeby
void MainWindow::toggleImportButtons() {
    if (importButtonsVisible) {
        ui->saveImportButton->hide();
        ui->loadImportButton->hide();
        ui->textEdit->hide();
        importButtonsVisible = false;
    } else {
        importScene();
        ui->saveImportButton->show();
        ui->loadImportButton->show();
        ui->textEdit->show();
        importButtonsVisible = true;
    }
}

// funkce pro nastavení parametrů pro nového robota
void MainWindow::addRobot() {
    bool ok;
    qreal x = QInputDialog::getDouble(this, tr("Add Robot"), tr("X Position:"), 0, scene->sceneRect().left(), scene->sceneRect().right(), 1, &ok);
    if (!ok) return;
    qreal y = QInputDialog::getDouble(this, tr("Add Robot"), tr("Y Position:"), 0, scene->sceneRect().top(), scene->sceneRect().bottom(), 1, &ok);
    if (!ok) return;
    qreal startingAngle = QInputDialog::getDouble(this, tr("Add Robot"), tr("Starting Angle (degrees):"), 0, 0, 360, 1, &ok);
    if (!ok) return;
    QString direction = QInputDialog::getItem(this, tr("Add Robot"), tr("Rotation Direction:"), QStringList() << "Clockwise" << "Counter Clockwise", 0, false, &ok);
    if (!ok) return;
    qreal speed = QInputDialog::getDouble(this, tr("Add Robot"), tr("Speed:"), 1, 0, 10, 1, &ok);
    if (!ok) return;
    qreal collisionAngle = QInputDialog::getDouble(this, tr("Add Robot"), tr("Collision Angle (degrees):"), 0, -360, 360, 1, &ok);
    if (!ok) return;
    qreal visionDistance = QInputDialog::getDouble(this, tr("Add Robot"), tr("Vision Distance:"), 120, 20, 300, 1, &ok);
    if (!ok) return;
    // zavolání funkce pro vložení robota do simulace
    addRobot1(x, y, startingAngle, direction == "Clockwise", speed, collisionAngle, visionDistance);
}

// funkce pro vložení robota do simulace
void MainWindow::addRobot1(qreal x, qreal y, qreal startingAngle, bool clockwise, qreal speed, qreal collisionAngle, qreal visionDistance) {
    Robot *robot = new Robot;
    robot->setPos(x, y);
    robot->setRotation(startingAngle);
    robot->setRotationDirection(clockwise ? Robot::Clockwise : Robot::CounterClockwise);
    robot->setSpeed(speed);
    robot->setCollisionRotationAngle(collisionAngle);
    robot->setVisionDistance(visionDistance);
    scene->addItem(robot);


    robot->setX(x);
    robot->setY(y);
    robot->setAngle(startingAngle);

    // vloží do listu robotů nového robota
    Robot::robots.push_back(robot);

    // povolí nové tlačítka pro ovládání robota
    ui->goButton->setEnabled(true);
    ui->goButton->setStyleSheet("background-color: none");
    ui->stopButton->setEnabled(true);
    ui->stopButton->setStyleSheet("background-color: none");
    ui->rotateCButton->setEnabled(true);
    ui->rotateCButton->setStyleSheet("background-color: none");
    ui->rotateCCButton->setEnabled(true);
    ui->rotateCCButton->setStyleSheet("background-color: none");
    ui->deleteLastRobotButton->setEnabled(true);
    ui->deleteLastRobotButton->setStyleSheet("background-color: none");

    ui->animResButton->setEnabled(true);
    ui->animResButton->setStyleSheet("background-color: none");
}

// funkce pro nastavení parametrů pro nové zdi
void MainWindow::addObstacle() {
    bool ok;
    qreal x = QInputDialog::getDouble(this, tr("Add Obstacle"), tr("X Position:"), 0, -500, 500, 1, &ok);
    if (!ok) return;
    qreal y = QInputDialog::getDouble(this, tr("Add Obstacle"), tr("Y Position:"), 0, -500, 500, 1, &ok);
    if (!ok) return;
    qreal size = QInputDialog::getDouble(this, tr("Add Obstacle"), tr("Size (pixels):"), 20, 1, 200, 1, &ok);
    if (!ok) return;
    qreal rotation = QInputDialog::getDouble(this, tr("Add Obstacle"), tr("Rotation (degrees):"), 0, 0, 360, 1, &ok);
    if (!ok) return;
    // zavolá funkci pro vložení zdi do simulace
    addObstacle1(x, y, size, rotation);
}

// funkce pro vložení zdi do simulace
void MainWindow::addObstacle1(qreal x, qreal y, qreal size, qreal rotation) {
    Wall *obstacle = new Wall;
    scene->addItem(obstacle);

    obstacle->setRotation(rotation);
    obstacle->setAngle(rotation);
    // vloží do listu zdí novou zeď
    Wall::walls.push_back(obstacle);

    // povolí tlačítko pro práci se zdí
    ui->deleteLastObstacleButton->setEnabled(true);
    ui->deleteLastObstacleButton->setStyleSheet("background-color: none");


    obstacle->setX(x);
    obstacle->setY(y);
    obstacle->setWidth(size);
    obstacle->setLength(size);
}

// funkce pro odstranění robota
void MainWindow::deleteRobot() {
    // pokud není prázdný list robotů
    if (!Robot::robots.empty()) {
        Robot* robert = Robot::getLastSelectedRobot();
        if(robert){
            for (auto it = Robot::robots.begin(); it != Robot::robots.end(); ++it) {
                if ((*it) == robert) {
                    // vymaže robota
                    Robot::robots.erase(it);
                    break;
                }
            }
            scene->removeItem(robert);
            delete robert;
            Robot::setLastSelectedRobot(nullptr);
        }
        else{
            return;
        }

        bool noRobotsLeft = true;
        foreach (QGraphicsItem *item, scene->items()) {
            if (dynamic_cast<Robot*>(item)) {
                noRobotsLeft = false;
                break;
            }
        }



        // pokud už v simulaci není žadný robot tak se zakážou tlačítka pro práci s robotem
        if (noRobotsLeft) {
            ui->goButton->setEnabled(false);
            ui->goButton->setStyleSheet("background-color: gray");
            ui->stopButton->setEnabled(false);
            ui->stopButton->setStyleSheet("background-color: gray");
            ui->rotateCButton->setEnabled(false);
            ui->rotateCButton->setStyleSheet("background-color: gray");
            ui->rotateCCButton->setEnabled(false);
            ui->rotateCCButton->setStyleSheet("background-color: gray");
            ui->deleteLastRobotButton->setEnabled(false);
            ui->deleteLastRobotButton->setStyleSheet("background-color: gray");
            ui->animStopButton->setEnabled(false);
            ui->animStopButton->setStyleSheet("background-color: gray");
            ui->animResButton->setEnabled(false);
            ui->animResButton->setStyleSheet("background-color: gray");
        }
    }
}

// funkce pro odstranění zdi
void MainWindow::deleteObstacle() {
    if (!Wall::walls.empty()) {
        Wall* lastObstacle = Wall::walls.back();

        // Remove the last element
        Wall::walls.pop_back();
        if(lastObstacle){
            for (auto it = Wall::walls.begin(); it != Wall::walls.end(); ++it) {
                if ((*it) == lastObstacle) {
                    // vymaže zeď
                    Wall::walls.erase(it);
                    break;
                }
            }
            scene->removeItem(lastObstacle);
            delete lastObstacle;
        }
    }

    // zakáže tlačítko pro odstraňování dalších zdí pokud zbývají 4 (hrací pole)
    if (Wall::walls.size() <= 4) {
        ui->deleteLastObstacleButton->setEnabled(false);
        ui->deleteLastObstacleButton->setStyleSheet("background-color: gray");
    }
}

// funkce pro ovládaní robotů
void MainWindow::go(){

    Robot* robert = Robot::getLastSelectedRobot();
    if(robert){
        robert->setMoveType(0);
    }

}
void MainWindow::stop(){


    Robot* robert = Robot::getLastSelectedRobot();
    if(robert){
        robert->setMoveType(1);
    }
}
void MainWindow::rotateC(){

    Robot* robert = Robot::getLastSelectedRobot();
    if(robert){
        robert->setMoveType(2);
    }
}
void MainWindow::rotateCC(){

    Robot* robert = Robot::getLastSelectedRobot();
    if(robert){
        robert->setMoveType(3);
    }
}

// funkce pro ovládání celé animace
void MainWindow::animStop(){

    ui->animStopButton->setEnabled(false);
    ui->animStopButton->setStyleSheet("background-color: gray");
    ui->animResButton->setEnabled(true);
    ui->animResButton->setStyleSheet("background-color: none");
    timer.stop();
}

void MainWindow::animRes(){

    ui->animStopButton->setEnabled(true);
    ui->animStopButton->setStyleSheet("background-color: none");
    ui->animResButton->setEnabled(false);
    ui->animResButton->setStyleSheet("background-color: gray");
    timer.start(1000 / 33);
}

// export
void MainWindow::exportScene(){
    saveSceneToJson("scene.json");
}

// funkce uloží QGraphicsScene objekty do .json souboru
void MainWindow::saveSceneToJson(const QString &filename)
{
    QJsonArray itemsArray;

    // projede zdi v simulaci
    foreach (QGraphicsItem *item, Wall::walls) {
        QJsonObject itemObject;

        // kontrola typu objektu (zeď)
        if (Wall *wall = dynamic_cast<Wall*>(item)) {
            // pokud je to zeď, tak si uloží její parametry

            itemObject["x"] = wall->getX();
            itemObject["y"] = wall->getY();
            itemObject["type"] = "Wall";
            itemObject["rotation"] = wall->getAngle();

            itemObject["width"] = wall->getWidth();
            itemObject["length"] = wall->getLength();

            // rozšíří pole objektů o danou zeď
            itemsArray.append(itemObject);
        }
    }

    // projede roboty v simulaci
    foreach (QGraphicsItem *item, Robot::robots) {
        QJsonObject itemObject2;


        // kontrola typu objektu (robot)
        if (Robot *robot = dynamic_cast<Robot*>(item)) {
            // pokud je to robot, tak si uloží jeho parametry

            itemObject2["x"] = robot->getX();
            itemObject2["y"] = robot->getY();
            itemObject2["type"] = "Robot";
            itemObject2["angle"] = robot->getAngle();
            itemObject2["speed"] = robot->getSpeed();
            itemObject2["collisionAngle"] = robot->collisionRotationAngle();
            itemObject2["direction"] = (robot->rotationDirection() == Robot::Clockwise) ? "Clockwise" : "Counterclockwise";
            itemObject2["visionDistance"] = robot->robotVisionDistance();

            // rozšíří pole objektů o daného robota
            itemsArray.append(itemObject2);
        }
    }

    // vytvoří .json dokument
    QJsonDocument document(itemsArray);

    // získá cestu k souboru
    QString directoryPath = QDir::currentPath() + "/../../";

    // přidá jmeno souboru do cesty
    QString filePath = directoryPath + filename;

    QFile file(filePath);
    // kontrola otevření
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Error";
        return;
    }

    // možnost zápisu do souboru
    QTextStream out(&file);

    // zápis obsahu do souboru
    out << document.toJson();

    // zavření souboru
    file.close();
}


MainWindow::~MainWindow()
{
    delete ui;
}

// funkce pro import
void MainWindow::importScene() {
    // nastaví cestu souboru
    QString fileName = QDir::currentPath() + "/../../scene.json";

    // otevře soubor
    QFile file(fileName);
    // kontrola otevření
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Error";
        return;
    }

    // načte obsah souboru a zavře ho
    QTextStream in(&file);
    QString fileContents = in.readAll();
    file.close();

    // zobrazí textEdit v GUI
    ui->textEdit->setPlainText(fileContents);
}

// funkce pro uložení simulace
void MainWindow::saveScene() {
    // získá text z textEditu
    QString sceneText = ui->textEdit->toPlainText();

    // otevře soubor
    QString fileName = QDir::currentPath() + "/../../scene.json";
    QFile file(fileName);
    // kontrola otevření
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Error";
        return;
    }

    // zapíse upravený text do souboru
    QTextStream out(&file);
    out << sceneText;
    file.close();
}

// funkce pro načtení simulace
void MainWindow::loadScene() {

    QString fileName = QDir::currentPath() + "/../../scene.json";

    // otevření a konrola
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Error";
        return;
    }

    // přečte obsah
    QByteArray jsonData = file.readAll();
    file.close();

    // parse obsahu souboru .json
    QJsonParseError parseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &parseError);
    if (jsonDoc.isNull()) {
        qDebug() << "Failed to parse JSON:" << parseError.errorString();
        return;
    }

    // kontrola obsahu
    if (!jsonDoc.isArray()) {
        qDebug() << "JSON file does not contain a top-level array.";
        return;
    }

    // extrahuje obsah
    QJsonArray jsonArray = jsonDoc.array();



    // vyčistení simulace
    scene->clear();

    Wall::walls.clear();
    Robot::robots.clear();

    // iteruje polem s obsahem
    for (const QJsonValue& value : jsonArray) {
        QJsonObject obj = value.toObject();
        QString output = obj["type"].toString();

        // pokud je to robot tak ho vytvoří s zadanýma parametrama a vloží do simulace
        if (output == "Robot") {

            Robot *robot = new Robot;
            robot->setPos(obj["x"].toDouble(), obj["y"].toDouble());


            robot->setRotation(obj["angle"].toDouble());
            scene->addItem(robot);

            robot->setX(obj["x"].toDouble());
            robot->setY(obj["y"].toDouble());
            robot->setAngle(obj["angle"].toDouble());
            robot->setSpeed(obj["speed"].toDouble());
            robot->setCollisionRotationAngle(obj["collisionAngle"].toDouble());
            robot->setVisionDistance(obj["visionDistance"].toDouble());
            Robot::robots.push_back(robot);        
        } // pokud je to zeď tak ji vytvoří se zadanýma parametrama a vloží do simulace
        else if (output == "Wall") {

            Wall *wall = new Wall;

            wall->setX((obj["x"].toDouble()  ));
            wall->setY((obj["y"].toDouble() ));
            wall->setAngle(obj["rotation"].toDouble());

            wall->setRotation(obj["rotation"].toDouble());
            wall->setWidth(obj["width"].toDouble());
            wall->setLength(obj["length"].toDouble());

            scene->addItem(wall);

            Wall::walls.push_back(wall);
        }
    }
    // kontola počtu objektu pro povolení tlačítek v GUI
    if(Robot::robots.size() > 0)
    {
        ui->goButton->setEnabled(true);
        ui->goButton->setStyleSheet("background-color: none");
        ui->stopButton->setEnabled(true);
        ui->stopButton->setStyleSheet("background-color: none");
        ui->rotateCButton->setEnabled(true);
        ui->rotateCButton->setStyleSheet("background-color: none");
        ui->rotateCCButton->setEnabled(true);
        ui->rotateCCButton->setStyleSheet("background-color: none");
        ui->deleteLastRobotButton->setEnabled(true);
        ui->deleteLastRobotButton->setStyleSheet("background-color: none");
        ui->animStopButton->setEnabled(true);
        ui->animStopButton->setStyleSheet("background-color: none");
    }
    if(Wall::walls.size() > 4)
    {
        ui->deleteLastObstacleButton->setEnabled(true);
        ui->deleteLastObstacleButton->setStyleSheet("background-color: none");
    }
}

// funkce pro plynulé fungování simulace
void MainWindow::simulationUpdate(){
    for (auto it = Robot::robots.begin(); it != Robot::robots.end(); ++it) {
        (*it)->robotUpdate(1);
    }
}
