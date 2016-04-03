#include "socketwrapper.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QDebug>
#include <sio_socket.h>

SocketWrapper::SocketWrapper(QObject *parent) :
    QObject(parent),
    _io(new client())
{
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
      connect(manager, SIGNAL(finished(QNetworkReply*)),
              this, SLOT(httpReplyFinished(QNetworkReply*)));

    QString eventsUrl(MAIN_URL);
    eventsUrl.append("api/events");
    manager->get(QNetworkRequest(QUrl(eventsUrl)));

    using std::placeholders::_1;
    using std::placeholders::_2;
    using std::placeholders::_3;
    using std::placeholders::_4;
    _io->set_socket_open_listener(std::bind(&SocketWrapper::OnConnected,this,std::placeholders::_1));
    _io->connect(MAIN_URL);
}

void SocketWrapper::OnConnected(const string &nsp)
{
    qDebug() << "Socket has been connected";
}

#ifdef WIN32
#define BIND_EVENT(IO,EV,FN) \
    do{ \
        socket::event_listener_aux l = FN;\
        IO->on(EV,l);\
    } while(0)

#else
#define BIND_EVENT(IO,EV,FN) \
    IO->on(EV,FN)
#endif
void SocketWrapper::httpReplyFinished(QNetworkReply *reply)
{
//    qDebug() << reply->readLine().toStdString().c_str();
    socketEvents = QJsonDocument::fromJson(reply->readLine()).object();
    socketEventNames = QJsonObject();
    for (auto it = socketEvents.begin(); it != socketEvents.end(); it++) {
        socketEventNames[it.value().toString()] = it.key();
    }

    socket::ptr sock =_io->socket();
    using std::placeholders::_1;
    using std::placeholders::_2;
    using std::placeholders::_3;
    using std::placeholders::_4;
    BIND_EVENT(sock,getSocketEvent(JOINED_ROOM_EVENT),std::bind(&SocketWrapper::OnNewMessage,this,_1,_2,_3,_4));
    BIND_EVENT(sock,getSocketEvent(CREATED_ROOM_EVENT),std::bind(&SocketWrapper::OnNewMessage,this,_1,_2,_3,_4));
    BIND_EVENT(sock,getSocketEvent(PLAYERS_EVENT),std::bind(&SocketWrapper::OnNewMessage,this,_1,_2,_3,_4));
    BIND_EVENT(sock,getSocketEvent(ERR_EVENT),std::bind(&SocketWrapper::OnNewMessage,this,_1,_2,_3,_4));
}

void SocketWrapper::OnNewMessage(const string &name, const message::ptr &data, bool hasAck,
                                 message::list &ack_resp)
{
    QString eventName = socketEventNames[name.c_str()].toString();
    qDebug() << "\nNew socket message:";
    qDebug() << eventName;

    if (eventName == CREATED_ROOM_EVENT) {
    qDebug() << "created room handler";
        int room_id = data->get_int();
        curRoomId = room_id;
        Q_EMIT roomJoin(curNickname, room_id);
    } else if (eventName == JOINED_ROOM_EVENT) {
        qDebug() << "room joined handler";
        Q_EMIT roomJoined(curRoomId);
    } else if (eventName == PLAYERS_EVENT) {
        Q_EMIT players(QJsonDocument::fromJson(data->get_string().c_str()).array());
    } else if (eventName == ERR_EVENT) {
        qDebug() << "error handler";
        qDebug() << data->get_string().c_str();
    } else {
        qDebug() << "Other event";
    }
}

void SocketWrapper::roomJoin(QString nickname, int room_id)
{
    QJsonObject params {
        {"nickname", nickname},
        {"room_id", room_id}
    };
    curRoomId = room_id;
    sendEvent(QString(JOIN_ROOM_EVENT), params);
}

void SocketWrapper::createRoom(QString nickname, int players_count)
{
    QJsonObject params {
        {"players", players_count}
    };
    sendEvent(QString(CREATE_ROOM_EVENT), params);
    curNickname = nickname;
}

void SocketWrapper::getWaitingPlayers()
{
    QJsonObject params;
    sendEvent(QString(GET_WAITING_PLAYERS_EVENT), params);
}

void SocketWrapper::sendEvent(QString event, QJsonObject &params)
{
    socket::ptr sock =_io->socket();
    QByteArray bytes = QJsonDocument(params).toJson(QJsonDocument::Compact);
    std::string message(bytes.data(), bytes.length());
    sock->emit(getSocketEvent(event), message);
    qDebug() << "\nSend socket" << event << message.c_str();
}

std::string SocketWrapper::getSocketEvent(QString const& event)
{
    return socketEvents[event].toString().toStdString();
}
