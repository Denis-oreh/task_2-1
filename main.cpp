#include <iostream>
#include <vector>
#include <string>
#include <memory>

#include "HRDepartment.h"

#ifdef _WIN32
#include <windows.h>
#endif

/**
 * @brief Печать набора строк с заголовком
 */
static void printLines(const std::vector<std::string>& lines, const std::string& title)
{
    std::cout << "\n      <" << title << ">\n";
    std::cout << "\n";
    if (lines.empty())
    {
        std::cout << "(пусто)\n";
        return;
    }
    for (const auto& line : lines)
    {
        std::cout << line << "\n";
    }
    std::cout << "\n";
    std::cout << "\n";
}

/**
 * @brief Точка входа в программу
 * @return 0, если программа выполнена корректно
 */
int main()
{
#ifdef _WIN32
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
#endif

    HRDepartment hr;

    hr.addDepartment(Department("IT"));
    hr.addDepartment(Department("Бухгалтерия"));
    hr.addDepartment(Department("HR"));

    hr.addPosition(Position("Программист"));
    hr.addPosition(Position("Бухгалтер"));
    hr.addPosition(Position("HR-менеджер"));

    Employee e1("Иванов Иван Иванович", "12.03.1985",
        Position("Программист"), Department("IT"), 1.0);
    const int e1Id = e1.getId();
    e1.setFlags(false, true, false, true);
    e1.addPreviousWorkplace(PreviousWorkplace("ООО Ромашка", "Junior", "2010-2013"));
    e1.addPreviousWorkplace(PreviousWorkplace("ЗАО Лютик", "Middle", "2013-2020"));

    Person child("Иванов Пётр Иванович", "29.10.2007");
    const int childId = child.getId();
    e1.addChildId(childId);
    hr.addPerson(child);
    hr.addEmployee(e1);

    Employee e2("Петрова Анна Петровна", "10.12.1960",
        Position("Бухгалтер"), Department("Бухгалтерия"), 0.5);
    e2.setFlags(true, false, true, false);
    hr.addEmployee(e2);

    Employee e3("Сидорова Мария Петровна", "21.11.1986",
        Position("Программист"), Department("IT"), 1.0);
    e3.addChildId(childId);
    e3.setFlags(false, false, false, true);
    hr.addEmployee(e3);

    std::vector<std::unique_ptr<Person>> staff;
    staff.push_back(std::make_unique<Person>(
        "Смирнов Олег Игоревич", "05.05.1990"));
    staff.push_back(std::make_unique<Employee>(
        "Кузнецов Артём Сергеевич", "17.08.1982",
        Position("Программист"), Department("IT"), 1.0));
    staff.push_back(std::make_unique<Employee>(
        "Волкова Елена Ивановна", "02.02.1975",
        Position("Бухгалтер"), Department("Бухгалтерия"), 0.5));

    std::cout << "\n     <=Полиморфная коллекция базового типа (Person)=>\n";
    std::cout << "\n";
    for (const auto& person : staff)
    {
        std::cout << person->getInfo() << "\n";
    }
    std::cout << "\n";

    printLines(hr.getAllInfo(), "Все люди");
    printLines(hr.getByPosition("Программист"), "Сотрудники-программисты");
    printLines(hr.getByRate(0.5), "Сотрудники со ставкой 0.5");
    printLines(hr.getWithChildren(), "Сотрудники с детьми");
    printLines(hr.getPensioners(), "Пенсионеры");
    printLines(hr.getDisabled(), "Сотрудники с инвалидностью");
    printLines(hr.getOnVacation(), "В отпуске");
    printLines(hr.getOnMaternityLeave(), "В декретном отпуске");
    printLines(hr.getPositionInfo(), "Информация о должностях");
    printLines(hr.getPreviousWorkplacesInfo(), "Предыдущие места работы");
    printLines(hr.getByFullName("Петрова Анна Петровна"), "Поиск по ФИО: Петрова Анна Петровна");
    printLines(hr.getChildrenOf(e1Id), "Дети сотрудника Иванов Иван Иванович");

    return 0;
}