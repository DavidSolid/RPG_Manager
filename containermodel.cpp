#include "containermodel.h"
#include <QIcon>
#include "Model/rpgweapon.h" //da eliminare, solo per moc
#include "Model/rpgarmor.h" //da eliminare, solo per moc
#include "Model/rpgconsumable.h" //da eliminare, solo per moc

ContainerModel::ContainerModel(QObject* parent):QAbstractListModel(parent)
{
    categories={{"weapon",0},{"armor",1},{"consumable",2}};
    /*items={RPGWeapon("Frangialba","Tesoro daedrico di Meridia",true,15.1,100,true),RPGWeapon("Wuuthrad","Ascia di Ysgramor",true,60,100,false),
           RPGArmor("Armatura del Berserk","Gatsu enorme",true,RPGArmor::mithril,100),RPGWeapon("La mazza che non ammazza","Mazza in plastica con decorazioni di carnevale, utilizzata da Corky il clown",false,12,23,false),
          RPGArmor("Un paio di stracci","Sono dei semplici stracci, nulla di più",true,RPGArmor::mithril,1),RPGWeapon("AYYYYLMA00000", "Arma aliena che disintegra i bersagli a colpi di dubstep",false,69,99,false),
          RPGWeapon("Mazzetta di banconote", "Ora potrai sbeffeggiare i tuoi avversari facendoli sentire dei poveracci", true,18,15,false),RPGConsumable("Pozione draconica","Grazie a questo elisir potrai vedere i drachi!",5,false),
          RPGConsumable("pozione bella","E' una pozione bella",5,true),RPGArmor("Armatura di ferro","Gatsu enorme",false,RPGArmor::iron,50)};*/
}

int ContainerModel::rowCount(const QModelIndex &)const{
    return static_cast<int>(items.size());
}

