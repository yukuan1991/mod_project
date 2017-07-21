#include "mod_analysis.h"
#include "ui_mod_analysis.h"
#include <QInputDialog>

mod_analysis::mod_analysis(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mod_analysis)
{
    ui->setupUi(this);
    init();
    init_conn();
}

mod_analysis::~mod_analysis()
{
    delete ui;
}

void mod_analysis::init()
{
    ui->widget_data->set_unit (0.129);
}

void mod_analysis::init_conn()
{
    connect (ui->widget_mod, &mod_widget::code_changed, ui->widget_data, &data_widget::add_code);
    connect (ui->widget_mod, &mod_widget::unit_changed, ui->widget_data, &data_widget::set_unit);
    connect (ui->widget_mod, &mod_widget::return_pressed, ui->widget_data, &data_widget::next_code);

    connect(this, &mod_analysis::cut, ui->widget_data, &data_widget::on_cut);
    connect(this, &mod_analysis::copy, ui->widget_data, &data_widget::on_copy);
    connect(this, &mod_analysis::paste, ui->widget_data, &data_widget::on_paste);
    connect(this, &mod_analysis::del, ui->widget_data, &data_widget::on_del);

    connect (ui->widget_data, &data_widget::std_time_sum,
             ui->widget_mod, &mod_widget::set_std_time_sum);
}

void mod_analysis::set_task_count()
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

void mod_analysis::add_row()
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

void mod_analysis::set_measure_date(const QDate &date)
{
    ui->widget_mod->set_measure_date(date);
}

QString mod_analysis::measure_date() const
{
    return ui->widget_mod->measure_date();
}

void mod_analysis::set_measure_man(const QString &data)
{
    ui->widget_mod->set_measure_man(data);
}

QString mod_analysis::measure_man() const
{
    return ui->widget_mod->measure_man();
}

void mod_analysis::set_task_man(const QString &data)
{
    ui->widget_mod->set_task_man(data);
}

QString mod_analysis::task_man() const
{
    return ui->widget_mod->task_man();
}


