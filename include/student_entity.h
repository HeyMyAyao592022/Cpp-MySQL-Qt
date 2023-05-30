#ifndef __STUDENT_ENTITY_H__
#define __STUDENT_ENTITY_H__

#include <iostream>

using std::string;

struct Student
{
    unsigned int no;
    string name;
    string sex;
    unsigned int age;
    string dept;

    Student() {}
    Student(char **row) : name(row[1]), sex(row[2]), dept(row[4])
    {
        // std::cout << "loading: " << row[0] << std::endl;
        no = (unsigned int)(*row[0]);
        no = atol(row[0]);
        age = atol(row[3]);
    }
    friend std::ostream &operator<<(std::ostream &os, const Student &val);
};

#endif // __STUDENT_ENTITY_H__