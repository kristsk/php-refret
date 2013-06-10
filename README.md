Refret PHP Extension
====================

Introduction 
------------

Built-in functions **call_user_func()** and **call_user_func_array()** currently do not support propperly returning references produced by called functions. This extension implements functions that can return references. It is done by taking orginal code of **call_user_func()** and **call_user_func_array()** and extending with a simple check and return of true reference instead of a zval copy.

Apart from some practical use for my own pet project, I would imagine this could be used as a example how a simple PHP extension is built and structured.


Implemented functions
---------------------

Currently following functions are implemented:

* **refret_call_user_func()** - reference returining version of **call_user_func()**
* **refret_call_user_func_array()** - reference returning version of **call_user_func_array()**

These new functions can also be used if function called is not returning by reference.


Installing
----------

The usual way.

<pre>
$ git clone git://github.com/kristsk/php-refret.git
$ cd php-refret
$ phpize
$ ./configure
$ make
$ make install
</pre>

Also, you probably will need to add following line to **php.ini** manually:
<pre>
extension=refret.so
</pre>


Tests
-----

A simple test is provided.
I did run test with Valgrind enabled and as I understood, no memory leaks were reported.