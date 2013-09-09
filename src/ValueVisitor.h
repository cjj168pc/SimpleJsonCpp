//
//  ValueVisitor.h
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
    virtual void visit(JsonValue* value) = 0;
};


class ValueStringVisitor : public ValueVisitor
{
public:
    ValueStringVisitor();
    virtual void visit(JsonValue* value);
    String getResult() const;

private:
    void forObject(JsonObject* obj);
    void forArray(JsonArray* arr);
    void forString(JsonString* str);
    void forNumber(JsonNumber* num);
    void forBoolean(JsonBoolean* boo);
    void forNull();

    StringBuilder _buff;
    int _depth;
};

#endif // defined(__SimpleJsonCpp_ValueVisitor__)
