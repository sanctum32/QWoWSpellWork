#pragma once

#include <array>
constexpr unsigned short MAX_UINT32_BITMASK_INDEX = 31;
constexpr unsigned short TOTAL_LOCALES = 12;

struct LocalizedString
{
    std::array<const char*, TOTAL_LOCALES> Str;
};
