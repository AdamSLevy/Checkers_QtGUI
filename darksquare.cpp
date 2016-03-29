#include "darksquare.hpp"

DarkSquare::DarkSquare(QGraphicsItem *parent, size_t row, size_t col, size_t id)
    : QGraphicsObject(parent), m_row(row), m_col(col), m_id(id), m_piece(0), m_selected(false), m_open(false)
{
    setAcceptDrops(true);
}

QRectF DarkSquare::boundingRect() const
{
    return QRectF(SQUARE_RECT);
}

void DarkSquare::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QBrush squareBrush;
    QPen pen;
    pen.setColor(Qt::black);
    pen.setCapStyle(Qt::SquareCap);
    pen.setJoinStyle(Qt::MiterJoin);
    squareBrush.setStyle(Qt::SolidPattern);
    QColor color = QColor(Qt::black);//QColor(DARK_SQUARE_COLOR);
    if (m_selected){
        color.setAlpha(150);
    }
    squareBrush.setColor(color);
    painter->setPen(pen);
    painter->setBrush(squareBrush);
    painter->drawRect(SQUARE_RECT);

}

void DarkSquare::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
//    qDebug() << QString("Row: %1, Col: %2, ID: %3").arg(m_row).arg(m_col).arg(m_id);
    Q_UNUSED(event)
    if(m_open){
        emit selected(m_id);
    }
}

void DarkSquare::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    if(m_open){
        event->acceptProposedAction();
//        event->setAccepted(true);
        m_selected = true;
        update();
    }
}

void DarkSquare::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{
    Q_UNUSED(event)
    deselect();
}

void DarkSquare::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    Q_UNUSED(event)
    if(m_open){
        emit selected(m_id);
    }
    deselect();
}

void DarkSquare::deselect()
{
    if(m_selected){
        m_selected = false;
        update();
    }
}

void DarkSquare::setOpen(bool open)
{
    m_open = open;
}

void DarkSquare::select()
{
    if(!m_selected){
        emit selected(m_id);
        m_selected = true;
        update();
    }
}
