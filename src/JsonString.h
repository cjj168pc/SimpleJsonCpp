//
//  JsonString.h
//  SimpleJsonCpp
//
//  Created by Chen Jiajun on 13-8-24.
//  Copyright (c) 2013 chenjiajun90@gmail.com
//

#ifndef __SimpleJsonCpp__JsonString__
#define __SimpleJsonCpp__JsonString__

#include "JsonValue.h"
#include "MyString.h"
#include "PassPtr.h"

class JsonString : public JsonValue
{
public:
    static PassPtr<JsonString> create(String str);
    static void appendReferencedString(StringBuilder& target, String src);
    
    virtual ~JsonString();
    virtual ValueType type() const;
    virtual void accept(ValueVisitor* visitor) const;
    String getString() const;
    void setString(String str);
    
protected:
    JsonString();
    
private:
    String _str;
};

#endif /* defined(__SimpleJsonCpp__JsonString__) */
