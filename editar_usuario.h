#ifndef EDITAR_USUARIO_H
#define EDITAR_USUARIO_H

#include <QDialog>

extern int index_login_tableView;
void atualizar_modelo();

namespace Ui {
class editar_usuario;
}

class editar_usuario : public QDialog
{
    Q_OBJECT

public:
    explicit editar_usuario(QWidget *parent = 0);
    ~editar_usuario();

private slots:
    void on_login_tableView_clicked(const QModelIndex &index);

    void on_pesquisar_lineEdit_returnPressed();

    void on_salvar_pushButton_clicked();

private:
    Ui::editar_usuario *ui;
};

#endif // EDITAR_USUARIO_H
