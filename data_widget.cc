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

    connect(result_model_.get(), &pts_model::dataChanged,
            [this] { auto sum = get_std_time_sum(); emit std_time_sum(sum); });
}

data_widget::~data_widget()
{
    delete ui;
}

QString data_widget::get_std_time_sum() const
{
    auto col = 5;
    double sum = 0;
    for (int row = 0; row < static_cast<int>(result_model_->size ()); ++row)
    {
        auto pos = result_model_->index (row, col);
        auto vat = result_model_->data (pos);
        if (vat.isNull ())
        {
            continue;
        }
        else
        {
            auto time = vat.toDouble ();
            sum += time;
        }
    }
    return QString::number(sum, 'f', 2);
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

json data_widget::save_left() try
{
    json left = json::array();
    QVariant vat;
    auto model = left_model_.get ();
    for(int j=0; j < model->rowCount();++j)
    {
        json json_row_obj = json::object ();

        auto key = "作业内容"s;
        vat = get_header_data (model, key.data (), j);
        json_row_obj[key] = vat.toString ().toStdString ();

        key = "代码";
        auto& code_arr = json_row_obj[key];
        code_arr = json::array ();
        vat = get_header_data (model, key.data (), j, Qt::UserRole + 20);
        auto list = vat.toStringList ();
        for (auto & it : list)
        {
            code_arr.push_back (it.toStdString ());
        }

        key = "数量*频次";
        vat = get_header_data (model, key.data (), j);
        json_row_obj[key] = vat.toInt ();

        key = "MOD";
        vat = get_header_data (model, key.data (), j);
        json_row_obj[key] = vat.toInt ();

        key = "评比系数";
        vat = get_header_data (model, key.data (), j);
        json_row_obj[key] = vat.toDouble ();

        key = "基本时间";
        vat = get_header_data (model, key.data (), j);
        json_row_obj[key] = vat.toDouble ();

        left.push_back (std::move (json_row_obj));
    }
    return left;
}
catch (std::exception &e)
{
    qDebug () << __LINE__ << e.what();
    return {};
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

bool data_widget::task_content_check()
{
    for (int i = 0; i < result_model_->rowCount (); i ++)
    {
        if (get_header_data (result_model_.get (), "作业内容", i).toString ().trimmed ().isEmpty ())
        {
            QMessageBox::information (this, "作业内容", "作业内容的第" + QString::number (i + 1) + "行为空");
            return false;
        }
        if (get_header_data (result_model_.get (), "代码", i, Qt::UserRole + 20).type () != QVariant::StringList)
        {
            QMessageBox::information (this, "作业内容", "作业内容的第" + QString::number (i + 1) + "行的代码不符合格式或为空");
            return false;
        }
    }

    return true;
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

json data_widget::save_result() try
{
    json result = json::array();
    QVariant vat;
    auto model = result_model_.get ();
    for(int j=0; j < model->rowCount();++j)
    {
        json json_row_obj = json::object ();

        auto key = "作业内容"s;
        vat = get_header_data (model, key.data (), j);
        json_row_obj[key] = vat.toString ().toStdString ();

        key = "代码";
        auto& code_arr = json_row_obj[key];
        code_arr = json::array ();
        vat = get_header_data (model, key.data (), j, Qt::UserRole + 20);
        auto list = vat.toStringList ();
        for (auto & it : list)
        {
            code_arr.push_back (it.toStdString ());
        }

        key = "数量*频次";
        vat = get_header_data (model, key.data (), j);
        json_row_obj[key] = vat.toInt ();

        key = "MOD";
        vat = get_header_data (model, key.data (), j);
        json_row_obj[key] = vat.toInt ();

        key = "评比系数";
        vat = get_header_data (model, key.data (), j);
        json_row_obj[key] = vat.toDouble ();

        key = "基本时间";
        vat = get_header_data (model, key.data (), j);
        json_row_obj[key] = vat.toDouble ();

        key = "宽放率";
        vat = get_header_data (model, key.data (), j);
        json_row_obj[key] = vat.toString ().toStdString ();

        key = "标准工时";
        vat = get_header_data (model, key.data (), j);
        json_row_obj["标准时间"] = vat.toDouble ();

        key = "增值/非增值";
        vat = get_header_data (model, key.data (), j);
        json_row_obj[key] = vat.toString ().toStdString ();

        key = "操作分类";
        vat = get_header_data (model, key.data (), j);
        json_row_obj[key] = vat.toString ().toStdString ();

        result.push_back (std::move (json_row_obj));
    }
    return result;
}
catch (std::exception &e)
{
    qDebug () << __LINE__ << e.what();
    return {};
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

json data_widget::save_right() try
{
    json right = json::array();
    QVariant vat;
    auto model = right_model_.get ();
    for(int j=0; j < model->rowCount();++j)
    {
        json json_row_obj = json::object ();

        auto key = "作业内容"s;
        vat = get_header_data (model, key.data (), j);
        json_row_obj[key] = vat.toString ().toStdString ();

        key = "代码";
        auto& code_arr = json_row_obj[key];
        code_arr = json::array ();
        vat = get_header_data (model, key.data (), j, Qt::UserRole + 20);
        auto list = vat.toStringList ();
        for (auto & it : list)
        {
            code_arr.push_back (it.toStdString ());
        }

        key = "数量*频次";
        vat = get_header_data (model, key.data (), j);
        json_row_obj[key] = vat.toInt ();

        key = "MOD";
        vat = get_header_data (model, key.data (), j);
        json_row_obj[key] = vat.toInt ();

        key = "评比系数";
        vat = get_header_data (model, key.data (), j);
        json_row_obj[key] = vat.toDouble ();

        key = "基本时间";
        vat = get_header_data (model, key.data (), j);
        json_row_obj[key] = vat.toDouble ();

        right.push_back (std::move (json_row_obj));
    }

    return right;
}
catch (std::exception &e)
{
    qDebug () << __LINE__ << e.what();
    return {};
}

