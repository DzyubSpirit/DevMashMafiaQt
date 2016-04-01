#include "mainwindow.h"
#include "ui_mainwindow.h"

#define MAIN_URL std::string("http://devmashmafia.herokuapp.com/")

#include <QPushButton>
#include <QLabel>
#include <QLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _io(new client())
{
    ui->setupUi(this);
    using std::placeholders::_1;
    _io->set_socket_open_listener(std::bind(&MainWindow::OnConnected,this,std::placeholders::_1));
    _io->connect(MAIN_URL);
    setView(ROOMS_VIEW);
}

void MainWindow::setView(WINDOW_VIEW view) {
    switch (view) {
        case ROOMS_VIEW: {
            curView = new QWidget(ui->centralWidget);
            curView->setGeometry(ui->centralWidget->geometry());
            QLabel *roomsLabel = new QLabel(curView);
            roomsLabel->setText("Rooms list");

        }break;
    }
}

void MainWindow::OnConnected(const string &nsp) {

}

MainWindow::~MainWindow()
{
    delete ui;
}
