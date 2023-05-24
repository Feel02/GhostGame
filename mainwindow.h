#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <cstdlib>
#include <QtWidgets>
#include <QDebug>
#include <vector>
#include <qmath.h>
#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr)                       //some main stuff
        : QMainWindow(parent)
    {
        setupUI();
        //900,600
        setFixedSize(1200, 790);
    }

protected:
    void keyPressEvent(QKeyEvent *event) override{              //when pressed a key

        if (event->key() == Qt::Key_Up){                        //if pressed key is UpArrow
            movePlayer(player1, 0, -10);                        //(movePlayer is at the bottom of the code)
        }
        else if (event->key() == Qt::Key_W){
            movePlayer(player2, 0, -10);
        }
        else if (event->key() == Qt::Key_Down){
            movePlayer(player1, 0, 10);
        }
        else if (event->key() == Qt::Key_S){
           movePlayer(player2, 0, 10);
        }
        else if (event->key() == Qt::Key_Left){
            movePlayer(player1, -10, 0);
        }
        else if (event->key() == Qt::Key_A){
            movePlayer(player2, -10, 0);
        }
        else if (event->key() == Qt::Key_Right){
            movePlayer(player1, 10, 0);
        }
        else if (event->key() == Qt::Key_D){
            movePlayer(player2, 10, 0);
        }
    }

private:

    QLabel *player1Label;
    QLabel *player2Label;
    QFrame *player1;
    QFrame *player2;
    QFrame *ghost;

    int xG,yG;

    std::vector<QPoint> player1Positions;                       //Player 1's location vector
    std::vector<QPoint> player2Positions;                       //Player 2's location vector

    void setupUI();

    void movePlayer(QFrame *player, int dx, int dy);


    void restartGhost();

    QPoint whereIsGhost();
};
#endif // MAINWINDOW_H
