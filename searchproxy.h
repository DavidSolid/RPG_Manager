#ifndef SEARCHPROXY_H
#define SEARCHPROXY_H
#include <QSortFilterProxyModel>
#include <QLineEdit>
#include <QCheckBox>

class SearchProxy : public QSortFilterProxyModel
{
    Q_OBJECT

private:
    QLineEdit* filter;
    QCheckBox *weapon,*armor,*consumable;
public:
    SearchProxy(QLineEdit*,QCheckBox*,QCheckBox*,QCheckBox*,QObject* =nullptr);
    bool filterAcceptsRow(int source_row, const QModelIndex & source_parent) const override;
};

#endif // SEARCHPROXY_H
