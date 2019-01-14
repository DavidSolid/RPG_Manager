#ifndef CONTAINER_H
#define CONTAINER_H
#include <functional>
#include <algorithm>
#include <iterator>
#include <cmath>

template<typename T>
class Container {
private:
    T* buffer;
    unsigned int capacity_b;
    unsigned int size_b;

    //private methods
    void expandBuffer();
public:
    class iterator {
        friend class Container;
    private:
        T* owned;
        iterator(T*);
    public:
        typedef T value_type;
        typedef std::ptrdiff_t difference_type;
        typedef T& reference;
        typedef T* pointer;
        typedef std::random_access_iterator_tag iterator_category;

        reference operator*()const;
        reference operator[](unsigned int)const;
        pointer operator->() const;

        iterator& operator++();
        iterator operator++(int);
        iterator& operator--();
        iterator operator--(int);
        iterator operator+(int)const;
        iterator operator-(int)const;
        difference_type operator-(const iterator&)const;

        iterator& operator+=(int);
        iterator& operator-=(int);

        bool operator>(const iterator&)const;
        bool operator>=(const iterator&)const;
        bool operator<(const iterator&)const;
        bool operator<=(const iterator&)const;

        bool operator==(const iterator&)const;
        bool operator!=(const iterator&)const;
    };
    class const_iterator {
        friend class Container;
    private:
        const T* owned;
        const_iterator(const T*);
    public:
        const T& operator*()const;
        const T& operator[](unsigned int)const;
        const T* operator->();

        const_iterator operator++();
        const_iterator operator++(int);
        const_iterator operator--();
        const_iterator operator--(int);

        bool operator !=(const const_iterator&);
    };
    //Constructor and Destructor
    Container();
    Container(std::initializer_list<T>);
    Container(const Container&);
    Container(Container&&);
    ~Container();

    //operators overload
    Container& operator=(const Container&);
    Container& operator=(Container&&);
    T& operator[](unsigned int)const;

    //iterators method
    iterator begin();
    const_iterator cbegin()const;
    iterator end();
    const_iterator cend()const;

    //information about dimensions
    unsigned int size()const;
    unsigned int capacity()const;
    bool empty()const;

    //buffer modifiers
    void push_back(const T&);
    void insert(iterator,const T&);
    iterator erase(iterator);
    iterator erase(iterator,iterator);
    void sort(std::function<bool(const T&,const T&)>);

    //data methods
    T& at(unsigned int)const;
};

//iterator methods definition
template<typename T>
Container<T>::iterator::iterator(T* a) :owned(a) {}

template<typename T>
typename Container<T>::iterator::reference Container<T>::iterator::operator*()const { return *owned; }

template<typename T>
typename Container<T>::iterator::reference Container<T>::iterator::operator[](unsigned int n)const { return *(owned + n); }

template<typename T>
typename Container<T>::iterator::pointer Container<T>::iterator::operator->()const { return owned; }

template<typename T>
typename Container<T>::iterator& Container<T>::iterator::operator++() {
    ++owned;
    return *this;
}

template<typename T>
typename Container<T>::iterator Container<T>::iterator::operator++(int) {
    iterator out(*this);
    ++owned;
    return out;
}

template<typename T>
typename Container<T>::iterator& Container<T>::iterator::operator--(){
    --owned;
    return *this;
}

template<typename T>
typename Container<T>::iterator Container<T>::iterator::operator--(int){
    iterator out(*this);
    --owned;
    return out;
}

template<typename T>
typename Container<T>::iterator Container<T>::iterator::operator+(int offset) const{
    return iterator(owned+offset);
}

template<typename T>
typename Container<T>::iterator Container<T>::iterator::operator-(int offset) const{
    return iterator(owned-offset);
}

template<typename T>
typename Container<T>::iterator::difference_type Container<T>::iterator::operator-(const iterator & a) const{
    return owned-a.owned;
}

template<typename T>
typename Container<T>::iterator& Container<T>::iterator::operator+=(int diff){
    owned+=diff;
    return *this;
}

template<typename T>
typename Container<T>::iterator& Container<T>::iterator::operator-=(int diff){
    owned-=diff;
    return *this;
}

template<typename T>
bool Container<T>::iterator::operator>(const iterator & a) const{
    return owned>a.owned;
}

template<typename T>
bool Container<T>::iterator::operator>=(const iterator & a) const{
    return owned >= a.owned;
}

template<typename T>
bool Container<T>::iterator::operator<(const iterator & a) const
{
    return owned < a.owned;
}

template<typename T>
bool Container<T>::iterator::operator<=(const iterator & a) const{
    return owned <= a.owned;
}

template<typename T>
bool Container<T>::iterator::operator==(const iterator& a)const{
    return owned==a.owned;
}

template<typename T>
bool Container<T>::iterator::operator!=(const iterator & a)const{
    return owned != a.owned;
}

//const_iterator methods definition
template<typename T>
Container<T>::const_iterator::const_iterator(const T* a) :owned(a) {}

template<typename T>
const T& Container<T>::const_iterator::operator*()const { return *owned; }

