#ifndef ROOMVIEW_H
#define ROOMVIEW_H

#include <QWidget>

namespace Ui {
class RoomView;
}

class RoomView : public QWidget
{
    Q_OBJECT

public:
    explicit RoomView(QWidget *parent = 0);
    ~RoomView();

private:
    Ui::RoomView *ui;
};

#endif // ROOMVIEW_H