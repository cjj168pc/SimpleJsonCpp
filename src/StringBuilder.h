//
//  StringBuilder.h
//  SimpleJsonCpp
//
//  Created by Teki on 13-8-22.
//  Copyright (c) 2013 chenjiajun90@gmail.com
//

#ifndef __SimpleJsonCpp__StringBuilder__
#define __SimpleJsonCpp__StringBuilder__

#include "MyString.h"

class StringBuffer;

class StringBuilder
{
public:
    StringBuilder();
    ~StringBuilder();
    void append(wchar_t ch);
    void append(String str);
    void append(const wchar_t* data, int length);
    void appendInt(int num);
    void appendDouble(double num);
    wchar_t at(int index) const;
    wchar_t& at(int index);
    String toString() const;
    String subString(int begin, int end) const;
    bool match(int begin, const String& pattern) const;
    void clear();
    int length() const;
    const wchar_t* data() const;
    
private:
    StringBuilder(const StringBuilder& other);
    StringBuilder& operator=(const StringBuilder& rhs);
    void ensureSpace(int size);
    
    static const int INIT_CAP = 16;
    
    StringBuffer* _cont;
    int _length;
};

#endif /* defined(__SimpleJsonCpp__StringBuilder__) */
