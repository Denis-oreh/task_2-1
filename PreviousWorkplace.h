#pragma once

#include <string>

/**
 * @brief класс PreviousWorkplace
 */
class PreviousWorkplace
{
	private:
		/**
		 * @brief Название компании
		 */
		std::string company;

		/**
		 * @brief должность
		 */
		std::string position;

		/**
		 * @brief период работы
		 */
		std::string period;
	public:
		/**
		 * @brief Конструктор по умолчанию
		 */
		PreviousWorkplace() = default;

		/**
		 * @brief Конструктор
		 * @param company - компания
		 * @param position - должность
		 * @param period - период работы
		 */
		PreviousWorkplace(const std::string& company, const std::string& position, const std::string& period);

		/**
		 * @brief Получить имя компании
		 * @return имя компании
		 */
		const std::string& getCompany() const noexcept;

		/**
		 * @brief Получить должность
		 * @return должность
		 */
		const std::string& getPosition() const noexcept;

		/**
		 * @brief получить период работы
		 * @return период работы
		 */
		const std::string& getPeriod() const noexcept;

		/**
		 * @brief получить строку с предыдущим местом работы
		 * @return строка с предыдущим местом работы
		 */
		std::string toString() const;
};
