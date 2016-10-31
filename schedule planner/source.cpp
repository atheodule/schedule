%This program is made
#include <Python.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

int main(void){
    
    Py_Initialize();
    PyRun_SimpleString("print 'Hello World'");
    Py_Finalize();
    return 0;
}