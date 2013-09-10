//
//  JsonBoolean.h
//  SimpleJsonCpp
//
//  Created by Chen Jiajun on 13-8-24.
//  Copyright (c) 2013 chenjiajun90@gmail.com
//

#ifndef __SimpleJsonCpp__JsonBoolean__
#define __SimpleJsonCpp__JsonBoolean__

#include "JsonValue.h"
#include "RefPtr.h"

class JsonBoolean : public JsonValue
{
public:
    static PassPtr<JsonBoolean> create(bool val);
    
    virtual ~JsonBoolean();
    virtual ValueType type() const;
    virtual void accept(ValueVisitor* visitor) const;
    void setValue(bool val);
    bool getValue() const;
    
protected:
    JsonBoolean();
    
private:
    bool _value;
};

#endif /* defined(__SimpleJsonCpp__JsonBoolean__) */
