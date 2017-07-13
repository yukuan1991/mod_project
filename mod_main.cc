#include "mod_main.h"
#include "ui_mod_main.h"

mod_main::mod_main(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mod_main)
{
    ui->setupUi(this);
}

mod_main::~mod_main()
{
    delete ui;
}
