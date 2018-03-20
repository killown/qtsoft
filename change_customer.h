#ifndef CHANGE_CUSTOMER_H
#define CHANGE_CUSTOMER_H

#include <QDialog>

namespace Ui {
class change_customer;
}

class change_customer : public QDialog
{
    Q_OBJECT

public:
    explicit change_customer(QWidget *parent = 0);
    ~change_customer();

private slots:

    void on_tableView_clicked(const QModelIndex &index);

    void on_localizar_lineEdit_returnPressed();

private:
    Ui::change_customer *ui;
};

#endif // CHANGE_CUSTOMER_H
