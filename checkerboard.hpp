#ifndef CHECKERBOARD_H
#define CHECKERBOARD_H

#include <QGraphicsObject>
#include <QVector>

#include "darksquare.hpp"
#include "piece.hpp"


class CheckerBoardGUI : public QGraphicsObject
{
    public:
        CheckerBoardGUI(QGraphicsItem *parent = 0);

        QRectF boundingRect() const;
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    signals:

    public slots:

    private:
        QVector<QGraphicsObject *>  dark_squares;

        QVector<QGraphicsItem *> red_pieces;
        QVector<QGraphicsItem *> blk_pieces;

        QPointF position(size_t i);

};

#endif // CHECKERBOARD_H
