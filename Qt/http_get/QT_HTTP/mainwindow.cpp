#include "mainwindow.h"
#include "ui_mainwindow.h"
QNetworkReply *reply;
QNetworkAccessManager *manager;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnShowBooks_clicked()
{
    QString site_url="http://localhost:3000/book";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished (QNetworkReply*)),this, SLOT(getBookSlot(QNetworkReply*)));
    reply = manager->get(request);
}

void MainWindow::getBookSlot (QNetworkReply *reply)
{
    QByteArray response_data=reply->readAll();
    qDebug()<<"DATA : "+response_data;
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
    QString book;
    foreach (const QJsonValue &value, json_array) {
        QJsonObject json_obj = value.toObject();
        book+=QString::number(json_obj["id_book"].toInt())+", "+json_obj["name"].toString()+", "+json_obj["author"].toString()+"\r";
    }

    ui->textBooks->setText(book);

    reply->deleteLater();
    manager->deleteLater();
}
