//
//  JsonValue.cpp
//  SimpleJsonCpp
//
//  Created by Chen Jiajun on 13-8-24.
//  Copyright (c) 2013 chenjiajun90@gmail.com
//

#include "JsonValue.h"
#include "JsonError.h"

String JsonValue::toString() const
{
    StringBuilder sb;

    appendToString(sb);

    return sb.toString();
}
