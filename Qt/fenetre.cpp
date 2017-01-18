#include "fenetre.h"
#include "ui_fenetre.h"
#include <QtSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QObject>
#include <QDialog>
#include <iostream>

Fenetre::Fenetre(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Fenetre), s_tmp(),s_humi(),scene_humi(&s_humi),scene_tmp(&s_tmp)
{
    ui->setupUi(this);
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
        *
        * Le code suivant est a lancer pour chaque nouveau arduino connecté ... remplir les données dans le fenetre.h
        *
        *
        *
        /
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

       }else{
           qDebug() << "Couldn't find the correct port for the arduino.\n";
       }

       //Les connects:
       QObject::connect(ui->bouton_temperature,SIGNAL(clicked(bool)),this,SLOT(afficher_tmp()));
       QObject::connect(ui->bouton_humiditee,SIGNAL(clicked(bool)),this,SLOT(afficher_humi()));
}
void Fenetre::afficher_tmp(){
    //Affichage graphique temperature:
    ui->global->addWidget(&scene_tmp,50,0);
}
void Fenetre::afficher_humi(){
    //Affichage graphique humiditee:
    ui->global->addWidget(&scene_humi,60,0);
}

void  Fenetre::readSerial(){
    /*
       * readyRead() doesn't guarantee that the entire message will be received all at once.
       * The message can arrive split into parts.  Need to buffer the serial data and then parse for the temperature value.
       *
       */
      serialData = arduino->readAll();
      serialBuffer = serialBuffer + QString::fromStdString(serialData.toStdString());
      serialData.clear();
      /*L'arduino envoie les données sous la forme:
       * DH:Valeur_humiditeeT:Valeur_temperature
       *
       * On split donc pour recuperer ces donnees*/
      QStringList buffer_split = serialBuffer.split("D");
      QString info=buffer_split[buffer_split.size()-1];
      QStringList info_split;
      if(info.split("H:").size()>1)
          info_split=info.split("H:")[1].split("T:");

      if(info_split.size()>1){
          std::cout<<"Humiditee: "<<info_split[0].toStdString()<<std::endl;
          std::cout<<"Temperature: "<<info_split[1].toStdString()<<std::endl;
          humiditee=info_split[0];
          temperature=info_split[1];

          //On ajoute la temperature et l'humiditee aux graphs:
          s_tmp.change_rect((int)temperature.toDouble());
          s_humi.change_rect((int)humiditee.toDouble());

          //On change la temperature et l'humiditee sur la fenetre:
          ui->lcd_temperature->display(temperature);
          ui->lcd_humiditee->display(humiditee);

          scene_humi.update();
          scene_tmp.update();

      }
}

Fenetre::~Fenetre()
{
    delete ui;
}
