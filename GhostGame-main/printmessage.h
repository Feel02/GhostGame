#ifndef PRINTMESSAGE_H
#define PRINTMESSAGE_H

#include <string>
#include <iostream>
#include <QLabel>

/*
 * Whitout typecayting
 void printMessage(QLabel* label, const std::string& message = "GAME OVER") {
    label->setText(QString::fromStdString(message));
}
*/

QString printMessage(const std::string& message = "GAME OVER") {

    return QString::fromStdString(message);
}


#endif // PRINTMESSAGE_H
