#include "SpellSearchFilter.hpp"

// extern variables
namespace SpellWork::Filters
{
const uint32_t* GenericSearchFilter::GetSpellFamily() const
{
    return m_spellFamily.first != -1 ? &m_spellFamily.second : nullptr;
}

const uint32_t *GenericSearchFilter::GetSpellAuraType() const
{
    return m_spellAuraType.first != -1 ? &m_spellAuraType.second : nullptr;
}

const uint32_t *GenericSearchFilter::GetSpellEffect() const
{
    return m_spellEffect.first != -1 ? &m_spellEffect.second : nullptr;
}

const uint32_t *GenericSearchFilter::GetSpellTargetA() const
{
    return m_spellTargetA.first != -1 ? &m_spellTargetA.second : nullptr;
}

const uint32_t *GenericSearchFilter::GetSpellTargetB() const
{
    return m_spellTargetB.first != -1 ? &m_spellTargetB.second : nullptr;
}

const uint8_t *AdvancedSearchData::GetFieldId() const
{
    return m_entryField.first != -1 ? &m_entryField.second : nullptr;
}

const uint8_t *AdvancedSearchData::GetCompareType() const
{
    return m_compareType.first != -1 ? &m_compareType.second : nullptr;
}
}  // namespace SpellWork::Filters
