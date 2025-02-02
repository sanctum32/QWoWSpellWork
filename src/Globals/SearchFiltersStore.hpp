#pragma once
#include <QString>
#include <array>

namespace SpellWork::SearchFilters
{
    struct GenericFilterData
    {
        GenericFilterData() = default;

        // Prevent copies
        GenericFilterData(const GenericFilterData&) = delete;
        GenericFilterData& operator=(const GenericFilterData&) = delete;

        inline bool HasData() const
        {
            return m_spellFamily.first != -1 || m_spellAuraType.first != -1 || m_spellEffect.first != -1 || m_spellTargetA.first != -1 || m_spellTargetB.first != -1;
        }

        const uint32_t* GetSpellFamily() const;
        const uint32_t* GetSpellAuraType() const;
        const uint32_t* GetSpellEffect() const;
        const uint32_t* GetSpellTargetA() const;
        const uint32_t* GetSpellTargetB() const;

        std::pair<int /*comboBoxindex*/, uint32_t /*value*/> m_spellFamily{-1, 0};
        std::pair<int /*comboBoxindex*/, uint32_t /*value*/> m_spellAuraType{-1, 0};
        std::pair<int /*comboBoxindex*/, uint32_t /*value*/> m_spellEffect{-1, 0};
        std::pair<int /*comboBoxindex*/, uint32_t /*value*/> m_spellTargetA{-1, 0};
        std::pair<int /*comboBoxindex*/, uint32_t /*value*/> m_spellTargetB{-1, 0};
    };

    struct AttributesFilterData
    {
        AttributesFilterData() = default;

        // Prevent copies
        AttributesFilterData(const AttributesFilterData&) = delete;
        AttributesFilterData& operator=(const AttributesFilterData&) = delete;

        inline bool HasData() const
        {
            return m_entryField.first != -1 && m_compareType.first != -1 && !m_compareValue.isEmpty();
        }

        const uint8_t* GetFieldId() const;
        const uint8_t* GetCompareType() const;
        const QString& GetCompareValue() const { return m_compareValue; }

        std::pair<int /*comboBoxindex*/, uint8_t /*value*/> m_entryField{-1, 0};
        std::pair<int /*comboBoxindex*/, uint8_t /*value*/> m_compareType{-1, 0};
        QString m_compareValue;
    };

    struct FilterData
    {
        GenericFilterData m_genericFilter;
        std::array<AttributesFilterData, 2> m_spellEntryFilter;          // Spell.dbc entry fields filter
        std::array<AttributesFilterData, 2> m_spellEffectFilter;         // SpellEffect.dbc entry fields filter
    };
}
