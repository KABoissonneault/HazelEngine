#pragma once

#include <memory>
#include <cstdarg>

std::string CStringFormat(const char* sFormat, va_list args);
std::string CStringFormat(const char* sFormat, ...);

using std::to_string;
using gsl::to_string;
std::string to_string(const std::exception& e);