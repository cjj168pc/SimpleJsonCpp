//
//  JsonNull.cpp
//  SimpleJsonCpp
//
//  Created by Chen Jiajun on 13-8-24.
//  Copyright (c) 2013 chenjiajun90@gmail.com
//

#include "JsonNull.h"
#include "ValueVisitor.h"


PassPtr<JsonNull> JsonNull::create()
{
    JsonNull* jn = new JsonNull;
    return adoptRef(jn);
}

void JsonNull::accept(ValueVisitor* visitor) const
{
	visitor->visitNull();
}
