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
        obj->add(String(L"abc"), subobj.get());
        obj->add(String(L"acc"), JsonObject::create().get());
        obj->add(String(L"daaa"), JsonString::create(String(L"string")).get());
        obj->add(String(L"array"), JsonArray::create().get());
    }
    
    RefPtr<JsonString> sss = static_cast<JsonString*>(obj->getValue(String(L"daaa")));
    print(sss->getString());
    
    RefPtr<JsonArray> arr = static_cast<JsonArray*>(obj->getValue(String(L"array")));
    arr->add(JsonString::create(String(L"this is an array item")).get());
    arr->add(JsonNumber::create(10.4).get());
    
    RefPtr<JsonString> strInArr = static_cast<JsonString*>(arr->get(0));
    print(strInArr->getString());
    
    RefPtr<JsonNumber> jn = static_cast<JsonNumber*>(arr->get(1));
    printf("\n%f ", jn->getValue());
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
        JsonObject* root = static_cast<JsonObject*>(res.get());
        JsonNumber* num = static_cast<JsonNumber*>(root->getValue(String(L"ww")));
        
        printf("num = %f\n", num->getValue());
        
        String jss = SJ_ValueToString(root);
        print(jss);
        
        RefPtr<JsonValue> v = parser.parse(jss);
        if (!v.isNull())
        {
            jss = SJ_ValueToString(v.get());
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
