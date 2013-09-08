//
//  JsonParser.cpp
//  SimpleJsonCpp
//
//  Created by Chen Jiajun on 13-8-24.
//  Copyright (c) 2013 chenjiajun90@gmail.com
//

#include "JsonParser.h"
#include "SourceStream.h"
#include "JsonToken.h"
#include "JsonTokenizer.h"
#include "JsonValueBuilder.h"


static String toErrorMsg(ErrorType code)
{
    static String invalidIdentifier = L"invalid identifier";
    static String unexpectedEnd = L"unexpected end";
    static String invalidCharactorInString = L"invalid charactor in string";
    static String invalidStringReference = L"invalid string reference";
    static String expectDigit = L"expect digit";
    static String unexpectedNumberEnd = L"unexpected number end";
    static String expectPairName = L"expect pair name";
    static String expectNameSeparator = L"expect name separator";
    static String expectElementSeparator = L"expect element separator";
    static String moreThanOneRoot = L"there are more than one root value";
    static String expectPairSeparator = L"expect pair separator";
    static String expectObjectSeparator = L"expect object separator";
    static String expectValue = L"expect value";
    
    switch (code)
    {
        case JSON_ERROR_INVALID_IDENTIFIER:
            return invalidIdentifier;
        case JSON_ERROR_UNEXPECTED_END:
            return unexpectedEnd;
        case JSON_ERROR_INVALID_CHARACTER_IN_STRING:
            return invalidCharactorInString;
        case JSON_ERROR_INVALID_STRING_REFERENCE:
            return invalidStringReference;
        case JSON_ERROR_EXPECT_DIGIT:
            return expectDigit;
        case JSON_ERROR_UNEXPECTED_NUMBER_END:
            return unexpectedNumberEnd;
        case JSON_ERROR_EXPECTED_PAIR_NAME:
            return expectPairName;
        case JSON_ERROR_EXPECTED_NAME_SEPARATOR:
            return expectNameSeparator;
        case JSON_ERROR_EXPECTED_ELEMENT_SEPARATOR:
            return expectElementSeparator;
        case JSON_ERROR_MORE_THAN_ONE_ROOT:
            return moreThanOneRoot;
        case JSON_ERROR_EXPECTED_PAIR_SEPARATOR:
            return expectPairSeparator;
        case JSON_ERROR_EXPECTED_OBJECT_OR_ARRAY:
            return expectObjectSeparator;
        case JSON_ERROR_EXPECTED_VALUE:
            return expectValue;
    }
}


JsonParser::JsonParser()
{
}

JsonParser::~JsonParser()
{
}

PassPtr<JsonValue> JsonParser::parse(String source)
{
    JsonTokenizer tokenizer;
    JsonValueBuilder builder;
    SourceStream ss(source);
    JsonToken token;
    
    while (!ss.end())
    {
        token.uninitialized();
        token.setBegin(ss.pos());
        
        if (!tokenizer.nextToken(ss, token))
        {
            break;
        }
        
        token.setEnd(ss.pos());
        
        if (!tokenAvailable(&token))
        {
            setError(token.getRange().end, token.getErrorType());
            return PassPtr<JsonValue>();
        }
        
        if (!builder.processToken(token))
        {
            setError(builder.getErrorPos(), builder.getErrorType());
            return PassPtr<JsonValue>();
        }
    }
    
    if (builder.finished())
    {
        return PassPtr<JsonValue>(builder.getRoot());
    }
    
    setError(ss.pos(), JSON_ERROR_UNEXPECTED_END);
    return PassPtr<JsonValue>();
}

bool JsonParser::tokenAvailable(const JsonToken* token) const
{
    return token->type() != JsonToken::Error && token->type() != JsonToken::Uninitialized;
}

void JsonParser::setError(int pos, ErrorType code)
{
    _lastErr.pos = pos;
    _lastErr.code = code;
    _lastErr.message = toErrorMsg(code);
}

JsonParser::ParseError JsonParser::getError() const
{
    return _lastErr;
}
