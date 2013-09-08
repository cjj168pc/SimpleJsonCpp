//
//  example.cpp
//  SimpleJsonCpp
//
//  Created by Teki on 13-8-22.
//  Copyright (c) 2013 chenjiajun90@gmail.com
//

#include <iostream>
#include <simplejsoncpp/SimpleJson.h>
#include <string>

void print(String str)
{
    std::wstring lit(str.data(), str.length());
    printf("%ls", lit.c_str());
}

void testJsonValues()
{
    RefPtr<JsonObject> obj = JsonObject::create();
    {
        RefPtr<JsonObject> subobj = JsonObject::create();
        obj->add(L"abc", subobj);
        obj->add(L"acc", JsonObject::create());
        obj->add(L"daaa", JsonString::create(L"string"));
        obj->add(L"array", JsonArray::create());
    }
    
    JsonString* sss = obj->getValue(L"daaa")->asString();
    print(sss->getString());
    
    JsonArray* arr = obj->getValue(L"array")->asArray();
    arr->add(JsonString::create(L"this is an array item"));
    arr->add(JsonNumber::create(10.4));
    arr->add(JsonString::create(L"a string literal"));
    
    JsonString* strInArr = arr->get(0)->asString();
    print(strInArr->getString());
    
    JsonNumber* jn = arr->get(1)->asNumber();
    printf("\n%f ", jn->getDouble());
}

void printParseError(JsonParser& parser, String source)
{
    JsonParser::ParseError err = parser.getError();
    String errSeg = source.subString(err.pos - 1, err.pos);
    std::wstring em(errSeg.data(), errSeg.length());
    std::wstring msg(err.message.data(), err.message.length());
    printf("error No.%d %ls\n at %d (%ls)", err.code, msg.c_str(), err.pos, em.c_str());
}

int main(int argc, const char * argv[])
{
    JsonParser parser;
    
    String source = L"{ \"cc\" : [\"s\\n\\u0034s\", null,{\"key\":0}, true,false,2131],\"ww\":-32.32e-7 }";
    
    RefPtr<JsonValue> res = parser.parse(source);
    if (!res.isNull())
    {
        JsonObject* root = res->asObject();
        JsonNumber* num = root->getValue(L"ww")->asNumber();
        
        printf("num = %f\n", num->getDouble());
        
        String jss = jsonValueToString(root);
        print(jss);
        
        RefPtr<JsonValue> v = parser.parse(jss);
        if (!v.isNull())
        {
            jss = jsonValueToString(v.get());
            printf("\n");
            print(jss);
            if (v != root)
            {
                printf("\nnot the same object\n");
            }
        }
        else
        {
            printParseError(parser, source);
        }
    }
    else
    {
        printParseError(parser, source);
    }
    
    return 0;
}
