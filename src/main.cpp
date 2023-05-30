#include "student_entity.h"
#include "student_dao.h"
#include <iostream>
#include <vector>

using uint = unsigned int;

int main(int, char **)
{
    StudentDAO dao;
    std::vector<Student> students;
    dao.loadStudents(students);
    for (auto s : students)
    {
        std::cout << s;
    }

    auto &temp = students.back();

    // update
    // temp.name = "gogegogegoge";
    // dao.updateStudent(temp);

    // delete
    // dao.deleteStudent(temp);

    // auto newStudent = temp;
    // newStudent.name = "big world";
    // dao.insertStudent(newStudent);

    return 0;
}

void test()
{
    const char *host = "root";
    const char *password = "520711YY";
    const char *database = "experiment1";

    MYSQL mysql;

    mysql_init(&mysql);

    printf("start connecting ...\n");
    if (!mysql_real_connect(&mysql, "localhost", host, password, database, 3306, nullptr, 0))
    {
        std::cout << "connect failed" << mysql_errno(&mysql) << std::endl;
    }
    printf("connect succeed\n");

    MYSQL_RES *res = nullptr;
    MYSQL_ROW row;

    const char *sql_buf = "select * from student";

    printf("select * from student\n");

    if (mysql_real_query(&mysql, sql_buf, (uint)strlen(sql_buf)))
    {
        std::cout << "query failed: " << mysql_errno(&mysql) << std::endl;
    }
    else
    {
        std::cout << "query done\n";
        res = mysql_store_result(&mysql);

        if (res == nullptr)
            std::cout << "store failed: " << mysql_errno(&mysql) << std::endl;
        else
        {
            while (row = mysql_fetch_row(res))
            {
                std::cout << row[0] << " " << row[1] << std::endl;
            }
        }
    }

    mysql_free_result(res);

    mysql_close(&mysql);
}
