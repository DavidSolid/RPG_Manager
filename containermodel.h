#ifndef CONTAINERMODEL_H
#define CONTAINERMODEL_H
#include <QAbstractListModel>
#include <Model/Container/container.h>
#include <Model/Container/deepptr.h>
#include <Model/rpgitem.h>
#include <map>

class ContainerModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum {
        DescriptionRole=16,
        CompleteInfoRole=17,
        JsonRole=18
    };
private:
    Container<DeepPtr<RPGItem>> items;
    std::map<std::string,int> categories;

public:
    ContainerModel(QObject* =nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex())const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    //QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
};

#endif // CONTAINERMODEL_H
