#include "lightsquare.hpp"

LightSquare::LightSquare(QGraphicsItem *parent)
    : QGraphicsItem(parent)
{
    setAcceptDrops(false);
}

QRectF LightSquare::boundingRect() const
{
    return QRectF(SQUARE_RECT);
}

void LightSquare::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QBrush squareBrush;
    QPen pen;
    pen.setColor(Qt::white);
    squareBrush.setStyle(Qt::LinearGradientPattern);
    QColor color = QColor(LIGHT_SQUARE_COLOR);
    squareBrush.setColor(color);
    painter->setPen(pen);
    painter->setBrush(squareBrush);
    painter->drawRect(SQUARE_RECT);
}
