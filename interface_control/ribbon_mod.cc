#include "ribbon_mod.h"
#include <base/lang/move.hpp>
#include <QPixmap>

ribbon_mod::ribbon_mod(QWidget *parent)
    : ribbon(parent)
{
    {
        std::array<ui_group, 2> edit;

        button_cell b;
        b.add ("剪切", QPixmap ("png/剪切.png"), cut_);
        b.add ("复制", QPixmap ("png/复制.png"), copy_);
        b.add ("粘贴", QPixmap ("png/粘贴.png"), paste_);
        b.add ("删除", QPixmap ("png/删除.png"), del_);
        b.set_title("第一类");

        edit[0] = ::move (b);

        b.add ("改变作业项数", QPixmap ("png/作业项数.png"));
        b.set_title("第二类");

        edit[1] = ::move (b);

        add_tab(edit, "编辑");
    }

    {
        std::array<ui_group, 1> help;

        button_cell b;
        b.add ("帮助", QPixmap ("png/帮助.png"), help_);
        b.set_title("第一类");

        help[0] = ::move(b);

        add_tab(help, "帮助");
    }

    connect(help_, &ribbon_tool::clicked, this, &ribbon_mod::help);
}
