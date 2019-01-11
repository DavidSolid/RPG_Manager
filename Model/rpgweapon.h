#ifndef RPGWEAPON_H
#define RPGWEAPON_H
#include "rpgitem.h"

class RPGWeapon : public RPGItem
{
private:
    double bdamage;
    int level;
    bool onehanded;

    static const double increase_per_level;
    static const double unique_boost;
    static const std::string weapon_identifier;
public:
    RPGWeapon(std::string,std::string,bool,double,int,bool);

    double damage()const;
    int getLevel()const;
    bool isOneHanded()const;

    void setLevel(int);
    void setOneHanded(bool);

    std::string getCategory()const final;
    double getPrice()const override;
    RPGItem* clone()const override;
};

#endif // RPGWEAPON_H
