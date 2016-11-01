//This program is made
#include <python3.4m/Python.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <iostream>

int main(void){
    char *cstr;
    
    //printf("yo what up homie");
    Py_Initialize();
    
    //getting the module(module is like a file)
    PyObject* module = PyImport_ImportModule("pittAPI");
    assert(module != NULL);

    //getting courseapi class
    PyObject* pClass = PyObject_GetAttrString(module, "CourseAPI");
    assert(pClass != NULL);

    // //making an instance of the class
    // PyObject* instance = PyObject_GetAttrString(pClass, "CourseAPI");
    // assert(instance != NULL);
    
    // PyObject* pPosArgs = PyTuple_New(2) ;
    // int classnum = PyTuple_SetItem(pPosArgs, 0, PyLong_FromLong(18037));
    // int term = PyTuple_SetItem(pPosArgs,1,PyLong_FromLong(2171));
    
    //calling the get class description function
    PyObject* result = PyObject_CallMethod(pClass, "get_class_description", "18037", "2171");
    assert(result != NULL);
    
    // convert the result to a string 
    PyArg_Parse(result, "s", &cstr);
    std::cout << "The answer: " << cstr<< std::endl;
    
    Py_Finalize();
    return 0;
}