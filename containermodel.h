#ifndef CONTAINERMODEL_H
#define CONTAINERMODEL_H
#include <QAbstractListModel>
#include <Model/Container/container.h>
#include <Model/Container/deepptr.h>
#include <Model/rpgitem.h>

class ContainerModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum {
        DescriptionRole=16,
        CompleteInfoRole=17
    };
private:
    Container<DeepPtr<RPGItem>> items;
public:
    ContainerModel(QObject* =nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex())const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    //QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
};

#endif // CONTAINERMODEL_H
