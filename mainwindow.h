/*#ifndef MAINWINDOW_H
#define MAINWINDOW_H
*/

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_connectPushButton_clicked();

    void on_sendPushButton_clicked();
    void serialReadyRead();

    //void on_comboBox_activated(int index);

    //void on_serialComboBox_currentTextChanged(const QString &arg1);

    //void on_serialComboBox_activated(int index);

private:
    Ui::MainWindow *ui;

    QSerialPort *mSerial;
    QList<QSerialPortInfo> mSerialPorts;
    QTimer *mSerialScanTimer;

    void updateSerialPorts();
};
//#endif // MAINWINDOW_H
