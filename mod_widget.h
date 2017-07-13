#ifndef MOD_WIDGET_H
#define MOD_WIDGET_H

#include <QWidget>
#include <Qt-Utils/tinyxml2.h>

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

private:
    Ui::mod_widget *ui;

    std::map<std::string, std::tuple<std::string, std::string, std::string, std::string, std::string>> mod_data_;
//    tinyxml2::XMLDocument mod_doc_;
//    tinyxml2::XMLElement* mod_attr_;
//    tinyxml2::XMLElement* mod_name_;
//    tinyxml2::XMLElement* mod_content_;
//    tinyxml2::XMLElement* mod_example_;
//    tinyxml2::XMLElement* mod_remark_;
};

#endif // MOD_WIDGET_H
