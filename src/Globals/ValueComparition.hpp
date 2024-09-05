#pragma once

#include <QString>
#include <QStringList>
#include <QStringView>
#include <optional>

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

template<class T>
struct AdvancedSearchParams
{
    bool hasData = false;
    ConditionCompareType compareType;
    std::optional<int32_t> int32val;
    std::optional<uint32_t> uint32val;
    std::optional<float> floatVal;
    std::optional<QString> textVal;

    uint8_t spellFieldId;

    bool CheckSpellFields(const T& dbcData) const
    {
        // Nothing to check
        if (!hasData)
        {
            return true;
        }

        switch (compareType)
        {
        case ConditionCompareType::NotEqual:
        case ConditionCompareType::Equal:
        case ConditionCompareType::GreaterThan:
        case ConditionCompareType::GreaterOrEqual:
        case ConditionCompareType::LowerThan:
        case ConditionCompareType::LowerOrEqual:
        {
            const auto& aVal = dbcData.GetField(spellFieldId);
            if (int32val.has_value())
            {
                return CompareNumericValues(compareType, aVal.int32Val, *int32val);
            }
            else if (uint32val.has_value())
            {
                return CompareNumericValues(compareType, aVal.uint32Val, *uint32val);
            }
            else if (floatVal.has_value())
            {
                return CompareNumericValues(compareType, aVal.floatVal, *floatVal);
            }
            break;
        }
        case ConditionCompareType::BitValue:
        case ConditionCompareType::NoBitValue:
        {
            const auto& aVal = dbcData.GetField(spellFieldId);
            if (uint32val.has_value())
            {
                return CompareBitMasks(compareType, aVal.uint32Val, *uint32val);
            }
            break;
        }
        case ConditionCompareType::StartsWith:
        case ConditionCompareType::EndsWith:
        case ConditionCompareType::Contains:
        {
            const auto& aVal = dbcData.GetField(spellFieldId);
            if (textVal.has_value())
            {
                return CompareStringValues(compareType, aVal.textVal, *textVal);
            }
            break;
        }
        }

        return false;
    }
};
