//
//  JsonTokenizer.cpp
//  SimpleJsonCpp
//
//  Created by Chen Jiajun on 13-8-23.
//  Copyright (c) 2013 chenjiajun90@gmail.com
//

#include "JsonTokenizer.h"
#include "TokenizerInlines.h"
#include <cassert>


#define JSON_BEGIN_STATE(state) BEGIN_STATE(JsonTokenizer, state)
#define JSON_RECONSUME_IN(state) RECONSUME_IN(JsonTokenizer, state)
#define JSON_ADVANCE_TO(state) ADVANCE_TO(JsonTokenizer, state)
#define JSON_SWITCH_TO(state) SWITCH_TO(JsonTokenizer, state)


static inline bool isWhiteSpace(wchar_t ch)
{
    return ch == ' ' || ch == '\x0A' || ch == '\x09' || ch == '\x0C';
}

static inline bool isAvailHexNumber(wchar_t ch)
{
    return (ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'f') || (ch >= 'A' && ch <= 'F');
}

static inline wchar_t hexDigit(wchar_t ch)
{
    assert(isAvailHexNumber(ch));
    if (ch >= '0' && ch <= '9')
    {
        return ch - '0';
    }
    else if (ch >= 'a' && ch <= 'f')
    {
        return 10 + ch - 'a';
    }
    else
    {
        return 10 + ch - 'A';
    }
}

static inline bool parseHexUnicode(SourceStream& input, wchar_t& code)
{
    code = 0;
    for (int i = 0; i < 4; i++)
    {
        input.consume();
        if (input.end())
        {
            return false;
        }
        wchar_t ch = input.currentChar();
        if (isAvailHexNumber(ch))
        {
            code = code * 16 + hexDigit(ch);
        }
    }
    return true;
}

JsonTokenizer::JsonTokenizer()
    : _state(DataState), _token(0), _integer(0),
    _frac(0), _exp(0), _fracLength(0), _numberSign(1),
    _expSign(1), _isInt(true)
{
}

JsonTokenizer::~JsonTokenizer()
{
}

bool JsonTokenizer::endToken(SourceStream& input, TokenState state)
{
    input.consume();
    _state = state;
    return true;
}

bool JsonTokenizer::endToken(SourceStream& input, TokenState state, int unconsume)
{
    input.consume(unconsume);
    _state = state;
    return true;
}

bool JsonTokenizer::endTokenNoConsume(SourceStream& input, TokenState state)
{
    _state = state;
    return true;
}

bool JsonTokenizer::parseError(ErrorType code)
{
    _token->error(code);
    return true;
}

void JsonTokenizer::beginNumber(int digit, int sign)
{
    _integer = digit;
    _frac = 0;
    _fracLength = 0;
    _exp = 0;
    _numberSign = sign;
    _expSign = 1;
    _isInt = true;
}

