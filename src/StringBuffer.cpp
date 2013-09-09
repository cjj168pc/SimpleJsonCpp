//
//  StringBuffer.cpp
//  SimpleJsonCpp
//
//  Created by Teki on 13-8-22.
//  Copyright (c) 2013 chenjiajun90@gmail.com
//

#include "StringBuffer.h"
#include <cstring>
#include <cassert>


StringBuffer::StringBuffer()
    : _buffer(0), _size(0), _refCount(0)
{
    retain();
}

StringBuffer* StringBuffer::create()
{
    return new StringBuffer;
}

StringBuffer* StringBuffer::create(int size)
{
    StringBuffer* sb = new StringBuffer;
    sb->resize(size);
    return sb;
}

StringBuffer* StringBuffer::create(const wchar_t* ref, int length)
{
    StringBuffer* sb = new StringBuffer;
    sb->resize(length);
    memcpy(sb->buffer(), ref, length * sizeof(wchar_t));
    return sb;
}

StringBuffer::~StringBuffer()
{
    assert(_refCount == 0);
    if (_buffer)
    {
        delete[] _buffer;
    }
}

const wchar_t* StringBuffer::buffer() const
{
    return _buffer;
}

wchar_t* StringBuffer::buffer()
{
    return _buffer;
}

int StringBuffer::size() const
{
    return _size;
}

void StringBuffer::resize(int size)
{
    wchar_t* newbuff = new wchar_t[size];
    if (_buffer)
    {
        int min = size;
        if (_size < min)
        {
            min = _size;
        }
        memcpy(newbuff, _buffer, min * sizeof(wchar_t));
        delete[] _buffer;
    }
    _size = size;
    _buffer = newbuff;
}

void StringBuffer::retain()
{
    ++_refCount;
}

void StringBuffer::release()
{
    assert(_refCount);
    --_refCount;
    if (_refCount == 0)
    {
        delete this;
    }
}
