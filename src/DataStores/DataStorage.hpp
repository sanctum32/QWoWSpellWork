#pragma once
#include <map>
#include <QLoggingCategory>
#include "DB2Structures.hpp"
#include "DBCStructures.hpp"

Q_DECLARE_LOGGING_CATEGORY(DataStores)

class DataStorage
{
public:
    static DataStorage* instance()
    {
        static DataStorage storage;
        return &storage;
    }

    // DBC data
    bool LoadDBCData();
    const auto& GetSpellEntries() const { return m_spellEntries; }
    const auto* GetSpellEntry(uint32_t id) const { return GetEntryFromStorage(id, m_spellEntries); }
    const auto* GetSpellScalingEntry(uint32_t id) const { return GetEntryFromStorage(id, m_SpellScalingEntries); }
    const auto* GetSpellCategoryEntry(uint32_t id) const { return GetEntryFromStorage(id, m_SpellCategoryEntries); }
    const auto* GetSpellCategoriesEntry(uint32_t id) const { return GetEntryFromStorage(id, m_SpellCategories); }
    const auto* GetSpellClassOptionsEntry(uint32_t id) const { return GetEntryFromStorage(id, m_SpellClassOptions); }
    const auto* GetSpellTargetRestrictionsEntry(uint32_t id) const { return GetEntryFromStorage(id, m_SpellTargetRestrictions); }
    const auto* GetSpellShapeshiftEntry(uint32_t id) const { return GetEntryFromStorage(id, m_SpellShapeshiftEntries); }
    const auto* GetSkillLineAbilityEntry(uint32_t id) const { return GetEntryFromStorage(id, m_SkillLineAbilityEntries); }
    const auto& GetSkillLineAbilityEntries() const { return m_SkillLineAbilityEntries; }
    const auto* GetSkillLineEntry(uint32_t id) const { return GetEntryFromStorage(id, m_SkillLineEntries); }
    const auto& GetSkillLineEntries() const { return m_SkillLineEntries; }
    const auto* GetSpellLevelsEntry(uint32_t id) const { return GetEntryFromStorage(id, m_SpellLevelsEntries); }
    const auto* GetSpellReagentsEntry(uint32_t id) const { return GetEntryFromStorage(id, m_SpellReagentsEntries); }
    const auto* GetSpellEquippedItemsEntry(uint32_t id) const { return GetEntryFromStorage(id, m_SpellEquippedItemsEntries); }
    const auto* GetSpellRangeEntry(uint32_t id) const { return GetEntryFromStorage(id, m_SpellRangeEntries); }
    const auto* GetSpellAuraOptionsEntry(uint32_t id) const { return GetEntryFromStorage(id, m_SpellAuraOptionsEntries); }
    const auto* GetSpellCastTimesEntry(uint32_t id) const { return GetEntryFromStorage(id, m_SpellCastTimesEntries); }
    const auto* GetSpellCooldownsEntry(uint32_t id) const { return GetEntryFromStorage(id, m_SpellCooldownsEntries); }
    const auto* GetSpellDurationEntry(uint32_t id) const { return GetEntryFromStorage(id, m_SpellDurationEntries); }
    const auto* GetSpellPowerEntry(uint32_t id) const { return GetEntryFromStorage(id, m_SpellPowerEntries); }
    const auto* GetSpellInterruptsEntry(uint32_t id) const { return GetEntryFromStorage(id, m_SpellInterruptsEntries); }
    const auto* GetSpellAuraRestrictionsEntry(uint32_t id) const { return GetEntryFromStorage(id, m_SpellAuraRestrictionsEntries); }
    const auto* GetAreaGroupEntry(uint32_t id) const { return GetEntryFromStorage(id, m_AreaGroupEntries); }
    const auto* GetAreaTableEntry(uint32_t id) const { return GetEntryFromStorage(id, m_AreaTableEntries); }
    const auto* GetSpellCastingRequirementsEntry(uint32_t id) const { return GetEntryFromStorage(id, m_SpellCastingRequirementsEntries); }
    const auto* GetGtSpellScalingEntry(uint32_t id) const { return GetEntryFromStorage(id, m_GtSpellScalingEntries); }
    const auto* GetGtNPCManaCostScalerEntry(uint32_t id) const { return GetEntryFromStorage(id, m_GtNPCManaCostScalerEntries); }
    const auto* GetOverrideSpellDataEntry(uint32_t id) const { return GetEntryFromStorage(id, m_OverrideSpellDataEntries); }
    const auto* GetScreenEffectEntry(uint32_t id) const { return GetEntryFromStorage(id, m_ScreenEffectEntries); }
    const auto* GetSpellRadiusEntry(uint32_t id) const { return GetEntryFromStorage(id, m_SpellRadiusEntries); }
    const auto* GetFactionEntry(uint32_t id) const { return GetEntryFromStorage(id, m_FactionEntries); }

