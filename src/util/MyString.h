//
//  MyString.h
//  SimpleJsonCpp
//
//  Created by Teki on 13-8-22.
//  Copyright (c) 2013 chenjiajun90@gmail.com
//

#ifndef __SimpleJsonCpp__String__
#define __SimpleJsonCpp__String__

class StringImpl;

class String
{
public:
    String();
    String(const wchar_t* nullEndStr);
    String(const wchar_t* data, int length);
    String(const String& other);
    ~String();
    String& operator=(const String& rhs);
    String subString(int offset);
    String subString(int begin, int end);
    int length() const;
    const wchar_t* data() const;
    wchar_t at(int index) const;
    bool operator<(const String& rhs) const;
    
private:
    String(StringImpl* impl);
    
    StringImpl* _impl;
};

#endif /* defined(__SimpleJsonCpp__String__) */
