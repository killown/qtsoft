#-------------------------------------------------
#
# Project created by QtCreator 2017-05-05T15:25:12
#
#-------------------------------------------------

QT       += core gui sql opengl multimedia multimediawidgets webkitwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qtsoft
TEMPLATE = app
CONFIG += warn_off

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        qtsoft_mainwindow.cpp \
    localizar_cliente.cpp \
    sistema_de_login.cpp \
    login.cpp \
    editar_usuario.cpp \
    camera.cpp \
    connect_database.cpp \
    new_job_title.cpp \
    allow_or_not.cpp \
    insert_permission.cpp \
    new_employee.cpp \
    new_customer.cpp \
    change_customer.cpp \
    encrypt.cpp \
    new_supplier.cpp \
    company.cpp \
    new_product_degree.cpp \
    new_product.cpp \
    sell.cpp

HEADERS  += qtsoft_mainwindow.h \
    localizar_cliente.h \
    permission.h \
    sistema_de_login.h \
    login.h \
    global.h \
    editar_usuario.h \
    camera.h \
    connect_database.h \
    new_job_title.h \
    allow_or_not.h \
    permission_list.h \
    insert_permission.h \
    new_employee.h \
    new_customer.h \
    change_customer.h \
    encrypt.h \
    new_supplier.h \
    company.h \
    new_product_degree.h \
    new_product.h \
    sell.h

FORMS    += qtsoft_mainwindow.ui \
    localizar_cliente.ui \
    sistema_de_login.ui \
    login.ui \
    editar_usuario.ui \
    camera.ui \
    new_job_title.ui \
    new_customer.ui \
    new_employee.ui \
    change_customer.ui \
    connect_db_window.ui \
    new_supplier.ui \
    new_product.ui \
    company.ui \
    new_product_degree.ui \
    sell.ui

RESOURCES += \
    icons.qrc

DISTFILES += \
    ../Icon Theme/numix-white/Numix-White/48/apps/kfloppy.svg \
    Icons/0ad.svg \
    Icons/add.svg \
    postgresql_reserved_words.txt \
    qtsoft.pri
