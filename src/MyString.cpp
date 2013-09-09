//
//  String.cpp
//  SimpleJsonCpp
//
//  Created by Teki on 13-8-22.
//  Copyright (c) 2013 chenjiajun90@gmail.com
//

#include "MyString.h"
#include "StringImpl.h"
#include <wchar.h>


String::String()
    : _impl(0)
{
}

String::String(const String& other)
    : _impl(other._impl)
{
    if (_impl)
    {
        _impl->retain();
    }
}

String::String(const wchar_t* nullEndStr)
{
    int length = (int)wcslen(nullEndStr);
    _impl = StringImpl::create(nullEndStr, length);
}

String::String(const wchar_t* data, int length)
{
    _impl = StringImpl::create(data, (int)length);
}

String::String(StringImpl* impl)
    : _impl(impl)
{
}

String::~String()
{
    if (_impl)
    {
        _impl->release();
    }
}

String& String::operator=(const String& rhs)
{
    StringImpl* impl = rhs._impl;
    if (impl != _impl)
    {
        if (impl)
        {
            impl->retain();
        }
        if (_impl)
        {
            _impl->release();
        }
        _impl = impl;
    }
    return *this;
}

String String::subString(int offset)
{
    return _impl ? String(_impl->subString(offset)) : String();
}

String String::subString(int begin, int end)
{
    return _impl ? String(_impl->subString(begin, end)) : String();
}

int String::length() const
{
    return _impl ? _impl->length() : 0;
}

const wchar_t* String::data() const
{
    return _impl ? _impl->data() : 0;
}

wchar_t String::at(int index) const
{
    return _impl ? *(_impl->data() + index) : 0;
}

bool String::operator<(const String& rhs) const
{
    return _impl ? _impl->less(rhs._impl) : false;
}