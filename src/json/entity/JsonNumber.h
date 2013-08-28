//
//  JsonNumber.h
//  SimpleJsonCpp
//
//  Created by Chen Jiajun on 13-8-24.
//  Copyright (c) 2013 chenjiajun90@gmail.com
//

#ifndef __SimpleJsonCpp__JsonNumber__
#define __SimpleJsonCpp__JsonNumber__

#include "JsonValue.h"
#include "RefPtr.h"

class JsonNumber : public JsonValue
{
public:
    static PassPtr<JsonNumber> create(double num);
    
    virtual ~JsonNumber();
    virtual ValueType type() const;
    virtual void toString(StringBuilder& target) const;
    void setValue(double num);
    double getValue() const;
    
protected:
    JsonNumber();

private:
    double _value;
};

#endif /* defined(__SimpleJsonCpp__JsonNumber__) */
