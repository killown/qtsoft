#ifndef COMPANY_H
#define COMPANY_H

#include <QMainWindow>

namespace Ui {
class company;
}

class company : public QMainWindow
{
    Q_OBJECT

public:
    explicit company(QWidget *parent = 0);
    ~company();

private:
    Ui::company *ui;
};

#endif // COMPANY_H
