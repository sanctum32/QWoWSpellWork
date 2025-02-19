#pragma once
#include <array>
#include <cstdint>

constexpr uint8_t MAX_UINT32_BITMASK_INDEX = 31;
constexpr uint8_t TOTAL_LOCALES = 12;

struct LocalizedString
{
    LocalizedString(const LocalizedString &) = default;
    LocalizedString(LocalizedString &&) = default;
    LocalizedString &operator=(const LocalizedString &) = default;
    LocalizedString &operator=(LocalizedString &&) = default;

    std::array<const char *, TOTAL_LOCALES> Str;
};

constexpr char const* printLine = "==============================================<br>";