    // DB2 data
    bool LoadDB2Datas();
    const auto* GetItemEntry(uint32_t id) const { return GetEntryFromStorage(id, m_ItemSparseEntries); }

    // Generates extra and links information to dbc data
    void GenerateExtraDataInfo();

private:
    bool LoadDBCDatas();
    bool LoadSqlDBCData();
    void LoadSqlDB2Data();

    template<class T>
    T const* GetEntryFromStorage(uint32_t id, std::map<uint32_t, T> const& storage) const
    {
        if (id == 0)
        {
            return nullptr;
        }

        auto const& itr = storage.find(id);
        return itr != storage.end() ? &(itr->second) : nullptr;
    }

    // DBC stores
    std::map<uint32_t, SpellEntry>                   m_spellEntries;                             // Spell.dbc
    std::map<uint32_t, SpellEffectEntry>             m_SpellEffectEntries;                       // SpellEffect.dbc
    std::map<uint32_t, SpellScalingEntry>            m_SpellScalingEntries;                      // SpellScaling.dbc
    std::map<uint32_t, SpellCategoryEntry>           m_SpellCategoryEntries;                     // SpellCategoryEntry
    std::map<uint32_t, SpellCategoriesEntry>         m_SpellCategories;                          // SpellCategories.dbc
    std::map<uint32_t, SpellClassOptionsEntry>       m_SpellClassOptions;                        // SpellClassOptions.dbc
    std::map<uint32_t, SpellTargetRestrictionsEntry> m_SpellTargetRestrictions;                  // SpellTargetRestrictions.dbc
    std::map<uint32_t, SpellShapeshiftEntry>         m_SpellShapeshiftEntries;                   // SpellShapeshift.dbc
    std::map<uint32_t, SkillLineAbilityEntry>        m_SkillLineAbilityEntries;                  // SkillLineAbility.dbc
    std::map<uint32_t, SkillLineEntry>               m_SkillLineEntries;                         // SkillLine.dbc
    std::map<uint32_t, SpellReagentsEntry>           m_SpellReagentsEntries;                     // SpellReagents.dbc
    std::map<uint32_t, SpellLevelsEntry>             m_SpellLevelsEntries;                       // SpellLevels.dbc
    std::map<uint32_t, SpellEquippedItemsEntry>      m_SpellEquippedItemsEntries;                // SpellEquippedItems.dbc
    std::map<uint32_t, SpellRangeEntry>              m_SpellRangeEntries;                        // SpellRange.dbc
    std::map<uint32_t, SpellAuraOptionsEntry>        m_SpellAuraOptionsEntries;                  // SpellAuraOptions.dbc
    std::map<uint32_t, SpellCastTimesEntry>          m_SpellCastTimesEntries;                    // SpellCastTimes.dbc
    std::map<uint32_t, SpellCooldownsEntry>          m_SpellCooldownsEntries;                    // SpellCooldowns.dbc
    std::map<uint32_t, SpellDurationEntry>           m_SpellDurationEntries;                     // SpellDuration.dbc
    std::map<uint32_t, SpellPowerEntry>              m_SpellPowerEntries;                        // SpellPower.dbc
    std::map<uint32_t, SpellInterruptsEntry>         m_SpellInterruptsEntries;                   // SpellInterrupts.dbc
    std::map<uint32_t, SpellAuraRestrictionsEntry>   m_SpellAuraRestrictionsEntries;             // SpellAuraRestrictions.dbc
    std::map<uint32_t, AreaGroupEntry>               m_AreaGroupEntries;                         // AreaGroup.dbc
    std::map<uint32_t, AreaTableEntry>               m_AreaTableEntries;                         // AreaTable.dbc
    std::map<uint32_t, SpellCastingRequirementsEntry> m_SpellCastingRequirementsEntries;         // SpellCastingRequirements.dbc
    std::map<uint32_t, GtSpellScalingEntry>          m_GtSpellScalingEntries;                    // gtSpellScaling.dbc
    std::map<uint32_t, GtNPCManaCostScalerEntry>     m_GtNPCManaCostScalerEntries;               // gtNPCManaCostScaler.dbc
    std::map<uint32_t, OverrideSpellDataEntry>       m_OverrideSpellDataEntries;                 // OverrideSpellData.dbc
    std::map<uint32_t, ScreenEffectEntry>            m_ScreenEffectEntries;                      // ScreenEffect.dbc
    std::map<uint32_t, SpellRadiusEntry>             m_SpellRadiusEntries;                       // SpellRadius.dbc
    std::map<uint32_t, FactionEntry>                 m_FactionEntries;                           // Faction.dbc

    // DB2 stores
    std::map<uint32_t, ItemSparseEntry>              m_ItemSparseEntries;                        // Item-sparse.db2
};

#define sDataStorage DataStorage::instance()
