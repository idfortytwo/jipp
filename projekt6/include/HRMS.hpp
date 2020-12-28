#include <list>
#include <map>

#include <Employee.hpp>

using namespace std;

#ifndef HRMS_HPP
#define HRMS_HPP

class HRMS {
private:
    map<string, Employee> employees;
    map<string, list<string>> departmentEmployeeIdsMap;
    map<string, double> employeeSalaries;

    set<string> uniqueIds;

    bool employeeExists(string employeeId);
    void checkEmployeeIdUniqueness(string employeeId);
    void checkIfEmployeeExists(string employeeId);

public:
    HRMS();

    void add(Employee employee, double salary);
    void printDepartment(string departmentId);
    void changeSalary(string employeeId, double salary);
    void printSalaries();
    void printSalariesSorted();
};

#endif