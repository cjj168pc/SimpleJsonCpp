//
//  JsonNull.h
//  SimpleJsonCpp
//
//  Created by Chen Jiajun on 13-8-24.
//  Copyright (c) 2013 chenjiajun90@gmail.com
//

#ifndef __SimpleJsonCpp__JsonNull__
#define __SimpleJsonCpp__JsonNull__

#include "JsonValue.h"
#include "RefPtr.h"

class JsonNull : public JsonValue
{
public:
    static PassPtr<JsonNull> create();
    
    virtual ~JsonNull()
    {
    }
    
    virtual ValueType type() const
    {
        return JsonValue::Null;
    }
    
    virtual void accept(ValueVisitor* visitor) const;
    
protected:
    JsonNull()
    {
    }
};

#endif /* defined(__SimpleJsonCpp__JsonNull__) */
