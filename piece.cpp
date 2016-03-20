#include "piece.hpp"

Piece::Piece(QGraphicsItem *parent, bool color)
 : QGraphicsItem(parent), m_color(color)
{
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemSendsScenePositionChanges);
    setCursor(Qt::OpenHandCursor);
    setAcceptedMouseButtons(Qt::LeftButton);
}

QRectF Piece::boundingRect() const
{
    return QRectF(CIRCLE_RECT);
}

void Piece::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QBrush pieceBrush;
    QPen pen;
    pen.setColor(Qt::white);
    if(m_color == RED){
        pieceBrush.setColor(Qt::red);
    } else{
        pieceBrush.setColor(Qt::gray);
    }
    pieceBrush.setStyle(Qt::SolidPattern);
    painter->setBrush(pieceBrush);
    painter->setPen(pen);
    QPoint center(0,0);
    painter->drawEllipse(center, CIRCLE_RADIUS, CIRCLE_RADIUS);
//    if(m_king){
//        QRect textRect(CIRCLE_RECT);
//        painter->drawText(textRect, "K");
//    }
}

void Piece::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (m_movable){
        setCursor(Qt::ClosedHandCursor);
        m_selected = true;
        update();
    }
}

void Piece::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (QLineF(event->screenPos(), event->buttonDownScreenPos(Qt::LeftButton))
        .length() < QApplication::startDragDistance()) {
        return;
    }

    QObject * sender = (QObject *)event->widget();
    QDrag *drag = new QDrag(sender);
    QMimeData *mime = new QMimeData;
    drag->setMimeData(mime);

    QPixmap pix(this->boundingRect().size().toSize());
//    QPixmap pix;
    QPainter painter(&pix);
    painter.setTransform(QTransform::fromScale(4,4));
    painter.setRenderHint(QPainter::Antialiasing);
    paint(&painter, 0, 0);
    painter.end();

    pix.setMask(pix.createHeuristicMask());

    drag->setPixmap(pix);
    drag->setHotSpot(this->boundingRect().bottomLeft().toPoint());
//    drag->setHotSpot();
    drag->exec();
    setCursor(Qt::OpenHandCursor);
}

void Piece::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    setCursor(Qt::OpenHandCursor);
    update();
}
