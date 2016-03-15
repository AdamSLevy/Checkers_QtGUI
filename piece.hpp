#ifndef PIECE_HPP
#define PIECE_HPP

#include <QGraphicsObject>
#include <QGraphicsScene>
#include <QPainter>
#include <QCursor>

#define CIRCLE_RADIUS 8
#define CIRCLE_RECT -CIRCLE_RADIUS/2,CIRCLE_RADIUS/2,CIRCLE_RADIUS,CIRCLE_RADIUS

#define RED 0
#define BLK 1

class Piece : public QGraphicsObject
{
    public:
        Piece(QGraphicsItem *parent = 0, bool color = RED);

        QRectF boundingRect() const;
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    protected:
        void mousePressEvent(QGraphicsSceneDragDropEvent *event);
        void mouseMoveEvent(QGraphicsSceneDragDropEvent *event);
        void mouseReleaseEvent(QGraphicsSceneDragDropEvent *event);

    signals:

    public slots:

    private:
        bool m_color;
        size_t m_piece;
        bool   m_king;
        bool dragOver;
};

#endif // PIECE_HPP
