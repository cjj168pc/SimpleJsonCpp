//
//  StringBuffer.h
//  SimpleJsonCpp
//
//  Created by Teki on 13-8-22.
//  Copyright (c) 2013 chenjiajun90@gmail.com
//

#ifndef __SimpleJsonCpp__StringBuffer__
#define __SimpleJsonCpp__StringBuffer__

class StringBuffer
{
public:
    static StringBuffer* create();
    static StringBuffer* create(int size);
    static StringBuffer* create(const wchar_t* ref, int length);
    const wchar_t* buffer() const;
    wchar_t* buffer();
    int size() const;
    void resize(int size);
    void retain();
    void release();
    
private:
    StringBuffer();
    StringBuffer(const StringBuffer& other);
    StringBuffer& operator=(const StringBuffer& rhs);
    ~StringBuffer();
    
    wchar_t* _buffer;
    int _size;
    int _refCount;
};

#endif /* defined(__SimpleJsonCpp__StringBuffer__) */
