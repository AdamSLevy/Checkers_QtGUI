#include "piece.hpp"

Piece::Piece(QGraphicsItem *parent, bool color)
 : QGraphicsItem(parent), m_color(color), m_movable(true)
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
    Q_UNUSED(option)
    Q_UNUSED(widget)
    QBrush pieceBrush;
    QPen pen;
    pen.setColor(Qt::white);
    if(m_color == RED){
        pieceBrush.setColor(Qt::red);
    } else{
        pieceBrush.setColor(Qt::gray);
    }
    if (m_selected){
        QColor color = pieceBrush.color();
        color.setAlpha(100);
        pieceBrush.setColor(color);
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
    Q_UNUSED(event)
    if (m_movable && !m_selected){
        setCursor(Qt::ClosedHandCursor);
        m_selected = true;
    } else{
        m_selected = false;
    }
    update();
}

void Piece::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
    if (!m_movable || QLineF(event->screenPos(), event->buttonDownScreenPos(Qt::LeftButton))
        .length() < QApplication::startDragDistance()) {
        return;
    }
    m_selected = true;
    update();

    QObject * sender = (QObject *)event->widget();
    QDrag *drag = new QDrag(sender);
    QMimeData *mime = new QMimeData;
    drag->setMimeData(mime);

    QSize rect = this->boundingRect().size().toSize();
    QPixmap pixmap(rect);
    pixmap.fill(Qt::white);

    QPainter painter(&pixmap);
    painter.translate(30, 30);
    painter.setRenderHint(QPainter::Antialiasing);
    paint(&painter, 0, 0);
    painter.end();

    pixmap.setMask(pixmap.createHeuristicMask());

    drag->setPixmap(pixmap);
    drag->setHotSpot(QPoint(rect.width()/2, rect.height()/2));
    drag->exec();
    setCursor(Qt::OpenHandCursor);
    m_selected = false;
    update();
}

void Piece::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
    qDebug() << "release";
    setCursor(Qt::OpenHandCursor);
    update();
}
