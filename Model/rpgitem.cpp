#include "rpgitem.h"

RPGItem::RPGItem(std::string n,std::string d,bool u):name(n),desc(d),unique(u){}

RPGItem::~RPGItem(){}

std::string RPGItem::getName()const{return name;}

std::string RPGItem::getDesc()const{return desc;}

bool RPGItem::isUnique()const{return unique;}

void RPGItem::setName(std::string n){name=n;}

void RPGItem::setDesc(std::string d){desc=d;}

void RPGItem::setUnique(bool u){unique=u;}
