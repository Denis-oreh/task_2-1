#pragma once

#include <string>

/**
 * @brief Класс Person
 */
class Person
{
	protected:
		/**
		 * @brief Статический счетчик ID
		 */
		static int nextId;

		/**
		 * @brief id человека из списка
		 */
		int id;

		/**
		 * @brief ФИО человека
		 */
		std::string fullName;

		/**
		 * @brief Дата рождения
		 */
		std::string birthDate;

	public:
		/**
		 * @brief Конструктор по умолчанию
		 */
		Person();

		/**
		 * @brief Конструктор
		 * @param fullName - ФИО
		 * @param birthDate - дата рождения
		 * @param id - id человека (0 для автогенерации)
		 */
		Person(const std::string& fullName, const std::string& birthDate, const int id = 0);

		/**
		 * @brief Виртуальный деструктор
		 */
		virtual ~Person() = default;

		/**
		 * @brief Получить id человека
		 * @return id человека
		 */
		int getId() const noexcept;

		/**
		 * @brief получить ФИО человека
		 * @return ФИО человека
		 */
		const std::string& getFullName() const noexcept;

		/**
		 * @brief получить дату рождения
		 * @return Дата рождения
		 */
		const std::string& getBirthDate() const noexcept;

		/**
		 * @brief виртуальный метод получения информации
		 */
		virtual std::string getInfo() const = 0;
};
