#ifndef MOD_WIDGET_H
#define MOD_WIDGET_H

#include <QWidget>

namespace Ui {
class mod_widget;
}

class mod_widget : public QWidget
{
    Q_OBJECT

public:
    explicit mod_widget(QWidget *parent = 0);
    ~mod_widget();

private:
    Ui::mod_widget *ui;
};

#endif // MOD_WIDGET_H
