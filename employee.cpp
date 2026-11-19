#include "Employee.h"
#include <sstream>
#include <iomanip>

Employee::Employee() : Person(), rate(1.0), pensioner(false), disabled(false), onVacation(false), onMaternityLeave(false) {}

Employee::Employee(const std::string& fullName, const std::string& birthDate, const Position& position, const Department& department, const double rate, const int id)
	: Person(fullName, birthDate, id), position(position), department(department), rate(rate), pensioner(false), disabled(false), onVacation(false), onMaternityLeave(false) {}

const Position& Employee::getPosition() const noexcept {return position;}

const Department& Employee::getDepartment() const noexcept {return department;}

double Employee::getRate() const noexcept {return rate;}

const std::vector<PreviousWorkplace>& Employee::getPreviousWorkplaces() const noexcept
{
	return previousWorkplace;
}

const std::vector<int>& Employee::getChildrenIds() const noexcept
{
	return childrenIds;
}

void Employee::addPreviousWorkplace(const PreviousWorkplace& wp)
{
	previousWorkplace.push_back(wp);
}

void Employee::addChildId(const int childId)
{
	childrenIds.push_back(childId);
}

void Employee::setFlags(const bool pensioner, const bool disabled, const bool onVacation, const bool onMaternityLeave)
{
	this -> pensioner = pensioner;
	this -> disabled = disabled;
	this -> onVacation = onVacation;
	this -> onMaternityLeave = onMaternityLeave;
}

bool Employee::hasChildren() const noexcept {return !childrenIds.empty();}
bool Employee::isPensioner() const noexcept {return pensioner;}
bool Employee::isDisabled() const noexcept {return disabled;}
bool Employee::isOnVacation() const noexcept {return onVacation;}
bool Employee::isOnMaternityLeave() const noexcept {return onMaternityLeave;}

namespace
{
	std::string formatRate(const double rate)
	{
		std::ostringstream oss;
		oss << std::fixed << std::setprecision(1) << rate;
		return oss.str();
	}
}

std::string Employee::getInfo() const
{
	std::string result = Person::getInfo();
	result += " | Должность: " + position.getTitle();
	result += " | Отдел: " + department.getName();
	result += " | Ставка: " + formatRate(rate);
	result += " | Дети: ";
	result += hasChildren() ? std::to_string(childrenIds.size()) : "Нет";
	if (pensioner) result += " | Пенсионер";
	if (disabled) result += " | Инвалид";
	if (onVacation) result += " | В отпуске";
	if (onMaternityLeave) result += " | В декретном отпуске";
	return result;
}
