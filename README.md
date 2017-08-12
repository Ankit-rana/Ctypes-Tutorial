# Contact
- This project explains you a way to Create a DLL of C++ code and use it in Python Code. 
- DLL refers to Dynamic Link Library(microsoft term) which is reffered to as Shared Library in Linux.
> **Note**
> - Shared libraries are libraries that are loaded by programs when they start.
> - Naming follow convention of having lib as prefix and .so as postfix
- Once you have coded C project, run these on Linux:
	- Compile lib code into a PIC (Position Independent Code)
	- $ gcc -c -Wall -Werror -fpic foo.c
	- convert object file into shared library
	- $ gcc -shared -o libfoo.so foo.o
	- make it known to loader (rpath, LD_LIBRARY_PATH or standard path)
	- cp /home/username/foo/libfoo.so /usr/lib
	- chmod 0755 /usr/lib/libfoo.so
	- ldconfig                    // updates cache
	- $ ldconfig -p | grep foo    // check if link got created
	- libfoo.so (libc6) => /usr/lib/libfoo.so
	- How to link to a c program ?
	- $ gcc -Wall -o test main.c -lfoo    // remember pthreads

- Mostly DLL's are kept at /usr/lib and /usr/local/lib 
- Now since .so have been created , I will use Python module ctypes to interact with our .so file
- But first a little background on ctypes
> **Note**
> - ctypes is the de facto library for interfacing with C/C++ from CPython, and it provides not only full access to the native C interface of most major operating systems (e.g., kernel32 on Windows, or libc on *nix), but also provides support for loading and interfacing with dynamic libraries, such as DLLs or shared objects at runtime
> - It does bring along with it a whole host of types for interacting with system APIs, and allows you to rather easily define your own complex types, such as structs and unions, and allows you to modify things such as padding and alignment, if needed.
> - It can be a bit crufty to use, but in conjunction with the struct module, you are essentially provided full control over how your data types get translated into something usable by a pure C(++) method.
MyStruct.h
```c
struct my_struct {
    int a;
    int b;
};
```
MyStruct.py
```python
import ctypes
class my_struct(ctypes.Structure):
    _fields_ = [("a", c_int),
                ("b", c_int)]
```
- On Linux, it is required to specify the filename including the extension to load a library, so attribute access can not be used to load libraries. Either the LoadLibrary() method of the dll loaders should be used, or you should load the library by creating an instance of CDLL by calling the constructor:
```python
	>>> from ctypes import *
	>>> cdll.LoadLibrary("libc.so.6")  
	<CDLL 'libc.so.6', handle ... at ...>
	>>> libc = CDLL("libc.so.6")       
	>>> libc                           
	<CDLL 'libc.so.6', handle ... at ...>
	>>>
```
- call the DLL's function
```python
	>>> print libc.time(None)  
	1150640792
	>>> printf = libc.printf
	>>> printf("Hello, %s\n", "World!")
	Hello, World!
	14
	>>> printf("Hello, %S\n", u"World!")
	Hello, World!
	14
	>>> printf("%d bottles of beer\n", 42)
	42 bottles of beer
	19
	>>> printf("%f bottles of beer\n", 42.5)
	Traceback (most recent call last):
  	  File "<stdin>", line 1, in <module>
	ArgumentError: argument 2: exceptions.TypeError: Don't know how to convert parameter 2
	>>> printf("An int %d, a double %f\n", 1234, c_double(3.14))
	An int 1234, a double 3.140000
	31
```
