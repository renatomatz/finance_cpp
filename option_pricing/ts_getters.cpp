#include <algorithm>
#include <vector>
#include"ts_getters.h"


template<typename T>
ConstGetter<T>::ConstGetter(T val) 
    : val(val) {}


template<typename T>
T ConstGetter<T>::getAt(int t)
{ 
    return val;
}


template<typename T>
ArrayGetter<T>::ArrayGetter(T val[]) 
    : val(val) {}


template<typename T>
ArrayGetter<T>::~ArrayGetter()
{ 
    delete [] val; 
}


template<typename T>
T ArrayGetter<T>::getAt(int t)
{ 
    return val[t]; 
}


template<typename T>
MapGetter<T>::MapGetter(std::map<int, T> val) 
    : val(val) {}
        

template<typename T>
T MapGetter<T>::getAt(int t)
{
    typename std::map<int, T>::iterator last_pair;
    for (typename std::map<int, T>::iterator it = val.begin(); it != val.end(); ++it) 
    {
        if (t < it->first)
            return last_pair->second;
        last_pair = it;
    }
    return last_pair->second;
}


template<typename T>
FastMapGetter<T>::FastMapGetter(std::map<int, T> val)
{
    size = (--val.end())->first;
    base = new T[size];
    int last_key = 0; 

    for (typename std::map<int, T>::iterator it = val.begin(); it != val.end(); ++it) 
    {
        for (int i = last_key; i < it->first; i++)
            base[i] = it->second;
        last_key = it->first;
    }

    last = val[last_key];
}


template<typename T>
FastMapGetter<T>::~FastMapGetter()
{
    delete [] base;
}


template<typename T>
T FastMapGetter<T>::getAt(int t)
{
    if (t < size)
        return base[t];
    else
        return last;
}
