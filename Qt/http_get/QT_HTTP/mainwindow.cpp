#include "mainwindow.h"
#include "ui_mainwindow.h"
QNetworkReply *reply;
QNetworkAccessManager *manager;
QNetworkAccessManager *postManager;
QNetworkAccessManager *putManager;
QByteArray response_data;


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

void MainWindow::addBookSlot (QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<response_data;
    reply->deleteLater();
    postManager->deleteLater();
}

void MainWindow::updateBookSlot (QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<response_data;
    reply->deleteLater();
    putManager->deleteLater();
}

void MainWindow::on_btnAddBook_clicked()
{
    QJsonObject jsonObj;
    jsonObj.insert("name","Uusi kirja");
    jsonObj.insert("author","Matti Mainio");
    jsonObj.insert("isbn","123-456-789");

    QString site_url="http://localhost:3000/book";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    //WEBTOKEN ALKU
    QByteArray myToken="Bearer xRstgr...";
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    //WEBTOKEN LOPPU

    postManager = new QNetworkAccessManager(this);
    connect(postManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(addBookSlot(QNetworkReply*)));

    reply = postManager->post(request, QJsonDocument(jsonObj).toJson());
}


void MainWindow::on_btnUpdateBook_clicked()
{
    QJsonObject jsonObj;
    jsonObj.insert("name","Breakfast of Champions");
    jsonObj.insert("author","Kurt Vonnegut");
    jsonObj.insert("isbn","222-222-222-222-g");

    QString site_url="http://localhost:3000/book/15";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    //WEBTOKEN ALKU
    QByteArray myToken="Bearer xRstgr...";
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    //WEBTOKEN LOPPU

    putManager = new QNetworkAccessManager(this);
    connect(putManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(updateBookSlot(QNetworkReply*)));

    reply = putManager->put(request, QJsonDocument(jsonObj).toJson());
}

