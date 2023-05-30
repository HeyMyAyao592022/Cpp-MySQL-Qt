#include "student_entity.h"

std::ostream &operator<<(std::ostream &os, const Student &val)
{
    os << "no:" << val.no << '\t'
       << "name:" << val.name << '\t'
       << "sex:" << val.sex << '\t'
       << "age:" << val.age << '\t'
       << "department:" << val.dept << '\n';
    return os;
}