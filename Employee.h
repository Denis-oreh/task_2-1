#pragma once
#include "Person.h"
#include "Position.h"
#include "Department.h"
#include "PreviousWorkplace.h"
#include <vector>

/**
 * @brief Класс Employee - наследник класса Person
 */
class Employee : public Person
{
	private:
		/**
		 * @brief Должность
		 */
		Position position;

		/**
		 * @brief Департамент
		 */
		Department department;

		/**
		 * @brief Ставка
		 */
		double rate;

		/**
		 * @brief Предыдущее место работы
		 */
		std::vector<PreviousWorkplace> previousWorkplace;

		/**
		 * @brief ID детей
		 */
		std::vector<int> childrenIds;

		/**
		 * @brief Флаг "Пенсионер"
		 */
		bool pensioner;

		/**
		 * @brief Флаг "Инвалид"
		 */
		bool disabled;

		/**
		 * @brief Флаг "В отпуске"
		 */
		bool onVacation;

		/**
		 * @brief Флаг "В декретном отпуске"
		 */
		bool onMaternityLeave;

	public:
		/**
		 * @brief Конструктор по умолчанию
		 */
		Employee();

		/**
		 * @brief Конструктор
		 * @param fullName - ФИО сотрудника
		 * @param birthDate - дата рождения
		 * @param position - должность
		 * @param department - отдел
		 * @param rate - ставка
		 * @param id - ID сотрудника (0 для автогенерации)
		 */
		Employee(const std::string& fullName, const std::string& birthDate, const Position& position, const Department& department, const double rate, const int id = 0);

		/**
		 * @brief Получить должность сотрудника
		 * @return ссылку на должность
		 */
		const Position& getPosition() const noexcept;

		/**
		 * @brief Получить отдел сотрудника
		 * @return ссылку на отдел
		 */
		const Department& getDepartment() const noexcept;

		/**
		 * @brief Получить ставку сотрудника
		 * @return ставку сотрудника
		 */
		double getRate() const noexcept;

		/**
		 * @brief Получить предыдущие места работы
		 * @return Массив мест работы сотрудника
		 */
		const std::vector<PreviousWorkplace>& getPreviousWorkplaces() const noexcept;

		/**
		 * @brief Получить ID детей сотрудника
		 * @return Массив ID детей
		 */
		const std::vector<int>& getChildrenIds() const noexcept;

		/**
		 * @brief Функция добавления предыдущего места работы
		 * @param wp - ссылка на предыдущее место работы
		 */
		void addPreviousWorkplace(const PreviousWorkplace& wp);

		/**
		 * @brief Функция добавления ребёнка по ID
		 * @param childId - ID ребёнка
		 */
		void addChildId(const int childId);

		/**
		 * @brief Функция присвоения флагов сотруднику
		 * @param pensioner - флаг "Пенсионер"
		 * @param disabled - флаг "Инвалид"
		 * @param onVacation - флаг "В отпуске"
		 * @param onMaternityLeave - флаг "В декрете"
		 */
		void setFlags(const bool pensioner, const bool disabled, const bool onVacation, const bool onMaternityLeave);

		/**
		 * @brief функция проверки наличия детей у сотрудника
		 * @return true - если есть дети, иначе false
		 */
		bool hasChildren() const noexcept;

		/**
		 * @brief функция проверки, является ли сотрудник пенсионером
		 * @return true - если пенсионер, иначе false
		 */
		bool isPensioner() const noexcept;

		/**
		 * @brief Функция проверки, инвалид ли сотрудник
		 * @return true - если инвалид, иначе false
		 */
		bool isDisabled() const noexcept;

		/**
		 * @brief Функция проверки, в отпуске ли сотрудник
		 * @return true - если в отпуске, иначе false
		 */
		bool isOnVacation() const noexcept;

		/**
		 * @brief Функция проверки, в декрете ли сотрудник
		 * @return true - если в декрете, иначе false
		 */
		bool isOnMaternityLeave() const noexcept;

		/**
		 * @brief Получение информации о сотруднике
		 * @return Информацию о сотруднике
		 */
		std::string getInfo() const override;
};
