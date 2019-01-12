#include "containermodel.h"
#include <QIcon>
#include "Model/rpgweapon.h" //da eliminare, solo per moc
#include "Model/rpgarmor.h" //da eliminare, solo per moc
#include "Model/rpgconsumable.h" //da eliminare, solo per moc

ContainerModel::ContainerModel(QObject* parent):QAbstractListModel(parent)
{
    categories={{"weapon",0},{"armor",1},{"consumable",2}};
    items={RPGWeapon("Frangialba","Tesoro daedrico di Meridia",true,15.1,100,true),RPGWeapon("Wuuthrad","Ascia di Ysgramor",true,60,100,false),
           RPGArmor("Armatura del Berserk","Gatsu enorme",true,RPGArmor::mithril,100),RPGWeapon("La mazza che non ammazza","Mazza in plastica con decorazioni di carnevale, utilizzata da Corky il clown",false,12,23,false),
          RPGArmor("Un paio di stracci","Sono dei semplici stracci, nulla di più",true,RPGArmor::mithril,1),RPGWeapon("AYYYYLMA00000", "Arma aliena che disintegra i bersagli a colpi di dubstep",false,69,99,false),
          RPGWeapon("Mazzetta di banconote", "Ora potrai sbeffeggiare i tuoi avversari facendoli sentire dei poveracci", true,18,15,false),RPGConsumable("Pozione draconica","Grazie a questo elisir potrai vedere i drachi!",5,false),
          RPGConsumable("pozione bella","E' una pozione bella",5,true),RPGArmor("Armatura di ferro","Gatsu enorme",false,RPGArmor::iron,50)};
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
        switch(categories.at(items[index]->getCategory())){
        case 0:
            out=QIcon(":/sword.png");
            break;
        case 1:
            out=QIcon(":/armor.png");
            break;
        case 2:
            out=QIcon(":/potion.png");
            break;
        }
        /*if(items[index]->getCategory()=="weapon"){
            out=QIcon(":/sword.png");
        }
        if(items[index]->getCategory()=="armor"){
            out=QIcon(":/armor.png");
        }
        if(items[index]->getCategory()=="consumable"){
            out=QIcon(":/potion.png");
        }*/
        break;
    case DescriptionRole:
        out=QString::fromStdString(items[index]->getDesc());
        break;
    case CompleteInfoRole:
        DeepPtr<RPGItem> item=items[index];
        QVariantMap map;
        std::string category=item->getCategory();
        switch(categories.at(category)){
        case 0:
            map.insert("category",tr("Arma"));
            map.insert("damage",dynamic_cast<RPGWeapon&>(*item).damage());
            map.insert("level",dynamic_cast<RPGWeapon&>(*item).getLevel());
            map.insert("onehanded",dynamic_cast<RPGWeapon&>(*item).isOneHanded());
            map.insert("legendary",item->isUnique());
            break;
        case 1:
            map.insert("category",tr("Armatura"));
            map.insert("defence",dynamic_cast<RPGArmor&>(*item).defense());
            map.insert("level",dynamic_cast<RPGArmor&>(*item).getLevel());
            map.insert("type",QString::fromStdString(dynamic_cast<RPGArmor&>(*item).getType()));
            map.insert("legendary",item->isUnique());
            break;
        case 2:
            map.insert("category",tr("Oggetto Consumabile"));
            map.insert("positive",dynamic_cast<RPGConsumable&>(*item).isPositive());
            break;
        }
        map.insert("price",item->getPrice());
        out=map;
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
