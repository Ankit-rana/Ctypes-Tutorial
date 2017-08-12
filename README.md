# Contact
- This project explains you a way to Create a DLL of C++ code and use it in Python Code. 

- Once you have coded Cpp project, run these on Linux:
	- g++ -fPIC -shared myclass.cc -o myclass.so
	- g++ class_user.cc -ldl -o class_user

- Mostly DLL's are kept at /usr/lib and /lib 
- Now since .so have been created , I will use Python module ctypes to interact with our .so file
- On Linux, it is required to specify the filename including the extension to load a library, so attribute access can not be used to load libraries. Either the LoadLibrary() method of the dll loaders should be used, or you should load the library by creating an instance of CDLL by calling the constructor:

	>>> cdll.LoadLibrary("libc.so.6")  
	<CDLL 'libc.so.6', handle ... at ...>
	>>> libc = CDLL("libc.so.6")       
	>>> libc                           
	<CDLL 'libc.so.6', handle ... at ...>
	>>>

- call the DLL's function

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
