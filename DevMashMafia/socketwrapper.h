#ifndef SOCKETWRAPPER_H
#define SOCKETWRAPPER_H

#define MAIN_URL "http://devmashmafia.herokuapp.com/"
#define JOINED_ROOM_EVENT "room joined"
#define JOIN_ROOM_EVENT "join room"
#define CREATE_ROOM_EVENT "create room"
#define CREATED_ROOM_EVENT "room created"
#define ERR_EVENT "err"

#include <QObject>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonArray>

#include <sio_client.h>

using namespace sio;

class SocketWrapper : public QObject
{
    Q_OBJECT
public:
    explicit SocketWrapper(QObject *parent = 0);

private:
    std::unique_ptr<client> _io;
    QJsonObject socketEvents;
    QJsonObject socketEventNames;
    QString curNickname;
    int curRoomId;
    std::string getSocketEvent(QString const& event);
    void sendEvent(QString event, QJsonObject &params);
    void OnConnected(std::string const& nsp);
    void OnNewMessage(std::string const& name,message::ptr const& data,bool hasAck,message::list &ack_resp);

Q_SIGNALS:
    void roomJoined();
    void players(QJsonArray players);

private Q_SLOTS:
    void httpReplyFinished(QNetworkReply*);
public Q_SLOTS:
    void roomJoin(QString nickname, int room_id);
    void createRoom(QString nickname, int players_count);
};

#endif // SOCKETWRAPPER_H
