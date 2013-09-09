//
//  SourceStreamPreprocessor.h
//  SimpleJsonCpp
//
//  Created by Chen Jiajun on 13-8-23.
//  Copyright (c) 2013 chenjiajun90@gmail.com
//

#ifndef __SimpleJsonCpp__SourceStreamPreprocessor__
#define __SimpleJsonCpp__SourceStreamPreprocessor__

#include "SourceStream.h"

class SourceStreamPreprocessor
{
public:
    SourceStreamPreprocessor();
    bool peek(SourceStream& stream);
    bool advance(SourceStream& stream);
    wchar_t nextChar() const;
    
private:
    SourceStreamPreprocessor(const SourceStreamPreprocessor& other);
    SourceStreamPreprocessor& operator=(const SourceStreamPreprocessor& rhs);
    
    wchar_t _next;
};

#endif /* defined(__SimpleJsonCpp__SourceStreamPreprocessor__) */
