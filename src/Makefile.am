AUTOMAKE_OPTIONS = foreign

SUBDIRS = util json/entity json/parser

lib_LTLIBRARIES = libsimplejsoncpp.la

libsimplejsoncpp_la_SOURCES = SimpleJson.h SimpleJson.cpp

libsimplejsoncpp_la_LIBADD = -ljsonparser

libsimplejsoncpp_la_LDFLAGS = -version-info 1:0:0 --whole-archive -Lutil -Ljson/entity -Ljson/parser

libsimplejsoncpp_la_CPPFLAGS = -Iutil -Ijson/entity -Ijson/parser -fPIC 

libsimplejsoncpp_la_includedir = $(includedir)/simplejsoncpp

libsimplejsoncpp_la_include_HEADERS = SimpleJson.h util/MyString.h util/PassPtr.h util/RefCounted.h util/RefPtr.h \
									  util/StringBuilder.h json/entity/JsonArray.h json/entity/JsonBoolean.h \
									  json/entity/JsonNull.h json/entity/JsonNumber.h json/entity/JsonObject.h \
									  json/entity/JsonString.h json/entity/JsonValue.h json/parser/JsonError.h \
									  json/parser/JsonParser.h json/parser/JsonToken.h json/parser/JsonTokenizer.h \
									  json/parser/JsonValueBuilder.h json/parser/SourceStream.h \
									  json/parser/SourceStreamPreprocessor.h json/parser/TokenizerInlines.h
