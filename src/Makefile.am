all_headers = JsonArray.h \
        JsonBoolean.h \
        JsonNull.h \
        JsonNumber.h \
        JsonObject.h \
        JsonString.h \
        JsonValue.h \
        JsonError.h \
        JsonParser.h \
        JsonToken.h \
        JsonTokenizer.h \
        JsonValueBuilder.h \
        SourceStream.h \
        SourceStreamPreprocessor.h \
        TokenizerInlines.h \
        MyString.h \
        PassPtr.h \
        RefCounted.h \
        RefPtr.h \
        StringBuffer.h \
        StringBuilder.h \
        StringImpl.h \
        ValueVisitor.h \
        ValueSerializer.h

all_sources = JsonArray.cpp \
        JsonBoolean.cpp \
        JsonNull.cpp \
        JsonNumber.cpp \
        JsonObject.cpp \
        JsonString.cpp \
        JsonValue.cpp \
        JsonParser.cpp \
        JsonToken.cpp \
        JsonTokenizer.cpp \
        JsonValueBuilder.cpp \
        SourceStream.cpp \
        SourceStreamPreprocessor.cpp \
        MyString.cpp \
        StringBuffer.cpp \
        StringBuilder.cpp \
        StringImpl.cpp \
        ValueSerializer.cpp

AUTOMAKE_OPTIONS = foreign

lib_LTLIBRARIES = libsimplejsoncpp.la

libsimplejsoncpp_la_SOURCES = $(all_headers) $(all_sources)

libsimplejsoncpp_la_LDFLAGS = -version-info 1:0:0

libsimplejsoncpp_la_CPPFLAGS = -fPIC 

libsimplejsoncpp_la_includedir = $(includedir)/simplejsoncpp

libsimplejsoncpp_la_include_HEADERS = SimpleJson.h MyString.h PassPtr.h RefCounted.h RefPtr.h \
									  StringBuilder.h JsonArray.h JsonBoolean.h \
									  JsonNull.h JsonNumber.h JsonObject.h \
									  JsonString.h JsonValue.h JsonError.h \
									  JsonParser.h JsonToken.h JsonTokenizer.h \
									  JsonValueBuilder.h SourceStream.h \
									  SourceStreamPreprocessor.h TokenizerInlines.h
