#ifndef CONTAINERMODEL_H
#define CONTAINERMODEL_H
#include <QAbstractListModel>
#include <Model/Container/container.h>
#include <Model/Container/deepptr.h>
#include <Model/rpgitem.h>
#include "Model/Container/rpgcontainer.h"
#include <map>

class ContainerModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum {
        //data
        CompleteInfoRole=16,
        JsonRole=17,
        //setdata
        SetRole=18
    };
private:
    /*Container<DeepPtr<RPGItem>> items;*/
    RPGContainer items;
    std::map<std::string,int> categories;

public:
    ContainerModel(QObject* =nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex())const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    //QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    bool validateRow(int row,QString,bool,bool,bool,const QModelIndex&) const;
};

#endif // CONTAINERMODEL_H
