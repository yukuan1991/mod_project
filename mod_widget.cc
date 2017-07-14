#include "mod_widget.h"
#include "ui_mod_widget.h"
#include <assert.h>

mod_widget::mod_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mod_widget)
{
    ui->setupUi(this);
}

mod_widget::~mod_widget()
{
    delete ui;
}

void mod_widget::init()
{
    auto list = children();
    for (auto & iter : list)
    {
        push_button* button = dynamic_cast<push_button*>(iter);
        if (button)
        {
            connect (button, &push_button::mouse_enter, this, &mod_widget::on_mod_hover);
            connect (button, &push_button::clicked, this, &mod_widget::on_mod_clicked);
        }
    }
}

void mod_widget::on_mod_hover()
{
    auto src = sender (); assert (src);
    push_button* button = dynamic_cast<push_button*>(src); assert (button);

    auto iter = mod_data_.find (button->text ().toStdString ());
    assert (iter != mod_data_.end ());
    std::string& attr = std::get<0> (iter->second);
    std::string& name = std::get<1> (iter->second);
    std::string& content = std::get<2> (iter->second);
    std::string& example = std::get<3> (iter->second);
    std::string& remark = std::get<4> (iter->second);

    mod_attr_->SetText (attr.data ());
    mod_name_->SetText (name.data ());
    mod_content_->SetText (content.data ());
    mod_example_->SetText (example.data ());
    mod_remark_->SetText (remark.data ());

    tinyxml2::XMLPrinter prt;
    mod_doc_.Print (&prt);

    ui->text_area_mod_description->setText (prt.CStr ());
}

void mod_widget::on_mod_clicked()
{
    QObject* src = sender (); assert (src);
    push_button* button = dynamic_cast<push_button*>(src); assert (button);
    QByteArray arr {("mod_" + button->text ()).toStdString ().data ()};
//    emit code_changed (arr);
}
