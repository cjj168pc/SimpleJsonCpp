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
    static PassPtr<JsonNumber> create(int num);
    
    virtual ~JsonNumber();
    virtual ValueType type() const;
    virtual void toString(StringBuilder& target) const;
    void setValue(double num);
    void setValue(int num);
    double getDouble() const;
    int getInteger() const;
    bool isInteger() const;
    
protected:
    JsonNumber();

private:
    double _fvalue;
    int _ivalue;
    bool _isInt;
};

#endif /* defined(__SimpleJsonCpp__JsonNumber__) */
