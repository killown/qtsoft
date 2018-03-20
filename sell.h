/* Copyright (C) QTsoft Systems, Inc - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Thiago Lucio <systemofdown@gmail.com>, 5 2017
 */
#ifndef SELL_H
#define SELL_H

#include <QMainWindow>

namespace Ui {
class sell;
}

class sell : public QMainWindow
{
    Q_OBJECT

public:
    explicit sell(QWidget *parent = 0);
    ~sell();

private:
    Ui::sell *ui;
};

#endif // SELL_H
