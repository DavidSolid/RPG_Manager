#ifndef RPGARMOR_H
#define RPGARMOR_H
#include "rpgitem.h"

class RPGArmor : public RPGItem
{
public:
    enum armorclass{
        wood,
        bronze,
        iron,
        steel,
        mithril
    };
private:
    armorclass type;
    int level;

    static const double increase_per_level;
    static const double unique_boost;
public:
    static armorclass fromString(std::string);
    static armorclass fromInt(int);
    RPGArmor(std::string,std::string,bool,armorclass,int);
    std::string getType()const;
    int getLevel()const;
    double defense()const;

    void setType(armorclass);
    void setLevel(int);

    std::string getCategory()const final;
    double getPrice()const override;
    RPGItem* clone()const override;
};

#endif // RPGARMOR_H
