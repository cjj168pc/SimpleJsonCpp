//
//  JsonParser.h
//  SimpleJsonCpp
//
//  Created by Chen Jiajun on 13-8-24.
//  Copyright (c) 2013 chenjiajun90@gmail.com
//

#ifndef __SimpleJsonCpp__JsonParser__
#define __SimpleJsonCpp__JsonParser__

#include "MyString.h"
#include "PassPtr.h"
#include "JsonError.h"

class JsonValue;
class JsonToken;

class JsonParser
{
public:
    struct ParseError
    {
        int pos;
        ErrorType code;
        String message;
    };
    
    JsonParser();
    ~JsonParser();
    PassPtr<JsonValue> parse(String source);
    ParseError getError() const;
    
private:
    JsonParser(const JsonParser& other);
    JsonParser& operator=(const JsonParser& rhs);
    bool tokenAvailable(const JsonToken* token) const;
    void setError(int pos, ErrorType code);
    
    ParseError _lastErr;
};

#endif /* defined(__SimpleJsonCpp__JsonParser__) */
