//
//  JsonValueBuilder.cpp
//  SimpleJsonCpp
//
//  Created by Chen Jiajun on 13-8-24.
//  Copyright (c) 2013 chenjiajun90@gmail.com
//

#include "JsonValueBuilder.h"
#include "JsonObject.h"
#include "JsonArray.h"
#include "JsonString.h"
#include "JsonNumber.h"
#include "JsonBoolean.h"
#include "JsonNull.h"
#include <cassert>


static inline bool isContainer(JsonValue* context)
{
    return (context->type() != JsonValue::Literal)
        && (context->type() != JsonValue::Number)
        && (context->type() != JsonValue::Boolean)
        && (context->type() != JsonValue::Null);
}

static PassPtr<JsonNumber> createNumberFromToken(const JsonToken& token)
{
    if (token.isInteger())
    {
        return JsonNumber::create(token.getInteger());
    }
    else
    {
        return JsonNumber::create(token.getDouble());
    }
}

JsonValueBuilder::JsonValueBuilder()
    : _mode(InitMode), _err(false)
{
}

JsonValueBuilder::~JsonValueBuilder()
{
}

bool JsonValueBuilder::processToken(const JsonToken& token)
{
    switch (token.type())
    {
        case JsonToken::Uninitialized:
            processUninitilized(token);
            break;
        case JsonToken::BeginObject:
            processBeginObject(token);
            break;
        case JsonToken::EndObject:
            processEndObject(token);
            break;
        case JsonToken::NameSeparator:
            processNameSeparator(token);
            break;
        case JsonToken::BeginArray:
            processBeginArray(token);
            break;
        case JsonToken::EndArray:
            processEndArray(token);
            break;
        case JsonToken::ValueSeparator:
            processValueSeparator(token);
            break;
        case JsonToken::Literal:
            processLiteral(token);
            break;
        case JsonToken::NumberValue:
            processNumber(token);
            break;
        case JsonToken::TrueValue:
            processTrue(token);
            break;
        case JsonToken::FalseValue:
            processFalse(token);
            break;
        case JsonToken::NullValue:
            processNull(token);
            break;
        case JsonToken::EndOfFile:
            processEndOfFile(token);
            break;
        case JsonToken::Error:
            assert(0);
            break;
    }
    
    return !_err;
}

void JsonValueBuilder::processUninitilized(const JsonToken& token)
{
    assert(0);
}

void JsonValueBuilder::processBeginObject(const JsonToken& token)
{
    if (_mode == InitMode)
    {
        _root = JsonObject::create();
        _path.push(_root.get());
        _mode = PairNameMode;
    }
    else if (_mode == PairValueMode)
    {
        JsonObject* context = static_cast<JsonObject*>(_path.top());
        RefPtr<JsonObject> value = JsonObject::create();
        _path.push(value.get());
        context->add(_tmpKey, value.get());
        _mode = PairNameMode;
    }
    else if (_mode == ElementMode || _mode == ElementOnlyMode)
    {
        JsonArray* context = static_cast<JsonArray*>(_path.top());
        RefPtr<JsonObject> value = JsonObject::create();
        _path.push(value.get());
        context->add(value.get());
        _mode = PairNameMode;
    }
    else
    {
        parseError(token);
    }
}

void JsonValueBuilder::processEndObject(const JsonToken& token)
{
    if (_mode == PairNameMode || _mode == PairSeparatorMode)
    {
        _path.pop();
        if (_path.empty())
        {
            _mode = EndMode;
            return;
        }
        JsonValue* context = _path.top();
        assert(isContainer(context));
        if (context->type() == JsonValue::Object)
        {
            _mode = PairSeparatorMode;
        }
        else if (context->type() == JsonValue::Array)
        {
            _mode = ElementSeparatorMode;
        }
    }
    else if (_mode == ElementMode)
    {
        JsonArray* context = static_cast<JsonArray*>(_path.top());
        RefPtr<JsonObject> value = JsonObject::create();
        _path.push(value.get());
        context->add(value.get());
        _mode = PairNameMode;
    }
    else
    {
        parseError(token);
    }
}

