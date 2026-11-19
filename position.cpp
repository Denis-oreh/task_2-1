#include "Position.h"

Position::Position(const std::string& title) : title(title) {}

const std::string& Position::getTitle() const noexcept {return title;}