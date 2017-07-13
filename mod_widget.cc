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

void mod_widget::init()
{
    auto list = children();
    for (auto & iter : list)
    {
        push_button* button = dynamic_cast<push_button*>(iter);
//        if (button)
//        {
//            connect (button, &push_button::mouse_enter, this, &method_widget::on_mod_hover);
//            connect (button, &push_button::clicked, this, &method_widget::on_mod_clicked);
//        }
    }
}
