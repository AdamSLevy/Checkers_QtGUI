#ifndef DARKSQUARE_H
#define DARKSQUARE_H

#include <QGraphicsObject>
#include <QDebug>
//#include <QGraphicsScene>
#include <QGraphicsSceneDragDropEvent>
#include <QPainter>

#include "squaresizes.hpp"

class DarkSquare : public QGraphicsObject
{
    Q_OBJECT
    public:
        DarkSquare(QGraphicsItem *parent = 0,
                   size_t row = 0, size_t col = 0, size_t id = 0);

        QRectF boundingRect() const;
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);


    protected:
        void mousePressEvent(QGraphicsSceneMouseEvent *event);
        void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
        void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);
        void dropEvent(QGraphicsSceneDragDropEvent *event);

    signals:
        void selected(size_t squareID);

    public slots:
        void deselect();
        void setOpen(bool open);

    private:
        size_t m_row;
        size_t m_col;
        size_t m_id;
        size_t m_piece;
        bool m_open;
        bool m_selected;

        void select();
};

#endif // DARKSQUARE_H
