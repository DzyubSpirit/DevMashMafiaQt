#ifndef SOCKETWRAPPER_H
#define SOCKETWRAPPER_H

#define MAIN_URL "http://devmashmafia.herokuapp.com/"
#define JOINED_ROOM_EVENT "room joined"
#define JOIN_ROOM_EVENT "join room"

#include <QObject>
#include <QNetworkReply>
#include <QJsonObject>

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
    void OnConnected(std::string const& nsp);
    void OnNewMessage(std::string const& name,message::ptr const& data,bool hasAck,message::list &ack_resp);

Q_SIGNALS:

private Q_SLOTS:
    void httpReplyFinished(QNetworkReply*);
public Q_SLOTS:
    void roomJoin(QString, QString);
};

#endif // SOCKETWRAPPER_H
