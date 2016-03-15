#ifndef DARKSQUARE_H
#define DARKSQUARE_H

#include <QGraphicsObject>
#include <QGraphicsScene>
#include <QGraphicsSceneDragDropEvent>
#include <QPainter>

#include "squaresizes.hpp"

#define RED 1
#define BLK 2

class DarkSquare : public QGraphicsObject
{
public:
    DarkSquare(QGraphicsItem *parent = 0);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);


protected:
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);
    void dropEvent(QGraphicsSceneDragDropEvent *event);

signals:

public slots:

private:
    size_t m_piece;
    bool   m_king;
    bool dragOver;
};

#endif // DARKSQUARE_H
