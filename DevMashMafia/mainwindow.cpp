#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPushButton>
#include <QLabel>
#include <QLayout>
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    socket(new SocketWrapper(this))
{
    ui->setupUi(this);
    setView(ROOMS_VIEW);
    connect(this, SIGNAL(roomJoin(QString, QString)),
            socket, SLOT(roomJoin(QString,QString)));
}

void MainWindow::setView(WINDOW_VIEW view) {
    switch (view) {
        case ROOMS_VIEW: {
            curView = new QWidget(ui->centralWidget);
            curView->setGeometry(ui->centralWidget->geometry());
        }break;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    Q_EMIT roomJoin(ui->lineEdit->text(), ui->lineEdit_2->text());
}
