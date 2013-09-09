//
//  JsonObject.h
//  SimpleJsonCpp
//
//  Created by Chen Jiajun on 13-8-24.
//  Copyright (c) 2013 chenjiajun90@gmail.com
//

#ifndef __SimpleJsonCpp__JsonObject__
#define __SimpleJsonCpp__JsonObject__

#include "JsonValue.h"
#include "PassPtr.h"
#include "RefPtr.h"
#include "MyString.h"
#include <map>

class JsonObject : public JsonValue
{
public:
    static PassPtr<JsonObject> create();
    
    virtual ~JsonObject();
    virtual ValueType type() const;
    virtual void appendToString(StringBuilder& target) const;
    void add(const String& key, JsonValue* value);
	void add(const String& key, RefPtr<JsonValue> value);
    JsonValue* getValue(const String& key) const;
    int count() const;
    
protected:
    JsonObject();
    
private:
    typedef std::map<String, RefPtr<JsonValue> > PairMap;
    PairMap _pairs;
};

#endif /* defined(__SimpleJsonCpp__JsonObject__) */
