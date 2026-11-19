#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include "HRDepartment.h"

#ifdef _WIN32
#include <windows.h>
#endif

/**
 * @brief Функция для вывода вектора строк в консоль
 */
void printInfo(const std::vector<std::string>& info)
{
    if (info.empty())
	{
        std::cout << "(пусто)" << std::endl;
        return;
    }
    for (const auto& line : info)
	{
        std::cout << line << std::endl;
    }
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

	Employee e1("Иванов Иван Иванович", "12.03.1985",  Position("Программист"), Department("IT"), 1.0);
	int e1Id = e1.getId();
	e1.setFlags(false, true, false, true);
	e1.addPreviousWorkplace(PreviousWorkplace("ООО Ромашка", "Junior", "2010-2013"));
	e1.addPreviousWorkplace(PreviousWorkplace("ЗАО лютик", "Middle", "2013-2020"));
	
	Employee child("Иванов Пётр Иванович", "29.10.2007", Position("Нет"), Department("Нет"), 0.0);
	int childId = child.getId();
	e1.addChildId(childId);
	
	hr.addPerson(static_cast<const Person&>(child));
	hr.addEmployee(e1);

	Employee e2("Петрова Анна Петровна", "10.12.1960", Position("Бухгалтер"), Department("Бухгалтерия"), 0.5);
	e2.setFlags(true, false, true, false);
	hr.addEmployee(e2);

	Employee e3("Сидорова Мария Петровна", "21.11.1986", Position("Программист"), Department("IT"), 1.0);
	e3.addChildId(childId);
	e3.setFlags(false, false, false, true);
	hr.addEmployee(e3);

	std::cout << "Все люди:" << std::endl;
	printInfo(hr.getAllInfo());

	std::cout << "\nСотрудники-программисты:" << std::endl;
	printInfo(hr.getByPosition("Программист"));

	std::cout << "\nСотрудники со ставкой 0.5:" << std::endl;
	printInfo(hr.getByRate(0.5));

	std::cout << "\nСотрудники с детьми:" << std::endl;
	printInfo(hr.getWithChildren());

	std::cout << "\nПенсионеры:" << std::endl;
	printInfo(hr.getPensioners());

	std::cout << "\nСотрудники с инвалидностью:" << std::endl;
	printInfo(hr.getDisabled());

	std::cout << "\nВ отпуске:" << std::endl;
	printInfo(hr.getOnVacation());

	std::cout << "\nВ декретном отпуске:" << std::endl;
	printInfo(hr.getOnMaternityLeave());

	std::cout << "\nИнформация о должностях:" << std::endl;
	printInfo(hr.getPositionInfo());

	std::cout << "\nПредыдущие места работы:" << std::endl;
	printInfo(hr.getPreviousWorkplacesInfo());

	std::cout << "\nПоиск по имени: Петрова Анна Петровна" << std::endl;
	printInfo(hr.getByFullName("Петрова Анна Петровна"));

	std::cout << "\nДети сотрудника:" << std::endl;
	printInfo(hr.getChildrenOf(e1Id));

	return 0;
}
