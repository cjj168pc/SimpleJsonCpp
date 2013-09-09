//
//  JsonToken.h
//  SimpleJsonCpp
//
//  Created by Chen Jiajun on 13-8-23.
//  Copyright (c) 2013 chenjiajun90@gmail.com
//

#ifndef __SimpleJsonCpp__JsonToken__
#define __SimpleJsonCpp__JsonToken__

#include "MyString.h"
#include "JsonError.h"

class JsonToken
{
public:
    enum TokenType
    {
        Uninitialized,
        BeginObject,
        EndObject,
        NameSeparator,
        BeginArray,
        EndArray,
        Literal,
        ValueSeparator,
        NumberValue,
        TrueValue,
        FalseValue,
        NullValue,
        EndOfFile,
        Error
    };
    
    struct Range
    {
        int begin;
        int end;
    };
    
    JsonToken();
    void uninitialized();
    void beginObject();
    void endObject();
    void nameSeparator();
    void beginArray();
    void endArray();
    void literal(String chars);
    void valueSeparator();
    void number(int integer, int numberSign, int frac, int fracLength, int exp, int expSign);
    void number(int integer);
    void trueValue();
    void falseValue();
    void nullValue();
    void endOfFile();
    void error(ErrorType code);
    void setBegin(int pos);
    void setEnd(int pos);
    Range getRange() const;
    TokenType type() const;
    String data() const;
    double getDouble() const;
    int getInteger() const;
    bool isInteger() const;
    ErrorType getErrorType() const;
    
private:
    JsonToken(const JsonToken& other);
    JsonToken& operator=(const JsonToken& rhs);
    
    TokenType _type;
    String _str;
    double _number;
    int _integer;
    bool _isInt;
    Range _range;
    ErrorType _err;
};

#endif /* defined(__SimpleJsonCpp__JsonToken__) */
