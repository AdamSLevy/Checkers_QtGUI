#ifndef CHECKERBOARD_H
#define CHECKERBOARD_H

#include <QGraphicsObject>

#include "darksquare.h"
#include "lightsquare.hpp"


class CheckerBoard : public QGraphicsObject
{
public:
    CheckerBoard();
    DarkSquare dark_squares[32];

signals:

public slots:
};

#endif // CHECKERBOARD_H
