#-------------------------------------------------
#
# Project created by QtCreator 2017-07-13T09:09:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG -= c++11
QMAKE_CXXFLAGS += -std=c++1z

TARGET = mod_project
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cc\
        mod_main.cc \
    interface_control/ribbon.cc \
    interface_control/ribbon_mod.cc \
    data_widget.cc \
    mod_widget.cc \
    interface_control/push_button.cpp \
    Qt-Utils/tinyxml2.cpp \
    Qt-Utils/encryption.cpp \
    Qt-Utils/des.cpp \
    view/table_view.cpp \
    model/json_model.cpp \
    pts/pts_delegate.cpp \
    pts/pts_model.cpp \
    pts/code_edit.cpp \
    interface_control/about_us_dlg.cc \
    mod_analysis.cc

HEADERS  += mod_main.h \
    interface_control/ribbon.h \
    interface_control/ribbon_mod.h \
    data_widget.h \
    mod_widget.h \
    interface_control/push_button.h \
    Qt-Utils/tinyxml2.h \
    Qt-Utils/stl_extension.hpp \
    Qt-Utils/json.hpp \
    arithmetic_resource.hpp \
    Qt-Utils/encryption.h \
    Qt-Utils/des.h \
    view/table_view.h \
    model/json_model.h \
    Qt-Utils/krys_application.hpp \
    pts/pts_delegate.h \
    pts/pts_model.h \
    pts/code_edit.h \
    interface_control/about_us_dlg.h \
    mod_analysis.h

FORMS    += mod_main.ui \
    data_widget.ui \
    mod_widget.ui \
    mod_analysis.ui

LIBS += -lboost_locale
LIBS += -liconv
LIBS += -lboost_filesystem
LIBS += -lboost_system
LIBS += -lboost_regex
