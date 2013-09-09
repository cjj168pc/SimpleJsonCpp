SimpleJsonCpp
=============

yet another JSON toolkit for C++

The principal objective of the project is to provide a simple way to use JSON in C++.

Features
-------------
* Parse string to json value
* Reference counted json value
* Convert json value to string

Build and install
-------------

    $ ./configure
    $ make
    $ sudo make install
    
Usage
-------------

*	**deserialize**

		String source;
		...
		JsonParser parser;
		// use RefPtr to protect the object from release
		RefPtr<JsonValue> value = parser.parse(source);
	
*	**build value**
		
		RefPtr<JsonObject> obj = JsonObject::create();
		obj->add(L"key1", JsonString::create(L"string value"));
		obj->add(L"key2", JsonNumber::create(-1234.32));
		
*	**conversion**

		JsonValue* val;
		...
		JsonObject* obj = val->asObject();

	
*	**serialize**
	
		RefPtr<JsonValue> value;
		...
		String str = value->toString();


*For more details plz reference example/example.cpp and example/makefile.*

Limitation
-------------
In order to avoid the cycle value nesting, we set a max depth of the nesting. The default value is 16, and you can modify it in JsonError.h.
    
Requirements
-------------
* Mac OS X or Linux
* gcc-g++
* gun make
* libtool

TODO
------------
* Design a more convenient way to convert between different json values, ie. convert `JsonValue` to `JsonArray`.
* Add Windows and other platform support.