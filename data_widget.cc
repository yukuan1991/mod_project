#include "data_widget.h"
#include "ui_data_widget.h"

data_widget::data_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::data_widget)
{
    ui->setupUi(this);
}

data_widget::~data_widget()
{
    delete ui;
}
