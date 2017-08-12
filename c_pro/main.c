/**
* this program calls foo() from foo.c
* typically we keep all .c file in src/ folder and .h in headers/ folder
* name : main.c
* author : Ankit Rana
*/

#include <stdio.h>
#include "foo.h"
 
int main(void)
{
    puts("This is a shared library test...");
    foo();
    return 0;
}
