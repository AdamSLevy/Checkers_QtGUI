#include "darksquare.hpp"

DarkSquare::DarkSquare(QGraphicsItem *parent, size_t row, size_t col, size_t id)
    : QGraphicsObject(parent), m_row(row), m_col(col), m_id(id), m_piece(0), dragOver(false)
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
    squareBrush.setColor(dragOver ? color.light(100) : color);
    painter->setPen(pen);
    painter->setBrush(squareBrush);
    painter->drawRect(SQUARE_RECT);

//    if(m_piece){
//        QBrush pieceBrush(squareBrush);
//        switch(m_piece){
//            case RED:
//                pieceBrush.setColor(Qt::red);
//                break;
//            case BLK:
//                pieceBrush.setColor(Qt::black);
//                break;
//        }
//        painter->setBrush(pieceBrush);
//        QPoint center(0,0);
//        painter->drawEllipse(center, CIRCLE_RADIUS, CIRCLE_RADIUS);
//        if(m_king){
//            QRect textRect(CIRCLE_RECT);
//            painter->drawText(textRect, "K");
//        }
    //    }
}

void DarkSquare::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << QString("Row: %1, Col: %2, ID: %3").arg(m_row).arg(m_col).arg(m_id);
}

//void DarkSquare::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
//{
////    if(m_piece == 0){
////        event->setAccepted(true);
////        dragOver = true;
////    }
//    update();
//}

//void DarkSquare::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
//{
//    Q_UNUSED(event);
////    dragOver = false;
//    update();
//}

//void DarkSquare::dropEvent(QGraphicsSceneDragDropEvent *event)
//{
////    dragOver = false;
//    update();
//}
