#include "searchproxy.h"
#include "containermodel.h"

SearchProxy::SearchProxy(QLineEdit * exp, QObject* parent):QSortFilterProxyModel(parent),filter(exp)
{

}

bool SearchProxy::filterAcceptsRow(int source_row, const QModelIndex & source_parent) const{
    return dynamic_cast<ContainerModel*>(sourceModel())->validateRow(source_row,filter->text(),source_parent);
}
