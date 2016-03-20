#include "checkerboard.hpp"

CheckerBoard::CheckerBoard(QGraphicsItem *parent)
    : QGraphicsObject(parent)
{
    setFlag(ItemHasNoContents);
    for(int i = 63; i >= 0; i--){
        if(i % 2 == (i/8) % 2){
            QGraphicsObject * square = new DarkSquare(this, i/8, (i%8)/2, i/2);
            square->setPos(position(i));
            dark_squares.push_back(square);
        }
    }

    for(int i = 63; i >= 0; i--){
        if(i % 2 == (i/8) % 2){
            QGraphicsItem * piece;
            if(i < 2*12){
                piece = new Piece(this);
                piece->setPos(position(i));
                red_pieces.push_back(piece);
            } else if(i > 2*(32-12)-1){
                piece = new Piece(this, BLK);
                piece->setPos(position(i));
                blk_pieces.push_back(piece);
            }
        }
    }
}

QRectF CheckerBoard::boundingRect() const
{
//    QSizeF rectSize = light_squares.first()->boundingRect().size();
//    return QRectF(-4 * rectSize.width(), -4 * rectSize.height(), 8 * rectSize.width(), 8 * rectSize.height());
//    return QRectF(0,0, 8 * rectSize.width(), 8 * rectSize.height());
    return QRectF();
}

void CheckerBoard::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);
//    for(QGraphicsItem * piece : blk_pieces){
//        piece->update();
//    }
//    for(QGraphicsItem * piece : red_pieces){
//        piece->update();
//    }
//    for(QGraphicsItem * square : dark_squares){
//        square->update();
//    }
}

QPointF CheckerBoard::position(size_t i)
{
    size_t row = i/8;
    size_t col = i%8;
    QPointF pos;
    pos.setX(    col * SQUARE_SIZE);
    pos.setY((7-row) * SQUARE_SIZE);
    return pos;
}

