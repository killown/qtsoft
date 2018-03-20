#ifndef NEW_PRODUCT_H
#define NEW_PRODUCT_H

#include <QMainWindow>

namespace Ui {
class new_product;
}

extern QString selected_code;
extern QString selected_degree;
extern QString selected_group;
extern QString selected_subgroup;
extern QString degreeTableView_index;
extern QString selected_row_cest_tableView;

class new_product : public QMainWindow
{
    Q_OBJECT

public:
    explicit new_product(QWidget *parent = 0);
    ~new_product();

public slots:
    void pricing_calc();
    void camera_closed(const QString result);

private slots:

    void on_doubleSpinBox_cost_mainData_valueChanged(const QString &arg1);

    void on_doubleSpinBox_profit_mainData_valueChanged(const QString &arg1);

    void on_doubleSpinBox_additional_commission_mainData_valueChanged(const QString &arg1);

    void on_newDegree_pushButton_clicked();

    void on_searchSupplier_pushButton_clicked();

    void on_supplier_tableView_clicked(const QModelIndex &index);

    void on_selectedSupplier_tableWidget_clicked(const QModelIndex &index);

    void on_action_registration_triggered();

    void on_newSupplier_pushButton_clicked();

    void on_degree_tableView_clicked(const QModelIndex &index);

    void on_cost_doubleSpinBox_mainData_valueChanged(const QString &arg1);

    void on_profit_doubleSpinBox_mainData_valueChanged(const QString &arg1);

    void on_additionalCommission_doubleSpinBox_mainData_valueChanged(const QString &arg1);

    void on_choosePicture_pushButton_clicked();

    void on_deleteImage_pushButton_clicked();

    void on_camera_pushbutton_clicked();

    void on_blockProduct_checkbox_mainData_clicked(bool checked);

    void on_enableDegree_checkBox_clicked(bool checked);

    void on_searchDegree_pushButton_clicked();

    void on_cestSearch_lineEdit_cursorPositionChanged(int arg1, int arg2);

    void on_cest_tableView_clicked(const QModelIndex &index);

private:
    Ui::new_product *ui;

    enum Column
    {
        id, degreeid, groupid, subgroupid, code, name
    };
};

#endif // new_product_H
