#include "mainwindow.h"
#include "printmessage.h"
#include <QDebug>
#include <string>
#include <QFile>
#include <QTextStream>
#include <QPlainTextEdit>

void MainWindow::setupUI(){

    flag = false;
    pointp1 = 0;
    pointp2 = 0;
    ishouldnotdothat = true;

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
    player1Label->setStyleSheet("background-color: rgba(195, 195, 195, 25);border-radius: 50px;");
    player1->setFixedSize(50, 50);
    player1Label->setFixedSize(150,150);

    QPixmap imageOne (":/img/src/images/goodBear5050.png");
    int w1 = player1->width();
    int h1 = player1->height();
    player1->setPixmap(imageOne.scaled(w1, h1, Qt::KeepAspectRatio));


    player2 = new QLabel(this);                             //p2
    player2Label = new QLabel(this);
    player2Label->setStyleSheet("background-color: rgba(195, 195, 195, 25);border-radius: 50px;");
    player2->setFixedSize(50, 50);
    player2Label->setFixedSize(150,150);

    QPixmap imageTwo (":/img/src/images/enemyBear.png");
    int w2 = player2->width();
    int h2 = player2->height();
    player2->setPixmap(imageTwo.scaled(w2, h2, Qt::KeepAspectRatio));

    ghostLabel = new QLabel(this);
    ghostLabel->setFixedSize(30,30);

    QPixmap imageThree (":/img/src/images/ghost.png");
    int w3 = ghostLabel->width();
    int h3 = ghostLabel->height();
    ghostLabel->setPixmap(imageThree.scaled(w3, h3, Qt::KeepAspectRatio));

    if(startFlag==false){
        player1Label->setVisible(false);
        player2Label->setVisible(false);
        startScreen();
    }

    layout->addWidget(player1,1,0);                         //first one is row, second one is coloumn
    layout->addWidget(player2,0,0);

    ghostLabel->setVisible(false);
    restartGhost();                                         //randomly generates x and y
    ghostLabel->move(whereIsGhost());
    player1Label->move(QPoint(375,330));
    player2Label->move(QPoint(375,115));

    player1Label->setVisible(true);
    player2Label->setVisible(true);

}

