#ifndef DATA_WIDGET_H
#define DATA_WIDGET_H

#include <QWidget>
#include <map>
#include <string>
#include <vector>
#include <QTableView>
#include "Qt-Utils/json.hpp"
#include <QFile>
#include "pts/pts_model.h"
#include "view/table_view.h"
#include "pts/pts_delegate.h"

using json = nlohmann::json;

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
