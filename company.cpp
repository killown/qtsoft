#include "company.h"
#include "ui_company.h"

company::company(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::company)
{
    ui->setupUi(this);
}

company::~company()
{
    delete ui;
}
