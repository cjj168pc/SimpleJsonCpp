//
//  TokenizerInlines.h
//  SimpleJsonCpp
//
//  Created by Chen Jiajun on 13-8-23.
//  Copyright (c) 2013 chenjiajun90@gmail.com
//

#ifndef SimpleJsonCpp_TokenizerInlines_h
#define SimpleJsonCpp_TokenizerInlines_h

#define BEGIN_STATE(prefix, stateName) case prefix::stateName: stateName:

#define END_STATE() break;

#define RECONSUME_IN(prefix, stateName)                                     \
do {                                                                        \
    _state = prefix::stateName;                                             \
    goto stateName;                                                         \
} while (false)

#define SWITCH_TO(prefix, stateName)                                        \
do {                                                                        \
    _state = prefix::stateName;                                             \
    if (!_preprocesser.peek(input))                                         \
    {                                                                       \
        return false;                                                       \
    }                                                                       \
    cc = _preprocesser.nextChar();                                          \
    goto stateName;                                                         \
} while (false)

#define ADVANCE_TO(prefix, stateName)                                       \
do {                                                                        \
    _state = prefix::stateName;                                             \
    if (input.end() || !_preprocesser.advance(input))                       \
    {                                                                       \
        return false;                                                       \
    }                                                                       \
    cc = _preprocesser.nextChar();                                          \
    goto stateName;                                                         \
} while (false)

#endif
