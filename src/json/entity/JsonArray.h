//
//  JsonArray.h
//  SimpleJsonCpp
//
//  Created by Chen Jiajun on 13-8-24.
//  Copyright (c) 2013 chenjiajun90@gmail.com
//

#ifndef __SimpleJsonCpp__JsonArray__
#define __SimpleJsonCpp__JsonArray__

#include "JsonValue.h"
#include "PassPtr.h"
#include "RefPtr.h"
#include <vector>

class JsonArray : public JsonValue
{
public:
    static PassPtr<JsonArray> create();
    
    virtual ~JsonArray();
    virtual ValueType type() const;
    virtual void toString(StringBuilder& target) const;
    void add(JsonValue* value);
    JsonValue* get(int index) const;
    int count() const;
    
protected:
    JsonArray();
    
private:
    typedef std::vector<RefPtr<JsonValue> > ValueVector;
    ValueVector _values;
};

#endif /* defined(__SimpleJsonCpp__JsonArray__) */
