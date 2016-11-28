This program is to help me
-will keep track of career goals (ee degree and cs minor requirements)
-will know what classes you took and if they complete the requirements
-will keep track of the different electives available and when they are scheduled ie fall, spring, summer
-will keep track of course description
-will tell you what else you need to complete for degree
-will calculate gpa

started 10/31/16

to run
type this into bash:
g++ -I/usr/include/python3.4m schedule_planner/source.cpp -Wno-write-strings -lpython3.4m && ./a.out 

https://help.github.com/articles/adding-an-existing-project-to-github-using-the-command-line/

### Courses
course = CourseAPI()

# Will return a list of dictionaries containing courses in subject
big_dict = course.get_courses(term="2161", subject="CS")

# Will return a list of dictionaries containing courses that fulfill req
big_dict = course.get_courses_by_req(term="2161", req="Q")

# Will return a string, which is the description of the course
description = course.get_class_description(class_number="10163", term="2161")

Ternary operators
condition ? value_if_true : value_if_false;

variable = condition ? value_if_true : value_if_false;

(condition ? variable1 : variable2) = value;  
	if the boolean expression condition yields the value true, the value is assigned to the variable1, otherwise, it is assigned to variable2.