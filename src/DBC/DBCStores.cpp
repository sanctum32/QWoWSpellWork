#include "DBCStores.h"

template<class T>
void ReadDBCRows(DBCFileLoader& dbcFile, std::map<uint32_t, T>& storage)
{
    for (uint32_t i = 0; i < dbcFile.GetNumRows(); ++i)
    {
        storage.emplace(dbcFile.getRecord(i).getUInt(0), dbcFile.getRecord(i));
    }
}

bool DBCStore::LoadDBCDatas()
{
    DBCFileLoader spellDBC("dbc/Spell.dbc", SpellEntry::GetDBCFormat());
    DBCFileLoader spellEffectDBC("dbc/SpellEffect.dbc", SpellEffectEntry::GetDBCFormat());
    DBCFileLoader spellScalingDBC("dbc/SpellScaling.dbc", SpellEffectEntry::GetDBCFormat());
    DBCFileLoader spellCategoryDBC("dbc/SpellCategory.dbc", SpellCategoryEntry::GetDBCFormat());
    DBCFileLoader spellCategoriesDBC("dbc/SpellCategories.dbc", SpellCategoriesEntry::GetDBCFormat());
    DBCFileLoader spellClassOptionsDBC("dbc/SpellClassOptions.dbc", SpellClassOptionsEntry::GetDBCFormat());
    DBCFileLoader spellTargetRestrictionsDBC("dbc/SpellTargetRestrictions.dbc", SpellTargetRestrictionsEntry::GetDBCFormat());
    DBCFileLoader spellShapeshiftDBC("dbc/SpellShapeshift.dbc", SpellShapeshiftEntry::GetDBCFormat());
    DBCFileLoader skillLineAbilityDBC("dbc/SkillLineAbility.dbc", SkillLineAbilityEntry::GetDBCFormat());
    DBCFileLoader skillLineDBC("dbc/SkillLine.dbc", SkillLineEntry::GetDBCFormat());
    DBCFileLoader spellRegentsDBC("dbc/SpellReagents.dbc", SpellReagentsEntry::GetDBCFormat());
    DBCFileLoader spellLevelsDBC("dbc/SpellLevels.dbc", SpellLevelsEntry::GetDBCFormat());
    DBCFileLoader spellEquippedItemsDBC("dbc/SpellEquippedItems.dbc", SpellEquippedItemsEntry::GetDBCFormat());
    DBCFileLoader spellRangeDBC("dbc/SpellRange.dbc", SpellRangeEntry::GetDBCFormat());
    DBCFileLoader spellAuraOptionsDBC("dbc/SpellAuraOptions.dbc", SpellAuraOptionsEntry::GetDBCFormat());
    DBCFileLoader spellCastTimesDBC("dbc/SpellCastTimes.dbc", SpellCastTimesEntry::GetDBCFormat());
    DBCFileLoader spellCooldownsDBC("dbc/SpellCooldowns.dbc", SpellCooldownsEntry::GetDBCFormat());
    DBCFileLoader spellDurationDBC("dbc/SpellDuration.dbc", SpellDurationEntry::GetDBCFormat());
    DBCFileLoader spellPowerDBC("dbc/SpellPower.dbc", SpellPowerEntry::GetDBCFormat());
    DBCFileLoader spellInterruptsDBC("dbc/SpellInterrupts.dbc", SpellInterruptsEntry::GetDBCFormat());
    DBCFileLoader spellAuraRestrictionsDBC("dbc/SpellAuraRestrictions.dbc", SpellAuraRestrictionsEntry::GetDBCFormat());
    DBCFileLoader areaGroupDBC("dbc/AreaGroup.dbc", AreaGroupEntry::GetDBCFormat());
    DBCFileLoader areaTableDBC("dbc/AreaTable.dbc", AreaTableEntry::GetDBCFormat());
    DBCFileLoader spellCastingRequirementsDBC("dbc/SpellCastingRequirements.dbc", SpellCastingRequirementsEntry::GetDBCFormat());
    DBCFileLoader gtSpellScalingDBC("dbc/gtSpellScaling.dbc", GtSpellScalingEntry::GetDBCFormat());
    DBCFileLoader overrideSpellDataEntriesDBC("dbc/OverrideSpellData.dbc", OverrideSpellDataEntry::GetDBCFormat());
    DBCFileLoader screenEffectDBC("dbc/ScreenEffect.dbc", ScreenEffectEntry::GetDBCFormat());
    DBCFileLoader spellRadiusDBC("dbc/SpellRadius.dbc", SpellRadiusEntry::GetDBCFormat());

    if (!spellDBC.IsLoaded() ||
        !spellEffectDBC.IsLoaded() ||
        !spellCategoryDBC.IsLoaded() ||
        !spellCategoriesDBC.IsLoaded() ||
        !spellScalingDBC.IsLoaded() ||
        !spellClassOptionsDBC.IsLoaded() ||
        !spellTargetRestrictionsDBC.IsLoaded() ||
        !spellShapeshiftDBC.IsLoaded() ||
        !skillLineAbilityDBC.IsLoaded() ||
        !skillLineDBC.IsLoaded() ||
        !spellRegentsDBC.IsLoaded() ||
        !spellLevelsDBC.IsLoaded() ||
        !spellEquippedItemsDBC.IsLoaded() ||
        !spellRangeDBC.IsLoaded() ||
        !spellAuraOptionsDBC.IsLoaded() ||
        !spellCastTimesDBC.IsLoaded() ||
        !spellCooldownsDBC.IsLoaded() ||
        !spellDurationDBC.IsLoaded() ||
        !spellPowerDBC.IsLoaded() ||
        !spellInterruptsDBC.IsLoaded() ||
        !spellAuraRestrictionsDBC.IsLoaded() ||
        !areaGroupDBC.IsLoaded() ||
        !areaTableDBC.IsLoaded() ||
        !spellCastingRequirementsDBC.IsLoaded() ||
        !gtSpellScalingDBC.IsLoaded() ||
        !overrideSpellDataEntriesDBC.IsLoaded() ||
        !screenEffectDBC.IsLoaded() ||
        !spellRadiusDBC.IsLoaded())
    {
        return false;
    }

    ReadDBCRows(spellDBC, m_spellEntries);
    ReadDBCRows(spellEffectDBC, m_SpellEffectEntries);
    ReadDBCRows(spellCategoryDBC, m_SpellCategoryEntries);
    ReadDBCRows(spellCategoriesDBC, m_SpellCategories);
    ReadDBCRows(spellClassOptionsDBC, m_SpellClassOptions);
    ReadDBCRows(spellTargetRestrictionsDBC, m_SpellTargetRestrictions);
    ReadDBCRows(spellShapeshiftDBC, m_SpellShapeshiftEntries);
    ReadDBCRows(skillLineAbilityDBC, m_SkillLineAbilityEntries);
    ReadDBCRows(skillLineDBC, m_SkillLineEntries);
    ReadDBCRows(spellRegentsDBC, m_SpellReagentsEntries);
    ReadDBCRows(spellLevelsDBC, m_SpellLevelsEntries);
    ReadDBCRows(spellEquippedItemsDBC, m_SpellEquippedItemsEntries);
    ReadDBCRows(spellRangeDBC, m_SpellRangeEntries);
    ReadDBCRows(spellAuraOptionsDBC, m_SpellAuraOptionsEntries);
    ReadDBCRows(spellCastTimesDBC, m_SpellCastTimesEntries);
    ReadDBCRows(spellCooldownsDBC, m_SpellCooldownsEntries);
    ReadDBCRows(spellDurationDBC, m_SpellDurationEntries);
    ReadDBCRows(spellPowerDBC, m_SpellPowerEntries);
    ReadDBCRows(spellInterruptsDBC, m_SpellInterruptsEntries);
    ReadDBCRows(spellAuraRestrictionsDBC, m_SpellAuraRestrictionsEntries);
    ReadDBCRows(areaGroupDBC, m_AreaGroupEntries);
    ReadDBCRows(areaTableDBC, m_AreaTableEntries);
    ReadDBCRows(spellCastingRequirementsDBC, m_SpellCastingRequirementsEntries);
    ReadDBCRows(gtSpellScalingDBC, m_GtSpellScalingEntries);
    ReadDBCRows(overrideSpellDataEntriesDBC, m_OverrideSpellDataEntries);
    ReadDBCRows(screenEffectDBC, m_ScreenEffectEntries);
    ReadDBCRows(spellRadiusDBC, m_SpellRadiusEntries);

    // link spell related pointers
    for (const auto& spellEffectItr : m_SpellEffectEntries)
    {
        auto const& effectEntry = spellEffectItr.second;
        assert(effectEntry.EffectIndex < MAX_SPELL_EFFECTS);

        auto spellEntryItr = m_spellEntries.find(effectEntry.SpellID);
        if (spellEntryItr != m_spellEntries.end())
        {
            spellEntryItr->second.m_spellEffects[effectEntry.EffectIndex] = &effectEntry;
        }
    }

    return true;
}
