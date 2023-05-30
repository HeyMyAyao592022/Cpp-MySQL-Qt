#include "student_dao.h"
#include <sstream>

StudentDAO::StudentDAO() : host("root"), password("520711YY"), database("experiment1")
{
    mysql_init(&mysql);
    if (!mysql_real_connect(&mysql, "localhost", host, password, database, 3306, nullptr, 0))
    {
        std::cout << "connect failed" << mysql_errno(&mysql) << std::endl;
    }
    else
        std::cout << "connect succeed" << std::endl;
}

StudentDAO::~StudentDAO()
{
    mysql_close(&mysql);
    printf("disconnect\n");
}

bool StudentDAO::loadStudents(std::vector<Student> &students)
{
    return queryStudents(students, "select * from student");
}

bool StudentDAO::loadStudentsBySex(std::vector<Student> &students, const char *sex)
{
    char query[] = "select * from student where Ssex = ";
    strcat(query, sex);
    return queryStudents(students, query);
}

int StudentDAO::insertStudent(const Student &val)
{
    std::stringstream builder;
    builder << "insert into student(Sname,SSex,Sage,Sdept) values('"
            << val.name << "','" << val.sex << "'," << val.age << ",'" << val.dept << "')";
    const string &str = builder.str();
    // std::cout << "sstr: " << str << '\n';
    const char *query = str.c_str();
    if (!exec(query))
        return 0;
    // return no
    const char query2[] = "select count(*) from student";
    return queryCount(query2) - 1;
}

bool StudentDAO::updateStudent(const Student &val)
{
    std::stringstream builder;
    builder << "update student set Sname = '" << val.name << "', Ssex = '" << val.sex << "', Sage = " << val.age
            << ", Sdept = '" << val.dept << "' where Sno = " << val.no;
    const string &str = builder.str();
    std::cout << "sstr: " << str << '\n';
    const char *query = str.c_str();
    return exec(query);
}

bool StudentDAO::deleteStudent(const Student &student)
{
    char query[] = "delete from student where Sno = ";
    strcat(query, std::to_string(student.no).c_str());
    return exec(query);
}

bool StudentDAO::queryStudents(std::vector<Student> &students, const char *query)
{
    if (exec(query))
    {
        res = mysql_store_result(&mysql);
        if (res == nullptr)
        {
            std::cout << "store failed: " << mysql_errno(&mysql) << std::endl;
            return false;
        }
        else
            while (row = mysql_fetch_row(res))
                students.emplace_back(Student(row));
    }
    mysql_free_result(res);
    return true;
}

int StudentDAO::queryCount(const char *query_sql)
{
    if (exec(query_sql))
    {
        res = mysql_store_result(&mysql);
        if (res == nullptr)
        {
            std::cout << "query failed: " << mysql_errno(&mysql) << '\n'
                      << "sql: " << query_sql << std::endl;
            return false;
        }
        else
            row = mysql_fetch_row(res);
    }
    mysql_free_result(res);
    return (int)(*row[0]);
}

bool StudentDAO::exec(const char *query)
{
    if (mysql_real_query(&(this->mysql), query, (unsigned int)strlen(query)))
    {
        std::cout << "exec failed: " << mysql_errno(&mysql) << '\n'
                  << "sql: " << query << std::endl;
        return false;
    }
    return true;
}
