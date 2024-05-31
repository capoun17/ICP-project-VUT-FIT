/* 
    Autoři:  Adam František Čapka xcapka06
            Filip Janoušek xjanou24
            
*/

/*
   Celkové chování robota, pohyb, detekce kolizi a manualni ovladani
*/

#include "robot.h"
#include "wall.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>
#include <QtMath>
#include <QDebug>

Robot* Robot::lastSelectedRobot = nullptr;
Robot::Robot()
{
    
}
QRectF Robot::boundingRect() const
{
    qreal penWidth = 1;
    return QRectF(-visionDistance - penWidth / 2, -visionDistance - penWidth / 2,
                  visionDistance*2 + penWidth, visionDistance*2 + penWidth);
}

// funkce kliknutí na robota
void Robot::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if(selected){
        selected = false;
        this->moveType = -1;
        lastSelectedRobot = nullptr;
    }
    else{
        if(lastSelectedRobot!= nullptr && lastSelectedRobot->selected == true){
            lastSelectedRobot->selected = false;
            lastSelectedRobot->moveType = -1;
        }
        selected = true;
        lastSelectedRobot = this;
    }
    update();
}

// vykreslení robota
QPainterPath Robot::shape() const
{
    QPainterPath path;

    path.addEllipse(-20, -20, 40, 40);
    return path;
}


bool Robot::isSelected() const {
    return selected;
}
//! [3]
void Robot::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    // vykreslení vize robota
    painter->drawRect(0, -20, visionDistance, 40);

    QPen pen(Qt::red); // Red color
    pen.setWidth(2);
    painter->setPen(pen);
    painter->drawRect(0, -20, visionDistance, 40);
    painter->setPen(Qt::NoPen);
    // tělo robota
    painter->setBrush(selected ? Qt::green : Qt::black);
    painter->drawEllipse(-20, -20, 40, 40);
}


void Robot::setMoveType(int type){
    this->moveType = type;
}

Robot* Robot::getLastSelectedRobot(){
    return lastSelectedRobot;
}

// simulace pohybu robota
void Robot::robotUpdate(int step)
{
    if (!step)
        return;

    if(this->moveType == 1){ // stop
        return;
    }
    else if(this->moveType == 2){ // rotace doleva
        angle = angle +5;
        setRotation(angle);

        return;
    }
    else if(this->moveType == 3){ // rotace doprava
        angle = angle -5;
        setRotation(angle);
        return;
    }

    // kontrola kolize robota s objekty
    bool collisionDetected = false;

    // iteruje přes všechny roboty
    for (auto it = Robot::robots.begin(); it != Robot::robots.end(); ++it) {
        if(this == (*it)){
            continue;
        }

        if(this->wallIsInVision((*it)->x + 20, (*it)->y +20, (*it)->x-20, (*it)->y+20)){
            collisionDetected = true;
        }
        if(this->wallIsInVision((*it)->x-20, (*it)->y+20, (*it)->x-20, (*it)->y-20)){
            collisionDetected = true;
        }
        if(this->wallIsInVision((*it)->x-20, (*it)->y-20, (*it)->x+20, (*it)->y-20)){
            collisionDetected = true;
        }
        if(this->wallIsInVision((*it)->x+20, (*it)->y-20, (*it)->x +20, (*it)->y+20)){
            collisionDetected = true;
        }
    }

    // iteruje přes všechny zdi
    for (auto it = Wall::walls.begin(); it != Wall::walls.end(); ++it) {
        // přes všechny úsečky tvořící zeď
        std::vector<std::pair<double, double>> vertices = (*it)->getRectangleVertices();
        for (auto i = 0; i < 3; i++) {
            if(this->wallIsInVision(vertices[i].first, vertices[i].second, vertices[i+1].first, vertices[i+1].second)){
                collisionDetected = true;
            }
        }
        if(this->wallIsInVision(vertices[3].first, vertices[3].second, vertices[0].first, vertices[0].second)){
            collisionDetected = true;
        }
    }

    // pokud nedojde ke kolizi tak se posunuje v simulaci pomocí dané funkce
    if(collisionDetected == false){
        x += cos(angle* M_PI / 180.0)*speed;
        y += sin(angle* M_PI / 180.0)*speed;
        setPos(x, y);
    }
    else if (this->moveType == 0){
        this->setMoveType(1);
    }
    else{
        if (rotateInversion == true) {
            // rotace doprava
            angle +=collisionAngle;
            while (angle < 0) {
                angle += 360.0;
            }
            while (angle >= 360.0) {
                angle -= 360.0;
            }
            setRotation(angle);


        } else {
            // rotace doleva
            angle -=collisionAngle;
            while (angle < 0) {
                angle += 360.0;
            }
            while (angle >= 360.0) {
                angle -= 360.0;
            }
            setRotation(angle);
        }
    }
}

