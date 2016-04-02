#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "socketwrapper.h"

enum WINDOW_VIEW{
    ROOMS_VIEW
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

Q_SIGNALS:
    void roomJoin(QString, QString);

private Q_SLOTS:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QWidget *curView;
    SocketWrapper *socket;
    void setView(WINDOW_VIEW view);
};

#endif // MAINWINDOW_H
