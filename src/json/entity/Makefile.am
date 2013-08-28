AUTOMAKE_OPTIONS = foreign

noinst_LTLIBRARIES = libjsonentity.la

libjsonentity_la_SOURCES = JsonArray.cpp JsonArray.h JsonBoolean.cpp JsonBoolean.h JsonNull.cpp JsonNull.h JsonNumber.cpp JsonNumber.h JsonObject.cpp JsonObject.h JsonString.cpp JsonString.h JsonValue.cpp JsonValue.h

libutildir = ../../util

libjsonentity_la_LIBADD = -lutil

libjsonentity_la_LDFLAGS = -L$(libutildir)

libjsonentity_la_CPPFLAGS = -I$(libutildir) -fPIC


export entityheaders = JsonArray.h JsonBoolean.h JsonNull.h JsonNumber.h JsonObject.h JsonString.h JsonValue.h
