#pragma once

#include <map>


template<typename T=float>
struct _TSGetter 
{
public:
   virtual T getAt(int t) = 0;
};


template<typename T=float>
struct ConstGetter: _TSGetter<T>
{
private:

    const T val;

public:
    
    ConstGetter(T val);

    T getAt(int t) override;
};


template<typename T=float>
struct ArrayGetter: _TSGetter<T>
{
private:

    T* val;

public:

    ArrayGetter(T val[]);
    ~ArrayGetter();

    T getAt(int t) override;
};


template<typename T=float>
struct MapGetter: _TSGetter<T>
{
private:

    std::map<int, T> val;

public:

    MapGetter(std::map<int, T> val);

    T getAt(int t) override;
};


template<typename T=float>
struct FastMapGetter: _TSGetter<T>
{
private:

    int size;
    T* base;
    T  last;

public:

    FastMapGetter(std::map<int, T> val);
    ~FastMapGetter();

    T getAt(int t) override;
};
