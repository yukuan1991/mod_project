#include "data_widget.h"
#include "ui_data_widget.h"
#include <QMessageBox>

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

void data_widget::add_code(const QVariant &code)
{
    if (current_view_ == nullptr or current_view_->selectionModel ()->selectedIndexes ().empty ())
    {
        QMessageBox::information (this, "代码", "请选中一个表格");
        return;
    }

    assert (current_view_);
    auto list = current_view_->selectionModel ()->selectedIndexes ();
    decltype (list) code_list;

    for (auto& index : list)
    {
        auto variant = index.model ()->headerData (index.column (), Qt::Horizontal, Qt::DisplayRole);
        QString header = variant.toString ();
        if (header == "代码")
        {
            code_list.append (index);
        }
    }

    if (code_list.empty ())
    {
        QMessageBox::information (this, "代码", "请选中代码这一列");
        return;
    }

    auto min_row = 99999;
    auto min_row_index = -1;
    for (int i = 0; i < code_list.size (); i++)
    {
        if (code_list[i].row () < min_row)
        {
            min_row_index = i;
            min_row = code_list[i].row ();
        }
    }
    assert (min_row_index != -1 and min_row_index < code_list.size ());

    current_view_->model ()->setData (code_list[min_row_index], code);
}

void data_widget::set_unit(double unit)
{
    this->left_model_->setData (QModelIndex (), unit, Qt::UserRole + 100);
    this->right_model_->setData (QModelIndex (), unit, Qt::UserRole + 100);
    this->result_model_->setData (QModelIndex (), unit, Qt::UserRole + 100);
}

void data_widget::next_code()
{
    if (current_view_ == nullptr or current_view_->model () == nullptr)
    {
        return;
    }

    auto list_index = current_view_->selectionModel ()->selectedIndexes ();


    QModelIndex code_index;
    for (auto& it : list_index)
    {
        auto variant = it.model ()->headerData (it.column (), Qt::Horizontal, Qt::DisplayRole);
        QString header = variant.toString ();
        if (header == "代码")
        {
            code_index = it;
            break;
        }
    }


    if (!code_index.isValid () or code_index.row () >= code_index.model ()->rowCount () - 1)
    {
        return;
    }

    auto next_index = current_view_->model ()->index (code_index.row () + 1, code_index.column ());
    current_view_->scrollTo(next_index);
    assert (next_index.isValid ());

    current_view_->clearSelection ();
    current_view_->selectionModel ()->select (next_index, QItemSelectionModel::Select);
}

void data_widget::set_row(int num)
{
    emit line_exists (num != 0);

    left_model_->resize (static_cast<unsigned int>(num));
    ui->table_left->setModel(nullptr);
    ui->table_left->setModel(left_model_.get ());

    right_model_->resize (static_cast<unsigned int>(num));
    ui->table_right->setModel(nullptr);
    ui->table_right->setModel(right_model_.get ());
    result_model_->resize (static_cast<unsigned int>(num));
    ui->table_result->setModel(nullptr);
    ui->table_result->setModel(result_model_.get ());
}

void data_widget::clear()
{
    result_model_->clear ();
    ui->table_result->setModel (nullptr);
    ui->table_result->setModel (result_model_.get ());
    left_model_->clear ();
    ui->table_left->setModel (nullptr);
    ui->table_left->setModel (left_model_.get ());
    right_model_->clear ();
    ui->table_right->setModel (nullptr);
    ui->table_right->setModel (right_model_.get ());
}
