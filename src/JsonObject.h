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

class ObjectIterator;

class JsonObject : public JsonValue
{
public:
    typedef std::map<String, RefPtr<JsonValue> > PairMap;

    static PassPtr<JsonObject> create();
    
    virtual ~JsonObject();
    virtual ValueType type() const;
    virtual void accept(ValueVisitor* visitor) const;
    void add(const String& key, JsonValue* value);
	void add(const String& key, RefPtr<JsonValue> value);
    JsonValue* getValue(const String& key) const;
    int count() const;
    ObjectIterator iterator() const;
    
protected:
    JsonObject();
    
private:
    PairMap _pairs;
};


class ObjectIterator
{
public:
    typedef JsonObject::PairMap::const_iterator IterImpl;

    ObjectIterator(const IterImpl& begin, const IterImpl& end);
    String getKey() const;
    JsonValue* getValue() const;
    void next();
    bool hasNext() const;

private:
    IterImpl _cur;
    IterImpl _end;
};

#endif /* defined(__SimpleJsonCpp__JsonObject__) */
