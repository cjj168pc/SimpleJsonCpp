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

void JsonNumber::toString(StringBuilder& target) const
{
    target.appendDouble(_value);
}

void JsonNumber::setValue(double num)
{
    _value = num;
}

double JsonNumber::getValue() const
{
    return _value;
}
