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

class ArrayIterator;

class JsonArray : public JsonValue
{
public:
    typedef std::vector<RefPtr<JsonValue> > ValueVector;

    static PassPtr<JsonArray> create();
    
    virtual ~JsonArray();
    virtual ValueType type() const;
    virtual void accept(ValueVisitor* visitor) const;
    void add(JsonValue* value);
	void add(RefPtr<JsonValue> value);
    JsonValue* get(int index) const;
    int count() const;
    ArrayIterator iterator() const;
    
protected:
    JsonArray();
    
private:
    ValueVector _values;
};


class ArrayIterator
{
public:
    typedef JsonArray::ValueVector::const_iterator IterImpl;

    ArrayIterator(const IterImpl& begin, const IterImpl& end);
    JsonValue* get() const;
    void next();
    bool hasNext() const;

private:
    IterImpl _cur;
    IterImpl _end;
};

#endif /* defined(__SimpleJsonCpp__JsonArray__) */
