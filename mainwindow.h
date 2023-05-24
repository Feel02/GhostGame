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
        setFixedSize(900, 600);
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

    void setupUI(){
        srand((unsigned)time(NULL));                            //for the random num
        QWidget *centralWidget = new QWidget(this);             //main widget
        setCentralWidget(centralWidget);

        QGridLayout *layout = new QGridLayout(centralWidget);   //for the main gridlayout(we don't use grid so much so don't care about that)
        QPalette pal = QPalette();                              //for background
        pal.setColor(QPalette::Window, Qt::black);
        centralWidget->setAutoFillBackground(true);
        centralWidget->setPalette(pal);

        player1 = new QFrame(this);                             //p1
        player1Label = new QLabel(this);                        //p1 vision area
        player1->setStyleSheet("background-color: red");
        player1Label->setStyleSheet("background-color: rgba(255, 0, 0, 40);");
        //player1->setStyleSheet("QLabel{border-image:url(https://www.pngfind.com/pngs/m/436-4369822_50-x-50-pixel-art-hd-png-download.png)}");
        player1->setFixedSize(50, 50);
        player1Label->setFixedSize(150,150);
        player1->setEnabled(false);                             //without that sometimes gives size error idk what this does
        //player1Label->setEnabled(false);

        player2 = new QFrame(this);                             //p2
        player2Label = new QLabel(this);
        player2->setStyleSheet("background-color: blue");
        player2Label->setStyleSheet("background-color: rgba(0, 0, 255, 40);");
        player2->setFixedSize(50, 50);
        player2Label->setFixedSize(150,150);
        player2->setEnabled(false);

        ghost = new QFrame(this);                               //ghost
        ghost->setStyleSheet("background-color: green");
        ghost->setFixedSize(30, 30);

        layout->addWidget(ghost,0,0);
        layout->addWidget(player1,1,0);                         //first one is row, second one is coloumn
        layout->addWidget(player2,2,0);

        ghost->setVisible(false);                               //ghost is invisible
        restartGhost();                                       //randomly generates x and y
        ghost->move(whereIsGhost());                           //gives what is this x and y and puts ghost there
        player1->move(player1->pos());                          //-------------------------------------------
        player1Label->move(player1->pos()-QPoint(50,50));       //this lines has error in it, it should move the vision area over the players
        player2Label->move(player2->pos()-QPoint(50,50));       //but it does until one of the players moves
                                                                //-------------------------------------------
    }

    void movePlayer(QFrame *player, int dx, int dy){            //moveplayer

        QPoint newPos = player->pos() + QPoint(dx, dy);         //create the new position
                                                                //for checking the borders (for the players not the vision area)
        newPos.setX(qBound(0, newPos.x(), centralWidget()->width() - player->width()));
        newPos.setY(qBound(0, newPos.y(), centralWidget()->height() - player->height()));
        player->move(newPos);                                   //move the player to new position

                                                                //check if we are over the ghost
        if(newPos.x() + 40 >= ghost->pos().x() && newPos.x() - 40 <= ghost->pos().x() && newPos.y() + 40 >= ghost->pos().y() && newPos.y() - 40 <= ghost->pos().y()){
            QPoint hold1 = player1->pos();                      //this 2 line for after catching the ghost not changing the players location
            QPoint hold2 = player2->pos();                      //but there is a error so players return to the middle after catching the ghost
            ghost->setVisible(false);                           //make the ghost invisible
            restartGhost();                                     //and move to ghost somewhere random
            ghost->move(whereIsGhost());
            player1->move(hold1);                               //for moving player to last location back(bug)
            player1Label->move(player1->pos()-QPoint(50,50));   //for moving vision size to player back(bug)
            player2->move(hold2);                               //again bug
            player2Label->move(player2->pos()-QPoint(50,50));   //again bug
        }
                                                                //check if we are near to ghost
        else if(newPos.x() + 80 >= ghost->pos().x() && newPos.x() - 80 <= ghost->pos().x() && newPos.y() + 80 >= ghost->pos().y() && newPos.y() - 80 <= ghost->pos().y()){
            QPoint hold1 = player1->pos();                      //this line holds the location of players so after ghost became
            QPoint hold2 = player2->pos();                      //visible players do not return back to middle(it works and this is the problem lol)
            ghost->setVisible(true);                            //make the ghost visible
            //ghost->hide();
            player1->move(hold1);                               //move the player back where it was
            player1Label->move(hold1-QPoint(50,50));            //move the vision area abck to player
            player2->move(hold2);                               //do the same for player2
            player2Label->move(hold2-QPoint(50,50));
            ghost->move(whereIsGhost());                        //and lastly be sure ghost is at the location where it should be
        }

                                                                //add the Player's location to vector
        if (player == player1){
            player1Label->move(newPos-QPoint(50,50));           //be sure the vision areas are with players to
            player2Label->move(player2->pos()-QPoint(50,50));
            player1Positions.push_back(newPos);
        }
        else if (player == player2){
            player2Label->move(newPos-QPoint(50,50));
            player1Label->move(player1->pos()-QPoint(50,50));
            player2Positions.push_back(newPos);
        }
    }

    void restartGhost(){                                        //random the position
        int randomx = rand() % 850;                             //borders will be changed
        int randomy = rand() % 550;                             //probably
        xG = randomx;
        yG = randomy;
    }

    QPoint whereIsGhost(){                                      //return the QPoint of ghost
        QPoint location = QPoint(xG,yG);
        return location;
    }
};
#endif // MAINWINDOW_H
