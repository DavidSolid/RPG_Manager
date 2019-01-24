#ifndef RPGCONTAINER_H
#define RPGCONTAINER_H
#include "Model/Container/container.h"
#include "Model/Container/deepptr.h"
#include "Model/rpgitem.h"

class RPGContainer : public Container<DeepPtr<RPGItem>>
{
public:
    RPGContainer();
    RPGContainer(std::initializer_list<DeepPtr<RPGItem>>);

    RPGContainer searchWildcardName(std::string) const;
};

#endif // RPGCONTAINER_H
