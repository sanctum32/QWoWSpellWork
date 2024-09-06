#include "ValueComparition.hpp"
#include "DBCStructures.hpp"

void DBCFieldDataCompare::SetValues(const std::map<uint8_t, DBCFieldAttrInfo> &attributeData, uint8_t fieldId, const ConditionCompareType cmpType, const QString &inputValue)
{
    const auto& itr = attributeData.find(fieldId);
    if (itr == attributeData.end())
    {
        return;
    }

    switch (itr->second.compareType)
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
