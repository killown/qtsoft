#ifndef NEW_PRODUCT_DEGREE_H
#define NEW_PRODUCT_DEGREE_H

#include <QDialog>

namespace Ui {
class new_product_degree;
}

class new_product_degree : public QDialog
{
    Q_OBJECT

public:
    explicit new_product_degree(QWidget *parent = 0);
    ~new_product_degree();

private slots:
    void on_add_pushButton_clicked();

    void on_register_pushButton_clicked();

private:
    Ui::new_product_degree *ui;
    enum Column
    {
        Grade, Grupo, Subgrupo
    };
};

#endif // NEW_PRODUCT_DEGREE_H
