#ifndef DEEPPTR_H
#define DEEPPTR_H
template<typename T>
class DeepPtr{
private:
    T* holding;
public:
    DeepPtr();
    DeepPtr(const T&);
    DeepPtr(const DeepPtr&);
    ~DeepPtr();
    DeepPtr& operator=(const DeepPtr&);
    DeepPtr& operator=(DeepPtr&&);
    bool isValid() const;
    T& operator*()const;
    T* operator->()const;
};
template<typename T>
DeepPtr<T>::DeepPtr():holding(nullptr){}

template<typename T>
DeepPtr<T>::DeepPtr(const T& a):holding(a.clone()){}

template<typename T>
DeepPtr<T>::DeepPtr(const DeepPtr& a){
    if(a.holding){
        holding=a.holding->clone();
    }
    else holding=nullptr;
}

template<typename T>
DeepPtr<T>::~DeepPtr(){
    delete holding;
}

template<typename T>
DeepPtr<T>& DeepPtr<T>::operator=(const DeepPtr& a){
    if(holding!=a.holding){
        delete holding;
        if(a.holding){
            holding=a.holding->clone();
        }
        else holding=nullptr;
    }
    return *this;
}

template<typename T>
DeepPtr<T>& DeepPtr<T>::operator=(DeepPtr&& a){
    if(holding){
        delete holding;
    }
    holding=a.holding;
    a.holding=nullptr;
    return *this;
}

template<typename T>
bool DeepPtr<T>::isValid() const{return holding!=nullptr;}

template<typename T>
T& DeepPtr<T>::operator*()const{return *holding;}

template<typename T>
T* DeepPtr<T>::operator->()const{return holding;}
#endif // DEEPPTR_H
