#include "searchproxy.h"
#include "containermodel.h"

SearchProxy::SearchProxy(QLineEdit * exp, QCheckBox * w, QCheckBox * a, QCheckBox * c, QObject* parent):QSortFilterProxyModel(parent),filter(exp),weapon(w),armor(a),consumable(c)
{

}

bool SearchProxy::filterAcceptsRow(int source_row, const QModelIndex & source_parent) const{
    return dynamic_cast<ContainerModel*>(sourceModel())->validateRow(source_row,filter->text(),weapon->isChecked(),armor->isChecked(),consumable->isChecked(),source_parent);
}
