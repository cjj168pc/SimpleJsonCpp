//
//  StringImpl.h
//  SimpleJsonCpp
//
//  Created by Teki on 13-8-22.
//  Copyright (c) 2013 chenjiajun90@gmail.com
//

#ifndef __SimpleJsonCpp__StringImpl__
#define __SimpleJsonCpp__StringImpl__

class StringBuffer;

class StringImpl
{
public:
    static StringImpl* create(const wchar_t* src, int length);
    StringImpl* subString(int offset);
    StringImpl* subString(int begin, int end);
    void retain();
    void release();
    int length() const;
    const wchar_t* data() const;
    bool less(const StringImpl* other) const;
    
private:
    StringImpl();
    ~StringImpl();
    StringImpl(const StringImpl& other);
    StringImpl& operator=(const StringImpl& rhs);
    
    StringBuffer* _cont;
    int _refCount;
    int _offset;
    int _length;
};

#endif /* defined(__SimpleJsonCpp__StringImpl__) */
