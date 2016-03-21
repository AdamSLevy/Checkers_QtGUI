#include "checkerboardgui.hpp"

CheckerBoardGUI::CheckerBoardGUI(QGraphicsItem *parent)
    : QGraphicsObject(parent), m_selectedPiece(NO_POS)
{
    setFlag(ItemHasNoContents);
    for(int i = 0; i <= 63; i++){
        if(i % 2 == (i/8) % 2){
            DarkSquare * square = new DarkSquare(this, i/8, (i%8)/2, i/2);
            square->setPos(position(i));
            dark_squares.push_back(square);
        }
    }

//    for(int i = 0; i < 64; i++){
//        if(i % 2 == (i/8) % 2){
//            Piece * piece;
//            if(i < 2*12){
//                piece = new Piece(dark_squares[i/2]);
//                red_pieces.push_back(piece);
//            } else if(i > 2*(32-12)-1){
//                piece = new Piece(dark_squares[i/2], BLK);
//                blk_pieces.push_back(piece);
//            }
//        }
//    }

    for(size_t i = 0; i < 32; i++){
        PieceG * piece;
        if(i < 12){
            piece = new PieceG(dark_squares[i], i);
            red_pieces.push_back(piece);
        } else if(i > (32-12)-1){
            piece = new PieceG(dark_squares[i], i, BLK);
            blk_pieces.push_back(piece);
        }

    }

//    for(int i = 0; i < blk_pieces.size(); i++){
//        for(int j = 0; j < blk_pieces.size(); j++){
//            if(i != j){
//                connect(blk_pieces[i], &Piece::selected,
//                        blk_pieces[j], &Piece::deselect);
//            } else{
////                connect(blk_pieces[i], &Piece::selected,
////                        this, &CheckerBoardGUI::)
//            }
//        }
//    }
//    for(int i = 0; i < red_pieces.size(); i++){
//        for(int j = 0; j < red_pieces.size(); j++){
//            if(i != j){
//                connect(red_pieces[i], &Piece::selected,
//                        red_pieces[j], &Piece::deselect);
//            }
//        }
//    }

    for(DarkSquare * ds : dark_squares){
        connect(ds, &DarkSquare::selected,
                this, &CheckerBoardGUI::handleSquareSelected);
    }
    for(PieceG * p : red_pieces){
        connect(p, &PieceG::selected,
                this, &CheckerBoardGUI::handlePieceSelected);
    }
    for(PieceG * p : blk_pieces){
        connect(p, &PieceG::selected,
                this, &CheckerBoardGUI::handlePieceSelected);
    }

    for(int i = 8; i < 0xC; i++){
        PieceG * p = (PieceG *)dark_squares[i]->childItems().first();
        p->setMovable(true);
    }
    for(int i = 0xC; i < 0x10; i++){
        dark_squares[i]->setOpen(true);
    }
}

QRectF CheckerBoardGUI::boundingRect() const
{
//    QSizeF rectSize = light_squares.first()->boundingRect().size();
//    return QRectF(-4 * rectSize.width(), -4 * rectSize.height(), 8 * rectSize.width(), 8 * rectSize.height());
//    return QRectF(0,0, 8 * rectSize.width(), 8 * rectSize.height());
    return QRectF();
}

void CheckerBoardGUI::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void CheckerBoardGUI::handleSquareSelected(size_t selectedSquare)
{
    if(m_selectedPiece != NO_POS){
        PieceG * p = (PieceG *)dark_squares[m_selectedPiece]->childItems().first();
        p->setSquareID(selectedSquare);
        p->setParentItem(dark_squares[selectedSquare]);
    }
    deselectAll();
}

void CheckerBoardGUI::handlePieceSelected(size_t selectedPiece)
{
    deselectAll();
    m_selectedPiece = selectedPiece;
}

void CheckerBoardGUI::deselectAll()
{
    for(PieceG * p : red_pieces){
        p->deselect();
    }
    for(PieceG * p : blk_pieces){
        p->deselect();
    }
    for(DarkSquare * ds : dark_squares){
        ds->deselect();
    }
    m_selectedPiece = NO_POS;
}

QPointF CheckerBoardGUI::position(size_t i)
{
    size_t row = i/8;
    size_t col = i%8;
    QPointF pos;
    pos.setX(    col * SQUARE_SIZE);
    pos.setY((7-row) * SQUARE_SIZE);
    return pos;
}


void CheckerBoardGUI::setBoard(BitBoard bb)
{
    m_cb.m_bb = bb;

}
