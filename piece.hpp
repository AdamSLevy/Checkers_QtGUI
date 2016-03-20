#ifndef PIECE_HPP
#define PIECE_HPP

#include <QDebug>
#include <QGraphicsItem>
#include <QPainter>
#include <QCursor>
#include <QBitmap>
#include <QDrag>
#include <QMimeData>
#include <QGraphicsSceneMouseEvent>
#include <QApplication>

#include "squaresizes.hpp"

class Piece : public QGraphicsItem
{
    public:
        Piece(QGraphicsItem *parent = 0, bool color = RED);

        QRectF boundingRect() const;
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    protected:
        void mousePressEvent(QGraphicsSceneMouseEvent *event);
        void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
//        void dragMoveEvent(QGraphicsSceneMoveEvent *event);
        void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    signals:

    public slots:

    private:
        bool m_color;
        bool m_selected;
        bool m_movable;
};

#endif // PIECE_HPP
