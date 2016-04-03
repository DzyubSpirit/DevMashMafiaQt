#ifndef ROOMVIEW_H
#define ROOMVIEW_H

#include <QWidget>
#include <QJsonArray>

#include "socketwrapper.h"

namespace Ui {
class RoomView;
}

class RoomView : public QWidget
{
    Q_OBJECT

public:
    explicit RoomView(QWidget *parent = 0, SocketWrapper *socket = 0);
    ~RoomView();

private:
    Ui::RoomView *ui;
    SocketWrapper *socket;

Q_SIGNALS:
    void getWaitingPlayers();

public Q_SLOTS:
    void players(QJsonArray players);
};

#endif // ROOMVIEW_H
