#ifndef MOD_ANALYSIS_H
#define MOD_ANALYSIS_H

#include <QWidget>
#include "Qt-Utils/json.hpp"


namespace Ui {
class mod_analysis;
}

using nlohmann::json;

class mod_analysis : public QWidget
{
    Q_OBJECT
signals:
    void copy();
    void cut();
    void paste();
    void del();
public:
    explicit mod_analysis(QWidget *parent = 0);
    ~mod_analysis();

    void init();
    void init_conn();
    void set_task_count ();
    void add_row();

private:
    Ui::mod_analysis *ui;

    json current_file_data_;
};

#endif // MOD_ANALYSIS_H
