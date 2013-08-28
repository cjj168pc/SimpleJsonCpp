//
//  SimpleJson.cpp
//  SimpleJsonCpp
//
//  Created by Chen Jiajun on 13-8-25.
//  Copyright (c) 2013 chenjiajun90@gmail.com
//

#include "SimpleJson.h"


String SJ_ValueToString(JsonValue *value)
{
    if (value == 0)
    {
        return String();
    }
    
    RefPtr<JsonValue> protect(value);
    
    StringBuilder jss;
    value->toString(jss);
    return jss.toString();
}