void MainWindow::movePlayer(QLabel *player, int dx, int dy){                                                           //moveplayer

    QPoint newPos = player->pos() + QPoint(dx, dy);         //create the new position
        //for checking the borders (for the players not the vision area)
    newPos.setX(qBound(0, newPos.x(), centralWidget()->width() - player->width()));
    newPos.setY(qBound(0, newPos.y(), centralWidget()->height() - player->height()));
    player->move(newPos);                                   //move the player to new position

    //check if we are over the ghost
    if(newPos.x() + 50 >= ghostLabel->pos().x() && newPos.x() - 30 <= ghostLabel->pos().x() && newPos.y() + 50 >= ghostLabel->pos().y() && newPos.y() - 30 <= ghostLabel->pos().y()){
        QPoint hold1 = player1->pos();
        QPoint hold2 = player2->pos();
        restartGhost();                                     //and move to ghost somewhere random
        ghostLabel->setVisible(false);
        player1->move(hold1);
        player1Label->move(hold1-QPoint(50,50));
        player2->move(hold2);
        player2Label->move(hold2-QPoint(50,50));
        ghostLabel->move(whereIsGhost());
        if(player == player1)
            pointp1++;
        else
            pointp2++;
    }
    //check if we are near to ghost
    else if(newPos.x() + 90 >= ghostLabel->pos().x() && newPos.x() - 70 <= ghostLabel->pos().x() && newPos.y() + 90 >= ghostLabel->pos().y() && newPos.y() - 70 <= ghostLabel->pos().y()){
        QPoint hold1 = player1->pos();                      //this line holds the location of players so after ghost became
        QPoint hold2 = player2->pos();                      //visible players do not return back to middle(it works and this is the problem lol)
        ghostLabel->setVisible(ishouldnotdothat);
        player1->move(hold1);                               //move the player back where it was
        player1Label->move(hold1-QPoint(50,50));            //move the vision area abck to player
        player2->move(hold2);                               //do the same for player2
        player2Label->move(hold2-QPoint(50,50));
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

    leftScoreBoard->setText(QString("Andy: " + (QString::number(pointp2))));
    rightScoreBoard->setText(QString("Wendy: " + (QString::number(pointp1))));
    checkGameOver();
}

void MainWindow::restartGhost(){                            //random the position
    int* randomx;                                           //Explicit Heap-Dynamic Variables
    randomx = new int(rand() % 850);
    int* randomy;
    randomy = new int(rand() % 550);
    xG = *randomx;
    yG = *randomy;
    delete randomx;
    delete randomy;
    ghostLabel->move(xG,yG);
}

QPoint MainWindow::whereIsGhost(){                          //return the QPoint of ghost
    QPoint location = QPoint(xG,yG);
    return location;
}

void MainWindow::gameOver(int input){

    printmessage* mes = new printmessage();

    flag = true;
    ishouldnotdothat = false;
    QLabel* panel = new QLabel();
    panel->setMinimumSize(900,600);
    panel->setStyleSheet("background-color: rgba(120, 120, 120, 55);");
    layout()->addWidget(panel);
    panel->move(0,0);
    //panel->setFocusPolicy(Qt::NoFocus);

    QLabel* panel2 = new QLabel();
    panel2->setMaximumSize(300,400);
    panel2->setStyleSheet("background-color: transparent;");
    layout()->addWidget(panel2);
    panel2->move(300,100);

    QLabel* txt = new QLabel();
    txt->setMaximumSize(300,50);
    txt->setStyleSheet("QLabel { background-color : transparent ; color : black;}");
    txt->setFont(QFont("Arial Black",20));

    if(input == 1){

        //printMessage(txt, "Wendy has won");  (Whitout typecayting)
        txt->setText(static_cast<QString>(mes->printMessage("Wendy has won")));
        QPixmap wendyImage(":/img/src/images/wonWendy.png");
        wendyImage = wendyImage.scaled(panel->size(), Qt::KeepAspectRatio);
        panel->setStyleSheet("background-image: url(:/img/src/images/wonWendy.png);");

    }
    else{
        //printMessage(txt, "Andy has won"); (Whitout typecayting)
        txt->setText(static_cast<QString>(mes->printMessage("Andy has won")));
        QPixmap andyImage(":/img/src/images/wonAndy.png");
        andyImage = andyImage.scaled(panel->size(), Qt::KeepAspectRatio);
        panel->setStyleSheet("background-image: url(:/img/src/images/wonAndy.png);");

    }
    layout()->addWidget(txt);
    txt->move(300,50);

    quitLabel = new QWidget(this);
    quitLabel->setFixedSize(150,60);
    QPushButton *quit = new QPushButton(quitLabel);
    quit->setStyleSheet("color : darkblue; font-size: 25px;height: 60px;width: 150px;font: bold;");
    quit->setText(QString("Quit"));
    quit->setFocusPolicy(Qt::NoFocus);
    connect(quit,SIGNAL(clicked()),this,SLOT(close()));

    againLabel = new QWidget(this);
    againLabel->setFixedSize(150,60);
    QPushButton *playAgain = new QPushButton(againLabel);
    playAgain->setStyleSheet("color : darkblue; font-size: 25px;height: 60px;width: 150px;font: bold;");
    playAgain->setText(QString("Play Again"));
    playAgain->setFocusPolicy(Qt::NoFocus);
    connect(playAgain,SIGNAL(clicked()),this,SLOT(restartGamee()));

    layout()->addWidget(quitLabel);
    layout()->addWidget(againLabel);
    quitLabel->move(375,300);
    againLabel->move(375,200);



}
void MainWindow::checkGameOver(){
    if(flag == false){
        if(pointp1 >= 3)
            gameOver(1);
        else if(pointp2 >= 3)
            gameOver(2);
    }

}

void MainWindow::restartGamee(){
    //exception handling
    try {
        setupUI();
        restartScoreTable();
    } catch (const std::exception& e) {
        // Handle the exception
        qDebug() << "An exception occurred: " << e.what();
    }
}

void MainWindow::startScreen(){

    startButtonThing = new QWidget(this);
    startButtonThing->setFixedSize(200,40);
    startButtonThing->move(350,470);
    startScreenPic = new QLabel();
    startScreenPic->setFixedSize(900,600);
    QPixmap imageFour (":/img/src/images/forest.jpg");
    startScreenPic->setPixmap(imageFour.scaled(950, 600, Qt::KeepAspectRatio));
    start = new QPushButton(startButtonThing);
    start->setStyleSheet("color : darkblue; font-size: 20px;height: 35px;width: 200px;font: bold;");
    start->setText(QString("START"));
    start->setFocusPolicy(Qt::NoFocus);
    layout()->addWidget(startScreenPic);
    layout()->addWidget(startButtonThing);
    startScreenPic->raise();
    startButtonThing->raise();
    connect(start,SIGNAL(clicked()),this,SLOT(changeStartFlag()));


    textEdit = new QPlainTextEdit(this);
    textEdit->setFixedSize(650, 380);
    //txtbox location
    textEdit->move(130, 65);
    textEdit->setReadOnly(true); // Set the read-only property to true
    textEdit->setFocusPolicy(Qt::NoFocus);

    QFont font("Arial Black", 10); // Specify the desired font family and size
    textEdit->setFont(font);

    // Set the background color to transparent using style sheet
    //textEdit->setStyleSheet("background-color: transparent;");

    // Set a semi-transparent white background using RGBA color value
    textEdit->setStyleSheet("background-color: rgba(255, 255, 255, 50);");

    QString filePath = ":/story/theLore.txt";
    QFile file(filePath);

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QString content = in.readAll();
        textEdit->setPlainText(content);
        file.close();
    } else {
        qDebug() << "The file could not be opened!";
    }


    //connect(start, SIGNAL(clicked()), this, SLOT(changeStartFlag()));
    connect(start, SIGNAL(clicked()), this, SLOT(closeFile()));

}

void MainWindow::changeStartFlag(){
    startFlag=true;
    start->setVisible(false);
    startScreenPic->setVisible(false);
    restartScoreTable();
    textEdit->setVisible(false);
}

void MainWindow::restartScoreTable(){
    leftScoreBoard = new QLabel();
    leftScoreBoard->setMaximumSize(150,80);
    leftScoreBoard->setStyleSheet("QLabel { color : white;}");
    leftScoreBoard->setFont(QFont("Times",16));
    leftScoreBoard->setText(QString("Andy: " + QString::number(pointp1)));
    layout()->addWidget(leftScoreBoard);
    leftScoreBoard->move(20,0);

    rightScoreBoard = new QLabel();
    rightScoreBoard->setMaximumSize(150,80);
    rightScoreBoard->setStyleSheet("QLabel { color : white;}");
    rightScoreBoard->setFont(QFont("Times",16));
    rightScoreBoard->setText(QString("Wendy: " + QString::number(pointp2)));
    layout()->addWidget(rightScoreBoard);
    rightScoreBoard->move(750,0);
}

void MainWindow::closeFile() {
    QFile file(":/story/theLore.txt");  // Define the file variable
    if (file.isOpen()) {                // Close if file is open
        file.close();
    }
}




