//
//  JsonTokenizer.h
//  SimpleJsonCpp
//
//  Created by Chen Jiajun on 13-8-23.
//  Copyright (c) 2013 chenjiajun90@gmail.com
//

#ifndef __SimpleJsonCpp__JsonTokenizer__
#define __SimpleJsonCpp__JsonTokenizer__

#include "JsonToken.h"
#include "StringBuilder.h"
#include "MyString.h"
#include "SourceStream.h"
#include "SourceStreamPreprocessor.h"
#include "JsonError.h"

class JsonTokenizer
{
public:
    enum TokenState
    {
        DataState,
        DoubleQuoteState,
        DoubleQuoteCharReferenceState,
        ZeroState,
        DigitState,
        NegtiveState,
        DotState,
        DotDigitState,
        ExpState,
        ExpDigitState,
        NumberEndState
    };
    
    JsonTokenizer();
    ~JsonTokenizer();
    bool nextToken(SourceStream& input, JsonToken& token);
    
private:
    bool endToken(SourceStream& input, TokenState state);
    bool endToken(SourceStream& input, TokenState state, int unconsume);
    bool endTokenNoConsume(SourceStream& input, TokenState state);
    bool parseError(ErrorType code);
    void beginNumber(int digit, int sign);
    
    TokenState _state;
    JsonToken* _token;
    StringBuilder _tmpBuffer;
    int _integer;
    int _numberSign;
    int _frac;
    int _fracLength;
    int _exp;
    int _expSign;
    bool _isInt;
    SourceStreamPreprocessor _preprocesser;
};

#endif /* defined(__SimpleJsonCpp__JsonTokenizer__) */
