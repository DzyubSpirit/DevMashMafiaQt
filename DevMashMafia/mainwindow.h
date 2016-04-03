#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QJsonArray>

#include "socketwrapper.h"

enum WINDOW_VIEW{
    ROOM_JOIN_VIEW,
    ROOM_VIEW
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private Q_SLOTS:

public Q_SLOTS:

private:
    Ui::MainWindow *ui;
    QWidget *curView;
    SocketWrapper *socket;
    void setView(WINDOW_VIEW view);
};

#endif // MAINWINDOW_H
