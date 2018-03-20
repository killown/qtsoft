#ifndef NEW_SUPPLIER_H
#define NEW_SUPPLIER_H

#include <QMainWindow>

namespace Ui {
class new_supplier;
}

class new_supplier : public QMainWindow
{
    Q_OBJECT

public:
    explicit new_supplier(QWidget *parent = 0);
    ~new_supplier();

private slots:

    void on_customerType_comboBox_mainData_currentTextChanged(const QString &text);

    void on_action_register_supplier_triggered();

private:
    Ui::new_supplier *ui;
    enum Column
    {
        code, name
    };
};

#endif // NEW_SUPPLIER_H
