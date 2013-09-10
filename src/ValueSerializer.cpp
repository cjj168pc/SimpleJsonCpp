//
//  ValueSerializer.cpp
//  SimpleJsonCpp
//
//  Created by Chen Jiajun on 13-9-9.
//  Copyright (c) 2013 chenjiajun90@gmail.com
//


#include "ValueSerializer.h"
#include "JsonObject.h"
#include "JsonArray.h"
#include "JsonNumber.h"
#include "JsonString.h"
#include "JsonBoolean.h"
#include "JsonNull.h"
#include "JsonError.h"


ValueSerializer::ValueSerializer()
    : _depth(MAX_NESTING), _ok(true)
{
}

void ValueSerializer::visitObject(const JsonObject* obj)
{
    bool first = true;
    _buff.append('{');

    if (_depth == 0)
    {
        _ok = false;
        return;
    }

    --_depth;
    for (ObjectIterator it = obj->iterator(); it.hasNext(); it.next())
    {
        if (first)
        {
            first = false;
        }
        else
        {
            _buff.append(',');
        }
        
        JsonString::appendReferencedString(_buff, it.getKey());
        _buff.append(':');
        it.getValue()->accept(this);
    }
    ++_depth;
    _buff.append('}');
}

void ValueSerializer::visitArray(const JsonArray* arr)
{
    bool first = true;
    _buff.append('[');
    
    if (_depth == 0)
    {
        _ok = false;
        return;
    }

    --_depth;
    for (ArrayIterator it = arr->iterator(); it.hasNext(); it.next())
    {
        if (first)
        {
            first = false;
        }
        else
        {
            _buff.append(',');
        }
        
        it.get()->accept(this);
    }
    ++_depth;
    _buff.append(']');
}

void ValueSerializer::visitString(const JsonString* str)
{
    JsonString::appendReferencedString(_buff, str->getString());
}

void ValueSerializer::visitNumber(const JsonNumber* num)
{
    if (num->isInteger())
    {
        _buff.appendInt(num->getInteger());
    }
    else
    {
        _buff.appendDouble(num->getDouble());
    }
}

void ValueSerializer::visitBoolean(const JsonBoolean* boo)
{
    static String strTrue = L"true";
    static String strFalse = L"false";

    if (boo->getValue())
    {
        _buff.append(strTrue);
    }
    else
    {
        _buff.append(strFalse);
    }
}

void ValueSerializer::visitNull()
{
    static String strNull = L"null";

    _buff.append(strNull);
}

String ValueSerializer::getResult() const
{
    return _buff.toString();
}

bool ValueSerializer::success() const
{
    return _ok;
}
