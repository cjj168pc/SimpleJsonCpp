//
//  JsonNumber.cpp
//  SimpleJsonCpp
//
//  Created by Chen Jiajun on 13-8-24.
//  Copyright (c) 2013 chenjiajun90@gmail.com
//

#include "JsonNumber.h"


PassPtr<JsonNumber> JsonNumber::create(double num)
{
    JsonNumber* jn = new JsonNumber;
    jn->setValue(num);
    return adoptRef(jn);
}

PassPtr<JsonNumber> JsonNumber::create(int num)
{
    JsonNumber* jn = new JsonNumber;
    jn->setValue(num);
    return adoptRef(jn);
}

JsonNumber::JsonNumber()
{
}

JsonNumber::~JsonNumber()
{
}

JsonValue::ValueType JsonNumber::type() const
{
    return JsonValue::Number;
}

void JsonNumber::appendToString(StringBuilder& target) const
{
    if (_isInt)
    {
        target.appendInt(_ivalue);
    }
    else
    {
        target.appendDouble(_fvalue);
    }
}

void JsonNumber::setValue(double num)
{
    _fvalue = num;
    _isInt = false;
}

void JsonNumber::setValue(int num)
{
    _ivalue = num;
    _isInt = true;
}

double JsonNumber::getDouble() const
{
    if (_isInt)
    {
        return static_cast<double>(_ivalue);
    }
    return _fvalue;
}

int JsonNumber::getInteger() const
{
    if (_isInt)
    {
        return _ivalue;
    }
    return static_cast<int>(_fvalue);
}

bool JsonNumber::isInteger() const
{
    return _isInt;
}

