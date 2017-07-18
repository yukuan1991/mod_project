#include "data_widget.h"
#include "ui_data_widget.h"
#include <QMessageBox>
#include <QScrollBar>

data_widget::data_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::data_widget)
{
    ui->setupUi(this);
    ui->table_left->setItemDelegate (left_delegate_.get ());
    ui->table_right->setItemDelegate (right_delegate_.get ());
    ui->table_result->setItemDelegate (result_delegate_.get ());

    views_.push_back (ui->table_result);
    views_.push_back (ui->table_left);
    views_.push_back (ui->table_right);
    set_views();
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

void data_widget::on_cut()
{
    if (current_view_ != nullptr)
    {
        current_view_->on_copy_del (table_view::OPERATION_COPY | table_view::OPERATION_DEL);
    }
}

void data_widget::on_copy()
{
    if (current_view_ != nullptr)
    {
        current_view_->on_copy_del (table_view::OPERATION_COPY);
    }
}

void data_widget::on_paste()
{
    if (current_view_ != nullptr)
    {
        current_view_->on_paste ();
    }
}

void data_widget::on_del()
{
    if (current_view_ != nullptr)
    {
        current_view_->on_copy_del (table_view::OPERATION_DEL);
    }
}

void data_widget::on_view_clicked()
{
    QObject* src = sender (); assert (src);
    current_view_ = dynamic_cast<table_view*>(src); assert (current_view_);

    for (typename decltype (views_)::size_type i = 0; i < views_.size (); i ++)
    {
        if (views_[i] != current_view_)
        {
            views_[i]->clearSelection ();
        }
    }
}

void data_widget::set_views()
{
    for (auto iter : views_)
    {
        assert (iter);
        connect (iter, &table_view::mouse_pressed, this, &data_widget::on_view_clicked);
        iter->horizontalHeader ()->setSectionResizeMode (QHeaderView::Interactive);
        iter->verticalHeader ()->setSectionResizeMode (QHeaderView::Fixed);

        auto scroll = make_unique<QScrollBar> ();
        iter->setHorizontalScrollBarPolicy (Qt::ScrollBarAlwaysOn);
        connect (scroll.get (), &QScrollBar::valueChanged, [=] (int value)
        {
            for (auto inner_iter : views_)
            {
                inner_iter->verticalScrollBar ()->setValue (value);
            }
        });

        iter->setVerticalScrollBar (scroll.release ());
    }
}
