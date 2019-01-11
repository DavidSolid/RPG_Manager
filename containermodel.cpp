#include "containermodel.h"
#include <QIcon>
#include "Model/rpgweapon.h" //da eliminare, solo per moc
#include "Model/rpgarmor.h" //da eliminare, solo per moc
#include "Model/rpgconsumable.h" //da eliminare, solo per moc

ContainerModel::ContainerModel(QObject* parent):QAbstractListModel(parent)
{
    items={RPGWeapon("Frangialba","Tesoro daedrico di Meridia",true,15.1,100,true),RPGWeapon("Wuuthrad","Ascia di Ysgramor",true,60,100,false),
           RPGArmor("Armatura del Berserk","Gatsu enorme",true,RPGArmor::mithril,100),RPGWeapon("La mazza che non ammazza","Mazza in plastica con decorazioni di carnevale, utilizzata da Corky il clown",false,12,23,false),
          RPGArmor("Un paio di stracci","Sono dei semplici stracci, nulla di più",true,RPGArmor::mithril,1),RPGWeapon("AYYYYLMA00000", "Arma aliena che disintegra i bersagli a colpi di dubstep",false,69,99,false),
          RPGWeapon("Mazzetta di banconote", "Ora potrai sbeffeggiare i tuoi avversari facendoli sentire dei poveracci", true,18,15,false),RPGConsumable("Pozione draconica","Grazie a questo elisir potrai vedere i drachi!",5,false),
          RPGConsumable("pozione bella","E' una pozione bella",5,true)};
}

int ContainerModel::rowCount(const QModelIndex &)const{
    return static_cast<int>(items.size());
}

QVariant ContainerModel::data(const QModelIndex & item,int role) const{
    QVariant out;
    unsigned int index=static_cast<unsigned int>(item.row());
    switch (role) {
    case Qt::DisplayRole:
        /*QVariantMap map;
        map.insert("nome",QVariant(QString::fromStdString(items[index]->getName())));
        out=map;*/
        out=QString::fromStdString(items[index]->getName());
        break;
    case Qt::DecorationRole:
        if(items[index]->getCategory()=="weapon"){
            out=QIcon(":/sword.png");
        }
        if(items[index]->getCategory()=="armor"){
            out=QIcon(":/armor.png");
        }
        if(items[index]->getCategory()=="consumable"){
            out=QIcon(":/potion.png");
        }
        break;
    case DescriptionRole:
        out=QString::fromStdString(items[index]->getDesc());
        break;
    case CompleteInfoRole:
        DeepPtr<RPGItem> item=items[index];
        QVariantMap map;
        map.insert("nome",QVariant(QString::fromStdString(item->getName())));
        map.insert("desc",QVariant(QString::fromStdString(item->getDesc())));

    }
    return out;
}

/*QVariant ContainerModel::headerData(int n,Qt::Orientation o,int role) const{
    QVariant out;
    switch(role){
    case Qt::DisplayRole:
        if(o==Qt::Vertical){
            out=n+1;
        }
        else if(!n){
            out="Oggetti";
        }
        break;
    }
    return out;
}*/
