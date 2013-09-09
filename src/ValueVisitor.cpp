#include "ValueVisitor.h"
#include "JsonObject.h"
#include "JsonArray.h"
#include "JsonNumber.h"
#include "JsonString.h"
#include "JsonBoolean.h"
#include "JsonNull.h"
#include "JsonError.h"


ValueStringVisitor::ValueStringVisitor()
    : _depth(MAX_NESTING)
{
}

void ValueStringVisitor::visit(JsonValue* value)
{
    if (_depth == 0)
    {
        return;
    }

    switch (value->type())
    {
    case JsonValue::Object:
        forObject(value->asObject());
        break;
    case JsonValue::Array:
        forArray(value->asArray());
        break;
    case JsonValue::Literal:
        forString(value->asString());
        break;
    case JsonValue::Number:
        forNumber(value->asNumber());
        break;
    case JsonValue::Boolean:
        forBoolean(value->asBoolean());
        break;
    case JsonValue::Null:
        forNull();
        break;
    }
}

void ValueStringVisitor::forObject(JsonObject* obj)
{
}

void ValueStringVisitor::forArray(JsonArray* arr)
{
    bool first = true;
    _buff.append('[');
    for (int i = 0; i < arr->count(); ++i)
    {
        if (first)
        {
            first = false;
        }
        else
        {
            _buff.append(',');
        }
        arr->get(i)->accept(this);
    }
    _buff.append(']');
}

void ValueStringVisitor::forString(JsonString* str)
{
    _buff.append(str->getString());
}

void ValueStringVisitor::forNumber(JsonNumber* num)
{
    if (num->isInteger())
    {
        _buff.appendInt(num->getInteger());
    }
    else
    {
        _buff.appendDouble(num->getDouble());
    }
}

void ValueStringVisitor::forBoolean(JsonBoolean* boo)
{
    static String strTrue = L"true";
    static String strFalse = L"false";

    if (boo->getValue())
    {
        _buff.append(strTrue);
    }
    else
    {
        _buff.append(strFalse);
    }
}

void ValueStringVisitor::forNull()
{
    static String strNull = L"null";

    _buff.append(strNull);
}

String ValueStringVisitor::getResult() const
{
    return _buff.toString();
}
