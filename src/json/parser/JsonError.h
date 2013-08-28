//
//  JsonError.h
//  SimpleJsonCpp
//
//  Created by Chen Jiajun on 13-8-25.
//  Copyright (c) 2013 chenjiajun90@gmail.com
//

#ifndef SimpleJsonCpp_JsonError_h
#define SimpleJsonCpp_JsonError_h

enum ErrorType
{
    JSON_ERROR_INVALID_IDENTIFIER,
    JSON_ERROR_UNEXPECTED_END,
    JSON_ERROR_INVALID_CHARACTER_IN_STRING,
    JSON_ERROR_INVALID_STRING_REFERENCE,
    JSON_ERROR_EXPECT_DIGIT,
    JSON_ERROR_UNEXPECTED_NUMBER_END,
    JSON_ERROR_EXPECTED_PAIR_NAME,
    JSON_ERROR_EXPECTED_NAME_SEPARATOR,
    JSON_ERROR_EXPECTED_ELEMENT_SEPARATOR,
    JSON_ERROR_MORE_THAN_ONE_ROOT,
    JSON_ERROR_EXPECTED_PAIR_SEPARATOR,
    JSON_ERROR_EXPECTED_OBJECT_OR_ARRAY,
    JSON_ERROR_EXPECTED_VALUE
};

#endif