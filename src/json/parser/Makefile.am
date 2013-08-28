AUTOMAKE_OPTIONS = foreign

noinst_LTLIBRARIES = libjsonparser.la

libjsonparser_la_SOURCES = JsonError.h JsonParser.cpp JsonParser.h JsonToken.cpp JsonToken.h JsonTokenizer.cpp JsonTokenizer.h JsonValueBuilder.cpp JsonValueBuilder.h SourceStream.cpp SourceStream.h SourceStreamPreprocessor.cpp SourceStreamPreprocessor.h TokenizerInlines.h

libutildir = ../../util
libjsonentitydir = ../entity

libjsonparser_la_LIBADD = -ljsonentity

libjsonparser_la_LDFLAGS = -L$(libutildir) -L$(libjsonentitydir)

libjsonparser_la_CPPFLAGS = -I$(libutildir) -I$(libjsonentitydir) -fPIC


export parserheaders = JsonError.h JsonParser.h JsonToken.h JsonTokenizer.h JsonValueBuilder.h SourceStream.h SourceStreamPreprocessor.h TokenizerInlines.h