void JsonValueBuilder::processNameSeparator(const JsonToken& token)
{
    if (_mode == NameSeparatorMode)
    {
        _mode = PairValueMode;
    }
    else
    {
        parseError(token);
    }
}

void JsonValueBuilder::processBeginArray(const JsonToken& token)
{
    if (_mode == InitMode)
    {
        _root = JsonArray::create();
        _path.push(_root.get());
        _mode = ElementMode;
    }
    else if (_mode == PairValueMode)
    {
        JsonObject* context = static_cast<JsonObject*>(_path.top());
        RefPtr<JsonArray> value = JsonArray::create();
        _path.push(value.get());
        context->add(_tmpKey, value.get());
        _mode = ElementMode;
    }
    else if (_mode == ElementMode || _mode == ElementOnlyMode)
    {
        JsonArray* context = static_cast<JsonArray*>(_path.top());
        RefPtr<JsonArray> value = JsonArray::create();
        _path.push(value.get());
        context->add(value.get());
        _mode = ElementMode;
    }
    else
    {
        parseError(token);
    }
}

void JsonValueBuilder::processEndArray(const JsonToken& token)
{
    if (_mode == ElementMode || _mode == ElementSeparatorMode)
    {
        _path.pop();
        if (_path.empty())
        {
            _mode = EndMode;
            return;
        }
        JsonValue* context = _path.top();
        assert(isContainer(context));
        if (context->type() == JsonValue::Object)
        {
            _mode = PairSeparatorMode;
        }
        else if (context->type() == JsonValue::Array)
        {
            _mode = ElementSeparatorMode;
        }
    }
    else
    {
        parseError(token);
    }
}

void JsonValueBuilder::processValueSeparator(const JsonToken& token)
{
    if (_mode == PairSeparatorMode)
    {
        _mode = PairNameOnlyMode;
    }
    else if (_mode == ElementSeparatorMode)
    {
        _mode = ElementOnlyMode;
    }
    else
    {
        parseError(token);
    }
}

void JsonValueBuilder::processLiteral(const JsonToken& token)
{
    if (_mode == PairNameMode || _mode == PairNameOnlyMode)
    {
        if (token.data().length() == 0)
        {
            parseError(token);
            return;
        }
        _tmpKey = token.data();
        _mode = NameSeparatorMode;
    }
    else if (_mode == PairValueMode)
    {
        JsonValue* context = _path.top();
        assert(context->type() == JsonValue::Object);
        JsonObject* obj = static_cast<JsonObject*>(context);
        obj->add(_tmpKey, JsonString::create(token.data()).get());
        _mode = PairSeparatorMode;
    }
    else if (_mode == ElementMode || _mode == ElementOnlyMode)
    {
        JsonValue* context = _path.top();
        assert(context->type() == JsonValue::Array);
        JsonArray* arr = static_cast<JsonArray*>(context);
        arr->add(JsonString::create(token.data()).get());
        _mode = ElementSeparatorMode;
    }
    else
    {
        parseError(token);
    }
}

void JsonValueBuilder::processNumber(const JsonToken& token)
{
    if (_mode == PairValueMode)
    {
        JsonValue* context = _path.top();
        assert(context->type() == JsonValue::Object);
        JsonObject* obj = static_cast<JsonObject*>(context);
        obj->add(_tmpKey, createNumberFromToken(token));
        _mode = PairSeparatorMode;
    }
    else if (_mode == ElementMode || _mode == ElementOnlyMode)
    {
        JsonValue* context = _path.top();
        assert(context->type() == JsonValue::Array);
        JsonArray* arr = static_cast<JsonArray*>(context);
        arr->add(createNumberFromToken(token));
        _mode = ElementSeparatorMode;
    }
    else
    {
        parseError(token);
    }
}

