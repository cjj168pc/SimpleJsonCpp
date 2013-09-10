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

class JsonObject;
class JsonString;
class JsonArray;
class JsonNumber;
class JsonBoolean;
class JsonNull;
class ValueVisitor;

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
    virtual void accept(ValueVisitor* visitor) const = 0;
    String toString() const;

	inline JsonObject* asObject()
	{
		if (type() == Object)
		{
			return static_cast<JsonObject*>(static_cast<void*>(this));
		}
		return 0;
	}

	inline JsonArray* asArray()
	{
		if (type() == Array)
		{
			return static_cast<JsonArray*>(static_cast<void*>(this));
		}
		return 0;
	}

	inline JsonString* asString()
	{
		if (type() == Literal)
		{
			return static_cast<JsonString*>(static_cast<void*>(this));
		}
		return 0;
	}

	inline JsonNumber* asNumber()
	{
		if (type() == Number)
		{
			return static_cast<JsonNumber*>(static_cast<void*>(this));
		}
		return 0;
	}

	inline JsonBoolean* asBoolean()
	{
		if (type() == Boolean)
		{
			return static_cast<JsonBoolean*>(static_cast<void*>(this));
		}
		return 0;
	}

	inline bool isNull() const
	{
		return type() == Null;
	}

protected:
    JsonValue()
    {
    }

    
private:
    JsonValue(const JsonValue& other);
    JsonValue& operator=(const JsonValue& rhs);
};

#endif /* defined(__SimpleJsonCpp__JsonValue__) */
