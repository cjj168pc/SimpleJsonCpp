//
//  JsonValueBuilder.h
//  SimpleJsonCpp
//
//  Created by Chen Jiajun on 13-8-24.
//  Copyright (c) 2013 chenjiajun90@gmail.com
//

#ifndef __SimpleJsonCpp__JsonValueBuilder__
#define __SimpleJsonCpp__JsonValueBuilder__

#include "JsonValue.h"
#include "RefPtr.h"
#include "JsonToken.h"
#include "JsonError.h"
#include <stack>

class JsonValueBuilder
{
public:
    JsonValueBuilder();
    ~JsonValueBuilder();
    bool processToken(const JsonToken& token);
    JsonValue* getRoot() const;
    bool finished() const;
    ErrorType getErrorType() const;
    int getErrorPos() const;
    
private:
    enum InsertionMode
    {
        InitMode,
        PairNameMode,
        NameSeparatorMode,
        PairValueMode,
        PairNameOnlyMode,
        PairSeparatorMode,
        ElementMode,
        ElementSeparatorMode,
        ElementOnlyMode,
        EndMode
    };
    
    JsonValueBuilder(const JsonValueBuilder& other);
    JsonValueBuilder& operator=(const JsonValueBuilder& rhs);
    
    void processUninitilized(const JsonToken& token);
    void processBeginObject(const JsonToken& token);
    void processEndObject(const JsonToken& token);
    void processNameSeparator(const JsonToken& token);
    void processBeginArray(const JsonToken& token);
    void processEndArray(const JsonToken& token);
    void processValueSeparator(const JsonToken& token);
    void processLiteral(const JsonToken& token);
    void processNumber(const JsonToken& token);
    void processTrue(const JsonToken& token);
    void processFalse(const JsonToken& token);
    void processNull(const JsonToken& token);
    void processEndOfFile(const JsonToken& token);
    
    void parseError(const JsonToken& token);
    void parseError(const JsonToken& token, ErrorType code);
    
    InsertionMode _mode;
    RefPtr<JsonValue> _root;
    String _tmpKey;
    std::stack<JsonValue*> _path;
    bool _err;
    ErrorType _errCode;
    int _errPos;
};

#endif /* defined(__SimpleJsonCpp__JsonValueBuilder__) */
