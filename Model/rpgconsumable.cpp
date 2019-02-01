#include "rpgconsumable.h"

RPGConsumable::RPGConsumable(std::string n,std::string d,double b,bool p):RPGItem(n,d,false),bcost(b),positive(p){}

double RPGConsumable::getBcost()const{return bcost;}
bool RPGConsumable::isPositive()const{return positive;}

void RPGConsumable::setBcost(double b){bcost=b;}
void RPGConsumable::setPositive(bool p){positive=p;}

std::string RPGConsumable::getCategory()const{return "consumable";}
double RPGConsumable::getPrice()const{return positive?bcost:3*bcost;}

RPGItem* RPGConsumable::clone()const{return new RPGConsumable(*this);}
