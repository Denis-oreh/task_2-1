#include "HRDepartment.h"

#include <algorithm>
#include <map>
#include <string>
#include <vector>

bool HRDepartment::containsId(const int id) const
{
    const bool inEmployees = std::any_of(employees.begin(), employees.end(),
        [id](const Employee& e) { return e.getId() == id; });
    if (inEmployees) return true;

    return std::any_of(people.begin(), people.end(),
        [id](const Person& p) { return p.getId() == id; });
}

void HRDepartment::addPerson(const Person& person)
{
    if (containsId(person.getId())) return;
    people.push_back(person);
}

void HRDepartment::addPerson(const Employee& employee)
{
    addEmployee(employee);
}

void HRDepartment::addEmployee(const Employee& employee)
{
    if (containsId(employee.getId())) return;
    employees.push_back(employee);
}

void HRDepartment::addDepartment(const Department& department)
{
    const auto it = std::find_if(departments.begin(), departments.end(),
        [&department](const Department& d) { return d.getName() == department.getName(); });
    if (it != departments.end()) return;
    departments.push_back(department);
}

void HRDepartment::addPosition(const Position& position)
{
    const auto it = std::find_if(positions.begin(), positions.end(),
        [&position](const Position& p) { return p.getTitle() == position.getTitle(); });
    if (it != positions.end()) return;
    positions.push_back(position);
}

const std::vector<Person>& HRDepartment::getPeople() const noexcept { return people; }
const std::vector<Employee>& HRDepartment::getEmployees() const noexcept { return employees; }
const std::vector<Department>& HRDepartment::getDepartments() const noexcept { return departments; }
const std::vector<Position>& HRDepartment::getPositions() const noexcept { return positions; }

std::vector<std::string> HRDepartment::getAllInfo() const
{
    std::vector<std::string> result;
    result.reserve(people.size() + employees.size());
    for (const Person& p : people)        result.push_back(p.getInfo());
    for (const Employee& emp : employees) result.push_back(emp.getInfo());
    return result;
}

std::vector<std::string> HRDepartment::getByPosition(const std::string& positionTitle) const {
    std::vector<std::string> result;
    for (const Employee& emp : employees)
    {
        if (emp.getPosition().getTitle() == positionTitle)
        {
            result.push_back(emp.getInfo());
        }
    }
    return result;
}

std::vector<std::string> HRDepartment::getByRate(const double rate) const
{
    std::vector<std::string> result;
    for (const Employee& emp : employees)
    {
        if (emp.getRate() == rate) result.push_back(emp.getInfo());
    }
    return result;
}

std::vector<std::string> HRDepartment::getWithChildren() const
{
    std::vector<std::string> result;
    for (const Employee& emp : employees)
    {
        if (emp.hasChildren()) result.push_back(emp.getInfo());
    }
    return result;
}

std::vector<std::string> HRDepartment::getPensioners() const
{
    std::vector<std::string> result;
    for (const Employee& emp : employees)
    {
        if (emp.isPensioner()) result.push_back(emp.getInfo());
    }
    return result;
}

std::vector<std::string> HRDepartment::getDisabled() const
{
    std::vector<std::string> result;
    for (const Employee& emp : employees)
    {
        if (emp.isDisabled()) result.push_back(emp.getInfo());
    }
    return result;
}

std::vector<std::string> HRDepartment::getOnVacation() const
{
    std::vector<std::string> result;
    for (const Employee& emp : employees)
    {
        if (emp.isOnVacation()) result.push_back(emp.getInfo());
    }
    return result;
}

std::vector<std::string> HRDepartment::getOnMaternityLeave() const
{
    std::vector<std::string> result;
    for (const Employee& emp : employees)
    {
        if (emp.isOnMaternityLeave()) result.push_back(emp.getInfo());
    }
    return result;
}

std::vector<std::string> HRDepartment::getPositionInfo() const
{
    std::map<std::string, int> counter;
    for (const Employee& emp : employees)
    {
        counter[emp.getPosition().getTitle()]++;
    }
    std::vector<std::string> result;
    result.reserve(counter.size());
    for (const auto& [title, count] : counter)
    {
        result.push_back(title + ": " + std::to_string(count));
    }
    return result;
}

std::vector<std::string> HRDepartment::getPreviousWorkplacesInfo() const
{
    std::vector<std::string> result;
    for (const Employee& emp : employees)
    {
        result.push_back(emp.getFullName() + ":");
        for (const PreviousWorkplace& wp : emp.getPreviousWorkplaces())
        {
            result.push_back("  " + wp.toString());
        }
    }
    return result;
}

std::vector<std::string> HRDepartment::getByFullName(const std::string& fullName) const
{
    std::vector<std::string> result;

    const auto itEmp = std::find_if(employees.begin(), employees.end(),
        [&fullName](const Employee& e) { return e.getFullName() == fullName; });
    if (itEmp != employees.end())
    {
        result.push_back(itEmp->getInfo());
        return result;
    }

    const auto itPer = std::find_if(people.begin(), people.end(),
        [&fullName](const Person& p) { return p.getFullName() == fullName; });
    if (itPer != people.end())
    {
        result.push_back(itPer->getInfo());
        return result;
    }

    result.push_back("Сотрудник не найден");
    return result;
}

std::vector<std::string> HRDepartment::getChildrenOf(const int parentId) const
{
    std::vector<std::string> result;

    const auto parentIt = std::find_if(employees.begin(), employees.end(),
        [parentId](const Employee& e) { return e.getId() == parentId; });
    if (parentIt == employees.end())
    {
        const auto personIt = std::find_if(people.begin(), people.end(),
            [parentId](const Person& p) { return p.getId() == parentId; });
        result.push_back(personIt != people.end() ? "Это не сотрудник" : "Родитель не найден");
        return result;
    }

    result.push_back("Дети: " + parentIt->getFullName());
    for (const int childId : parentIt->getChildrenIds())
    {
        const auto childIt = std::find_if(people.begin(), people.end(),
            [childId](const Person& p) { return p.getId() == childId; });
        if (childIt != people.end())
        {
            result.push_back(childIt->getInfo());
            continue;
        }
        const auto childEmpIt = std::find_if(employees.begin(), employees.end(),
            [childId](const Employee& e)
            { return e.getId() == childId; });
        if (childEmpIt != employees.end())
        {
            result.push_back(childEmpIt->getInfo());
        }
    }
    return result;
}