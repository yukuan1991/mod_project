#include "mod_widget.h"
#include "ui_mod_widget.h"

mod_widget::mod_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mod_widget)
{
    ui->setupUi(this);
}

mod_widget::~mod_widget()
{
    delete ui;
}
