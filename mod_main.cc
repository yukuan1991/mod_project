#include "mod_main.h"
#include "ui_mod_main.h"
#include "interface_control/about_us_dlg.h"
#include <QInputDialog>
#include "mod_analysis.h"
#include <memory>
#include <QMdiSubWindow>

using namespace std;

mod_main::mod_main(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mod_main)
{
    ui->setupUi(this);
    ui->mdi->setViewMode (QMdiArea::TabbedView);
//    init();
    init_conn();
    set_button_enabled();
}

mod_main::~mod_main()
{
    delete ui;
}

//void mod_main::init()
//{
//}

void mod_main::init_conn()
{
    connect(ui->widget_ribbon, &ribbon_mod::file_menu_triggered, [this] (const QString & s) { file_operations(s); });

    connect(ui->widget_ribbon, &ribbon_mod::help, this, &mod_main::help_advice);

//    connect (ui->widget_data, &data_widget::line_exists, ui->widget_ribbon, &ribbon_mod::set_enabled);
    connect(ui->mdi, &QMdiArea::subWindowActivated, this, &mod_main::set_button_enabled);

//    connect (ui->widget_data, &data_widget::std_time_sum,
//             ui->widget_mod, &mod_widget::set_std_time_sum);

}

void mod_main::set_button_enabled()
{
    const bool state = (active_window() != nullptr);
    ui->widget_ribbon->set_enabled(state);
}

void mod_main::file_operations(const QString &s)
{
    if(s == "新建")
    {
        file_new();
    }
    else if(s == "保存")
    {
        file_save();
    }
    else if(s == "退出")
    {
        close();
    }
}

void mod_main::file_save()
{
//    if (!ui->widget_data->task_content_check ())
//    {
//        return;
//    }
}



void mod_main::help_advice()
{
    const QString text = R"(<html><head/><body><p>如果您有任何需求与改进建议，</p><p>请随时联系IEToolkit君qq3350436646</p>
                         <p><span style=" font-weight:600; color:red">加好友请扫右边二维码---&gt;</span></p></body></html>)";
    const QString qr_code = R"( <a href = "www.shionto.com"> <img src="./png/about-us.png" width="300" height = "400"/></a>)";
    about_us_dlg::show_info(text, qr_code);
}

not_null<mod_analysis *> mod_main::create_window(const QString &title)
{
    auto mod_win = make_unique<mod_analysis> ();
    auto ptr_mod_win = mod_win.get();

    mod_win->setAttribute (Qt::WA_DeleteOnClose);
    auto w = ui->mdi->addSubWindow (ptr_mod_win);
    w->setWindowTitle (title);

    w->setWindowState (Qt::WindowMaximized);

    connect(ui->widget_ribbon, &ribbon_mod::add_row, ptr_mod_win, &mod_analysis::add_row);
    connect(ui->widget_ribbon, &ribbon_mod::copy, ptr_mod_win, &mod_analysis::copy);
    connect(ui->widget_ribbon, &ribbon_mod::cut, ptr_mod_win, &mod_analysis::cut);
    connect(ui->widget_ribbon, &ribbon_mod::paste, ptr_mod_win, &mod_analysis::paste);
    connect(ui->widget_ribbon, &ribbon_mod::del, ptr_mod_win, &mod_analysis::del);

    return mod_win.release ();
}

mod_analysis *mod_main::active_window()
{
    if(QMdiSubWindow* active_subwindow = ui->mdi->activeSubWindow())
    {
        mod_analysis* canvas_ptr = dynamic_cast<mod_analysis*>(active_subwindow->widget());
        return canvas_ptr;
    }
    else
    {
        return nullptr;
    }
}

void mod_main::file_new()
{
    auto w = create_window ("未命名");
    w->set_task_count ();
}
