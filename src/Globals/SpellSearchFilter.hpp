#pragma once
#include <QString>
#include <array>

namespace SpellWork::Filters
{
    struct GenericSearchFilter
    {
        GenericSearchFilter() = default;

        GenericSearchFilter(GenericSearchFilter &&) = delete;
        GenericSearchFilter &operator=(GenericSearchFilter &&) = delete;
        // Prevent copies
        GenericSearchFilter(const GenericSearchFilter&) = delete;
        GenericSearchFilter& operator=(const GenericSearchFilter&) = delete;

        [[nodiscard]] bool HasData() const
        {
            return m_spellFamily.first != -1 || m_spellAuraType.first != -1 || m_spellEffect.first != -1 || m_spellTargetA.first != -1 || m_spellTargetB.first != -1;
        }

        [[nodiscard]] const uint32_t* GetSpellFamily() const;
        [[nodiscard]] const uint32_t* GetSpellAuraType() const;
        [[nodiscard]] const uint32_t* GetSpellEffect() const;
        [[nodiscard]] const uint32_t* GetSpellTargetA() const;
        [[nodiscard]] const uint32_t* GetSpellTargetB() const;

        std::pair<int /*comboBoxindex*/, uint32_t /*value*/> m_spellFamily{-1, 0};
        std::pair<int /*comboBoxindex*/, uint32_t /*value*/> m_spellAuraType{-1, 0};
        std::pair<int /*comboBoxindex*/, uint32_t /*value*/> m_spellEffect{-1, 0};
        std::pair<int /*comboBoxindex*/, uint32_t /*value*/> m_spellTargetA{-1, 0};
        std::pair<int /*comboBoxindex*/, uint32_t /*value*/> m_spellTargetB{-1, 0};
    };

    struct AdvancedSearchData
    {
        AdvancedSearchData() = default;

        AdvancedSearchData(AdvancedSearchData &&) = delete;
        AdvancedSearchData &operator=(AdvancedSearchData &&) = delete;
        // Prevent copies
        AdvancedSearchData(const AdvancedSearchData&) = delete;
        AdvancedSearchData& operator=(const AdvancedSearchData&) = delete;

        [[nodiscard]] bool HasData() const
        {
            return m_entryField.first != -1 && m_compareType.first != -1 && !m_compareValue.isEmpty();
        }

        [[nodiscard]] const uint8_t* GetFieldId() const;
        [[nodiscard]] const uint8_t* GetCompareType() const;
        [[nodiscard]] const QString& GetCompareValue() const { return m_compareValue; }

        std::pair<int /*comboBoxindex*/, uint8_t /*value*/> m_entryField{-1, 0};
        std::pair<int /*comboBoxindex*/, uint8_t /*value*/> m_compareType{-1, 0};
        QString m_compareValue;
    };

    struct SpellSearchFilter
    {
        GenericSearchFilter m_genericFilter;
        std::array<AdvancedSearchData, 2> m_spellEntryFieldsFilter;          // Spell.dbc entry fields filter
        std::array<AdvancedSearchData, 2> m_spellEffectFieldsFilter;         // SpellEffect.dbc entry fields filter
    };
}  // namespace SpellWork::Filters
