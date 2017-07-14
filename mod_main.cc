#include "mod_main.h"
#include "ui_mod_main.h"
#include "interface_control/about_us_dlg.h"

mod_main::mod_main(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mod_main)
{
    ui->setupUi(this);
    init_conn();
}

mod_main::~mod_main()
{
    delete ui;
}

void mod_main::init_conn()
{
    connect(ui->widget_ribbon, &ribbon_mod::file_menu_triggered, [this] (const QString & s) { file_operations(s); });
    connect(ui->widget_ribbon, &ribbon_mod::help, this, &mod_main::help_advice);
    connect(ui->widget_ribbon, &ribbon_mod::help, [] { qDebug() << "help"; });

}

void mod_main::file_operations(const QString &s)
{
    if(s == "新建")
    {
        file_new();
    }
    else if(s == "退出")
    {
        close();
    }
}

void mod_main::file_new()
{

}

void mod_main::help_advice()
{
    const QString text = R"(<html><head/><body><p>如果您有任何需求与改进建议，</p><p>请随时联系IEToolkit君qq3350436646</p>
                         <p><span style=" font-weight:600; color:red">加好友请扫右边二维码---&gt;</span></p></body></html>)";
    const QString qr_code = R"( <a href = "www.shionto.com"> <img src="./png/about-us.png" width="300" height = "400"/></a>)";
    about_us_dlg::show_info(text, qr_code);
}
