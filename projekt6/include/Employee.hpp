#include <string>
#include <set>

using namespace std;

#ifndef EMPLOYEE_HPP
#define EMPLOYEE_HPP

class Employee {
private:
    string id, name, surname, departmentId, position;

public:
    Employee(string id, string name, string surname, string departmentId, string position);
    Employee();

    string getId();
    string getName();
    string getSurname();
    string getDepartmentId();
    string getPosition();
};

#endif
