//
//  JsonToken.cpp
//  SimpleJsonCpp
//
//  Created by Chen Jiajun on 13-8-23.
//  Copyright (c) 2013 chenjiajun90@gmail.com
//

#include "JsonToken.h"


JsonToken::JsonToken()
    : _type(Uninitialized), _number(0)
{
    _range.begin = -1;
    _range.end = -1;
}

void JsonToken::uninitialized()
{
    _type = Uninitialized;
    _range.begin = -1;
    _range.end = -1;
}

void JsonToken::beginObject()
{
    _type = BeginObject;
}

void JsonToken::endObject()
{
    _type = EndObject;
}

void JsonToken::nameSeparator()
{
    _type = NameSeparator;
}

void JsonToken::beginArray()
{
    _type = BeginArray;
}

void JsonToken::endArray()
{
    _type = EndArray;
}

void JsonToken::literal(String chars)
{
    _type = Literal;
    _str = chars;
}

void JsonToken::valueSeparator()
{
    _type = ValueSeparator;
}

void JsonToken::number(int integer, int numberSign, int frac, int fracLength, int exp, int expSign)
{
    _type = NumberValue;
    
    double mantissa = frac;
    while (fracLength--)
    {
        mantissa /= 10.0;
    }
    double preRegular = integer + mantissa;
    if (numberSign == -1)
    {
        preRegular = -preRegular;
    }
    if (expSign == 1)
    {
        for (int i = 0; i < exp; i++)
        {
            preRegular *= 10;
        }
    }
    else
    {
        for (int i = 0; i < exp; i++)
        {
            preRegular /= 10;
        }
    }
    
    _number = preRegular;
}

void JsonToken::trueValue()
{
    _type = TrueValue;
}

void JsonToken::falseValue()
{
    _type = FalseValue;
}

void JsonToken::nullValue()
{
    _type = NullValue;
}

void JsonToken::endOfFile()
{
    _type = EndOfFile;
}

void JsonToken::error(ErrorType code)
{
    _type = Error;
    _err = code;
}

void JsonToken::setBegin(int pos)
{
    _range.begin = pos;
}

void JsonToken::setEnd(int pos)
{
    _range.end = pos;
}

JsonToken::Range JsonToken::getRange() const
{
    return _range;
}

JsonToken::TokenType JsonToken::type() const
{
    return _type;
}

String JsonToken::data() const
{
    return _str;
}

double JsonToken::value() const
{
    return _number;
}

ErrorType JsonToken::getErrorType() const
{
    return _err;
}