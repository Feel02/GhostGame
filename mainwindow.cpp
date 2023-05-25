#include "mainwindow.h"

void MainWindow::setupUI(){
    srand((unsigned)time(NULL));                            //for the random num
    QWidget *centralWidget = new QWidget(this);             //main widget
    setCentralWidget(centralWidget);

    QGridLayout *layout = new QGridLayout(centralWidget);   //for the main gridlayout(we don't use grid so much so don't care about that)
    QPalette pal = QPalette();                              //for background
    pal.setColor(QPalette::Window, Qt::black);
    centralWidget->setAutoFillBackground(true);
    centralWidget->setPalette(pal);

    player1 = new QLabel(this);                             //p1
    player1Label = new QLabel(this);                        //p1 vision area
    //player1->setStyleSheet("background-color: rgba(255, 0, 0, 0);");
    player1Label->setStyleSheet("background-color: rgba(195, 195, 195, 25);");
    //player1->setStyleSheet("QLabel{border-image:url(https://www.pngfind.com/pngs/m/436-4369822_50-x-50-pixel-art-hd-png-download.png)}");
    player1->setFixedSize(50, 50);
    player1Label->setFixedSize(150,150);

    QPixmap imageOne (":/img/src/images/goodBear5050.png");
    int w1 = player1->width();
    int h1 = player1->height();
    player1->setPixmap(imageOne.scaled(w1, h1, Qt::KeepAspectRatio));


    player2 = new QLabel(this);                             //p2
    player2Label = new QLabel(this);
    //player2->setStyleSheet("background-color: rgba(0, 0, 255, 0);");
    player2Label->setStyleSheet("background-color: rgba(195, 195, 195, 25);");
    player2->setFixedSize(50, 50);
    player2Label->setFixedSize(150,150);

    QPixmap imageTwo (":/img/src/images/enemyBear.png");
    int w2 = player2->width();
    int h2 = player2->height();
    player2->setPixmap(imageTwo.scaled(w2, h2, Qt::KeepAspectRatio));



    ghost = new QFrame(this);                               //ghost
    ghostLabel = new QLabel(this);
    ghost->setStyleSheet("background-color: green");
    ghost->setFixedSize(30, 30);


    QPixmap imageThree (":/img/src/images/ghost.png");
    int w3 = ghostLabel->width();
    int h3 = ghostLabel->height();
    ghostLabel->setPixmap(imageThree.scaled(w3, h3, Qt::KeepAspectRatio));

    layout->addWidget(ghost,2,0);
    layout->addWidget(player1,1,0);                         //first one is row, second one is coloumn
    layout->addWidget(player2,0,0);

    ghost->setVisible(false);                               //ghost is invisible
    ghostLabel->setVisible(false);
    restartGhost();                                         //randomly generates x and y
    ghost->move(whereIsGhost());                            //gives what is this x and y and puts ghost there
    ghostLabel->move(whereIsGhost());
    player1Label->move(QPoint(375,330));
    player2Label->move(QPoint(375,115));
}

void MainWindow::movePlayer(QLabel *player, int dx, int dy){                                                           //moveplayer

    QPoint newPos = player->pos() + QPoint(dx, dy);         //create the new position
                                                            //for checking the borders (for the players not the vision area)
    newPos.setX(qBound(0, newPos.x(), centralWidget()->width() - player->width()));
    newPos.setY(qBound(0, newPos.y(), centralWidget()->height() - player->height()));
    player->move(newPos);                                   //move the player to new position

                                                            //check if we are over the ghost
    if(newPos.x() + 40 >= ghost->pos().x() && newPos.x() - 40 <= ghost->pos().x() && newPos.y() + 40 >= ghost->pos().y() && newPos.y() - 40 <= ghost->pos().y()){
        QPoint hold1 = player1->pos();
        QPoint hold2 = player2->pos();
        ghost->setVisible(false);                           //make the ghost invisible
        ghostLabel->setVisible(false);
        restartGhost();                                     //and move to ghost somewhere random
        player1->move(hold1);
        player1Label->move(hold1-QPoint(50,50));
        player2->move(hold2);
        player2Label->move(hold2-QPoint(50,50));
        ghost->move(whereIsGhost());
        ghostLabel->move(whereIsGhost());
    }
                                                            //check if we are near to ghost
    else if(newPos.x() + 80 >= ghost->pos().x() && newPos.x() - 80 <= ghost->pos().x() && newPos.y() + 80 >= ghost->pos().y() && newPos.y() - 80 <= ghost->pos().y()){
        QPoint hold1 = player1->pos();                      //this line holds the location of players so after ghost became
        QPoint hold2 = player2->pos();                      //visible players do not return back to middle(it works and this is the problem lol)
        ghost->setVisible(false);                            //make the ghost visible
        ghostLabel->setVisible(true);
        //ghost->hide();
        player1->move(hold1);                               //move the player back where it was
        player1Label->move(hold1-QPoint(50,50));            //move the vision area abck to player
        player2->move(hold2);                               //do the same for player2
        player2Label->move(hold2-QPoint(50,50));
        ghost->move(whereIsGhost());                        //and lastly be sure ghost is at the location where it should be
        ghostLabel->move(whereIsGhost());
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
void MainWindow::restartGhost(){                            //random the position
    int randomx = rand() % 850;                             //borders will be changed
    int randomy = rand() % 550;                             //probably
    xG = randomx;
    yG = randomy;
}
QPoint MainWindow::whereIsGhost(){                          //return the QPoint of ghost
    QPoint location = QPoint(xG,yG);
    return location;
}

