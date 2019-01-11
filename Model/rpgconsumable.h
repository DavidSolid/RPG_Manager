#ifndef RPGCONSUMABLE_H
#define RPGCONSUMABLE_H
#include "rpgitem.h"

class RPGConsumable : public RPGItem
{
private:
    double bcost;
    bool positive;
public:
    RPGConsumable(std::string,std::string,double,bool);

    bool isPositive()const;

    std::string getCategory()const final;
    double getPrice()const override;
    RPGItem* clone()const override;
};

#endif // RPGCONSUMABLE_H
