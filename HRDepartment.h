#pragma once
#include <string>
#include <vector>

#include "Person.h"
#include "Employee.h"
#include "Department.h"
#include "Position.h"
#include "PreviousWorkplace.h"

/**
 * @brief Класс HRDepartment — хранилище людей/сотрудников и отчёты
 */
class HRDepartment
{
private:
    std::vector<Person> people;             // Люди
    std::vector<Employee> employees;        // Сотрудники
    std::vector<Department> departments;    // Отделы
    std::vector<Position> positions;        // Должности

    /**
     * @brief Проверить наличие человека с данным ID
     * @param id - ID человека
     * @return true, если человек с таким ID уже есть
     */
    bool containsId(const int id) const;

public:
    HRDepartment() = default;
    ~HRDepartment() = default;

    void addPerson(const Person& person);
    void addPerson(const Employee& employee);
    void addEmployee(const Employee& employee);
    void addDepartment(const Department& department);
    void addPosition(const Position& position);

    const std::vector<Person>& getPeople() const noexcept;
    const std::vector<Employee>& getEmployees() const noexcept;
    const std::vector<Department>& getDepartments() const noexcept;
    const std::vector<Position>& getPositions() const noexcept;

    std::vector<std::string> getAllInfo() const;
    std::vector<std::string> getByPosition(const std::string& positionTitle) const;
    std::vector<std::string> getByRate(const double rate) const;
    std::vector<std::string> getWithChildren() const;
    std::vector<std::string> getPensioners() const;
    std::vector<std::string> getDisabled() const;
    std::vector<std::string> getOnVacation() const;
    std::vector<std::string> getOnMaternityLeave() const;
    std::vector<std::string> getPositionInfo() const;
    std::vector<std::string> getPreviousWorkplacesInfo() const;
    std::vector<std::string> getByFullName(const std::string& fullName) const;
    std::vector<std::string> getChildrenOf(const int parentId) const;
};