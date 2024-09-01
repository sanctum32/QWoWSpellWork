#pragma once
#include <unordered_map>
#include <QLoggingCategory>
#include "DBCStructures.hpp"

Q_DECLARE_LOGGING_CATEGORY(DBCStores)

class DBCStore
{
public:
    static DBCStore* instance()
    {
        static DBCStore dbc;
        return &dbc;
    }

    bool LoadData();

    const auto& GetSpellEntries() const { return m_spellEntries; }
    const auto* GetSpellEntry(uint32_t id) const { return GetDBCEntry(id, m_spellEntries); }
    const auto* GetSpellScalingEntry(uint32_t id) const { return GetDBCEntry(id, m_SpellScalingEntries); }
    const auto* GetSpellCategoryEntry(uint32_t id) const { return GetDBCEntry(id, m_SpellCategoryEntries); }
    const auto* GetSpellCategoriesEntry(uint32_t id) const { return GetDBCEntry(id, m_SpellCategories); }
    const auto* GetSpellClassOptionsEntry(uint32_t id) const { return GetDBCEntry(id, m_SpellClassOptions); }
    const auto* GetSpellTargetRestrictionsEntry(uint32_t id) const { return GetDBCEntry(id, m_SpellTargetRestrictions); }
    const auto* GetSpellShapeshiftEntry(uint32_t id) const { return GetDBCEntry(id, m_SpellShapeshiftEntries); }
    const auto* GetSkillLineAbilityEntry(uint32_t id) const { return GetDBCEntry(id, m_SkillLineAbilityEntries); }
    const auto& GetSkillLineAbilityEntries() const { return m_SkillLineAbilityEntries; }
    const auto* GetSkillLineEntry(uint32_t id) const { return GetDBCEntry(id, m_SkillLineEntries); }
    const auto& GetSkillLineEntries() const { return m_SkillLineEntries; }
    const auto* GetSpellLevelsEntry(uint32_t id) const { return GetDBCEntry(id, m_SpellLevelsEntries); }
    const auto* GetSpellReagentsEntry(uint32_t id) const { return GetDBCEntry(id, m_SpellReagentsEntries); }
    const auto* GetSpellEquippedItemsEntry(uint32_t id) const { return GetDBCEntry(id, m_SpellEquippedItemsEntries); }
    const auto* GetSpellRangeEntry(uint32_t id) const { return GetDBCEntry(id, m_SpellRangeEntries); }
    const auto* GetSpellAuraOptionsEntry(uint32_t id) const { return GetDBCEntry(id, m_SpellAuraOptionsEntries); }
    const auto* GetSpellCastTimesEntry(uint32_t id) const { return GetDBCEntry(id, m_SpellCastTimesEntries); }
    const auto* GetSpellCooldownsEntry(uint32_t id) const { return GetDBCEntry(id, m_SpellCooldownsEntries); }
    const auto* GetSpellDurationEntry(uint32_t id) const { return GetDBCEntry(id, m_SpellDurationEntries); }
    const auto* GetSpellPowerEntry(uint32_t id) const { return GetDBCEntry(id, m_SpellPowerEntries); }
    const auto* GetSpellInterruptsEntry(uint32_t id) const { return GetDBCEntry(id, m_SpellInterruptsEntries); }
    const auto* GetSpellAuraRestrictionsEntry(uint32_t id) const { return GetDBCEntry(id, m_SpellAuraRestrictionsEntries); }
    const auto* GetAreaGroupEntry(uint32_t id) const { return GetDBCEntry(id, m_AreaGroupEntries); }
    const auto* GetAreaTableEntry(uint32_t id) const { return GetDBCEntry(id, m_AreaTableEntries); }
    const auto* GetSpellCastingRequirementsEntry(uint32_t id) const { return GetDBCEntry(id, m_SpellCastingRequirementsEntries); }
    const auto* GetGtSpellScalingEntry(uint32_t id) const { return GetDBCEntry(id, m_GtSpellScalingEntries); }
    const auto* GetOverrideSpellDataEntry(uint32_t id) const { return GetDBCEntry(id, m_OverrideSpellDataEntries); }
    const auto* GetScreenEffectEntry(uint32_t id) const { return GetDBCEntry(id, m_ScreenEffectEntries); }
    const auto* GetSpellRadiusEntry(uint32_t id) const { return GetDBCEntry(id, m_SpellRadiusEntries); }
    const auto* GetFactionEntry(uint32_t id) const { return GetDBCEntry(id, m_FactionEntries); }

private:
    bool LoadDBCDatas();
    bool LoadSqlDBCData();

