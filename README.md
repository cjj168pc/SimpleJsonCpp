SimpleJsonCpp
=============

yet another JSON tool kit for C++

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
    
Requirements
-------------
* Mac OS X or Linux
* GUN g++
* GNU make
* GUN libtool

TODO
------------
* Design a more convenient way to convert between different json values, ie. convert `JsonValue` to `JsonArray`.
* Add Windows and other platform support.