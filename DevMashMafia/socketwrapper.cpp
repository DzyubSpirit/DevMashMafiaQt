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

void SocketWrapper::httpReplyFinished(QNetworkReply *reply)
{
//    qDebug() << reply->readLine().toStdString().c_str();
    socketEvents = QJsonDocument::fromJson(reply->readLine()).object();
    socket::ptr sock =_io->socket();
    using std::placeholders::_1;
    using std::placeholders::_2;
    using std::placeholders::_3;
    using std::placeholders::_4;
    sock->on(socketEvents[JOINED_ROOM_EVENT].toString().toStdString()
            ,std::bind(&SocketWrapper::OnNewMessage,this,_1,_2,_3,_4));
}

void SocketWrapper::OnNewMessage(const string &name, const message::ptr &data, bool hasAck,
                                 message::list &ack_resp)
{
    qDebug() << "New socket message:";
    qDebug() << name.c_str();
    qDebug() << data->get_string().c_str();
    qDebug() << hasAck;
    qDebug() << ack_resp.to_array_message()->get_string().c_str();
}

void SocketWrapper::roomJoin(QString nickname, QString room_id)
{
    socket::ptr sock =_io->socket();
    QJsonObject params {
        {"nickname", nickname},
        {"room_id", room_id}
    };
    QByteArray bytes = QJsonDocument(params).toJson(QJsonDocument::Compact);
    std::string message(bytes.data(), bytes.length());
    sock->emit(socketEvents[JOIN_ROOM_EVENT].toString().toStdString(),
               message);
    qDebug() << message.c_str();
}
