//
//  StringImpl.cpp
//  SimpleJsonCpp
//
//  Created by Teki on 13-8-22.
//  Copyright (c) 2013 chenjiajun90@gmail.com
//

#include "StringImpl.h"
#include "StringBuffer.h"
#include <cassert>


StringImpl::StringImpl()
    : _cont(0), _length(0), _offset(0)
{
    retain();
}

StringImpl* StringImpl::create(const wchar_t* src, int length)
{
    StringImpl* si = new StringImpl;
    si->_cont = StringBuffer::create(src, length);
    si->_length = length;
    return si;
}

StringImpl::~StringImpl()
{
    assert(_refCount == 0);
    _cont->release();
}

StringImpl* StringImpl::subString(int offset)
{
    return subString(offset, _length);
}

StringImpl* StringImpl::subString(int begin, int end)
{
    assert(begin < _length && begin >= 0);
    assert(end <= _length && end > begin);
    StringImpl* sub = new StringImpl;
    sub->_cont = _cont;
    _cont->retain();
    sub->_length = end - begin;
    sub->_offset = _offset + begin;
    return sub;
}

int StringImpl::length() const
{
    return _length;
}

const wchar_t* StringImpl::data() const
{
    return _cont->buffer() + _offset;
}

void StringImpl::retain()
{
    _refCount++;
}

void StringImpl::release()
{
    assert(_refCount);
    --_refCount;
    if (_refCount == 0)
    {
        delete this;
    }
}

bool StringImpl::less(const StringImpl* other) const
{
    assert(other);
    const wchar_t* q = other->data();
    const wchar_t* p = data();
    const wchar_t* pend = p + length();
    const wchar_t* qend = q + other->length();
    
    while (p != pend && q != qend)
    {
        if (*p < *q)
        {
            return true;
        }
        else if (*p == *q)
        {
            ++p;
            ++q;
        }
        else
        {
            return false;
        }
    }
    
    return (p == pend) && (q != qend);
}