bool JsonTokenizer::nextToken(SourceStream& input, JsonToken& token)
{
    assert(token.type() == JsonToken::Uninitialized);
    _token = &token;
    
    if (input.end() || !_preprocesser.peek(input))
    {
        return false;
    }
    wchar_t cc = _preprocesser.nextChar();
    
    switch (_state)
    {
        JSON_BEGIN_STATE(DataState)
        {
            if (isWhiteSpace(cc))
            {
                JSON_ADVANCE_TO(DataState);
            }
            else if (cc == '{')
            {
                token.beginObject();
                return endToken(input, DataState);
            }
            else if (cc == '}')
            {
                token.endObject();
                return endToken(input, DataState);
            }
            else if (cc == ':')
            {
                token.nameSeparator();
                return endToken(input, DataState);
            }
            else if (cc == '[')
            {
                token.beginArray();
                return endToken(input, DataState);
            }
            else if (cc == ']')
            {
                token.endArray();
                return endToken(input, DataState);
            }
            else if (cc == ',')
            {
                token.valueSeparator();
                return endToken(input, DataState);
            }
            else if (cc == '\"')
            {
                _tmpBuffer.clear();
                JSON_ADVANCE_TO(DoubleQuoteState);
            }
            else if (cc >= '1' && cc <= '9')
            {
                beginNumber(cc - '0', 1);
                JSON_ADVANCE_TO(DigitState);
            }
            else if (cc == '0')
            {
                beginNumber(0, 1);
                JSON_ADVANCE_TO(ZeroState);
            }
            else if (cc == '-')
            {
                beginNumber(cc - '0', -1);
                JSON_ADVANCE_TO(NegtiveState);
            }
            else if (cc == 't')
            {
                static const String TRUE_VALUE = L"true";
                if (input.lookAhead(TRUE_VALUE))
                {
                    token.trueValue();
                    return endToken(input, DataState, TRUE_VALUE.length());
                }
                else
                {
                    return parseError(JSON_ERROR_INVALID_IDENTIFIER);
                }
            }
            else if (cc == 'f')
            {
                static const String FALSE_VALUE = L"false";
                if (input.lookAhead(FALSE_VALUE))
                {
                    token.falseValue();
                    return endToken(input, DataState, FALSE_VALUE.length());
                }
                else
                {
                    return parseError(JSON_ERROR_INVALID_IDENTIFIER);
                }
            }
            else if (cc == 'n')
            {
                static const String NULL_VALUE = L"null";
                if (input.lookAhead(NULL_VALUE))
                {
                    token.nullValue();
                    return endToken(input, DataState, NULL_VALUE.length());
                }
            }
            else
            {
                return parseError(JSON_ERROR_INVALID_IDENTIFIER);
            }
        }
        END_STATE()
            
        JSON_BEGIN_STATE(DoubleQuoteState)
        {
            if (cc == '\"')
            {
                token.literal(_tmpBuffer.toString());
                return endToken(input, DataState);
            }
            else if (cc == '\\')
            {
                JSON_ADVANCE_TO(DoubleQuoteCharReferenceState);
            }
            else if (cc == '\0')
            {
                return parseError(JSON_ERROR_INVALID_CHARACTER_IN_STRING);
            }
            else
            {
                _tmpBuffer.append(cc);
                JSON_ADVANCE_TO(DoubleQuoteState);
            }
        }
        END_STATE()
            
        JSON_BEGIN_STATE(DoubleQuoteCharReferenceState)
        {
            if (cc == '\"' || cc == '\\')
            {
                _tmpBuffer.append(cc);
                JSON_ADVANCE_TO(DoubleQuoteState);
            }
            else if (cc == '/')
            {
                _tmpBuffer.append('/');
                JSON_ADVANCE_TO(DoubleQuoteState);
            }
            else if (cc == 'b')
            {
                _tmpBuffer.append('\b');
                JSON_ADVANCE_TO(DoubleQuoteState);
            }
            else if (cc == 'f')
            {
                _tmpBuffer.append('\f');
                JSON_ADVANCE_TO(DoubleQuoteState);
            }
            else if (cc == 'n')
            {
                _tmpBuffer.append('\n');
                JSON_ADVANCE_TO(DoubleQuoteState);
            }
            else if (cc == 'r')
            {
                _tmpBuffer.append('\r');
                JSON_ADVANCE_TO(DoubleQuoteState);
            }
            else if (cc == 't')
            {
                _tmpBuffer.append('\t');
                JSON_ADVANCE_TO(DoubleQuoteState);
            }
            else if (cc == 'u')
            {
                wchar_t refChar;
                if (!parseHexUnicode(input, refChar))
                {
                    return parseError(JSON_ERROR_INVALID_STRING_REFERENCE);
                }
                _tmpBuffer.append(refChar);
                JSON_ADVANCE_TO(DoubleQuoteState);
            }
            else
            {
                return parseError(JSON_ERROR_INVALID_STRING_REFERENCE);
            }
        }
        END_STATE()
            
        JSON_BEGIN_STATE(ZeroState)
        {
            if (cc == '.')
            {
                JSON_ADVANCE_TO(DotState);
            }
            else if (cc == 'e' || cc == 'E')
            {
                JSON_ADVANCE_TO(ExpState);
            }
            else
            {
                _isInt = true;
                JSON_RECONSUME_IN(NumberEndState);
            }
        }
        END_STATE()
            
        JSON_BEGIN_STATE(DigitState)
        {
            if (cc >= '0' && cc <= '9')
            {
                _integer = _integer * 10 + cc - '0';
                JSON_ADVANCE_TO(DigitState);
            }
            else if (cc == '.')
            {
                JSON_ADVANCE_TO(DotState);
            }
            else if (cc == 'e' || cc == 'E')
            {
                JSON_ADVANCE_TO(ExpState);
            }
            else
            {
                _isInt = true;
                JSON_RECONSUME_IN(NumberEndState);
            }
        }
        END_STATE()
            
        JSON_BEGIN_STATE(NegtiveState)
        {
            if (cc >= '1' && cc <= '9')
            {
                _integer = cc - '0';
                JSON_ADVANCE_TO(DigitState);
            }
            else if (cc == '0')
            {
                _integer = 0;
                JSON_ADVANCE_TO(ZeroState);
            }
            else
            {
                return parseError(JSON_ERROR_EXPECT_DIGIT);
            }
        }
        END_STATE()
            
        JSON_BEGIN_STATE(DotState)
        {
            if (cc >= '0' && cc <= '9')
            {
                _fracLength = 1;
                _frac = cc - '0';
                JSON_ADVANCE_TO(DotDigitState);
            }
            else
            {
                return parseError(JSON_ERROR_EXPECT_DIGIT);
            }
        }
        END_STATE()
            
        JSON_BEGIN_STATE(DotDigitState)
        {
            if (cc >= '0' && cc <= '9')
            {
                _fracLength++;
                _frac = _frac * 10 + cc - '0';
                JSON_ADVANCE_TO(DotDigitState);
            }
            else if (cc == 'e' || cc == 'E')
            {
                JSON_ADVANCE_TO(ExpState);
            }
            else
            {
                _isInt = false;
                JSON_RECONSUME_IN(NumberEndState);
            }
        }
        END_STATE()
            
        JSON_BEGIN_STATE(ExpState)
        {
            if (cc == '+')
            {
                _expSign = 1;
                JSON_ADVANCE_TO(ExpDigitState);
            }
            else if (cc == '-')
            {
                _expSign = -1;
                JSON_ADVANCE_TO(ExpDigitState);
            }
            else if (cc >= '0' && cc <= '9')
            {
                _exp = cc - '0';
                JSON_ADVANCE_TO(ExpDigitState);
            }
            else
            {
                return parseError(JSON_ERROR_EXPECT_DIGIT);
            }
        }
        END_STATE()
            
        JSON_BEGIN_STATE(ExpDigitState)
        {
            if (cc >= '0' && cc <= '9')
            {
                _exp = _exp * 10 + cc - '0';
                JSON_ADVANCE_TO(ExpDigitState);
            }
            else
            {
                _isInt = false;
                JSON_RECONSUME_IN(NumberEndState);
            }
        }
        END_STATE()
            
        JSON_BEGIN_STATE(NumberEndState)
        {
            if (isWhiteSpace(cc))
            {
                if (_isInt)
                {
                    token.number(_integer * _numberSign);
                    return endToken(input, DataState);
                }
                else
                {
                    token.number(_integer, _numberSign, _frac, _fracLength, _exp, _expSign);
                    return endToken(input, DataState);
                }
            }
            else if (cc == '{' || cc == '}' || cc == '['
                     || cc == ']' || cc == ',' || cc == ':' || cc == '\"')
            {
                if (_isInt)
                {
                    token.number(_integer * _numberSign);
                    return endTokenNoConsume(input, DataState);
                }
                else
                {
                    token.number(_integer, _numberSign, _frac, _fracLength, _exp, _expSign);
                    return endTokenNoConsume(input, DataState);
                }
            }
            else
            {
                return parseError(JSON_ERROR_UNEXPECTED_NUMBER_END);
            }
        }
        END_STATE()
    }
    
    return false;
}
