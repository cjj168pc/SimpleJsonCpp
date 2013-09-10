//
//  JsonValue.cpp
//  SimpleJsonCpp
//
//  Created by Chen Jiajun on 13-8-24.
//  Copyright (c) 2013 chenjiajun90@gmail.com
//

#include "JsonValue.h"
#include "ValueSerializer.h"

String JsonValue::toString() const
{
	ValueSerializer ser;
	accept(&ser);
	return ser.getResult();
}