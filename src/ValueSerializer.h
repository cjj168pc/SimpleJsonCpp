//
//  ValueSerializer.h
//  SimpleJsonCpp
//
//  Created by Chen Jiajun on 13-9-9.
//  Copyright (c) 2013 chenjiajun90@gmail.com
//

#ifndef __SimpleJsonCpp_ValueSerializer__
#define __SimpleJsonCpp_ValueSerializer__

#include "ValueVisitor.h"

class ValueSerializer : public ValueVisitor
{
public:
    ValueSerializer();
    virtual void visitObject(const JsonObject* value);
    virtual void visitArray(const JsonArray* array);
    virtual void visitString(const JsonString* str);
    virtual void visitNumber(const JsonNumber* num);
    virtual void visitBoolean(const JsonBoolean* boo);
    virtual void visitNull();
    String getResult() const;
    bool success() const;

private:
    StringBuilder _buff;
    int _depth;
    bool _ok;
};

#endif // defined(__SimpleJsonCpp_ValueSerializer__)