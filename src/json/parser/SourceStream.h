//
//  SourceStream.h
//  SimpleJsonCpp
//
//  Created by Teki on 13-8-22.
//  Copyright (c) 2013 chenjiajun90@gmail.com
//

#ifndef __SimpleJsonCpp__SourceStream__
#define __SimpleJsonCpp__SourceStream__

#include "StringBuilder.h"

class SourceStream
{
public:
    SourceStream();
    SourceStream(String src);
    ~SourceStream();
    wchar_t currentChar() const;
    void consume();
    void consume(int count);
    bool end() const;
    int pos() const;
    bool lookAhead(const String &pattern);
    void load(String src);
    void append(String src);
    
private:
    SourceStream(const SourceStream& other);
    SourceStream& operator=(const SourceStream& rhs);
    
    StringBuilder _src;
    int _pos;
};

#endif /* defined(__SimpleJsonCpp__SourceStream__) */
