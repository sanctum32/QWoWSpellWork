#pragma once

#include <QString>
#include <QStringList>
#include <QStringView>

// in actual defitions only one flag should be used.
enum class CompareTypes
{
    None                = 0,
    SignedNumber        = 1,
    UnsignedNumber      = 2,
    Float               = 3,
    String              = 4,
};

enum class ConditionCompareType : uint8_t
{
    NotEqual        = 0,    // x != y
    Equal           = 1,    // x == y
    GreaterThan     = 2,    // x > y
    GreaterOrEqual  = 3,    // x >= y
    LowerThan       = 4,    // x < y
    LowerOrEqual    = 5,    // x <= y
    BitValue        = 6,    // (x & y) != 0
    NoBitValue      = 7,    // (x & y) == 0
    StartsWith      = 8,    // x Starts With y
    EndsWith        = 9,    // x Ends With y
    Contains        = 10    // x Contains y
};

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
        return xVal.startsWith(yVal, Qt::CaseInsensitive);
    case EndsWith:
        return xVal.endsWith(yVal, Qt::CaseInsensitive);
    case Contains:
        return xVal.contains(yVal, Qt::CaseInsensitive);
    default:
        break;
    }
    return false;
}
