//This program is made
#include <python3.4m/Python.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>

void showCourseDescript(int classEntry, int termEntry);
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
        Course getCourse(int indexOfCourse){
            return available_courses.at(indexOfCourse);
        }
        bool isEmpty(void){
            bool result;
            number_of_courses == 0 ? result = true : result = false;
            return result;
        };
};

int main(void)
{
    std::cout<<"~~~~~~Welcome to Class Scheduler Assitant!~~~~~\n";
    listclasses();
    return 0;
}

void listclasses(void){
    //asking what classes would you like to see
    int class_select; char *s_subject; int userterm;
    
    std::string questsub = "What subject would you like to search:\n1. CS Courses\n2. ECE Courses\n3. COE Courses\n4. Enter My Own Subject\nAnswer: ";
    std::cout<<questsub; std::cin>>class_select;
    
    switch (class_select){
        case 1: s_subject = "CS"; 
        break;
        
        case 2: s_subject = "ECE";
        break;
        
        case 3: s_subject = "COE";
        break;
        
        case 4:
        std::cout<<"\nSubject Code: ";
        s_subject = new char [10];
        std::cin>>s_subject;
        break;
    }
    
    //asking which term
    std::string questterm = "\nWhat term would you like to search:\n1. Fall 2016\n2. Spring 2017\n3. Summer 2017\nAnswer: ";
    std::cout<<questterm; std::cin>>userterm;
    
    switch (userterm){
        case 1: userterm = 2171; 
        break;
        
        case 2: userterm = 2174;
        break;
        
        case 3: userterm = 2177;
        break;
    }
   
    Py_Initialize();

    //PyRun_SimpleString("import sys");
    //PyRun_SimpleString("print(sys.path)");

    //loading pittAPI
    PyObject* module = PyImport_ImportModule("pittAPI");
     if (module == NULL){
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
    PyObject* pName2 = PyUnicode_FromString("get_course_numbers");
    PyObject* pName3 = PyUnicode_FromString("get_class_time");
    PyObject* pName4 = PyUnicode_FromString("get_class_instructor");
    
    
    //calling the get course dictionary function
    PyObject* courselist = PyObject_CallMethodObjArgs(instance, pName, instance,term, class_sub,NULL);
    if (courselist== NULL){
       PyErr_Print();
    }
    assert(courselist != NULL);
   
    //getting dictionary of files
    BigCourseList course_list;
    for(int i = 0; i < PyList_Size(courselist); i++){
      
      //initilazing temp variables
      char *term_string;
      char *title_string;
      
      //getting temp item
      PyObject* tempitem = PyList_GetItem(courselist,i);
     
      //setting attributes from temp item    
      PyObject* classes_to_ignore = PyDict_GetItemString(tempitem,"catalog_number");
      PyObject* class_title = PyDict_GetItemString(tempitem,"title");
      PyArg_Parse(classes_to_ignore, "s", &term_string);
      PyArg_Parse(class_title, "s", &title_string);
      
      //adding to courselist
      if(atoi(term_string) < 1900){
        Course tempCourse(title_string,term_string);
        course_list.addCourse(tempCourse);
      }
    }
   
    //showing courses    
    std::cout<<"\nNumber of courses: "<<course_list.getNumberOfCourses()<<"\n";
    std::cout<<"\nWhat course would you like to get information for: \n";
    course_list.printCourses();
    std::cout<<"\nAnswer: ";
    int userchoice; std::cin>>userchoice; std::cout<<"\n";
    
    //getting course that user wants to see
    Course userCourse = course_list.getCourse((userchoice-1));
    std::cout<<"You picked "<<userCourse.getTitle()<<"\n";
    
    //calling get course numbers
    PyObject* class_tit = PyUnicode_FromString(userCourse.getTitle().c_str());
    PyObject* course_class_numbers = PyObject_CallMethodObjArgs(instance, pName2, class_sub, term, class_tit,NULL);
    if (course_class_numbers== NULL){
       PyErr_Print();
    }
    assert(course_class_numbers != NULL);
    
    //getting class numbers
    std::vector<int> classNumbers;
    
    for(int i = 0;i < PyList_Size(course_class_numbers); i++){
        char *temp;
        PyObject* tempitem = PyList_GetItem(course_class_numbers,i);
        PyArg_Parse(tempitem, "s", &temp);
        classNumbers.push_back(atoi(temp));
    }
    
    //calling get class time
    std::vector<std::string> classTimes;
    std::vector<std::string> classInstructors;
    
    for(int i = 0; i < classNumbers.size(); i++){
        std::string s = std::to_string(classNumbers[i]);
        
        char *temp; 
        PyObject* class_num = PyUnicode_FromString(s.c_str());
        
        PyObject* class_time = PyObject_CallMethodObjArgs(instance, pName3, class_num, term,NULL);
        if (class_time== NULL){
            PyErr_Print();
        }
        assert(class_time != NULL);
        
        PyArg_Parse(class_time, "s", &temp);
        classTimes.push_back(temp);
    }
    
    for(int i = 0; i < classNumbers.size(); i++){
        std::string s = std::to_string(classNumbers[i]);
        char *temp2;
        PyObject* class_num = PyUnicode_FromString(s.c_str());
        
        PyObject* class_instruct = PyObject_CallMethodObjArgs(instance, pName4, class_num, term,NULL);
        if (class_instruct== NULL){
            PyErr_Print();
        }
        assert(class_instruct != NULL);
        
        PyArg_Parse(class_instruct, "s", &temp2);

        classInstructors.push_back(temp2);
    }
    
    Py_Finalize();
    
    std::cout<<"\nClass details for "<<userCourse.getTitle()<<":";
     
    for(int i = 0;i < classNumbers.size(); i++){
         std::cout<<"\n"<<classNumbers[i]<<": "<<classTimes[i]<<" / "<<classInstructors[i];
    }
    std::cout<<"\n";
    
}


void showCourseDescript(int classEntry, int termEntry){
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
    std::cout << "\nThe course description for class "<< userclassnum <<" and term "<< userterm <<" is "<< cstr<<"\n";

    //end python api
    Py_Finalize();
}

// void userMenu(){
//     int userAns;
//     std::cout<<"\nWhat would you like to do: \n1. See Course Description\n2. View Class Times and Instructor\n3. Pick another subject\n4. Pick another term\n5. Pick another course\nAnswer: ";
//     std::cin>>userAns;
// }


