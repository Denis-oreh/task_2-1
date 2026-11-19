#pragma once

#include <string>

/**
 * @brief Класс Position
 */
class Position
{
	private:
		/**
		 * @brief название должности
		 */
		std::string title;
	
	public:
		/**
		 * @brief конструктор по умолчанию
		 */
		Position() = default;

		/**
		 * @brief Конструктор
		 * @param title - название должности
		 */
		explicit Position(const std::string& title);

		/**
		 * @brief получить название должности
		 * @return название должности
		 */
		const std::string& getTitle() const noexcept;

};
