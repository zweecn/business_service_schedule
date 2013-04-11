#ifndef SINGLETON_H
#define SINGLETON_H

#include <cstdio>

template<typename T>
class Singleton
{
public:
    static T *getInstance()
    {
        if (instance == NULL) {
            instance = new T;
        }
        return instance;

    }
protected:
    Singleton(){}
    Singleton(const Singleton &s){}
    void operator=(const Singleton &rhs){}

private:
    static T *instance;
};

template<typename T> T * Singleton<T>::instance = NULL;



#endif // SINGLETON_H
