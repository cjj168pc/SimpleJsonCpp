//
//  JsonArray.cpp
//  SimpleJsonCpp
//
//  Created by Chen Jiajun on 13-8-24.
//  Copyright (c) 2013 chenjiajun90@gmail.com
//

#include "JsonArray.h"


PassPtr<JsonArray> JsonArray::create()
{
    JsonArray* arr = new JsonArray;
    return adoptRef(arr);
}

JsonArray::JsonArray()
{
}

JsonArray::~JsonArray()
{
}

JsonValue::ValueType JsonArray::type() const
{
    return JsonValue::Array;
}

void JsonArray::appendToString(StringBuilder& target) const
{
    target.append('[');
    bool first = true;
    for (ValueVector::const_iterator it = _values.begin(); it != _values.end(); ++it)
    {
        if (first)
        {
            first = false;
        }
        else
        {
            target.append(',');
        }
        (*it)->appendToString(target);
    }
    target.append(']');
}

void JsonArray::add(JsonValue* value)
{
    _values.push_back(RefPtr<JsonValue>(value));
}

void JsonArray::add(RefPtr<JsonValue> value)
{
    add(value.get());
}

JsonValue* JsonArray::get(int index) const
{
    return _values.at(index).get();
}

int JsonArray::count() const
{
    return static_cast<int>(_values.size());
}
