//
//  StringBuilder.cpp
//  SimpleJsonCpp
//
//  Created by Teki on 13-8-22.
//  Copyright (c) 2013 chenjiajun90@gmail.com
//

#include "StringBuilder.h"
#include "StringBuffer.h"
#include <cstring>
#include <cwchar>
#include <cassert>


StringBuilder::StringBuilder()
    : _cont(0), _length(0)
{
    _cont = StringBuffer::create(INIT_CAP);
}

StringBuilder::~StringBuilder()
{
    _cont->release();
}

void StringBuilder::append(wchar_t ch)
{
    int size = _length + 1;
    ensureSpace(size);
    *(_cont->buffer() + _length) = ch;
    _length = size;
}

void StringBuilder::append(String str)
{
    append(str.data(), str.length());
}

void StringBuilder::append(const wchar_t* data, int length)
{
    int size = _length + length;
    ensureSpace(size);
    memcpy(_cont->buffer() + _length, data, length * sizeof(wchar_t));
    _length = size;
}

void StringBuilder::appendInt(int num)
{
    static const int INT_LENGTH = 16;
    wchar_t numbuff[INT_LENGTH];
    size_t length = swprintf(numbuff, INT_LENGTH, L"%d", num);
    int size = static_cast<int>(_length + length);
    ensureSpace(size);
    memcpy(_cont->buffer() + _length, numbuff, length * sizeof(wchar_t));
    _length = size;
}

void StringBuilder::appendDouble(double num)
{
    static const int INT_LENGTH = 32;
    wchar_t numbuff[INT_LENGTH];
    size_t length;
    double abso = num < 0 ? -num : num;
    if (abso != 0 && (abso < 0.001 || abso > 100000))
    {
        length = swprintf(numbuff, INT_LENGTH, L"%e", num);
    }
    else
    {
        length = swprintf(numbuff, INT_LENGTH, L"%lf", num);
    }
    int size = static_cast<int>(_length + length);
    ensureSpace(size);
    memcpy(_cont->buffer() + _length, numbuff, length * sizeof(wchar_t));
    _length = size;
}

wchar_t StringBuilder::at(int index) const
{
    return *(_cont->buffer() + index);
}

wchar_t& StringBuilder::at(int index)
{
    return *(_cont->buffer() + index);
}

String StringBuilder::toString() const
{
    return String(_cont->buffer(), _length);
}

void StringBuilder::ensureSpace(int size)
{
    if (size > _cont->size())
    {
        int nsize = _cont->size() * 2;
        if (nsize < size)
        {
            nsize = size;
        }
        _cont->resize(nsize);
    }
}

String StringBuilder::subString(int begin, int end) const
{
    assert(begin < _length && begin >= 0);
    assert(end <= _length && end > begin);
    return String(_cont->buffer() + begin, end - begin);
}

bool StringBuilder::match(int begin, const String& pattern) const
{
    assert(begin >= 0 && begin < _length);
    if (_length - begin < pattern.length())
    {
        return false;
    }
    const wchar_t* end = pattern.data() + pattern.length();
    const wchar_t* p = _cont->buffer() + begin;
    const wchar_t* q = pattern.data();
    while (q != end)
    {
        if (*p != *q)
        {
            return false;
        }
        ++p;
        ++q;
    }
    return true;
}

const wchar_t* StringBuilder::data() const
{
    return _cont->buffer();
}

void StringBuilder::clear()
{
    _length = 0;
}

int StringBuilder::length() const
{
    return _length;
}