QVariant ContainerModel::data(const QModelIndex & item,int role) const{
    QVariant out;
    unsigned int index=static_cast<unsigned int>(item.row());
    DeepPtr<RPGItem> obj=items[index];
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
    case CompleteInfoRole:{
        QVariantMap map;
        std::string category=obj->getCategory();
        map.insert("name",QString::fromStdString(obj->getName()));
        map.insert("description",QString::fromStdString(obj->getDesc()));
        switch(categories.at(category)){
        case 0:
            map.insert("category",tr("Arma"));
            map.insert("b_damage",dynamic_cast<RPGWeapon&>(*obj).getBdamage());
            map.insert("damage",dynamic_cast<RPGWeapon&>(*obj).damage());
            map.insert("level",dynamic_cast<RPGWeapon&>(*obj).getLevel());
            map.insert("onehanded",dynamic_cast<RPGWeapon&>(*obj).isOneHanded());
            map.insert("legendary",obj->isUnique());
            break;
        case 1:
            map.insert("category",tr("Armatura"));
            map.insert("defence",dynamic_cast<RPGArmor&>(*obj).defense());
            map.insert("level",dynamic_cast<RPGArmor&>(*obj).getLevel());
            map.insert("type",QString::fromStdString(dynamic_cast<RPGArmor&>(*obj).getType()));
            map.insert("legendary",obj->isUnique());
            break;
        case 2:
            map.insert("category",tr("Consumabile"));
            map.insert("b_cost",dynamic_cast<RPGConsumable&>(*obj).getBcost());
            map.insert("positive",dynamic_cast<RPGConsumable&>(*obj).isPositive());
            break;
        }
        map.insert("price",obj->getPrice());
        out=map;
        break;}
    case JsonRole:
        QVariantMap json;
        json.insert("category",QString::fromStdString(obj->getCategory()));
        json.insert("name",QString::fromStdString(obj->getName()));
        json.insert("description",QString::fromStdString(obj->getDesc()));
        switch(categories.at(obj->getCategory())){
        case 0:
            json.insert("legendary",obj->isUnique());
            json.insert("b_damage",dynamic_cast<RPGWeapon&>(*obj).getBdamage());
            json.insert("level",dynamic_cast<RPGWeapon&>(*obj).getLevel());
            json.insert("onehanded",dynamic_cast<RPGWeapon&>(*obj).isOneHanded());
            break;
        case 1:
            json.insert("legendary",obj->isUnique());
            json.insert("type",QString::fromStdString(dynamic_cast<RPGArmor&>(*obj).getType()));
            json.insert("level",dynamic_cast<RPGArmor&>(*obj).getLevel());
            break;
        case 2:
            json.insert("b_cost",dynamic_cast<RPGConsumable&>(*obj).getBcost());
            json.insert("positive",dynamic_cast<RPGConsumable&>(*obj).isPositive());
            break;
        }
        out=json;
        break;
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

bool ContainerModel::setData(const QModelIndex& item, const QVariant& value, int role){
    unsigned int index=static_cast<unsigned int>(item.row()); //neg. -1
    DeepPtr<RPGItem>& oldobj=items[index];
    QVariantMap newobj=value.toMap();
    switch(role){
    case Qt::EditRole:
        switch(categories.at(newobj["category"].toString().toStdString())){
        case 0:
            oldobj=RPGWeapon(newobj["name"].toString().toStdString(),newobj["description"].toString().toStdString(),newobj["legendary"].toBool(),newobj["b_damage"].toDouble(),newobj["level"].toInt(),newobj["onehanded"].toBool());
            break;
        case 1:
            RPGArmor::armorclass type;
            if(newobj["type"].type()==QMetaType::Int){
                type=RPGArmor::fromInt(newobj["type"].toInt());
            }
            else{
                type=RPGArmor::fromString(newobj["type"].toString().toStdString());
            }
            oldobj=RPGArmor(newobj["name"].toString().toStdString(),newobj["description"].toString().toStdString(),newobj["legendary"].toBool(),type,newobj["level"].toInt());
            break;
        case 2:
            oldobj=RPGConsumable(newobj["name"].toString().toStdString(),newobj["description"].toString().toStdString(),newobj["b_cost"].toDouble(),newobj["positive"].toBool());
            break;
        }
        break;
    case SetRole:
        oldobj->setName(newobj["name"].toString().toStdString());
        oldobj->setDesc(newobj["description"].toString().toStdString());
        switch(categories[newobj["category"].toString().toStdString()]){
        case 0:
            oldobj->setUnique(newobj["legendary"].toBool());
            dynamic_cast<RPGWeapon&>(*oldobj).setBDamage(newobj["b_damage"].toDouble());
            dynamic_cast<RPGWeapon&>(*oldobj).setLevel(newobj["level"].toInt());
            dynamic_cast<RPGWeapon&>(*oldobj).setOneHanded(newobj["onehanded"].toBool());
            break;
        case 1:
            oldobj->setUnique(newobj["legendary"].toBool());
            dynamic_cast<RPGArmor&>(*oldobj).setLevel(newobj["level"].toInt());
            dynamic_cast<RPGArmor&>(*oldobj).setType(RPGArmor::fromInt(newobj["type"].toInt()));
            break;
        case 2:
            dynamic_cast<RPGConsumable&>(*oldobj).setBcost(newobj["b_cost"].toDouble());
            dynamic_cast<RPGConsumable&>(*oldobj).setPositive(newobj["positive"].toBool());
            break;
        }
        break;
    }
    emit dataChanged(item,item);
    return true;
}

bool ContainerModel::insertRows(int row, int count, const QModelIndex &parent){
    beginInsertRows(parent,row,row+count-1);
    for(int i=0;i<count;i++){
        items.insert(items.begin()+row,DeepPtr<RPGItem>());
    }
    endInsertRows();
    return true;
}

bool ContainerModel::removeRows(int row, int count, const QModelIndex &parent){
    if(count){
        beginRemoveRows(parent,row,row+count-1);
        items.erase(items.begin()+row,items.begin()+row+count);
        endRemoveRows();
    }
    return true;
}

bool ContainerModel::validateRow(int row, QString wildcardname, bool w, bool a, bool c, const QModelIndex &) const{
    RPGContainer foundbyname=items.searchWildcardName(wildcardname.toStdString());
    DeepPtr<RPGItem> tovalidate=items[static_cast<unsigned int>(row)];
    RPGContainer foundbytype=items.searchAllByType(w,a,c);
    return std::find_if(foundbyname.cbegin(),foundbyname.cend(),[tovalidate](DeepPtr<RPGItem> a){
        if(tovalidate.isValid()){
            return a->getName()==tovalidate->getName();
        }
        else return false;
    })!=foundbyname.cend()
    && std::find_if(foundbytype.cbegin(),foundbytype.cend(),[tovalidate](DeepPtr<RPGItem> a)->bool{
        if(tovalidate.isValid()){
            return a->getName()==tovalidate->getName() && a->getCategory()==tovalidate->getCategory();
        }
        else return false;
    })!=foundbytype.cend();

}
