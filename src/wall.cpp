/* 
    Autoři:  Adam František Čapka xcapka06
            Filip Janoušek xjanou24
            
*/

/*
    Funcke pro vykreslovani zdi a nastaveni jejich parametru
*/

#include "wall.h"
#include "qpainter.h"
#include "qpen.h"
#include <QtMath>
Wall::Wall()
{
    this->width = 50;
    this->length = 50;
    this->angle = 0;
}


std::vector<std::pair<double, double>> Wall::getRectangleVertices() {
    std::vector<std::pair<double, double>> vertices(4);

    // relativní souřadnice vrcholů
    double relativeX[4] = {-width / 2, width / 2, width / 2, -width / 2};
    double relativeY[4] = {-length / 2, -length / 2, length / 2, length / 2};


    // přidáme k nim rotaci
    for (int i = 0; i < 4; ++i) {
        vertices[i].first = x + relativeX[i]*cos(angle* M_PI / 180.0) - relativeY[i]*sin(angle* M_PI / 180.0);

        vertices[i].second  = y +relativeX[i]*sin(angle* M_PI / 180.0) + relativeY[i]*cos(angle* M_PI / 180.0);
    }
    return vertices;
}

QRectF Wall::boundingRect() const
{
    return QRectF(x -width/2, y -length/2,
                  width, length);
}

// vykreslí zeď do simulace
void Wall::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QPen pen(Qt::black);
    pen.setWidth(2);
    painter->setPen(pen);
    painter->drawPolygon(QRectF(x -width/2, y -length/2, width, length));
    painter->setPen(Qt::NoPen);
}

// settery a gettery pro parametry zdi v simulaci
void Wall::setX(qreal x){
    this->x = x;
}
qreal Wall::getX(){
    return this->x;
}

void Wall::setY(qreal y){
    this->y = y;
}
qreal Wall::getY(){
    return this->y;
}

void Wall::setAngle(qreal angle){
    this->angle = angle;
}
qreal Wall::getAngle(){
    return this->angle;
}

void Wall::setWidth(qreal width){
    this->width = width;
}
qreal Wall::getWidth(){
    return this->width;
}

void Wall::setLength(qreal length){
    this->length = length;
}
qreal Wall::getLength(){
    return this->length;
}
