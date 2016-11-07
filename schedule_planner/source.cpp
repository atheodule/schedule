//This program is made
#include <python3.4m/Python.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <iostream>

int main(void){
    char *cstr;
    
    Py_Initialize();

    //loading pittAPI
    PyObject* module = PyImport_ImportModule("pittAPI");
     if (module== NULL){
       PyErr_Print();
    }
    assert(module != NULL);
    
    //making an instance of the class CourseAPI
    PyObject* instance = PyObject_GetAttrString(module, "CourseAPI");
    if (instance == NULL){
      PyErr_Print();
    }
    assert(instance != NULL);
    
    //setting variables
    PyObject* classnum = PyLong_FromLong(18037);
    PyObject* term = PyLong_FromLong(2171);
    PyObject* pName = PyUnicode_FromString("get_class_description");
    
    //calling the get class description function
    PyObject* result = PyObject_CallMethodObjArgs(instance, pName, classnum,term,NULL);
    if (result== NULL){
       PyErr_Print();
    }
    assert(result != NULL);
    
    // convert the result to a string 
    PyArg_Parse(result, "s", &cstr);
    std::cout << "The answer: " << cstr<< std::endl;
    
    Py_Finalize();
    return 0;
}