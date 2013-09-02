//
//  PassPtr.h
//  SimpleJsonCpp
//
//  Created by Chen Jiajun on 13-8-24.
//  Copyright (c) 2013 chenjiajun90@gmail.com
//

#ifndef SimpleJsonCpp_PassPtr_h
#define SimpleJsonCpp_PassPtr_h

template <typename T>
class PassPtr
{
private:
    mutable T* _ptr;
    
public:
    PassPtr()
        : _ptr(0)
    {
    }
    
    T* leak() const
    {
        T* tmp = _ptr;
        _ptr = 0;
        return tmp;
    }
    
    T* get() const
    {
        return _ptr;
    }
    
    PassPtr(const PassPtr& other)
    {
        _ptr = other.leak();
    }
    
    PassPtr(T* ptr)
        : _ptr(ptr)
    {
        if (ptr)
        {
            ptr->retain();
        }
    }
    
    template <typename U>
    PassPtr(U* ptr)
        : _ptr(ptr)
    {
        if (ptr)
        {
            ptr->retain();
        }
    }
    
    PassPtr& operator=(const PassPtr& rhs)
    {
        if (_ptr != rhs.get())
        {
            if (_ptr)
            {
                _ptr->release();
            }
            _ptr = rhs.leak();
        }
        return *this;
    }
    
    template <typename U>
    PassPtr& operator=(const PassPtr<U>& rhs)
    {
        if (_ptr != rhs.get())
        {
            if (_ptr)
            {
                _ptr->release();
            }
            _ptr = rhs.leak();
        }
        return *this;
    }
    
    ~PassPtr()
    {
        if (_ptr)
        {
            _ptr->release();
        }
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

	T* operator()()
	{
		return _ptr;
	}

	const T* operator()() const
	{
		return _ptr;
	}
    
    template <typename U>
    friend PassPtr<U> adoptRef(U* ptr);
};


template <typename T>
PassPtr<T> adoptRef(T* ptr)
{
    PassPtr<T> pass;
    pass._ptr = ptr;
    return pass;
}

template <typename T, typename U>
bool operator==(const PassPtr<T>& lhs, const PassPtr<U>& rhs)
{
    return lhs.get() == rhs.get();
}

template <typename T, typename U>
bool operator==(const PassPtr<T>& lhs, U* rhs)
{
    return lhs.get() == rhs;
}

template <typename T, typename U>
bool operator==(T* lhs, const PassPtr<U>& rhs)
{
    return lhs == rhs.get();
}

template <typename T, typename U>
bool operator!=(const PassPtr<T>& lhs, const PassPtr<U>& rhs)
{
    return lhs.get() != rhs.get();
}

template <typename T, typename U>
bool operator!=(const PassPtr<T>& lhs, U* rhs)
{
    return lhs.get() != rhs;
}

template <typename T, typename U>
bool operator!=(T* lhs, const PassPtr<U>& rhs)
{
    return lhs != rhs.get();
}

#endif
