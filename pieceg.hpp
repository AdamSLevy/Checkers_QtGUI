#ifndef PIECE_HPP
#define PIECE_HPP

#include <QDebug>
#include <QObject>
#include <QGraphicsObject>
#include <QPainter>
#include <QCursor>
#include <QBitmap>
#include <QDrag>
#include <QMimeData>
#include <QGraphicsSceneMouseEvent>
#include <QApplication>

#include "squaresizes.hpp"

#define NO_POS std::numeric_limits<size_t>::max()

class PieceG : public QGraphicsObject
{
    Q_OBJECT
    public:
        PieceG(QGraphicsItem *parent = 0,
               size_t squareID = NO_POS,
               size_t pieceID = NO_POS,
               bool color = RED,
               bool king = false);

        QRectF boundingRect() const;
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
        size_t getPieceID();
        size_t getSquareID();
        bool getColor();
        bool isKing();

    protected:
        void mousePressEvent(QGraphicsSceneMouseEvent *event);
        void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
        void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    signals:
        void selected(size_t piece_id);

    public slots:
        void deselect();
        void setMovable(bool movable);
        void setSquareID(size_t squareID);
        void setKing(bool king);

    private:
        size_t m_squareID;
        size_t m_pieceID;
        bool m_color;
        bool m_king;

        bool m_selected;
        bool m_movable;

        void select();
};

#endif // PIECE_HPP
