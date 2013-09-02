//
//  JsonString.cpp
//  SimpleJsonCpp
//
//  Created by Chen Jiajun on 13-8-24.
//  Copyright (c) 2013 chenjiajun90@gmail.com
//

#include "JsonString.h"


static inline wchar_t digitToChar(wchar_t digit)
{
    assert(digit < 16 && digit >= 0);
    if (digit < 10)
    {
        return digit + '0';
    }
    else
    {
        return digit - 10 + 'A';
    }
}

static inline void appendHexChar(StringBuilder& target, wchar_t ch)
{
    target.append('u');
    
    target.append(digitToChar(ch & 0xf000));
    target.append(digitToChar(ch & 0x0f00));
    target.append(digitToChar(ch & 0x00f0));
    target.append(digitToChar(ch & 0x000f));
}

static inline void appendChar(StringBuilder& target, wchar_t ch)
{
    if (ch >= ' ')
    {
        target.append(ch);
    }
    else
    {
        target.append('\\');
        if (ch == '\"' || ch == '\\')
        {
            target.append(ch);
        }
        else if (ch == '\b')
        {
            target.append('b');
        }
        else if (ch == '\f')
        {
            target.append('f');
        }
        else if (ch == '\n')
        {
            target.append('n');
        }
        else if (ch == '\r')
        {
            target.append('r');
        }
        else if (ch == '\t')
        {
            target.append('t');
        }
        else
        {
            appendHexChar(target, ch);
        }
    }
}

PassPtr<JsonString> JsonString::create(String str)
{
    JsonString* js = new JsonString;
    js->_str = str;
    return adoptRef(js);
}

JsonString::JsonString()
{
}

JsonString::~JsonString()
{
}

JsonValue::ValueType JsonString::type() const
{
    return JsonValue::Literal;
}

void JsonString::toString(StringBuilder& target) const
{
    appendReferencedString(target, _str);
}

void JsonString::appendReferencedString(StringBuilder& target, String src)
{
    target.append('\"');
    
    const wchar_t* end = src.data() + src.length();
    for (const wchar_t* p = src.data(); p != end; ++p)
    {
        appendChar(target, *p);
    }
    
    target.append('\"');
}

String JsonString::getString() const
{
    return _str;
}

void JsonString::setString(String str)
{
    _str = str;
}
