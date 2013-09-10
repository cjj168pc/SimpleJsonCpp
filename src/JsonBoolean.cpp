//
//  JsonBoolean.cpp
//  SimpleJsonCpp
//
//  Created by Chen Jiajun on 13-8-24.
//  Copyright (c) 2013 chenjiajun90@gmail.com
//

#include "JsonBoolean.h"
#include "ValueVisitor.h"


PassPtr<JsonBoolean> JsonBoolean::create(bool val)
{
    JsonBoolean* jb = new JsonBoolean;
    jb->setValue(val);
    return adoptRef(jb);
}

JsonBoolean::JsonBoolean()
{
}

JsonBoolean::~JsonBoolean()
{
}

JsonValue::ValueType JsonBoolean::type() const
{
    return JsonValue::Boolean;
}

void JsonBoolean::accept(ValueVisitor* visitor) const
{
	visitor->visitBoolean(this);
}

void JsonBoolean::setValue(bool val)
{
    _value = val;
}

bool JsonBoolean::getValue() const
{
    return _value;
}
