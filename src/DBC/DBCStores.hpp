#ifndef DBCSTORES_H
#define DBCSTORES_H

#include <map>
#include "DBCStructures.hpp"

class DBCStore
{
public:
    static DBCStore* instance()
    {
        static DBCStore dbc;
        return &dbc;
    }

    bool LoadDBCDatas();

    // Stores
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
    std::map<uint32_t, OverrideSpellDataEntry>       m_OverrideSpellDataEntries;                 // OverrideSpellData.dbc
    std::map<uint32_t, ScreenEffectEntry>            m_ScreenEffectEntries;                      // ScreenEffect.dbc
    std::map<uint32_t, SpellRadiusEntry>             m_SpellRadiusEntries;                       // SpellRadius.dbc
    std::map<uint32_t, FactionEntry>                 m_FactionEntries;                           // Faction.dbc
};

#define sDBCStores DBCStore::instance()

template<class T>
T const* GetDBCEntry(uint32_t id, std::map<uint32_t, T> const& storage)
{
    if (id == 0)
    {
        return nullptr;
    }

    auto const& itr = storage.find(id);
    return itr != storage.end() ? &(itr->second) : nullptr;
}

#endif // DBCSTORES_H
