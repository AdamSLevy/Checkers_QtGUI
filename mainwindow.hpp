#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QMessageBox>

#include "checkerboardgui.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void handleWin(bool winner);
    void handleTurn(bool turn);


private:
    Ui::MainWindow *ui;

    QGraphicsScene * scene;
    CheckerBoardGUI * board;
};

#endif // MAINWINDOW_H
