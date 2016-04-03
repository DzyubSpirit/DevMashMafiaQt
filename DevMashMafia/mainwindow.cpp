#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPushButton>
#include <QLabel>
#include <QLayout>
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>

#include "views/roomjoinview.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    socket(new SocketWrapper(this))
{
    ui->setupUi(this);
    setView(ROOM_JOIN_VIEW);
}

void MainWindow::setView(WINDOW_VIEW view) {
    switch (view) {
    case ROOM_JOIN_VIEW: {
        curView = new RoomJoinView(this, socket);
    } break;
    case ROOM_VIEW: {

    } break;
    default: {
        return;
    }
    }
    this->setCentralWidget(curView);
}

MainWindow::~MainWindow()
{
    delete ui;
}

