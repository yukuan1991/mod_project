﻿#ifndef MOD_WIDGET_H
#define MOD_WIDGET_H

#include <QWidget>
#include <Qt-Utils/tinyxml2.h>

class QComboBox;
namespace Ui {
class mod_widget;
}

class mod_widget : public QWidget
{
    Q_OBJECT

public:
    explicit mod_widget(QWidget *parent = 0);
    ~mod_widget();
private:
    void init();
    void init_xml ();
    void on_mod_hover ();
    void on_mod_clicked ();

private:
    Ui::mod_widget *ui;

    std::map<std::string, std::tuple<std::string, std::string, std::string, std::string, std::string>> mod_data_;
    tinyxml2::XMLDocument mod_doc_;
    tinyxml2::XMLElement* mod_attr_ = nullptr;
    tinyxml2::XMLElement* mod_name_ = nullptr;
    tinyxml2::XMLElement* mod_content_ = nullptr;
    tinyxml2::XMLElement* mod_example_ = nullptr;
    tinyxml2::XMLElement* mod_remark_ = nullptr;

    static std::map<std::string, int> kv_tmu_;
};

#endif // MOD_WIDGET_H
