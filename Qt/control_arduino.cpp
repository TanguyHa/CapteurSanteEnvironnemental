#include "control_arduino.h"
#include <QtSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QObject>
#include <QDialog>
#include <iostream>


Control_Arduino::Control_Arduino(){
    arduino = new QSerialPort(this);
       serialBuffer = "";
       parsed_data = "";
       temperature_value = 0.0;

       /*
        *  Testing code, prints the description, vendor id, and product id of all ports.
        *  Used it to determine the values for the arduino uno.
        *
        */
       /*
       qDebug() << "Number of ports: " << QSerialPortInfo::availablePorts().length() << "\n";
       foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
           qDebug() << "Description: " << serialPortInfo.description() << "\n";
           qDebug() << "Has vendor id?: " << serialPortInfo.hasVendorIdentifier() << "\n";
           qDebug() << "Vendor ID: " << serialPortInfo.vendorIdentifier() << "\n";
           qDebug() << "Has product id?: " << serialPortInfo.hasProductIdentifier() << "\n";
           qDebug() << "Product ID: " << serialPortInfo.productIdentifier() << "\n";
       }
        */

       /*
        *   Identify the port the arduino uno is on.
        */
       bool arduino_is_available = false;
       QString arduino_uno_port_name;
       //
       //  For each available serial port
       foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
           //  check if the serialport has both a product identifier and a vendor identifier
           if(serialPortInfo.hasProductIdentifier() && serialPortInfo.hasVendorIdentifier()){
               //  check if the product ID and the vendor ID match those of the arduino uno
               if((serialPortInfo.productIdentifier() == arduino_uno_product_id)
                       && (serialPortInfo.vendorIdentifier() == arduino_uno_vendor_id)){
                   arduino_is_available = true; //    arduino uno is available on this port
                   arduino_uno_port_name = serialPortInfo.portName();
               }
           }
       }

       /*
        *  Open and configure the arduino port if available
        */
       if(arduino_is_available){
           qDebug() << "Found the arduino port...\n";
           arduino->setPortName(arduino_uno_port_name);
           arduino->open(QSerialPort::ReadOnly);
           arduino->setBaudRate(QSerialPort::Baud9600);
           arduino->setDataBits(QSerialPort::Data8);
           arduino->setFlowControl(QSerialPort::NoFlowControl);
           arduino->setParity(QSerialPort::NoParity);
           arduino->setStopBits(QSerialPort::OneStop);
           QObject::connect(arduino, SIGNAL(readyRead()), this, SLOT(readSerial()));
          // serialData = arduino->readAll();
           //std::cout<<serialData.toStdString()<<std::endl;

       }else{
           qDebug() << "Couldn't find the correct port for the arduino.\n";
         //  QMessageBox::information(this, "Serial Port Error", "Couldn't open serial port to arduino.");
       }

}
void Control_Arduino::readSerial(){
    /*
       * readyRead() doesn't guarantee that the entire message will be received all at once.
       * The message can arrive split into parts.  Need to buffer the serial data and then parse for the temperature value.
       *
       */
      serialData = arduino->readAll();
      serialBuffer = serialBuffer + QString::fromStdString(serialData.toStdString());
      serialData.clear();
      std::cout<<"New message\n";
      QStringList buffer_split = serialBuffer.split("D"); //  split the serialBuffer string, parsing with ',' as the separator
      QString info=buffer_split[buffer_split.size()-1];
      QStringList info_split;
      if(info.split("H:").size()>1)
          info_split=info.split("H:")[1].split("T:");

      if(info_split.size()>1){
          std::cout<<"Humiditee: "<<info_split[0].toStdString()<<std::endl;
          std::cout<<"Temperature: "<<info_split[1].toStdString()<<std::endl;
          humiditee=info_split[0];
          temperature=info_split[1];

      }
}
Fenetre::~Fenetre
