#include "rpgweapon.h"

const double RPGWeapon::increase_per_level=1.5;
const double RPGWeapon::unique_boost=50;
const std::string RPGWeapon::weapon_identifier="weapon";

RPGWeapon::RPGWeapon(std::string n,std::string d,bool u,double bd,int l,bool o):RPGItem(n,d,u),bdamage(bd),level(l),onehanded(o){}

double RPGWeapon::damage()const{
    double dam=bdamage+increase_per_level*level;
    return onehanded?dam:2*dam;
}

double RPGWeapon::getBdamage()const{return bdamage;}
int RPGWeapon::getLevel()const{return level;}
bool RPGWeapon::isOneHanded()const{return onehanded;}

void RPGWeapon::setLevel(int l){level=l;}
void RPGWeapon::setBDamage(double b){bdamage=b;}
void RPGWeapon::setOneHanded(bool o){onehanded=o;}

std::string RPGWeapon::getCategory()const{return weapon_identifier;}
double RPGWeapon::getPrice()const{
    double price=level*increase_per_level;
    return isUnique()?price+unique_boost:price;
}
RPGItem* RPGWeapon::clone()const{return new RPGWeapon(*this);}
