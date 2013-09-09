//
//  RefCounted.h
//  SimpleJsonCpp
//
//  Created by Chen Jiajun on 13-8-24.
//  Copyright (c) 2013 chenjiajun90@gmail.com
//

#ifndef SimpleJsonCpp_RefCounted_h
#define SimpleJsonCpp_RefCounted_h

#include <cassert>

template <typename T>
class RefCounted
{
private:
    int _refCount;

public:
    void retain()
    {
        ++_refCount;
    }
    
    void release()
    {
        assert(_refCount);
        --_refCount;
        if (_refCount == 0)
        {
            delete static_cast<T*>(this);
        }
    }
    
    int refCount() const
    {
        return _refCount;
    }
    
protected:
    RefCounted()
        : _refCount(1)
    {
    }
    
    ~RefCounted()
    {
    }
};

#endif
