#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>

#include <HRMS.hpp>

using namespace std;


bool HRMS::employeeExists(string employeeId) {
    return this->uniqueIds.find(employeeId) != this->uniqueIds.end();
}

void HRMS::checkEmployeeIdUniqueness(string employeeId) {
    if (employeeExists(employeeId)) {
        string errorStr = "User with id ";
        errorStr += employeeId;
        errorStr += " already exists\n";
        throw invalid_argument(errorStr);
    }
}

void HRMS::checkIfEmployeeExists(string employeeId) {
    if (!employeeExists(employeeId)) {
        string errorStr = "User with id ";
        errorStr += employeeId;
        errorStr += " does not exist\n";
        throw invalid_argument(errorStr);
    }
}

void HRMS::add(Employee employee, double salary) {
    if (salary <= 0) {
        string errorStr = "Salary for employee with id ";
        errorStr += employee.getId();
        errorStr += " should be greater than 0\n";
        throw invalid_argument(errorStr);
    }

    string employeeId = employee.getId();
    string departmentId = employee.getDepartmentId();

    checkEmployeeIdUniqueness(employeeId);
    uniqueIds.insert(employeeId);

    this->employees[employeeId] = employee;
    this->employeeSalaries[employeeId] = salary;
    this->departmentEmployeeIdsMap[departmentId].push_back(employeeId);
}

void HRMS::printDepartment(string departmentId) {
    cout << "Department id " << departmentId << " employees:" << endl;

    list<string> employeeIds = this->departmentEmployeeIdsMap[departmentId];
    if (employeeIds.empty()) {
        cout << "Department is empty" << endl;
    } else {
        for (auto employeeId : employeeIds) {
            Employee employee = this->employees[employeeId];
            cout << employee.getName() << " " << employee.getSurname() << " - " << employee.getPosition() << endl;
        }
    }
    cout << endl;
}

void HRMS::changeSalary(string employeeId, double salary) {
    checkIfEmployeeExists(employeeId);
    this->employeeSalaries[employeeId] = salary;
}

void HRMS::printSalaries() {
    for (auto employeeSalary : this->employeeSalaries) {
        string employeeId = employeeSalary.first;
        double salary = employeeSalary.second;

        Employee employee = this->employees[employeeId];

        cout << employee.getId() << " " << employee.getName() << " " << employee.getSurname()
             << " (" << employee.getPosition() << "): " << salary << endl;
    }
    cout << endl;
}

void HRMS::printSalariesSorted() {
    vector<pair<string, double>> sortedSalaries;

    for (auto employeeSalary : this->employeeSalaries) {
        sortedSalaries.push_back(employeeSalary);
    }

    sort(sortedSalaries.begin(), sortedSalaries.end(),
         [](pair<string, double> &a, pair<string, double>&b) -> bool {return a.second < b.second;}
    );

    for (auto employeeSalary : sortedSalaries) {
        string employeeId = employeeSalary.first;
        double salary = employeeSalary.second;

        Employee employee = this->employees[employeeId];

        cout << employee.getId() << " " << employee.getName() << " " << employee.getSurname()
             << " (" << employee.getPosition() << "): " << salary << endl;
    }
    cout << endl;
}

HRMS::HRMS() {};