#ifndef __STUDENT_DAO_H__
#define __STUDENT_DAO_H__

#include "mysql.h"
#include "student_entity.h"

#include <iostream>
#include <vector>
#include <memory>
#include <mutex>

class StudentDAO
{
private:
    char host[20];
    char password[50];
    char database[20];

    MYSQL mysql;    // handle
    MYSQL_RES *res; // res
    MYSQL_ROW row;  // row

    static std::shared_ptr<StudentDAO> instance;
    static std::mutex mtx;

public:
    StudentDAO();
    ~StudentDAO();

    static std::shared_ptr<StudentDAO> getInstance();

    bool iniDAO();
    void disConnect();

    bool loadStudents(std::vector<Student> &students);
    bool loadStudentsBySex(std::vector<Student> &students, const char *sex);

    int insertStudent(const Student &student);

    bool updateStudent(const Student &student);

    bool deleteStudent(const Student &student);

private:
    bool queryStudents(std::vector<Student> &students, const char *query_sql);
    int queryCount(const char *query_sql);
    bool exec(const char *query);
};

#endif // __STUDENT_DAO_H__