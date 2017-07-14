#ifndef MOD_MAIN_H
#define MOD_MAIN_H

#include <QWidget>
#include "Qt-Utils/json.hpp"

namespace Ui {
class mod_main;
}

using nlohmann::json;

class mod_main : public QWidget
{
    Q_OBJECT
public:
    explicit mod_main(QWidget *parent = 0);
    ~mod_main();
private:
    void init();
    void init_conn();
private:
    void file_operations(const QString& s);
    void file_new();
private:
    void add_row();
    void help_advice();
private:
    Ui::mod_main *ui;

    json current_file_data_;

};

#endif // MOD_MAIN_H
