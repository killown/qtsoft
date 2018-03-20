#ifndef CADASTRAR_CLIENTE_H
#define CADASTRAR_CLIENTE_H

#include <QDialog>

namespace Ui {
class cadastrar_cliente;
}

class cadastrar_cliente : public QDialog
{
    Q_OBJECT

public:
    explicit cadastrar_cliente(QWidget *parent = 0);
    ~cadastrar_cliente();

private slots:
    void on_cep_lineEdit_returnPressed();

    void on_cep_lineEdit_textChanged(const QString &arg1);


    void on_confirmar_cadastro_pushButton_clicked();

    void on_cep_lineEdit_cursorPositionChanged(int arg1, int arg2);

private:
    Ui::cadastrar_cliente *ui;
};

#endif // CADASTRAR_CLIENTE_H
