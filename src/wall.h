#ifndef WALL_H
#define WALL_H

/* 
    Autoři:  Adam František Čapka xcapka06
            Filip Janoušek xjanou24           
*/

/* 
    Definice pro wall.cpp
*/

#include <QGraphicsItem>

class Wall : public QGraphicsItem
{
public:
    Wall();

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

    // deklarace listu zdí
    static std::list<Wall*> walls;
    std::vector<std::pair<double, double>> getRectangleVertices();

    // settery a gettery pro atributy zdi
    void setX(qreal x);
    qreal getX();

    void setY(qreal y);
    qreal getY();

    void setAngle(qreal angle);
    qreal getAngle();

    void setWidth(qreal width);
    qreal getWidth();

    void setLength(qreal length);
    qreal getLength();

// proměnné pro práci se zdí
private:
    qreal x;
    qreal y;
    qreal angle = 0;
    qreal width = 50;
    qreal length = 50;

};

#endif // WALL_H
