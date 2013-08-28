//
//  SourceStream.cpp
//  SimpleJsonCpp
//
//  Created by Teki on 13-8-22.
//  Copyright (c) 2013 chenjiajun90@gmail.com
//

#include "SourceStream.h"


SourceStream::SourceStream()
    : _pos(0)
{
}

SourceStream::SourceStream(String src)
{
    load(src);
}

SourceStream::~SourceStream()
{
}

wchar_t SourceStream::currentChar() const
{
    return _src.at(_pos);
}

void SourceStream::consume()
{
    _pos++;
}

void SourceStream::consume(int count)
{
    _pos += count;
}

bool SourceStream::lookAhead(const String &pattern)
{
    return _src.match(_pos, pattern);
}

bool SourceStream::end() const
{
    return _pos == _src.length();
}

int SourceStream::pos() const
{
    return _pos;
}

void SourceStream::load(String src)
{
    _src.clear();
    _src.append(src);
    _pos = 0;
}

void SourceStream::append(String src)
{
    _src.append(src);
}