/* Copyright (C) QTsoft Systems, Inc - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Thiago Lucio <systemofdown@gmail.com>, 5 2017
 */
#include "sell.h"
#include "ui_sell.h"

sell::sell(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::sell)
{
    ui->setupUi(this);
}

sell::~sell()
{
    delete ui;
}
