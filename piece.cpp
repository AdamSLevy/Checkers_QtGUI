#include "piece.hpp"

Piece::Piece(QGraphicsItem *parent, size_t squareID, bool color, bool king)
 : QGraphicsObject(parent), m_squareID(squareID), m_color(color), m_king(king), m_selected(false), m_movable(false)
{
//    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemSendsScenePositionChanges);
//    setCursor(Qt::OpenHandCursor);
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
    if(m_king){
        QRect textRect(CIRCLE_RECT);
        painter->drawText(textRect, "K");
    }
}

void Piece::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
    if (m_movable){
        setCursor(Qt::ClosedHandCursor);
        select();
    } else{
        deselect();
    }
}

void Piece::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
    if (!m_movable || QLineF(event->screenPos(), event->buttonDownScreenPos(Qt::LeftButton))
        .length() < QApplication::startDragDistance()) {
        return;
    }

    select();

    QObject * sender = (QObject *)event->widget();
    QDrag *drag = new QDrag(sender);
    QMimeData *mime = new QMimeData;
//    mime->setData("");
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
    deselect();
}

void Piece::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
    setCursor(Qt::OpenHandCursor);
    update();
}

void Piece::deselect()
{
    if(m_selected){
        m_selected = false;
        update();
    }
}

void Piece::setMovable(bool movable)
{
    m_movable = movable;
    if(m_movable){
        setCursor(Qt::OpenHandCursor);
    } else{
        setCursor(Qt::ArrowCursor);
    }
}

void Piece::setSquareID(size_t squareID)
{
    if(squareID < NO_POS){
        m_squareID = squareID;
    }
}

void Piece::setKing()
{
    if(!m_king){
        m_king = true;
        update();
    }
}

void Piece::select()
{
    if(!m_selected){
        emit selected(m_squareID);
        m_selected = true;
        update();
    }
}
