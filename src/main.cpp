#include "mysql.h"
#include <iostream>

const char *host = "root";
const char *password = "520711YY";
const char *database = "experiment1";

int main(int, char **)
{
    printf("program starts\n");

    MYSQL mysql;

    mysql_init(&mysql);

    printf("start connecting ...\n");

    if (!mysql_real_connect(&mysql, "localhost", host, password, database, 3306, nullptr, 0))
    {
        std::cout << "connect failed" << mysql_errno(&mysql) << std::endl;
        return -1;
    }

    return 0;
}
