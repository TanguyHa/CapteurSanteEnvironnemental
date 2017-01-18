#include "fenetre.h"
#include <QApplication>
#include <QtSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include "control_arduino.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Fenetre w;
    w.show();
    return a.exec();
}
