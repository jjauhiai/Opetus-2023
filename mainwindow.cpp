#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QScrollBar>
#include <QComboBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Serial");

    mSerial = new QSerialPort(this);
    updateSerialPorts();

    mSerialScanTimer = new QTimer(this);
    mSerialScanTimer->setInterval(5000);
    mSerialScanTimer->start();

    connect(mSerialScanTimer, &QTimer::timeout,
            this, &MainWindow::updateSerialPorts);

    connect(ui->inputLineEdit, &QLineEdit::returnPressed,
            this, &MainWindow::on_sendPushButton_clicked);

    connect(mSerial, &QSerialPort::readyRead,
            this, &MainWindow::serialReadyRead);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateSerialPorts()
{
    mSerialPorts = QSerialPortInfo::availablePorts();

    ui->serialComboBox->clear();
    //ui->QComboBox->clear();
    for (QSerialPortInfo port : mSerialPorts) {
        ui->serialComboBox->addItem(port.portName(), port.systemLocation());
    }
}

void MainWindow::on_connectPushButton_clicked()
{
    ui->connectPushButton->setEnabled(false);
   QString serialName =  ui->serialComboBox->currentText();
   QString serialLoc  =  ui->serialComboBox->currentData().toString();

    if (mSerial->isOpen()) {
        qDebug() << "Serial already connected, disconnecting!";
        mSerial->close();
    }

    mSerial->setPortName(serialLoc);
    mSerial->setBaudRate(QSerialPort::Baud9600);
    mSerial->setDataBits(QSerialPort::Data8);
    mSerial->setParity(QSerialPort::NoParity);
    mSerial->setStopBits(QSerialPort::OneStop);
    mSerial->setFlowControl(QSerialPort::NoFlowControl);

    if(mSerial->open(QIODevice::ReadWrite)) {
        qDebug() << "SERIAL: OK!";
    } else {
        qDebug() << "SERIAL: ERROR!";
    }
    ui->connectPushButton->setEnabled(true);
}

void MainWindow::on_sendPushButton_clicked()
{
    if (mSerial->isOpen()) {

        QString str= ui->inputLineEdit->text();
        ui->inputLineEdit->clear();
        str.append("\r\n");
        mSerial->write(str.toLocal8Bit());
    } else {
        qDebug() << "Serial port not connected!";
    }
}

void MainWindow::serialReadyRead()
{
    QByteArray data = mSerial   ->readAll();
    QString str = QString(data);
    ui->outputTextBrowser->insertPlainText(str);
    QScrollBar *sb = ui->outputTextBrowser->verticalScrollBar();
    sb->setValue(sb->maximum());
}




/*

void MainWindow::on_serialComboBox_activated(int index)
{
    MainWindow::updateSerialPorts();
}
*/
