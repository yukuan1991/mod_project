#include "mod_main.h"
#include "ui_mod_main.h"
#include "interface_control/about_us_dlg.h"
#include <QInputDialog>

mod_main::mod_main(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mod_main)
{
    ui->setupUi(this);

    init();
    init_conn();
}

mod_main::~mod_main()
{
    delete ui;
}

void mod_main::init()
{
    ui->widget_data->set_unit (0.129);
}

void mod_main::init_conn()
{
    connect(ui->widget_ribbon, &ribbon_mod::file_menu_triggered, [this] (const QString & s) { file_operations(s); });
    connect(ui->widget_ribbon, &ribbon_mod::add_row, this, &mod_main::add_row);
    connect(ui->widget_ribbon, &ribbon_mod::help, this, &mod_main::help_advice);

    connect (ui->widget_mod, &mod_widget::code_changed, ui->widget_data, &data_widget::add_code);
    connect (ui->widget_mod, &mod_widget::unit_changed, ui->widget_data, &data_widget::set_unit);
    connect (ui->widget_mod, &mod_widget::return_pressed, ui->widget_data, &data_widget::next_code);

    connect (ui->widget_data, &data_widget::line_exists, ui->widget_ribbon, &ribbon_mod::set_enabled);

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
    QInputDialog dlg;
    dlg.setWindowTitle ("调整步数");
    dlg.setLabelText ("请输入工作步数");
    dlg.setOkButtonText ("确 定");
    dlg.setCancelButtonText ("取 消");
    dlg.setInputMode (QInputDialog::IntInput);
    dlg.setIntRange (0, 10000);

    if (dlg.exec () == QDialog::Accepted)
    {
        auto row = dlg.intValue ();
        ui->widget_data->clear ();
        ui->widget_data->set_row (row);

        current_file_data_.clear ();
    }
}

void mod_main::add_row()
{
    QInputDialog dlg;
    dlg.setWindowTitle ("调整步数");
    dlg.setLabelText ("请输入工作步数");
    dlg.setOkButtonText ("确 定");
    dlg.setCancelButtonText ("取 消");
    dlg.setInputMode (QInputDialog::IntInput);
    dlg.setIntRange (0, 10000);

    if (dlg.exec () == QDialog::Accepted)
    {
        auto row = dlg.intValue ();
        ui->widget_data->set_row (row);
    }
}

void mod_main::help_advice()
{
    const QString text = R"(<html><head/><body><p>如果您有任何需求与改进建议，</p><p>请随时联系IEToolkit君qq3350436646</p>
                         <p><span style=" font-weight:600; color:red">加好友请扫右边二维码---&gt;</span></p></body></html>)";
    const QString qr_code = R"( <a href = "www.shionto.com"> <img src="./png/about-us.png" width="300" height = "400"/></a>)";
    about_us_dlg::show_info(text, qr_code);
}
