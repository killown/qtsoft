#ifndef SISTEMA_DE_LOGIN_H
#define SISTEMA_DE_LOGIN_H

#include <QDialog>

QStringList inserir_dados(const QStringList lista);

namespace Ui {
class sistema_de_login;
}

class sistema_de_login : public QDialog
{
    Q_OBJECT

public:
    explicit sistema_de_login(QWidget *parent = 0);
    ~sistema_de_login();


private slots:

    void on_cadastrar_pushButton_clicked();

    void on_administrador_checkBox_toggled(bool checked);

private:
    Ui::sistema_de_login *ui;
};

#endif // SISTEMA_DE_LOGIN_H
