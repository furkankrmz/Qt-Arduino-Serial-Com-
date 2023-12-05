#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    //setup qserialport
    arduino = new QSerialPort;
    arduino_is_available = false;
    arduino_port_name = "";

    //view ports on your system
    qDebug() << "Number of Ports: " << QSerialPortInfo::availablePorts().length();
    foreach (const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
        if(serialPortInfo.hasVendorIdentifier() && serialPortInfo.hasProductIdentifier()){
            qDebug() << "VendorID: " <<serialPortInfo.vendorIdentifier();
            qDebug() << "ProductID: " << serialPortInfo.productIdentifier();
        }
    }
    foreach (const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
        if(serialPortInfo.hasVendorIdentifier() && serialPortInfo.hasProductIdentifier()){
            if(serialPortInfo.vendorIdentifier() == arduino_uno_vendorID){
                if(serialPortInfo.productIdentifier() == arduino_uno_productID){
                    arduino_port_name = serialPortInfo.portName();
                    arduino_is_available = true;
                    qDebug() << "Port Available!";
                }
            }

        }
    }
    if(arduino_is_available)
    {
        arduino->setPortName(arduino_port_name);
        arduino->open(QSerialPort::WriteOnly|QSerialPort::ReadOnly);
        arduino->setBaudRate(QSerialPort::Baud9600);
        arduino->setDataBits(QSerialPort::Data8);
        arduino->setParity(QSerialPort::NoParity);
        arduino->setStopBits(QSerialPort::OneStop);
        arduino->setFlowControl(QSerialPort::NoFlowControl);
        connect(arduino, &QSerialPort::readyRead, this, &Dialog::readSensorValue);
    }
    else{
        QMessageBox::warning(this,"Port Error!","Couldn't find arduino");
    }
}

Dialog::~Dialog()
{
    if(arduino->isOpen()){
        qDebug() << "closing port";
        arduino->close();
    }
    delete ui;
}

void Dialog::on_degree45Button_clicked()
{
    servoSetting = "180";
    updateServo(servoSetting);
    readSensorValue();
}



void Dialog::updateServo(QString command){
    if(arduino->isWritable()){
        qDebug() << command .toStdString().c_str();
        arduino->write(command.toStdString().c_str());
    }
    else
        qDebug() << "Could not write to serial";
}

void Dialog::readSensorValue(){
    if(arduino->isReadable()){
        QByteArray data = arduino->readAll();
        QString receivedData = QString(data);
        qDebug() << "Received data: "<< receivedData;
    }
    else
        qDebug() << "Couldn't read from serial";


}