void JsonValueBuilder::processTrue(const JsonToken& token)
{
    if (_mode == PairValueMode)
    {
        JsonValue* context = _path.top();
        assert(context->type() == JsonValue::Object);
        JsonObject* obj = static_cast<JsonObject*>(context);
        obj->add(_tmpKey, JsonBoolean::create(true).get());
        _mode = PairSeparatorMode;
    }
    else if (_mode == ElementMode || _mode == ElementOnlyMode)
    {
        JsonValue* context = _path.top();
        assert(context->type() == JsonValue::Array);
        JsonArray* arr = static_cast<JsonArray*>(context);
        arr->add(JsonBoolean::create(true).get());
        _mode = ElementSeparatorMode;
    }
    else
    {
        parseError(token);
    }
}

void JsonValueBuilder::processFalse(const JsonToken& token)
{
    if (_mode == PairValueMode)
    {
        JsonValue* context = _path.top();
        assert(context->type() == JsonValue::Object);
        JsonObject* obj = static_cast<JsonObject*>(context);
        obj->add(_tmpKey, JsonBoolean::create(false).get());
        _mode = PairSeparatorMode;
    }
    else if (_mode == ElementMode || _mode == ElementOnlyMode)
    {
        JsonValue* context = _path.top();
        assert(context->type() == JsonValue::Array);
        JsonArray* arr = static_cast<JsonArray*>(context);
        arr->add(JsonBoolean::create(false).get());
        _mode = ElementSeparatorMode;
    }
    else
    {
        parseError(token);
    }
}

void JsonValueBuilder::processNull(const JsonToken& token)
{
    if (_mode == PairValueMode)
    {
        JsonValue* context = _path.top();
        assert(context->type() == JsonValue::Object);
        JsonObject* obj = static_cast<JsonObject*>(context);
        obj->add(_tmpKey, JsonNull::create().get());
        _mode = PairSeparatorMode;
    }
    else if (_mode == ElementMode || _mode == ElementOnlyMode)
    {
        JsonValue* context = _path.top();
        assert(context->type() == JsonValue::Array);
        JsonArray* arr = static_cast<JsonArray*>(context);
        arr->add(JsonNull::create().get());
        _mode = ElementSeparatorMode;
    }
    else
    {
        parseError(token);
    }
}

void JsonValueBuilder::processEndOfFile(const JsonToken& token)
{
    
}

void JsonValueBuilder::parseError(const JsonToken& token)
{
    switch (_mode)
    {
        case InitMode:
            parseError(token, JSON_ERROR_EXPECTED_OBJECT_OR_ARRAY);
            break;
        case PairNameMode:
        case PairNameOnlyMode:
            parseError(token, JSON_ERROR_EXPECTED_PAIR_NAME);
            break;
        case NameSeparatorMode:
            parseError(token, JSON_ERROR_EXPECTED_NAME_SEPARATOR);
            break;
        case PairValueMode:
        case ElementMode:
        case ElementOnlyMode:
            parseError(token, JSON_ERROR_EXPECTED_VALUE);
            break;
        case PairSeparatorMode:
            parseError(token, JSON_ERROR_EXPECTED_NAME_SEPARATOR);
            break;
        case ElementSeparatorMode:
            parseError(token, JSON_ERROR_EXPECTED_ELEMENT_SEPARATOR);
            break;
        case EndMode:
            parseError(token, JSON_ERROR_MORE_THAN_ONE_ROOT);
            break;
    }
}

void JsonValueBuilder::parseError(const JsonToken& token, ErrorType code)
{
    _err = true;
    _errCode = code;
    _errPos = token.getRange().begin;
}

JsonValue* JsonValueBuilder::getRoot() const
{
    return _root.get();
}

bool JsonValueBuilder::finished() const
{
    return _mode == EndMode;
}

ErrorType JsonValueBuilder::getErrorType() const
{
    return _errCode;
}

int JsonValueBuilder::getErrorPos() const
{
    return _errPos;
}

