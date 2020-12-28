#include <iostream>

#include <HRMS.hpp>
#include <Employee.hpp>

int main() {
    HRMS system;

    list<pair<Employee, double>> employees;
    employees.emplace_back(Employee("101", "Neena", "Kochhar", "90", "AD VP"), 17000);
    employees.emplace_back(Employee("102", "Lex", "De Haan", "90", "AD VP"), 17000);
    employees.emplace_back(Employee("104", "Bruce", "Ernst", "60", "IT PROG"), 6000);
    employees.emplace_back(Employee("105", "David", "Austin", "60", "IT PROG"), 4800);
    employees.emplace_back(Employee("106", "Valli", "Pataballa", "60", "IT PROG"), 4800);
    employees.emplace_back(Employee("107", "Diana", "Lorentz", "60", "IT PROG"), 4200);
    employees.emplace_back(Employee("109", "Daniel", "Faviet", "100", "FI ACCOUNT"), 9000);
    employees.emplace_back(Employee("110", "John", "Chen", "100", "FI ACCOUNT"), 8200);
    employees.emplace_back(Employee("111", "Ismael", "Sciarra", "100", "FI ACCOUNT"), 7700);
    employees.emplace_back(Employee("112", "Jose", "Urman", "100", "FI ACCOUNT"), 7800);
    employees.emplace_back(Employee("113", "Luis", "Popp", "100", "FI ACCOUNT"), 6900);
    employees.emplace_back(Employee("117", "Sigal", "Tobias", "30", "PU CLERK"), 3100);

    for (auto employeeSalary : employees)
        system.add(employeeSalary.first, employeeSalary.second);

    system.printDepartment("30");
    system.printDepartment("60");
    system.printDepartment("200");

    cout << "unsorted salaries:" << endl;
    system.printSalaries();

    cout << "Sigal gets 1000$ more..." << endl << endl;
    system.changeSalary("117", 4100);

    cout << "sorted salaries:" << endl;
    system.printSalariesSorted();


    cout << endl << "--- error testing ---" << endl << endl;

    cout << "Adding employee with already existing id..." << endl;
    try {
        Employee emp = Employee("101", "Neena2", "Kochhar2", "90", "AD VP");
        system.add(emp, 10000);
    } catch (invalid_argument &e) {
        cout << e.what() << endl;
    }

    cout << "adding employee with salary -5000..." << endl;
    try {
        system.add(Employee("test", "Negative", "Salary", "999", "TEST POS"), -5000);
    } catch (invalid_argument &e) {
        cout << e.what() << endl;
    }

    cout << "changing salary of non existant employee..." << endl;
    try {
        system.changeSalary("1000", 5000);
    } catch (invalid_argument &e) {
        cout << e.what() << endl;
    }

    return 0;
}
