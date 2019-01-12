#include "rpgarmor.h"

const double RPGArmor::increase_per_level=2;
const double RPGArmor::unique_boost=25;

RPGArmor::armorclass RPGArmor::fromString(std::string s){
    if(s=="wood"){
        return wood;
    }
    if(s=="bronze"){
        return bronze;
    }
    if(s=="iron"){
        return iron;
    }
    if(s=="steel"){
        return steel;
    }
    //if(s=="mithril"){
        return mithril;
    //}
}

RPGArmor::RPGArmor(std::string n,std::string d,bool u,armorclass t,int l):RPGItem(n,d,u),type(t),level(l){}

int RPGArmor::getLevel()const{return level;}

std::string RPGArmor::getType()const{
    std::string out;
    switch(type){
    case wood:
        out="wood";
        break;
    case bronze:
        out="bronze";
        break;
    case iron:
        out="iron";
        break;
    case steel:
        out="steel";
        break;
    case mithril:
        out="mithril";
        break;
    }
    return out;
}

double RPGArmor::defense()const{return (type+1)*increase_per_level*level;}

void RPGArmor::setType(armorclass t){type=t;}

void RPGArmor::setLevel(int l){level=l;}

std::string RPGArmor::getCategory()const{return "armor";}

double RPGArmor::getPrice()const{
    double price=level+type;
    if(isUnique()){
        price+=unique_boost;
    }
    return price;
}

RPGItem* RPGArmor::clone()const{return new RPGArmor(*this);}
