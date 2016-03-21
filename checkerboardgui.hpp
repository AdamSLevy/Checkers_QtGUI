#ifndef CHECKERBOARD_H
#define CHECKERBOARD_H

#include <QGraphicsObject>
#include <QVector>

#include "darksquare.hpp"
#include "piece.hpp"
#include "checkers/checkerboard.hpp"

class CheckerBoardGUI : public QGraphicsObject
{
    public:
        CheckerBoardGUI(QGraphicsItem *parent = 0);

        QRectF boundingRect() const;
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    signals:

    public slots:
        void handleSquareSelected(size_t selectedSquare);
        void handlePieceSelected(size_t selected);
        void deselectAll();

    private:
        QVector<DarkSquare *>  dark_squares;

        QVector<Piece *> red_pieces;
        QVector<Piece *> blk_pieces;

        QPointF position(size_t i);

        size_t m_selectedPiece;

        CheckerBoard m_cb;

};

#endif // CHECKERBOARD_H
