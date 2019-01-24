#include "rpgcontainer.h"
#include <algorithm>
#include <regex>

RPGContainer::RPGContainer()
{

}

RPGContainer::RPGContainer(std::initializer_list<DeepPtr<RPGItem>> a):Container<DeepPtr<RPGItem>>(a){}

RPGContainer RPGContainer::searchWildcardName(std::string s) const{
    RPGContainer out;
    std::function<bool(DeepPtr<RPGItem>)> wildcardcomp=[s](DeepPtr<RPGItem> a)->bool{
        if(a.isValid()){
            return std::regex_match(a->getName(),std::regex("("+s+")(.*)",std::regex::ECMAScript | std::regex::icase));
        }
        return false;
    };
    auto it=std::find_if(cbegin(),cend(),wildcardcomp);
    while(it!=cend()){
        out.push_back(*it);
        it=std::find_if(++it,cend(),wildcardcomp);
    }
    return out;
}
