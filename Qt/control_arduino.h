#ifndef CONTROL_ARDUINO
#define CONTROL_ARDUINO

#include <QtSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QObject>
#include <QDialog>

class Control_Arduino:public QDialog{
    Q_OBJECT
public:
    Control_Arduino();

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


private:
    QSerialPort *arduino;
    static const quint16 arduino_uno_vendor_id = 9025;
    static const quint16 arduino_uno_product_id = 579;
    QByteArray serialData;
    QString serialBuffer;
    QString parsed_data;
    double temperature_value;
    QString temperature;
    QString humiditee;
};

#endif // CONTROL_ARDUINO

