#ifndef RPGITEM_H
#define RPGITEM_H
#include <string>

class RPGItem
{
private:
    std::string name,desc;
    bool unique;
public:
    RPGItem(std::string,std::string,bool);
    virtual ~RPGItem();

    std::string getName()const;
    std::string getDesc()const;
    bool isUnique()const;

    void setName(std::string);
    void setDesc(std::string);
    void setUnique(bool);

    virtual std::string getCategory()const = 0;
    virtual double getPrice()const = 0;
    virtual RPGItem* clone()const = 0;
};

#endif // RPGITEM_H
