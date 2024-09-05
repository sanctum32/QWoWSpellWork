#pragma once

#include <QString>
#include <QStringList>
#include <QStringView>
#include <map>
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

constexpr std::array<const char*, 11> ConditionCompareTypeStr =
{
    "x != y",           // 0
    "x == y",           // 1
    "x > y",            // 2
    "x >= y",           // 3
    "x < y",            // 4
    "x <= y",           // 5
    "(x & y) != 0",     // 6
    "(x & y) == 0",     // 7
    "x Starts With y",  // 8
    "x Ends With y",    // 9
    "x Contains y"      // 10
};

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

template<typename T>
static bool CompareBitMasks(ConditionCompareType type, T xVal, T yVal)
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


struct DBCFieldDataCompare
{
    bool hasData = false;

    ConditionCompareType m_compareType;
    std::optional<int32_t> m_int32val;
    std::optional<uint32_t> m_uint32val;
    std::optional<float> m_floatVal;
    std::optional<QString> m_textVal;
    uint8_t m_fieldId;

    /**
     * @brief SetValues
     * Initializes comparition values
     *
     * @param attributeData
     * @param fieldId
     * @param cmpType
     * @param inputValue
     */
    void SetValues(const std::map<uint8_t /*fieldId*/, std::pair<QString /*fieldName*/, CompareTypes /*compareType*/>>& attributeData,
                   uint8_t fieldId,
                   const ConditionCompareType cmpType,
                   const QString& inputValue)
    {
        const auto& itr = attributeData.find(fieldId);
        if (itr == attributeData.end())
        {
            return;
        }

        switch (itr->second.second)
        {
            case CompareTypes::SignedNumber:
            {
                bool ok = false;
                const int32_t val = inputValue.toInt(&ok);
                if (ok)
                {
                    m_int32val = val;
                }

            break;
        }
        case CompareTypes::UnsignedNumber:
        {
            bool ok = false;
            const uint32_t val = inputValue.toUInt(&ok);
            if (ok)
            {
                m_uint32val = val;
            }

            break;
        }
        case CompareTypes::Float:
        {
            bool ok = false;
            const float val = inputValue.toFloat(&ok);
            if (ok)
            {
                m_floatVal = val;
            }

            break;

        }
        case CompareTypes::String:
            m_textVal = inputValue;
            break;
        default:
            break;
        }

        m_fieldId = itr->first;
        m_compareType = cmpType;
        hasData = true;
    }

    /**
     * @brief DoCheck
     * function performs A(dbc field) and B(input) comparition
     *
     * @param dbcEntry - dbc entry
     * @return true if comparition is successful
     */
    template<typename T>
    bool DoCheck(const T& dbcEntry) const
    {
        // Nothing to check
        if (!hasData)
        {
            return true;
        }

        switch (m_compareType)
        {
        case ConditionCompareType::NotEqual:
        case ConditionCompareType::Equal:
        case ConditionCompareType::GreaterThan:
        case ConditionCompareType::GreaterOrEqual:
        case ConditionCompareType::LowerThan:
        case ConditionCompareType::LowerOrEqual:
        {
            const auto& aVal = dbcEntry.GetField(m_fieldId);  // A value
            if (m_int32val.has_value())
            {
                return CompareNumericValues(m_compareType, aVal.int32Val, *m_int32val);
            }
            else if (m_uint32val.has_value())
            {
                return CompareNumericValues(m_compareType, aVal.uint32Val, *m_uint32val);
            }
            else if (m_floatVal.has_value())
            {
                return CompareNumericValues(m_compareType, aVal.floatVal, *m_floatVal);
            }
            break;
        }
        case ConditionCompareType::BitValue:
        case ConditionCompareType::NoBitValue:
        {
            const auto& aVal = dbcEntry.GetField(m_fieldId);
            if (m_uint32val.has_value())
            {
                return CompareBitMasks(m_compareType, aVal.uint32Val, *m_uint32val);
            }
            break;
        }
        case ConditionCompareType::StartsWith:
        case ConditionCompareType::EndsWith:
        case ConditionCompareType::Contains:
        {
            const auto& aVal = dbcEntry.GetField(m_fieldId);
            if (m_textVal.has_value())
            {
                return CompareStringValues(m_compareType, aVal.textVal, *m_textVal);
            }
            break;
        }
        }

        return false;
    }
};
