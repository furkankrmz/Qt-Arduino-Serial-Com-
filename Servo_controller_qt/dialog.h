#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QtWidgets>
QT_BEGIN_NAMESPACE
namespace Ui {
class Dialog;
}
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_degree180Button_clicked();
    void updateServo(QString command);
    void readSensorValue();

private:
    QString servoSetting;
    QSerialPort *arduino;
    static const quint16 arduino_uno_vendorID = 6790;
    static const quint16 arduino_uno_productID = 29987;
    QString arduino_port_name;
    bool arduino_is_available;
    Ui::Dialog *ui;
};
#endif // DIALOG_H
