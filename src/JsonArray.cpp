//
//  JsonArray.cpp
//  SimpleJsonCpp
//
//  Created by Chen Jiajun on 13-8-24.
//  Copyright (c) 2013 chenjiajun90@gmail.com
//

#include "JsonArray.h"
#include "ValueVisitor.h"


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

void JsonArray::accept(ValueVisitor* visitor) const
{
    visitor->visitArray(this);
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

ArrayIterator JsonArray::iterator() const
{
    return ArrayIterator(_values.begin(), _values.end());
}


ArrayIterator::ArrayIterator(const IterImpl& begin, const IterImpl& end)
    : _cur(begin), _end(end)
{
}

JsonValue* ArrayIterator::get() const
{
    return (*_cur).get();
}

void ArrayIterator::next()
{
    ++_cur;
}

bool ArrayIterator::hasNext() const
{
    return _cur != _end;
}