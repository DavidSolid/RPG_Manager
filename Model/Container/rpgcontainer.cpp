#include "rpgcontainer.h"
#include <algorithm>
#include <regex>

RPGContainer::RPGContainer(){}

RPGContainer::RPGContainer(const Container<DeepPtr<RPGItem> >& a):Container<DeepPtr<RPGItem>>(a)
{

}

RPGContainer::RPGContainer(std::initializer_list<DeepPtr<RPGItem>> a):Container<DeepPtr<RPGItem>>(a){}

RPGContainer RPGContainer::searchWildcardName(std::string s) const{
    std::function<bool(DeepPtr<RPGItem>)> wildcardcomp=[s](DeepPtr<RPGItem> a)->bool{
        if(a.isValid()){
            return std::regex_match(a->getName(),std::regex("("+s+")(.*)",std::regex::ECMAScript | std::regex::icase));
        }
        return false;
    };
    return search(wildcardcomp);
}

RPGContainer RPGContainer::searchAllByType(bool w,bool a,bool c) const{
    std::function<bool(DeepPtr<RPGItem>)> typeeval=[w,a,c](DeepPtr<RPGItem> el)->bool{
        if(el.isValid()){
            return (w && el->getCategory()=="weapon") || (a && el->getCategory()=="armor") || (c && el->getCategory()=="consumable");
        }
        return false;
    };
    return search(typeeval);
}
