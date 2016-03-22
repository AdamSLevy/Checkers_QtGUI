#include "checkerboardgui.hpp"

CheckerBoardGUI::CheckerBoardGUI(QGraphicsItem *parent)
    : QGraphicsObject(parent), m_selectedPiece(NO_POS)
{
    setFlag(ItemHasNoContents);
    for(int i = 0; i <= 63; i++){
        if(i % 2 == (i/8) % 2){
            DarkSquare * square = new DarkSquare(this, i/8, (i%8)/2, i/2);
            square->setPos(position(i));
            m_darkSquares.push_back(square);
        }
    }

    for(size_t i = 0; i < 32; i++){
        PieceG * piece;
        if(i < 12){
            size_t pieceID = m_pieces.size();
            piece = new PieceG(0, pieceID, i);
            piece->setVisible(false);
            m_pieces.push_back(piece);
        } else if(i > (32-12)-1){
            size_t pieceID = m_pieces.size();
            piece = new PieceG(0, pieceID, i, BLK);
            piece->setVisible(false);
            m_pieces.push_back(piece);
        }
    }

    for(DarkSquare * ds : m_darkSquares){
        connect(ds, &DarkSquare::selected,
                this, &CheckerBoardGUI::handleSquareSelected);
    }
    for(PieceG * p : m_pieces){
        connect(p, &PieceG::selected,
                this, &CheckerBoardGUI::handlePieceSelected);
    }

//    for(int i = 8; i < 0xC; i++){
//        PieceG * p = (PieceG *)m_darkSquares[i]->childItems().first();
//        p->setMovable(true);
//    }
    for(int i = 0xC; i < 0x10; i++){
        m_darkSquares[i]->setOpen(true);
    }
    setBoard(m_cb.m_bb);
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
        PieceG * p = m_pieces[m_selectedPiece];
        p->setSquareID(selectedSquare);
        p->setParentItem(m_darkSquares[selectedSquare]);
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
    for(PieceG * p : m_pieces){
        p->deselect();
    }
    for(DarkSquare * ds : m_darkSquares){
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

    uint32_t play_pos;
    uint32_t oppo_pos;

    if (bb.turn == BLK){
        play_pos = bb.blk_pos;
        oppo_pos = bb.red_pos;
    } else{
        play_pos = bb.red_pos;
        oppo_pos = bb.blk_pos;
    }
    bool turn = bb.turn;

    uint32_t occupied = (play_pos | oppo_pos);
    uint32_t empty = ~occupied;

    uint32_t movers      = BCKWD(turn, empty) & play_pos;// & ~bb.king_pos;
//    uint32_t king_movers = (BCKWD(turn, empty) | FORWD(turn, empty)) & play_pos & bb.king_pos;
    size_t square = 0;
    for(int i = 0; i < m_pieces.size(); i++){
        PieceG * p = m_pieces[i];
        static bool color = p->getColor();
        static uint32_t board = bb.blk_pos;
        if(color != p->getColor()){
            board = bb.red_pos;
            color = p->getColor();
            square = 0;
        }
        for(/*size_t square*/;square < 32; square++){
            uint32_t pos = POS_MASK[square];
            if(pos & board){
                p->setVisible(true);
                p->setMovable(pos & movers);
                p->setKing(pos & bb.king_pos);
                p->setSquareID(square);
                p->setParentItem(m_darkSquares[square]);
                square++;
                break;
            }
        }
    }
}
