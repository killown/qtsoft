#ifndef QTSOFT_MAINWINDOW_H
#define QTSOFT_MAINWINDOW_H

#include <QMainWindow>

bool permitir_ou_nao(const QStringList lista);

namespace Ui {
class QTSOFT_MainWindow;
}

class QTSOFT_MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit QTSOFT_MainWindow(QWidget *parent = 0);
    ~QTSOFT_MainWindow();

private slots:

    void createStatusBar();

    void on_cadastrar_cliente_action_triggered();

    void on_cadastrar_usuario_action_triggered();

    void on_localizar_cliente_action_triggered();

    void on_editar_cliente_action_triggered();

    void on_editar_usuario_action_triggered();

    void on_actionFuncionario_triggered();

    void on_action_new_supplier_triggered();

    void on_action_new_product_triggered();

    void on_actionSell_triggered();

private:
    Ui::QTSOFT_MainWindow *ui;
};

#endif // QTSOFT_MAINWINDOW_H
