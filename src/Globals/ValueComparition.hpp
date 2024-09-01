#pragma once

#include <QString>
#include <QStringList>
#include <QStringView>

enum class CompareTypes
{
    Numeric,
    Float,
    String
};

enum class ConditionCompareType : uint8_t
{
    NotEqual,           // x != y
    Equal,              // x == y
    GreaterThan,        // x > y
    GreaterOrEqual,     // x >= y
    LowerThan,          // x < y
    LowerOrEqual,       // x <= y
    BitValue,           // (x & y) != 0
    NoBitValue,         // (x & y) == 0
    StartsWith,         // x Starts With y
    EndsWith,           // x Ends With y
    Contains            // x Contains y
};

constexpr uint8_t MAX_COMPARE_CHECK_TYPES = 11;

static QString GetValueCompareTypeStr(ConditionCompareType type)
{
    using enum ConditionCompareType;
    switch (type)
    {
    case NotEqual:
        return "x != y";
    case Equal:
        return "x == y";
    case GreaterThan:
        return "x > y";
    case GreaterOrEqual:
        return "x >= y";
    case LowerThan:
        return "x < y";
    case LowerOrEqual:
        return "x <= y";
    case BitValue:
        return "(x & y) != 0";
    case NoBitValue:
        return "(x & y) == 0";
    case StartsWith:
        return "x Starts With y";
    case EndsWith:
        return "x Ends With y";
    case Contains:
        return "x Contains y";
    default:
        assert(false && "unhandled condition check type");
    }

    // Should not happen
    return "";
}

/**
 * @brief DoConditionCompare
 * @param type - see enum ConditionCompareType
 * @param xVal
 * @param yVal
 * @return true if condition is fullfilled
 */
template<typename T>
static bool CompareNumericValues(ConditionCompareType type, T xVal, T yVal)
{
    using enum ConditionCompareType;

    switch (type)
    {
    case NotEqual:
        return xVal != yVal;
    case Equal:
        return xVal == yVal;
    case GreaterThan:
        return xVal > yVal;
    case GreaterOrEqual:
        return xVal >= yVal;
    case LowerThan:
        return xVal < yVal;
    case LowerOrEqual:
        return xVal <= yVal;
    default:
        return false;
    }
}

static bool CompareBitMasks(ConditionCompareType type, uint32_t xVal, uint32_t yVal)
{
    using enum ConditionCompareType;

    switch (type)
    {
    case BitValue:
        return (xVal & yVal) != 0;
    case NoBitValue:
        return (xVal & yVal) == 0;
    default:
        return false;
    }
}

static bool CompareStringValues(ConditionCompareType type, QStringView xVal, QStringView yVal)
{
    using enum ConditionCompareType;
    switch (type)
    {
    case StartsWith:
        return xVal.startsWith(yVal);
    case EndsWith:
        return xVal.endsWith(yVal);
    case Contains:
        return xVal.contains(yVal);
    default:
        break;
    }
    return false;
}
