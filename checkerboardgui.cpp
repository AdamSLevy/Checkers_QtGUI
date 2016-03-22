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
        BitBoard bb = m_cb.m_bb;
        size_t piecePOS = m_pieces[m_selectedPiece]->getSquareID();
        if(bb.turn == BLK){
            bb.blk_pos = (bb.blk_pos & ~POS_MASK[piecePOS]) | POS_MASK[selectedSquare];
            bb.turn = RED;
        } else{
            bb.red_pos = (bb.red_pos & ~POS_MASK[piecePOS]) | POS_MASK[selectedSquare];
            print_board(bb.red_pos);
            bb.turn = BLK;
        }

        setBoard(bb);
//        PieceG * p = m_pieces[m_selectedPiece];
//        p->setSquareID(selectedSquare);
//        p->setParentItem(m_darkSquares[selectedSquare]);
    }
    deselectAll();
}

void CheckerBoardGUI::handlePieceSelected(size_t selectedPiece)
{
    deselectAll();
    m_selectedPiece = selectedPiece;
    if(m_selectedPiece < m_pieces.size()){
        // Open valid squares
        bool turn = m_cb.m_bb.turn;

        uint32_t occupied = (m_cb.m_bb.red_pos | m_cb.m_bb.blk_pos);
        uint32_t empty = ~occupied;

        size_t squareID = m_pieces[m_selectedPiece]->getSquareID();
        uint32_t pos = POS_MASK[squareID];
        uint32_t available = FORWD(turn, pos) & empty;
        for(int square = 0; square < 32; square++){
            m_darkSquares[square]->setOpen(POS_MASK[square] & available);
        }
    }
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
    closeAllSquares();
}

void CheckerBoardGUI::closeAllSquares()
{
    for(DarkSquare * ds : m_darkSquares){
        ds->setOpen(false);
    }
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
    print_bb(bb);

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
    int i = 0;
    for(; i < m_pieces.size()/2; i++){
        PieceG * p = m_pieces[i];
        uint32_t board = bb.red_pos;

        if(square == 32){
            p->setParent(this);
            p->setVisible(false);
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
    square = 0;
    for(; i < m_pieces.size(); i++){
        PieceG * p = m_pieces[i];
        uint32_t board = bb.blk_pos;

        if(square == 32){
            p->setParent(this);
            p->setVisible(false);
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

