#ifndef CHECKERBOARD_H
#define CHECKERBOARD_H

#include <QGraphicsObject>
#include <QVector>

#include "darksquare.hpp"
#include "pieceg.hpp"
#include "checkers/checkerboard.hpp"

class CheckerBoardGUI : public QGraphicsObject
{
    Q_OBJECT
    public:
        CheckerBoardGUI(QGraphicsItem *parent = 0);

        QRectF boundingRect() const;
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    signals:
        void win(bool winner);
        void turn(bool turn);

    public slots:
        void handleSquareSelected(size_t selectedSquare);
        void handlePieceSelected(size_t selected);
        void deselectAll();
        void closeAllSquares();
        void setBoard(BitBoard bb, uint32_t moveMask = 0xffFFffFF);
        void resetBoard();

    public:
        bool makeMove(BitBoard bb);

    private:
        QVector<DarkSquare *>  m_darkSquares;

        QVector<PieceG *> m_pieces;

        QPointF position(size_t i);

        size_t m_selectedPiece;

        BitBoard m_bb;
        vector<BitBoard> m_children;
};

#endif // CHECKERBOARD_H
