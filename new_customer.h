#ifndef NEW_CUSTOMER_H
#define NEW_CUSTOMER_H

#include <QMainWindow>
#include <QPainter>

namespace Ui {
class new_customer;
}



class new_customer : public QMainWindow
{
    Q_OBJECT




public:
    explicit new_customer(QWidget *parent = 0);
    ~new_customer();

private:
    Ui::new_customer *ui;

public slots:
    void camera_closed(const QString teste);
    void closeEvent(QCloseEvent *event);

private slots:

    void on_actionSalvar_Cadastro_triggered();
    void on_cep_lineEdit_charge_cursorPositionChanged(int arg1, int arg2);
    void on_takepic_pushbutton_mainData_clicked();
    void on_cep_lineEdit_mainData_textChanged(const QString &arg1);
    void on_cep_lineEdit_mainData_cursorPositionChanged(int arg1, int arg2);
    void on_landlinePhone_lineEdit_mainData_cursorPositionChanged(int arg1, int arg2);
    void on_cellPhone_lineEdit_mainData_cursorPositionChanged(int arg1, int arg2);
    void on_additionalPhone_lineEdit_mainData_cursorPositionChanged(int arg1, int arg2);
    void on_number_lineEdit_mainData_cursorPositionChanged(int arg1, int arg2);
    void on_complement_lineEdit_mainData_cursorPositionChanged(int arg1, int arg2);
    void on_cep_lineEdit_charge_textChanged(const QString &arg1);
    void on_cep_lineEdit_deliver_cursorPositionChanged(int arg1, int arg2);

    void on_pushButton_2_clicked();
    void on_remove_pushButton_picture_clicked();
    void on_addCustomer_pushButton_link_clicked();
};




#endif // CADASTRAR_CLIENTE_H

