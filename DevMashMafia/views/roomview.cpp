#include "roomview.h"
#include "ui_roomview.h"

RoomView::RoomView(QWidget *parent, SocketWrapper *socket) :
    QWidget(parent),
    ui(new Ui::RoomView),
    socket(socket)
{
    ui->setupUi(this);
    connect(this, SIGNAL(getWaitingPlayers()),
            socket, SLOT(getWaitingPlayers()));
    connect(socket, SIGNAL(players(QJsonArray)),
            this, SLOT(players(QJsonArray)));
    Q_EMIT getWaitingPlayers();
}

void RoomView::players(QJsonArray players)
{
    ui->listWidget->clear();
    for (int i = 0; i < players.size(); i++) {
        ui->listWidget->addItem(players[i].toString());
    }
}

RoomView::~RoomView()
{
    delete ui;
}
