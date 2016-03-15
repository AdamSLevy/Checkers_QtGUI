#ifndef LIGHTSQUARE_HPP
#define LIGHTSQUARE_HPP

#include <QGraphicsItem>

#include "squaresizes.hpp"

class LightSquare : public QGraphicsItem
{
    public:
        LightSquare(QGraphicsItem *parent = 0);

        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
        QRectF boundingRect() const;
    signals:

    public slots:
};

#endif // LIGHTSQUARE_HPP
