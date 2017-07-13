#ifndef DATA_WIDGET_H
#define DATA_WIDGET_H

#include <QWidget>

namespace Ui {
class data_widget;
}

class data_widget : public QWidget
{
    Q_OBJECT

public:
    explicit data_widget(QWidget *parent = 0);
    ~data_widget();

private:
    Ui::data_widget *ui;
};

#endif // DATA_WIDGET_H
