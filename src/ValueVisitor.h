//
//  ValueStringVisitor.h
//  SimpleJsonCpp
//
//  Created by Chen Jiajun on 13-9-9.
//  Copyright (c) 2013 chenjiajun90@gmail.com
//

#ifndef __SimpleJsonCpp_ValueVisitor__
#define __SimpleJsonCpp_valueVisitor__

#include "StringBuilder.h"

class JsonValue;
class JsonObject;
class JsonArray;
class JsonString;
class JsonNumber;
class JsonBoolean;
class JsonNull;

class ValueVisitor
{
public:
    virtual void visitObject(const JsonObject* value) = 0;
    virtual void visitArray(const JsonArray* array) = 0;
    virtual void visitString(const JsonString* str) = 0;
    virtual void visitNumber(const JsonNumber* num) = 0;
    virtual void visitBoolean(const JsonBoolean* boo) = 0;
    virtual void visitNull() = 0;
};


class ValueStringVisitor : public ValueVisitor
{
public:
    ValueStringVisitor();
    virtual void visitObject(const JsonObject* value);
    virtual void visitArray(const JsonArray* array);
    virtual void visitString(const JsonString* str);
    virtual void visitNumber(const JsonNumber* num);
    virtual void visitBoolean(const JsonBoolean* boo);
    virtual void visitNull();
    String getResult() const;

private:
    StringBuilder _buff;
    int _depth;
};

#endif // defined(__SimpleJsonCpp_ValueVisitor__)
