#ifndef DATA_WIDGET_H
#define DATA_WIDGET_H

#include <QWidget>
#include <map>
#include <string>
#include <vector>
#include <QTableView>
#include "Qt-Utils/json.hpp"
#include <QFile>
#include "pts/pts_model.h"
#include "view/table_view.h"
#include "pts/pts_delegate.h"

using json = nlohmann::json;

namespace Ui {
class data_widget;
}

class data_widget : public QWidget
{
    Q_OBJECT

public:
    explicit data_widget(QWidget *parent = 0);
    ~data_widget();

    void add_code (const QVariant& code);
    void set_unit (double unit);
    void next_code ();
    json save_left();
    json save_result();
    json save_right();
    bool load_left(const json& left_array);
    bool load_right(const json& right_array);
    bool load_result(const json& result_array);
    json json_data ();
    void save(const std::map<QString, QString> &additional_info, const QString& method_info);

    void set_row (int num);
    void add_row (int num);
    void reduce_row (int num);
    int row();
    void set_no_editable ();
    bool task_content_check ();
    void clear ();
    void on_cut ();
    void on_copy ();
    void on_paste ();
    void on_del ();

private:
    void on_view_clicked ();
    json map_to_json (const std::map <QString,QString>& map);
    json info_pandect ();
    void save_task (const QString& filename, const std::map <QString,QString>& info,const json &data);
    void set_views ();

signals:
    void line_exists (bool yes_or_no);
    void total_time_changed (const QString& sum);

private:
    std::vector<table_view*> views_;
    std::unique_ptr<json_model> left_model_ = pts_model::make (PTS::left);
    std::unique_ptr<QStyledItemDelegate> left_delegate_ {new pts_delegate};
    std::unique_ptr<json_model> right_model_ = pts_model::make (PTS::right);
    std::unique_ptr<QStyledItemDelegate> right_delegate_ {new pts_delegate};

    std::unique_ptr<json_model> result_model_ = pts_model::make (PTS::result);
    std::unique_ptr<QStyledItemDelegate> result_delegate_ {new pts_delegate};
    table_view* current_view_ = nullptr;

    bool is_editable_ = true;

private:
    Ui::data_widget *ui;
};

#endif // DATA_WIDGET_H
