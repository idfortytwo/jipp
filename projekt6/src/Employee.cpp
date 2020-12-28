#include <string>

#include <Employee.hpp>

using namespace std;

Employee::Employee(string id, string name, string surname, string departmentId, string position) {
    this->id = id;
    this->name = name;
    this->surname = surname;
    this->departmentId = departmentId;
    this->position = position;
}

string Employee::getId() {
    return this->id;
}

string Employee::getName() {
    return this->name;
}

string Employee::getSurname() {
    return this->surname;
}

string Employee::getPosition() {
    return this->position;
}

string Employee::getDepartmentId() {
    return this->departmentId;
}

Employee::Employee() {};

