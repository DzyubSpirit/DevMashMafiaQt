#ifndef ROOMJOINVIEW_H
#define ROOMJOINVIEW_H

#include <QWidget>
#include <QJsonArray>

#include "socketwrapper.h"

namespace Ui {
    class RoomJoinView;
}

class RoomJoinView : public QWidget
{
    Q_OBJECT

private:
    Ui::RoomJoinView *ui;
    SocketWrapper *socket;

public:
    explicit RoomJoinView(QWidget *parent = 0, SocketWrapper *socket = 0);

Q_SIGNALS:
    void roomJoin(QString, int);
    void createRoom(QString, int);

public Q_SLOTS:
    void roomJoined();
    void players(QJsonArray players);

private Q_SLOTS:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
};

#endif // ROOMJOINVIEW_H
