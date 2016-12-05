//This program is made
#include <python3.4m/Python.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>

void showClassDescript(int classEntry, int termEntry);
void listclasses(void);

class Course{
    private:
        char *name;
        char *course_number;
        //int number_of_credits;
        //char *professor;
        
    public:
        Course(char *title, char *course_num){
            name = title;;
            course_number = course_num;
           // number_of_credits = credit;
        };
        std::string getCourseNumber(){
            std::string newString(course_number);
            return newString;
            
        };
        //int getNumberOfCredits(){return number_of_credits;};
        std::string getTitle(){
            std::string newString(name);
            return newString;
            
        };
};

class BigCourseList{
    private:
        std::vector<Course> available_courses;
        int number_of_courses;
    public:
        BigCourseList(){
            number_of_courses = 0;
        };
        void addCourse(Course newCourse){
            if(this -> contains(newCourse)==false){
                available_courses.push_back(newCourse);
                number_of_courses++;
            }
        };
        bool removeCourse(Course entry){
            bool result = false;
            if(contains(entry) == true){
                for(int i=0;i<number_of_courses;i++){
                    if(available_courses[i].getCourseNumber() == entry.getCourseNumber()){
                        int decrease =number_of_courses-1;
                        available_courses[i] = available_courses[decrease];
                        number_of_courses--;
                        result=true;                        
                    }
                }
            }
            return result;
        };
        int getNumberOfCourses(void){return number_of_courses;};
        bool contains(Course entry){
            bool contained=false;;
            for(int i = 0; i<number_of_courses;i++){
                    if(available_courses.at(i).getCourseNumber() == entry.getCourseNumber()){contained = true;}
            }
            return contained;
        };
        void printCourses(){
            for(int i =0;i<number_of_courses;i++){
                 std::cout<<"\n"<<(i+1)<<": "<< available_courses.at(i).getTitle()<<" "<<available_courses.at(i).getCourseNumber();
            }
        };
        bool isEmpty(void){
            bool result;
            number_of_courses == 0 ? result = true : result = false;
            return result;
        };
};

int main(void)
{
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
   BigCourseList course_list;
   
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
        Course tempCourse(title_string,term_string);
        course_list.addCourse(tempCourse);
     }
   }
    //end python api
    Py_Finalize();

    //showing courses    
    //std::cout<<"\nNumber of courses: "<<course_list.getNumberOfCourses()<<"\n";
    std::cout<<"\nWhat class would you like to get information for: \n";
    course_list.printCourses();
    int userchoice;
    std::cout<<"\nAnswer: ";
    std::cin>>userchoice;
}

// void chooseCourse(int userChoice){
//     std::string questsub = "What class would you like to see information for:\n1. CS Courses\n2. ECE Courses\n3. COE Courses\nAnswer: ";
//     std::cout<<questsub; 
//     std::cin>>class_select;
    
//     switch (class_select){
//         case 1: s_subject = "CS"; 
//         break;
        
//         case 2: s_subject = "ECE";
//         break;
        
//         case 3: s_subject = "COE";
//         break;
//     }
// }


void showClassDescript(int classEntry, int termEntry)
{
    //initilazing variables
    char *cstr;
    int userterm = termEntry; 
    int userclassnum = classEntry;
   
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