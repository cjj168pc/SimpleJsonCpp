//
//  JsonObject.cpp
//  SimpleJsonCpp
//
//  Created by Chen Jiajun on 13-8-24.
//  Copyright (c) 2013 chenjiajun90@gmail.com
//

#include "JsonObject.h"
#include "JsonString.h"


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

void JsonObject::toString(StringBuilder& target) const
{
    target.append('{');
    bool first = true;
    for (PairMap::const_iterator it = _pairs.begin(); it != _pairs.end(); ++it)
    {
        if (first)
        {
            first = false;
        }
        else
        {
            target.append(',');
        }
        JsonString::appendReferencedString(target, (*it).first);
        target.append(':');
        (*it).second->toString(target);
    }
    target.append('}');
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

