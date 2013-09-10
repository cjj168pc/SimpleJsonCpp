//
//  JsonObject.cpp
//  SimpleJsonCpp
//
//  Created by Chen Jiajun on 13-8-24.
//  Copyright (c) 2013 chenjiajun90@gmail.com
//

#include "JsonObject.h"
#include "JsonString.h"
#include "ValueVisitor.h"


PassPtr<JsonObject> JsonObject::create()
{
    JsonObject* obj = new JsonObject;
    return adoptRef(obj);
}

JsonObject::JsonObject()
{
}

JsonObject::~JsonObject()
{
}

JsonObject::ValueType JsonObject::type() const
{
    return JsonValue::Object;
}

void JsonObject::accept(ValueVisitor* visitor) const
{
    visitor->visitObject(this);
}

void JsonObject::add(const String& key, JsonValue* value)
{
    _pairs.insert(std::make_pair(key, RefPtr<JsonValue>(value)));
}

void JsonObject::add(const String& key, RefPtr<JsonValue> value)
{
    add(key, value.get());
}

JsonValue* JsonObject::getValue(const String& key) const
{
    PairMap::const_iterator res = _pairs.find(key);
    if (res == _pairs.end())
    {
        return 0;
    }
    return (*res).second.get();
}

int JsonObject::count() const
{
    return static_cast<int>(_pairs.size());
}

ObjectIterator JsonObject::iterator() const
{
    return ObjectIterator(_pairs.begin(), _pairs.end());
}


ObjectIterator::ObjectIterator(const IterImpl& begin, const IterImpl& end)
    : _cur(begin), _end(end)
{
}

String ObjectIterator::getKey() const
{
    return (*_cur).first;
}

JsonValue* ObjectIterator::getValue() const
{
    return (*_cur).second.get();
}

void ObjectIterator::next()
{
    ++_cur;
}

bool ObjectIterator::hasNext() const
{
    return _cur != _end;
}