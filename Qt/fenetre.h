#ifndef FENETRE_H
#define FENETRE_H

#include <QWidget>
#include <QObject>
#include <QtSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QGraphicsView>
#include "my_scene.h"

namespace Ui {
class Fenetre;
}

class Fenetre : public QWidget
{
    Q_OBJECT

public:
    explicit Fenetre(QWidget *parent = 0);
    ~Fenetre();
    inline QString getTemperature(){
        return temperature;
    }

    inline QString getHumidity(){
        return humiditee;
    }

signals:
    void tempchange();
private slots:
    void readSerial();
    void afficher_tmp();
    void afficher_humi();

private:

    My_Scene s_tmp;
    My_Scene s_humi;
    QGraphicsView scene_tmp;
    QGraphicsView scene_humi;
    QSerialPort *arduino;
    static const quint16 arduino_uno_vendor_id = 9025;  //INFO A REMPLIR POUR CHAQUE NOUVEL ARDUINO
    static const quint16 arduino_uno_product_id = 579;  //INFO A REMPLIR POUR CHAQUE NOUVEL ARDUINO
    QByteArray serialData;
    QString serialBuffer;
    QString parsed_data;
    double temperature_value;
    QString temperature;
    QString humiditee;


private:
    Ui::Fenetre *ui;
};

#endif // FENETRE_H
