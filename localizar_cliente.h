#ifndef LOCALIZAR_CLIENTE_H
#define LOCALIZAR_CLIENTE_H

#include <QDialog>
#include <QPainter>
#include <QVariant>
#include <QSortFilterProxyModel>
#include <QHeaderView>

namespace Ui {
class localizar_cliente;
}

QString translate(const QString translation);

class localizar_cliente : public QDialog
{
    Q_OBJECT

public:
    explicit localizar_cliente(QWidget *parent = 0);
    ~localizar_cliente();

private slots:
    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_tableView_clicked(const QModelIndex &index);

    void on_search_lineEdit_returnPressed();

private:
    Ui::localizar_cliente *ui;
};




// Handles Horizontal header
class HeaderModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    explicit HeaderModel(QObject * parent = 0)
        : QSortFilterProxyModel(parent)
    { }

    QVariant headerData(int section, Qt::Orientation orientation, int role) const
    {
        if(orientation == Qt::Horizontal)
        {
            if(role == Qt::DisplayRole)
                switch(section)
                {
                case 0: return "Id";            break;
                case 1: return "Designation";   break;
                case 2: return "Famille";       break;
                case 3: return "Qte Maximum";   break;
                case 4: return "Qte Minimum";   break;
                case 5: return "Prix";          break;
                case 6: return "Prix vente";    break;
                default:
                    return QString("Column %1").arg(section + 1);
                    break;
                }
        }

        return QVariant();
    }
};

// Handles Vertical header
class Header : public QHeaderView
{
    Q_OBJECT
public:
    explicit Header(QWidget * parent)
        : QHeaderView(Qt::Vertical, parent)
        , mSelectedIndex(-1)
    {
        setMinimumWidth(QImage("imgs/arrow.png").width());
    }

public slots:
    void changeCurrent(const QModelIndex & current, const QModelIndex & previous)
    {
        int section = current.row();

        if(mSelectedIndex != section)
        {
            mSelectedIndex = section;
            viewport()->update();
        }
    }

protected:
    void paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const
    {
        painter->save();
        if(mSelectedIndex > -1)
        {
            if(mSelectedIndex == logicalIndex)
                if(!isSectionHidden(logicalIndex))
                    painter->drawImage(rect, QImage("imgs/arrow.png"));
        }
        painter->restore();
    }

private:
    int mSelectedIndex;
};



#endif // LOCALIZAR_CLIENTE_H
