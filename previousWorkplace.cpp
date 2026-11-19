#include "PreviousWorkplace.h"

PreviousWorkplace::PreviousWorkplace(const std::string& company, const std::string& position, const std::string& period) : company(company), position(position), period(period) {}

const std::string& PreviousWorkplace::getCompany() const noexcept {return company;}

const std::string& PreviousWorkplace::getPosition() const noexcept {return position;}

const std::string& PreviousWorkplace::getPeriod() const noexcept {return period;}

std::string PreviousWorkplace::toString() const
{
	return company + " -- " + position + " (" + period + ")";
}