    template<class T>
    T const* GetDBCEntry(uint32_t id, std::unordered_map<uint32_t, T> const& storage) const
    {
        if (id == 0)
        {
            return nullptr;
        }

        auto const& itr = storage.find(id);
        return itr != storage.end() ? &(itr->second) : nullptr;
    }

    // Stores
    std::unordered_map<uint32_t, SpellEntry>                   m_spellEntries;                             // Spell.dbc
    std::unordered_map<uint32_t, SpellEffectEntry>             m_SpellEffectEntries;                       // SpellEffect.dbc
    std::unordered_map<uint32_t, SpellScalingEntry>            m_SpellScalingEntries;                      // SpellScaling.dbc
    std::unordered_map<uint32_t, SpellCategoryEntry>           m_SpellCategoryEntries;                     // SpellCategoryEntry
    std::unordered_map<uint32_t, SpellCategoriesEntry>         m_SpellCategories;                          // SpellCategories.dbc
    std::unordered_map<uint32_t, SpellClassOptionsEntry>       m_SpellClassOptions;                        // SpellClassOptions.dbc
    std::unordered_map<uint32_t, SpellTargetRestrictionsEntry> m_SpellTargetRestrictions;                  // SpellTargetRestrictions.dbc
    std::unordered_map<uint32_t, SpellShapeshiftEntry>         m_SpellShapeshiftEntries;                   // SpellShapeshift.dbc
    std::unordered_map<uint32_t, SkillLineAbilityEntry>        m_SkillLineAbilityEntries;                  // SkillLineAbility.dbc
    std::unordered_map<uint32_t, SkillLineEntry>               m_SkillLineEntries;                         // SkillLine.dbc
    std::unordered_map<uint32_t, SpellReagentsEntry>           m_SpellReagentsEntries;                     // SpellReagents.dbc
    std::unordered_map<uint32_t, SpellLevelsEntry>             m_SpellLevelsEntries;                       // SpellLevels.dbc
    std::unordered_map<uint32_t, SpellEquippedItemsEntry>      m_SpellEquippedItemsEntries;                // SpellEquippedItems.dbc
    std::unordered_map<uint32_t, SpellRangeEntry>              m_SpellRangeEntries;                        // SpellRange.dbc
    std::unordered_map<uint32_t, SpellAuraOptionsEntry>        m_SpellAuraOptionsEntries;                  // SpellAuraOptions.dbc
    std::unordered_map<uint32_t, SpellCastTimesEntry>          m_SpellCastTimesEntries;                    // SpellCastTimes.dbc
    std::unordered_map<uint32_t, SpellCooldownsEntry>          m_SpellCooldownsEntries;                    // SpellCooldowns.dbc
    std::unordered_map<uint32_t, SpellDurationEntry>           m_SpellDurationEntries;                     // SpellDuration.dbc
    std::unordered_map<uint32_t, SpellPowerEntry>              m_SpellPowerEntries;                        // SpellPower.dbc
    std::unordered_map<uint32_t, SpellInterruptsEntry>         m_SpellInterruptsEntries;                   // SpellInterrupts.dbc
    std::unordered_map<uint32_t, SpellAuraRestrictionsEntry>   m_SpellAuraRestrictionsEntries;             // SpellAuraRestrictions.dbc
    std::unordered_map<uint32_t, AreaGroupEntry>               m_AreaGroupEntries;                         // AreaGroup.dbc
    std::unordered_map<uint32_t, AreaTableEntry>               m_AreaTableEntries;                         // AreaTable.dbc
    std::unordered_map<uint32_t, SpellCastingRequirementsEntry> m_SpellCastingRequirementsEntries;         // SpellCastingRequirements.dbc
    std::unordered_map<uint32_t, GtSpellScalingEntry>          m_GtSpellScalingEntries;                    // gtSpellScaling.dbc
    std::unordered_map<uint32_t, OverrideSpellDataEntry>       m_OverrideSpellDataEntries;                 // OverrideSpellData.dbc
    std::unordered_map<uint32_t, ScreenEffectEntry>            m_ScreenEffectEntries;                      // ScreenEffect.dbc
    std::unordered_map<uint32_t, SpellRadiusEntry>             m_SpellRadiusEntries;                       // SpellRadius.dbc
    std::unordered_map<uint32_t, FactionEntry>                 m_FactionEntries;                           // Faction.dbc
};

#define sDBCStores DBCStore::instance()
