#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <sio_client.h>

enum WINDOW_VIEW{
    ROOMS_VIEW
};

namespace Ui {
class MainWindow;
}

using namespace sio;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QWidget *curView;
    std::unique_ptr<client> _io;
    void setView(WINDOW_VIEW view);
    void OnConnected(std::string const& nsp);
};

#endif // MAINWINDOW_H
