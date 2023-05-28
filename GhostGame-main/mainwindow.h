#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <cstdlib>
#include <QtWidgets>
#include <QDebug>
#include <vector>
#include <qmath.h>
#include <QMainWindow>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QFont>
#include <QFile>
#include <QTextStream>
#include <QPlainTextEdit>


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    bool startFlag = false;

    MainWindow(QWidget *parent = nullptr)                       //some main stuff
        : QMainWindow(parent)
    {
        setupUI();
        setFixedSize(900, 600);
    }

public Q_SLOTS:
    void restartGamee();
    void changeStartFlag();
    void closeFile();

protected:
    void keyPressEvent(QKeyEvent *event) override{              //when pressed a key


        if(startFlag==true){
            if (event->key() == Qt::Key_Up){                        //if pressed key is UpArrow
                movePlayer(player1, 0, -20);
            }
            else if (event->key() == Qt::Key_W){
                movePlayer(player2, 0, -20);
            }
            else if (event->key() == Qt::Key_Down){
                movePlayer(player1, 0, 20);
            }
            else if (event->key() == Qt::Key_S){
                movePlayer(player2, 0, 20);
            }
            else if (event->key() == Qt::Key_Left){
                movePlayer(player1, -20, 0);
            }
            else if (event->key() == Qt::Key_A){
                movePlayer(player2, -20, 0);
            }
            else if (event->key() == Qt::Key_Right){
                movePlayer(player1, 20, 0);
            }
            else if (event->key() == Qt::Key_D){
                movePlayer(player2, 20, 0);
            }
        }

    }

private:

    QLabel *player1Label;
    QLabel *player2Label;
    QLabel *ghostLabel;
    QLabel *player1;
    QLabel *player2;
    QFrame *ghost;

    QWidget* quitLabel;
    QWidget* againLabel;
    QWidget* startButtonThing;
    QLabel *startScreenPic;
    QPushButton* start;

    QLabel* leftScoreBoard;
    QLabel* rightScoreBoard;

    bool flag = false;
    bool ishouldnotdothat = true;
    int xG,yG;
    int pointp1 = 0,pointp2 = 0;

    std::vector<QPoint> player1Positions;                       //Player 1's location vector
    std::vector<QPoint> player2Positions;                       //Player 2's location vector

    void setupUI();

    void movePlayer(QLabel *player, int dx, int dy);

    void restartGhost();

    QPoint whereIsGhost();

    void checkGameOver();

    void startScreen();

    void gameOver(int input);

    void restartScoreTable();

};
#endif // MAINWINDOW_H
