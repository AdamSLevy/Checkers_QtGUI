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

    m_cb.m_bb = from_string("rrrrrR_rR__R__B__rr____B__Bbbbbb", BLK);
    setBoard(m_cb.m_bb);
}

QRectF CheckerBoardGUI::boundingRect() const
{
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
        uint32_t play_pos;
        uint32_t oppo_pos;

        if (bb.turn == BLK){
            play_pos = bb.blk_pos;
            oppo_pos = bb.red_pos;
        } else{
            play_pos = bb.red_pos;
            oppo_pos = bb.blk_pos;
        }

        PieceG * p = m_pieces[m_selectedPiece];

        uint32_t piecePOS  = POS_MASK[p->getSquareID()];
        uint32_t squarePOS = POS_MASK[selectedSquare];
        uint32_t moveMask  = 0xffFFffFF;

        bool turn = bb.turn;
        bool isKing   = p->isKing();
        bool isJumper = piecePOS & get_jumpers(bb,isKing);

        // Move the piece
        play_pos = (play_pos & ~piecePOS) | squarePOS;
        if(isKing){
            bb.king_pos = (bb.king_pos & ~piecePOS) | squarePOS;
        }

        // Capture opponent piece
        if(isJumper){
            uint32_t captured = FORWD(turn, piecePOS) & BCKWD(turn, squarePOS);
            if(isKing){
                captured |= BCKWD(turn, piecePOS) & FORWD(turn, squarePOS);
            }
            print_board(captured);
            oppo_pos &= ~captured;
            moveMask = squarePOS;
        }

        // King me
        bool kinged = false;
        if(!isKing){
            kinged = squarePOS & KING_ME_ROW_MASK(turn);
            if(kinged){
                bb.king_pos |= squarePOS;
            }
        }

        // Apply to BitBoard
        if(bb.turn == BLK){
            bb.blk_pos = play_pos;
            bb.red_pos = oppo_pos;
        } else{
            bb.blk_pos = oppo_pos;
            bb.red_pos = play_pos;
        }
        // End the move
        if(isJumper){
            uint32_t jumpers = get_jumpers(bb, isKing);
        }
        if(!isJumper || kinged || !(get_jumpers(bb, isKing) & squarePOS)){
            turn = !turn;
            moveMask = 0xffFFffFF;
        }

        bb.turn = turn;

        // Update GUI
        setBoard(bb, moveMask);
    }
    deselectAll();
}

void CheckerBoardGUI::handlePieceSelected(size_t selectedPiece)
{
    deselectAll();
    m_selectedPiece = selectedPiece;
    if(m_selectedPiece < m_pieces.size()){
        PieceG * p = m_pieces[m_selectedPiece];
        bool isKing = p->isKing();
        BitBoard bb = m_cb.m_bb;
        uint32_t jump_loc = get_jump_locations(bb, isKing, POS_MASK[p->getSquareID()]);
        uint32_t available = 0;
        if(jump_loc){
            available = jump_loc;
        } else{
            available = get_move_locations(m_cb.m_bb, isKing, POS_MASK[p->getSquareID()]);
        }
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


void CheckerBoardGUI::setBoard(BitBoard bb, uint32_t moveMask)
{
    m_cb.m_bb = bb;

    print_bb(bb);

    uint32_t jumpers = get_jumpers(bb) | get_jumpers(bb, true);
    uint32_t movers = 0;
    if(jumpers){
        movers = jumpers;
    } else{
        movers = get_movers(bb) | get_movers(bb, true);
    }

    size_t square = 0;
    int i = 0;
    for(/*i*/; i < m_pieces.size()/2; i++){
        PieceG * p = m_pieces[i];
        uint32_t board = bb.red_pos;
        bool set = false;

        for(/*size_t square*/;square < 32; square++){
            uint32_t pos = POS_MASK[square];
            if(pos & board){
                p->setVisible(true);
                p->setSquareID(square);
                p->setParentItem(m_darkSquares[square]);
                p->setKing(pos & bb.king_pos);
                p->setMovable(pos & movers & moveMask);
                set = true;
                if(square < 32){
                    square++;
                }
                break;
            }
        }
        if(!set){
            p->setParent(this);
            p->setVisible(false);
        }
    }
    square = 0;
    for(; i < m_pieces.size(); i++){
        PieceG * p = m_pieces[i];
        uint32_t board = bb.blk_pos;
        bool set = false;

        for(/*size_t square*/;square < 32; square++){
            uint32_t pos = POS_MASK[square];
            if(pos & board){
                p->setVisible(true);
                p->setSquareID(square);
                p->setParentItem(m_darkSquares[square]);
                p->setKing(pos & bb.king_pos);
                p->setMovable(pos & movers & moveMask);
                set = true;
                if(square < 32){
                    square++;
                }
                break;
            }
        }
        if(!set){
            p->setParent(this);
            p->setVisible(false);
        }
    }
}