template<typename T>
const T& Container<T>::const_iterator::operator[](unsigned int n)const { return *(owned + n); }

template<typename T>
const T* Container<T>::const_iterator::operator->() { return owned; }

template<typename T>
typename Container<T>::const_iterator Container<T>::const_iterator::operator++() {
    ++owned;
    return *this;
}

template<typename T>
typename Container<T>::const_iterator Container<T>::const_iterator::operator++(int) {
    const_iterator out(*this);
    ++owned;
    return out;
}

template<typename T>
typename Container<T>::const_iterator Container<T>::const_iterator::operator--(){
    const_iterator out(*this);
    --owned;
    return out;
}

template<typename T>
typename Container<T>::const_iterator Container<T>::const_iterator::operator--(int){
    --owned;
    return *this;
}

template<typename T>
bool Container<T>::const_iterator::operator!=(const const_iterator & a){
    return owned!=a.owned;
}

//container constructor and destructor methods definition
template<typename T>
Container<T>::Container() :buffer(0), capacity_b(0), size_b(0) {}

template<typename T>
Container<T>::Container(std::initializer_list<T> il):capacity_b(pow(2,ceil(log2(il.size())))),size_b(il.size()){
    buffer=new T[capacity_b];
    int index=0;
    for(auto it=il.begin();it!=il.end();++it){
        buffer[index]=*it;
        ++index;
    }
}

template<typename T>
Container<T>::Container(const Container& a) : buffer(new T[a.capacity()]), capacity_b(a.capacity()), size_b(a.size()) {
    for (unsigned int i = 0; i < a.size(); ++i) {
        buffer[i] = a.buffer[i];
    }
}

template<typename T>
Container<T>::Container(Container && a):buffer(a.buffer),capacity_b(a.capacity_b),size_b(a.size_b){
    a.buffer = nullptr;
}

template<typename T>
Container<T>::~Container() { delete[] buffer; }

//operator overloads method
template<typename T>
Container<T>& Container<T>::operator=(const Container<T>& a) {
    if (this != &a) {
        delete[] buffer;
        buffer = new T[a.capacity()];
        size_b = a.size();
        capacity_b = a.capacity();
        for (unsigned int i = 0; i < size(); ++i) {
            buffer[i] = a.buffer[i];
        }
    }
    return *this;
}

template<typename T>
Container<T>& Container<T>::operator=(Container<T> && a){
    delete[] buffer;
    buffer = a.buffer;
    size_b = a.size_b;
    capacity_b = a.capacity_b;
    a.buffer = nullptr;
    return *this;
}

template<typename T>
T& Container<T>::operator[](unsigned int n)const { return buffer[n]; }

//iterator methods definition
template<typename T>
typename Container<T>::iterator Container<T>::begin() { return iterator(buffer); }

template<typename T>
typename Container<T>::const_iterator Container<T>::cbegin()const { return const_iterator(buffer); }

template<typename T>
typename Container<T>::iterator Container<T>::end() { return iterator(buffer + size_b); }

template<typename T>
typename Container<T>::const_iterator Container<T>::cend()const { return const_iterator(buffer + size_b); }

//container private methods
template<typename T>
void Container<T>::expandBuffer(){
    T* nbuffer;
    unsigned int nsize;
    if (!size_b) {
        nsize = 1;
    }
    else {
        nsize = 2 * capacity_b;
    }
    nbuffer = new T[nsize];
    for (unsigned int i = 0; i < size_b; ++i) {
        nbuffer[i] = buffer[i];
    }
    capacity_b = nsize;
    delete[] buffer;
    buffer = nbuffer;
}

//dimension method definition
template<typename T>
unsigned int Container<T>::size()const { return size_b; }

template<typename T>
unsigned int Container<T>::capacity()const { return capacity_b; }

template<typename T>
bool Container<T>::empty()const { return size(); }

//buffer modifiers definition
template<typename T>
void Container<T>::push_back(const T& element) {
    if (size_b == capacity_b) {
        expandBuffer();
    }
    buffer[size_b] = element;
    ++size_b;
}

template<typename T>
void Container<T>::insert(Container<T>::iterator pos, const T & a){
    int index=pos-begin();
    if(size_b==capacity_b){
        expandBuffer();
    }
    pos=begin()+index;
    iterator it=end();
    int i=0;
    for(;it!=pos;--it){
        *it=it[-1]; //forse problema qui
        ++i;
    }
    *it=a;
    ++size_b;
}

template<typename T>
typename Container<T>::iterator Container<T>::erase(Container<T>::iterator e){
    return erase(e,e+1);
}

template<typename T>
typename Container<T>::iterator Container<T>::erase(Container<T>::iterator i, Container<T>::iterator f){
    iterator out=i;
    for(;f!=end();++i){
        *i=*f;
        ++f;
    }
    size_b-=f-i;
    return out;
}
template<typename T>
void Container<T>::sort(std::function<bool(const T&, const T&)> foo){
    std::stable_sort(begin(), end(), foo);
}
#endif
