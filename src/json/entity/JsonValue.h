//
//  JsonValue.h
//  SimpleJsonCpp
//
//  Created by Chen Jiajun on 13-8-24.
//  Copyright (c) 2013 chenjiajun90@gmail.com
//

#ifndef __SimpleJsonCpp__JsonValue__
#define __SimpleJsonCpp__JsonValue__

#include "RefCounted.h"
#include "StringBuilder.h"

class JsonValue : public RefCounted<JsonValue>
{
public:
    enum ValueType
    {
        Object,
        Array,
        Literal,
        Boolean,
        Number,
        Null
    };
    
    virtual ~JsonValue()
    {
    }
    
    virtual ValueType type() const = 0;
    virtual void toString(StringBuilder& target) const = 0;
    
protected:
    JsonValue()
    {
    }
    
private:
    JsonValue(const JsonValue& other);
    JsonValue& operator=(const JsonValue& rhs);
};

#endif /* defined(__SimpleJsonCpp__JsonValue__) */
