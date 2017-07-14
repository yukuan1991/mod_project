﻿#pragma once
#include "ribbon.h"

class ribbon_mod : public ribbon
{
    Q_OBJECT
signals:
    void add_row();
    void help();
public:
    ribbon_mod(QWidget * parent = nullptr);
private:
    ribbon_tool *cut_, *copy_, *paste_, *del_;
    ribbon_tool *add_row_;
    ribbon_tool *help_;
};

