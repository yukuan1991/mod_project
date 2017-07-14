#ifndef MOD_MAIN_H
#define MOD_MAIN_H

#include <QWidget>

namespace Ui {
class mod_main;
}

class mod_main : public QWidget
{
    Q_OBJECT

public:
    explicit mod_main(QWidget *parent = 0);
    ~mod_main();
private:
    void init_conn();
private:
    void file_operations(const QString& s);
    void file_new();
private:
    void help_advice();
private:
    Ui::mod_main *ui;
};

#endif // MOD_MAIN_H
