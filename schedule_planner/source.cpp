//This program is made
#include <python3.4m/Python.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <iostream>
#include <string>

void classdesc(void);
void listclasses(void);

class Course{
    private:
        char *name;
        int course_number;
        int number_of_credits;
        
    public:
        Course(char *title, int course_num, int credit){
            title = name;
            course_number = course_num;
            number_of_credits = credit;
        };
        Course(){
            name = NULL;
            course_number = 0;
            number_of_credits = 0;
        };
        void renameCourse(char * new_name){
            name = new_name;
        };
        int getCourseNumber(){
            return course_number;
        };
        int getNumberOfCredits(){
            return number_of_credits;
        };
        char* getInstructor();
};

class CourseList{
    private:
        Course available_courses [];
        int number_of_courses;
        int maxCapacity;
    
    public:
        CourseList(){
            maxCapacity = 30;
            number_of_courses = 0;
            Course available_courses [maxCapacity];
        };
        
        void addCourse(Course);
        void removeCourse(Course);
        int getNumberOfCourses();
        bool contains(Course);
        void printCourses();
        bool isEmpty();
};

int main(void)
{
    //classdesc();
    listclasses();
    return 0;
}

void listclasses(void){
    //asking what classes would you like to see
    int class_select; char *s_subject; int userterm;
    
    std::string questsub = "What subject would you like to search:\n1. CS Courses\n2. ECE Courses\n3. COE Courses\nAnswer: ";
    std::cout<<questsub; 
    std::cin>>class_select;
    
    switch (class_select){
        case 1: s_subject = "CS"; 
        break;
        
        case 2: s_subject = "ECE";
        break;
        
        case 3: s_subject = "COE";
        break;
    }
    
    //asking which term
    std::string questterm = "\nWhat term would you like to search:\n1. Fall\n2. Spring\n3. Summer\nAnswer: ";
    std::cout<<questterm; 
    std::cin>>userterm;
    
    switch (userterm){
        case 1: userterm = 2171; 
        break;
        
        case 2: userterm = 2174;
        break;
        
        case 3: userterm = 2167;
        break;
    }
   
    Py_Initialize();

    //PyRun_SimpleString("import sys");
    //PyRun_SimpleString("print(sys.path)");

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
    PyObject* class_sub = PyUnicode_FromString(s_subject);
    PyObject* term = PyLong_FromLong(userterm);
    PyObject* pName = PyUnicode_FromString("get_courses");
    
    //calling the get class description function
    PyObject* courselist = PyObject_CallMethodObjArgs(instance, pName, instance,term, class_sub,NULL);
    if (courselist== NULL){
       PyErr_Print();
    }
    assert(courselist != NULL);
   
   //getting dictionary of files
   
   for(int i = 0; i < PyList_Size(courselist); i++){
      
      char *term_string;
      char *title_string;
      char *class_string;
      char *professor_string;
      
      PyObject* tempitem = PyList_GetItem(courselist,i);
      //instructor gives you class title
      //catalog_number gives you course subject, ie ECE
      //term gives you course number, ie for class ECE 1201 it will give you 1201
      //title gives you the session and term number ie 2171 AT
      //class_number gives you class number
      PyObject* classes_to_ignore = PyDict_GetItemString(tempitem,"catalog_number");
      PyObject* class_title = PyDict_GetItemString(tempitem,"title");
      PyObject* class_numcheck = PyDict_GetItemString(tempitem,"class_number");
      PyObject* professor = PyDict_GetItemString(tempitem,"instructor");
      
      /*<tr> 
    <th width="9%">Subject</th> 0
    <th width="8%">Catalog #</th> 1
    <th width="10%">Term</th>     2
    <th width="9%">Class # </th>  3
    <th width="24%">Title</th>    4
    <th width="25%">Instructor</th>   5 
    <th width="15%">Credits/Units</th>   6
  </tr>*/
      
      PyArg_Parse(classes_to_ignore, "s", &term_string);
      PyArg_Parse(class_title, "s", &title_string);
      PyArg_Parse(class_numcheck, "s", &class_string);
      PyArg_Parse(professor, "s", &professor_string);
      
     if(atoi(term_string) < 1885){
        std::cout<<"\nItem "<<(i+1)<<":"<<"\n"<<title_string<<" "<<term_string<<" "<<professor_string;
     }
   }
  
   
}

void classdesc(void)
{
    //initilazing variables
    char *cstr;
    int userterm; int userclassnum;
   
    std::string questterm = "What term would you like to search? ";
    std::cout<<questterm; 
    std::cin>>userterm;
    
    std::string questclass = "What is the class number? ";
    std::cout<<questclass;
    std::cin>>userclassnum;
    
    
    Py_Initialize();

    //PyRun_SimpleString("import sys");
    //PyRun_SimpleString("print(sys.path)");

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
    PyObject* classnum = PyLong_FromLong(userclassnum);
    PyObject* term = PyLong_FromLong(userterm);
    PyObject* pName = PyUnicode_FromString("get_class_description");
    
    //calling the get class description function
    PyObject* result = PyObject_CallMethodObjArgs(instance, pName, classnum,term,NULL);
    if (result== NULL){
       PyErr_Print();
    }
    assert(result != NULL);
    
    // convert the result to a string 
    PyArg_Parse(result, "s", &cstr);
    std::cout << "\nThe class description for class "<< userclassnum <<" and term "<< userterm <<" is "<< cstr<<"\n";

    //end python api
    Py_Finalize();
    
}