// funkce pro detekci kolizí
bool Robot::wallIsInVision(double x1, double y1, double x2, double y2) const{

    double x3;
    double y3;
    double x4;
    double y4;

    // prvni vrchol a stred
    double relativeX = visionDistance;
    double relativeY = -20;
    x3  = x + relativeX*cos(angle* M_PI / 180.0) - relativeY*sin(angle* M_PI / 180.0);
    y3  = y + relativeX*sin(angle* M_PI / 180.0) + relativeY*cos(angle* M_PI / 180.0);

    relativeX = visionDistance;
    relativeY = 20;
    x4  = x + relativeX*cos(angle* M_PI / 180.0) - relativeY*sin(angle* M_PI / 180.0);
    y4  = y + relativeX*sin(angle* M_PI / 180.0) + relativeY*cos(angle* M_PI / 180.0);
    double alfa = ((x4-x3)*(y3-y1) -(y4-y3)*(x3-x1)) / ((x4-x3)*(y2-y1) -(y4-y3)*(x2-x1));
    double beta = ((x2-x1)*(y3-y1) -(y2-y1)*(x3-x1)) / ((x4-x3)*(y2-y1) -(y4-y3)*(x2-x1));


    if (alfa >= 0 && alfa <= 1 && beta >= 0 && beta<= 1){
        return true;
    }

    // druhý
    relativeX = 0;
    relativeY = 20;
    x3  = x + relativeX*cos(angle* M_PI / 180.0) - relativeY*sin(angle* M_PI / 180.0);
    y3  = y + relativeX*sin(angle* M_PI / 180.0) + relativeY*cos(angle* M_PI / 180.0);



    alfa = ((x4-x3)*(y3-y1) -(y4-y3)*(x3-x1)) / ((x4-x3)*(y2-y1) -(y4-y3)*(x2-x1));
    beta = ((x2-x1)*(y3-y1) -(y2-y1)*(x3-x1)) / ((x4-x3)*(y2-y1) -(y4-y3)*(x2-x1));


    if (alfa >= 0 && alfa <= 1 && beta >= 0 && beta<= 1){
        return true;
    }

    // třetí
    relativeX = 0;
    relativeY = -20;
    x4  = x + relativeX*cos(angle* M_PI / 180.0) - relativeY*sin(angle* M_PI / 180.0);
    y4  = y + relativeX*sin(angle* M_PI / 180.0) + relativeY*cos(angle* M_PI / 180.0);



    alfa = ((x4-x3)*(y3-y1) -(y4-y3)*(x3-x1)) / ((x4-x3)*(y2-y1) -(y4-y3)*(x2-x1));
    beta = ((x2-x1)*(y3-y1) -(y2-y1)*(x3-x1)) / ((x4-x3)*(y2-y1) -(y4-y3)*(x2-x1));


    if (alfa >= 0 && alfa <= 1 && beta >= 0 && beta<= 1){
        return true;
    }

    // čtvrtý
    relativeX = visionDistance;
    relativeY = -20;
    x3  = x + relativeX*cos(angle* M_PI / 180.0) - relativeY*sin(angle* M_PI / 180.0);
    y3  = y + relativeX*sin(angle* M_PI / 180.0) + relativeY*cos(angle* M_PI / 180.0);



    alfa = ((x4-x3)*(y3-y1) -(y4-y3)*(x3-x1)) / ((x4-x3)*(y2-y1) -(y4-y3)*(x2-x1));
    beta = ((x2-x1)*(y3-y1) -(y2-y1)*(x3-x1)) / ((x4-x3)*(y2-y1) -(y4-y3)*(x2-x1));


    if (alfa >= 0 && alfa <= 1 && beta >= 0 && beta<= 1){
        return true;
    }

    return false;
}

// settery a gettery pro parametry robota
void Robot::setX(qreal x){
    this->x = x;
}
qreal Robot::getX(){
    return this->x;
}

void Robot::setY(qreal y){
    this->y = y;
}
qreal Robot::getY(){
    return this->y;
}

void Robot::setAngle(qreal angle){
    this->angle = angle;
}
qreal Robot::getAngle(){
    return this->angle;
}

qreal Robot::getSpeed() const { return speed; }
void Robot::setSpeed(qreal speed) { this->speed = speed; }


Robot::RotationDirection Robot::rotationDirection() const { return rotateInversion ? Clockwise : CounterClockwise; }
void Robot::setRotationDirection(RotationDirection direction) { rotateInversion = (direction == Clockwise); }

qreal Robot::collisionRotationAngle() const { return collisionAngle; }
void Robot::setCollisionRotationAngle(qreal angle) { collisionAngle = angle; }

qreal Robot::robotVisionDistance() const { return visionDistance; }
void Robot::setVisionDistance(qreal distance) { visionDistance = distance; }

void Robot::setLastSelectedRobot(Robot* robotptr){ Robot::lastSelectedRobot = robotptr; }
