//
//  RefPtr.h
//  SimpleJsonCpp
//
//  Created by Chen Jiajun on 13-8-24.
//  Copyright (c) 2013 chenjiajun90@gmail.com
//

#ifndef SimpleJsonCpp_RefPtr_h
#define SimpleJsonCpp_RefPtr_h

#include "PassPtr.h"

template <typename T>
class RefPtr
{
private:
    T* _ptr;
    
public:
    RefPtr()
        : _ptr(0)
    {
    }
    
    ~RefPtr()
    {
        if (_ptr)
        {
            _ptr->release();
        }
    }
    
    inline T* get() const
    {
        return _ptr;
    }
    
    RefPtr(const RefPtr& other)
        : _ptr(other.get())
    {
        if (_ptr)
        {
            _ptr->retain();
        }
    }
    
    template <typename U>
    RefPtr(const RefPtr<U>& other)
        : _ptr(other.get())
    {
        if (_ptr)
        {
            _ptr->retain();
        }
    }
    
    RefPtr(const PassPtr<T>& rhs)
    {
        _ptr = rhs.leak();
    }
    
    RefPtr(T* ptr)
        : _ptr(ptr)
    {
        if (ptr)
        {
            _ptr->retain();
        }
    }
    
    template <typename U>
    RefPtr(U* ptr)
        : _ptr(ptr)
    {
        if (ptr)
        {
            _ptr->retain();
        }
    }
    
    PassPtr<T> release()
    {
        PassPtr<T> pass = adoptRef(_ptr);
        _ptr = 0;
        return pass;
    }
    
    RefPtr& operator=(const RefPtr& rhs)
    {
        T* ptr = rhs.get();
        if (_ptr != ptr)
        {
            if (ptr)
            {
                ptr->retain();
            }
            if (_ptr)
            {
                _ptr->release();
            }
            _ptr = ptr;
        }
        return *this;
    }
    
    template <typename U>
    RefPtr& operator=(const RefPtr<U>& rhs)
    {
        U* ptr = rhs.get();
        if (_ptr != ptr)
        {
            if (ptr)
            {
                ptr->retain();
            }
            if (_ptr)
            {
                _ptr->release();
            }
            _ptr = ptr;
        }
        return *this;
    }
    
    RefPtr& operator=(const PassPtr<T>& pass)
    {
        if (pass.get() != _ptr)
        {
            if (_ptr)
            {
                _ptr->release();
            }
            _ptr = pass.leak();
        }
        return *this;
    }
    
    template <typename U>
    RefPtr& operator=(const PassPtr<U>& pass)
    {
        if (pass.get() != _ptr)
        {
            if (_ptr)
            {
                _ptr->release();
            }
            _ptr = pass.leak();
        }
        return *this;
    }
    
    T* operator->()
    {
        return _ptr;
    }
    
    const T* operator->() const
    {
        return _ptr;
    }
    
    T& operator*()
    {
        return *_ptr;
    }
    
    const T& operator*() const
    {
        return *_ptr;
    }
    
    bool isNull() const
    {
        return !_ptr;
    }
};


template <typename T, typename U>
RefPtr<T> ref_static_cast(const RefPtr<U>& from)
{
    return RefPtr<T>(static_cast<T*>(from.get()));
}

template <typename T, typename U>
RefPtr<T> ref_const_cast(const RefPtr<U>& from)
{
    return RefPtr<T>(const_cast<T*>(from.get()));
}

template <typename T, typename U>
bool operator==(const RefPtr<T>& lhs, const RefPtr<U>& rhs)
{
    return lhs.get() == rhs.get();
}

template <typename T, typename U>
bool operator==(const RefPtr<T>& lhs, U* rhs)
{
    return lhs.get() == rhs;
}

template <typename T, typename U>
bool operator==(T* lhs, const RefPtr<U>& rhs)
{
    return lhs == rhs.get();
}

template <typename T, typename U>
bool operator==(const RefPtr<T>& lhs, const PassPtr<U>& rhs)
{
    return lhs.get() == rhs.get();
}

template <typename T, typename U>
bool operator==(const PassPtr<T>& lhs, const RefPtr<U>& rhs)
{
    return lhs.get() == rhs.get();
}

template <typename T, typename U>
bool operator!=(const RefPtr<T>& lhs, const RefPtr<U>& rhs)
{
    return lhs.get() != rhs.get();
}

template <typename T, typename U>
bool operator!=(const RefPtr<T>& lhs, U* rhs)
{
    return lhs.get() != rhs;
}

template <typename T, typename U>
bool operator!=(T* lhs, const RefPtr<U>& rhs)
{
    return lhs != rhs.get();
}

template <typename T, typename U>
bool operator!=(const RefPtr<T>& lhs, const PassPtr<U>& rhs)
{
    return lhs.get() != rhs.get();
}

template <typename T, typename U>
bool operator!=(const PassPtr<T>& lhs, const RefPtr<U>& rhs)
{
    return lhs.get() != rhs.get();
}

#endif
