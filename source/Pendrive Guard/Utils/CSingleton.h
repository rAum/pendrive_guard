#ifndef __CSINGLETON_H_
#define __CSINGLETON_H_

#include <cassert>

template <typename T>
class CSingleton
{
public:
    static T * GetSingletonPtr() { return msSingleton; }
    static T & GetSingleton()
    {
        if (msSingleton == 0)
            new T();
        return  *msSingleton;
    }
protected:
    static T *msSingleton;

    CSingleton()
    {
        assert(!msSingleton);
        msSingleton = static_cast<T *> (this);
    }
    ~CSingleton()
    {
        assert(msSingleton);
        msSingleton = 0;
    }
};

#endif // __CSINGLETON_H_ //
