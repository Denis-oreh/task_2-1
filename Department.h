#pragma once
#include <string>

/**
 * @brief Класс Департамент
 */
class Department
{
	private:
		/**
		 * @brief Название департамента
		 */
		std::string name;
	public:
		/**
		 * @brief Конструктор по умолчанию
		 */
		Department() = default;

		/**
		 * @brief Конструктор
		 * @param name - название департамента
		 */
		explicit Department(const std::string& name);

		/**
		 * @brief Получить название департамента
		 * @return название департамента
		 */
		const std::string& getName() const noexcept;
};
