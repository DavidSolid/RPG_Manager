#ifndef SEARCHPROXY_H
#define SEARCHPROXY_H
#include <QSortFilterProxyModel>
#include <QLineEdit>

class SearchProxy : public QSortFilterProxyModel
{
    Q_OBJECT

private:
    QLineEdit* filter;
public:
    SearchProxy(QLineEdit*,QObject* =nullptr);
    bool filterAcceptsRow(int source_row, const QModelIndex & source_parent) const override;
};

#endif // SEARCHPROXY_H
