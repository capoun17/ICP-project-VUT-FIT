#ifndef ROBOT_H
#define ROBOT_H

/* 
    Autoři:  Adam František Čapka xcapka06
            Filip Janoušek xjanou24
            
*/

/* 
    Definice pro robot.cpp
*/


#include <QGraphicsItem>


class Robot : public QGraphicsItem
{

public:
    enum RotationDirection {
        Clockwise,
        CounterClockwise
    };

    Robot();

    QRectF boundingRect() const override;
    QPainterPath shape() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    // funkce pro označení a práci s robotem
    bool isSelected() const;
    void setMoveType(int type);
    static Robot* getLastSelectedRobot();
    static void setLastSelectedRobot(Robot* robotptr);

    // deklarace listu robotů
    static std::list<Robot*> robots;

    // kontrola kolize robotů s cizími objekty
    bool wallIsInVision(double x1, double y1, double x2, double y2) const;

    void robotUpdate(int step);

    // settery a gettery pro atributy robota
    void setX(qreal x);
    qreal getX();

    void setY(qreal y);
    qreal getY();

    void setAngle(qreal angle);
    qreal getAngle();

    qreal getSpeed() const;
    void setSpeed(qreal speed);

    RotationDirection rotationDirection() const;
    void setRotationDirection(RotationDirection direction);

    qreal collisionRotationAngle() const;
    void setCollisionRotationAngle(qreal angle);

    qreal robotVisionDistance() const;
    void setVisionDistance(qreal distance);



signals:
    void selectionChanged(bool selected);

// proměnné pro práci s robotem
private:
    qreal x;
    qreal y;
    qreal angle = 0;
    qreal speed = 3;
    qreal visionDistance = 120;
    qreal rotateAngle = 30;
    bool rotateInversion = true;
    bool selected = false;
    static Robot*lastSelectedRobot;
    qreal moveType = -1;
    qreal collisionAngle = 0;
};



#endif // ROBOT_H
