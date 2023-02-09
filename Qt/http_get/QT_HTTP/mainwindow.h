#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>

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
    void on_btnShowBooks_clicked();
private slots:
    void getBookSlot (QNetworkReply *);
    void addBookSlot (QNetworkReply *);
    void updateBookSlot (QNetworkReply *);
    void on_btnAddBook_clicked();

    void on_btnUpdateBook_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
