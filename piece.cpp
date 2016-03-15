#include "piece.hpp"

Piece::Piece(QGraphicsItem *parent, bool color)
 : QGraphicsObject(parent), m_color(color)
{
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
    setCursor(Qt::OpenHandCursor);
    setAcceptedMouseButtons(Qt::LeftButton);
}

QRectF Piece::boundingRect() const
{
    return QRectF(CIRCLE_RECT);
}

void Piece::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}

void Piece::mousePressEvent(QGraphicsSceneDragDropEvent *event)
{
    setCursor(Qt::ClosedHandCursor);
}

void Piece::mouseMoveEvent(QGraphicsSceneDragDropEvent *event)
{

}

void Piece::mouseReleaseEvent(QGraphicsSceneDragDropEvent *event)
{

}
