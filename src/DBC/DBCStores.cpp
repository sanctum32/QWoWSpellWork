#include "DBCStores.hpp"
#ifdef SPELLWORK_BUILD_SQL
#include "SQL/sqlConnection.hpp"
#endif // SPELLWORK_BUILD_SQL
#include "appSettings.hpp"

Q_LOGGING_CATEGORY(DBCStores, "spellwork.dbcstores");

template<class T>
void ReadDBCRows(DBCFileLoader& dbcFile, std::map<uint32_t, T>& storage)
{
    for (uint32_t i = 0; i < dbcFile.GetNumRows(); ++i)
    {
        storage.emplace(dbcFile.getRecord(i).getUInt(0), dbcFile.getRecord(i));
    }
}

bool DBCStore::LoadData()
{
    if (!LoadDBCDatas())
    {
        return false;
    }

#ifdef SPELLWORK_BUILD_SQL
    if (!LoadSqlDBCData())
    {
        return false;
    }
#endif

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

bool DBCStore::LoadDBCDatas()
{
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
    DBCFileLoader factionDBC("dbc/Faction.dbc", FactionEntry::GetDBCFormat());

    if (!spellCategoryDBC.IsLoaded() ||
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
        !spellRadiusDBC.IsLoaded() ||
        !factionDBC.IsLoaded())
    {
        return false;
    }

    if (sSpellWorkConfig->GetAppConfig().loadDBCSpells)
    {
        DBCFileLoader spellDBC("dbc/Spell.dbc", SpellEntry::GetDBCFormat());
        DBCFileLoader spellEffectDBC("dbc/SpellEffect.dbc", SpellEffectEntry::GetDBCFormat());

        if (!spellDBC.IsLoaded() || !spellEffectDBC.IsLoaded())
        {
            return false;
        }

        ReadDBCRows(spellDBC, m_spellEntries);
        ReadDBCRows(spellEffectDBC, m_SpellEffectEntries);
    }

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
    ReadDBCRows(factionDBC, m_FactionEntries);

    return true;
}

#ifdef SPELLWORK_BUILD_SQL
bool DBCStore::LoadSqlDBCData()
{
    if (!sSpellWorkConfig->GetSQLConfig().enable || !sSpellWorkConfig->GetAppConfig().loadSQLSpells)
    {
        return true;
    }

    auto* connection = sSpellWorkSQL->GetConnection();
    if (connection == nullptr)
    {
        return false;
    }

    // Load spell_dbc
    {
        std::stringstream query;
        query << "SELECT ";
        query << "`Id`,";                           // 0
        query << "`Attributes`,";                   // 1
        query << "`AttributesEx`,";                 // 2
        query << "`AttributesEx2`,";                // 3
        query << "`AttributesEx3`,";                // 4
        query << "`AttributesEx4`,";                // 5
        query << "`AttributesEx5`,";                // 6
        query << "`AttributesEx6`,";                // 7
        query << "`AttributesEx7`,";                // 8
        query << "`AttributesEx8`,";                // 9
        query << "`AttributesEx9`,";                // 10
        query << "`AttributesEx10`,";               // 11
        query << "`CastingTimeIndex`,";             // 12
        query << "`DurationIndex`,";                // 13
        query << "`RangeIndex`,";                   // 14
        query << "`SchoolMask`,";                   // 15
        query << "`SpellAuraOptionsId`,";           // 16
        query << "`SpellCastingRequirementsId`,";   // 17
        query << "`SpellCategoriesId`,";            // 18
        query << "`SpellClassOptionsId`,";          // 19
        query << "`SpellEquippedItemsId`,";         // 20
        query << "`SpellInterruptsId`,";            // 21
        query << "`SpellLevelsId`,";                // 22
        query << "`SpellTargetRestrictionsId`,";    // 23
        query << "`SpellName`";                     // 24
        query << " FROM `spell_dbc`";

        if (mysql_query(connection, query.str().c_str()) != 0)
        {
            qCDebug(DBCStores) << "DBCStore::LoadSqlDBCData: failed to execute spell_dbc query. Error: " << mysql_error(connection);
            return false;
        }

        auto* result = mysql_store_result(connection);
        if (result == nullptr)
        {
            qCDebug(DBCStores) << "DBCStore::LoadSqlDBCData: failed to fetch result data from spell_dbc query; Error: " << mysql_error(connection);
            return false;
        }

        uint32_t count = 0;
        while (auto row = mysql_fetch_row(result))
        {
            const uint32_t entry = static_cast<uint32_t>(std::stoul(row[0]));
            if (entry == 0)
            {
                continue;
            }

            if (m_SpellEffectEntries.contains(entry))
            {
                qCDebug(DBCStores) << "DBCStore::LoadSqlDBCData: tried to load spell_dbc entry" << QString::number(entry) << ", but entry already exists in storage. Skipped!";
                continue;
            }

            SpellEntry spell;
            spell.m_IsServerSide = true;
            spell.Id = entry;

            // 1 - 11
            for (uint8_t i = 0; i < MAX_SPELL_ATTRIBUTES; ++i)
            {
                spell.Attributes[0] = static_cast<uint32_t>(atoi(row[1 + i]));
            }

            spell.CastingTimeIndex      = static_cast<uint32_t>(std::stoul(row[12]));
            spell.DurationIndex         = static_cast<uint32_t>(std::stoul(row[13]));
            spell.rangeIndex            = static_cast<uint32_t>(std::stoul(row[14]));
            spell.SchoolMask            = static_cast<uint32_t>(std::stoul(row[15]));
            spell.SpellAuraOptionsId    = static_cast<uint32_t>(std::stoul(row[16]));
            spell.SpellCastingRequirementsId = static_cast<uint32_t>(std::stoul(row[17]));
            spell.SpellCategoriesId     = static_cast<uint32_t>(std::stoul(row[18]));
            spell.SpellClassOptionsId   = static_cast<uint32_t>(std::stoul(row[19]));
            spell.SpellEquippedItemsId  = static_cast<uint32_t>(std::stoul(row[20]));
            spell.SpellInterruptsId     = static_cast<uint32_t>(std::stoul(row[21]));
            spell.SpellLevelsId         = static_cast<uint32_t>(std::stoul(row[22]));
            spell.SpellTargetRestrictionsId = static_cast<uint32_t>(std::stoul(row[23]));
            spell.SpellName             = row[24];
            spell.SpellName += " - Server Side";
            spell.m_spellNameUpper = QString(spell.SpellName.c_str()).toUpper();


            m_spellEntries.emplace(entry, spell);
            ++count;
        }

        mysql_free_result(result);

        qCDebug(DBCStores) << "DBCStore::LoadSqlDBCData: loaded " << count << " entries from spell_dbc";
    }

    // Load spelleffect_dbc
    {
        std::stringstream query;
        query << "SELECT ";
        query << "`Id`,";                       // 0
        query << "`Effect`,";                   // 1
        query << "`EffectAmplitude`,";          // 2
        query << "`EffectAura`,";               // 3
        query << "`EffectAuraPeriod`,";         // 4
        query << "`EffectBasePoints`,";         // 5
        query << "`EffectBonusCoefficient`,";   // 6
        query << "`EffectChainAmplitude`,";     // 7
        query << "`EffectChainTargets`,";       // 8
        query << "`EffectDieSides`,";           // 9
        query << "`EffectItemType`,";           // 10
        query << "`EffectMechanic`,";           // 11
        query << "`EffectMiscValue`,";          // 12
        query << "`EffectMiscValueB`,";         // 13
        query << "`EffectPointsPerResource`,";  // 14
        query << "`EffectRadiusIndex`,";        // 15
        query << "`EffectRadiusMaxIndex`,";     // 16
        query << "`EffectRealPointsPerLevel`,"; // 17
        query << "`EffectSpellClassMaskA`,";    // 18
        query << "`EffectSpellClassMaskB`,";    // 19
        query << "`EffectSpellClassMaskC`,";    // 20
        query << "`EffectTriggerSpell`,";       // 21
        query << "`EffectImplicitTargetA`,";    // 22
        query << "`EffectImplicitTargetB`,";    // 23
        query << "`SpellID`,";                  // 24
        query << "`EffectIndex`";               // 25
        query << " FROM `spelleffect_dbc`";

        if (mysql_query(connection, query.str().c_str()) != 0)
        {
            qCDebug(DBCStores) << "DBCStore::LoadSqlDBCData: failed to execute spelleffect_dbc query. Error: " << mysql_error(connection);
            return false;
        }

        auto* result = mysql_store_result(connection);
        if (result == nullptr)
        {
            qCDebug(DBCStores) << "DBCStore::LoadSqlDBCData: failed to fetch result data from spell_dbc query; Error: " << mysql_error(connection);
            return false;
        }

        uint32_t count = 0;
        while (auto row = mysql_fetch_row(result))
        {
            const uint32_t entry = static_cast<uint32_t>(std::stoul(row[0]));
            if (entry == 0)
            {
                continue;
            }

            if (m_SpellEffectEntries.contains(entry))
            {
                qCDebug(DBCStores) << "DBCStore::LoadSqlDBCData: tried to load spelleffect_dbc entry" << QString::number(entry) << ", but entry already exists in storage. Skipped!";
                continue;
            }

            SpellEffectEntry effect;
            effect.Id                       = entry;
            effect.Effect                   = static_cast<uint32_t>(std::stoul(row[1]));
            effect.EffectAmplitude          = std::stof(row[2]);
            effect.EffectAura               = static_cast<uint32_t>(std::stoul(row[3]));
            effect.EffectAuraPeriod         = static_cast<uint32_t>(std::stoul(row[4]));
            effect.EffectBasePoints         = static_cast<uint32_t>(std::stoul(row[5]));
            effect.EffectBonusCoefficient   = std::stof(row[6]);
            effect.EffectChainAmplitude     = std::stof(row[7]);
            effect.EffectChainTargets       = static_cast<uint32_t>(std::stoul(row[8]));
            effect.EffectDieSides           = static_cast<uint32_t>(std::stoul(row[9]));
            effect.EffectItemType           = static_cast<uint32_t>(std::stoul(row[10]));
            effect.EffectMechanic           = static_cast<uint32_t>(std::stoul(row[11]));
            effect.EffectMiscValue          = static_cast<uint32_t>(std::stoul(row[12]));
            effect.EffectMiscValueB         = static_cast<uint32_t>(std::stoul(row[13]));
            effect.EffectPointsPerResource  = std::stof(row[14]);;
            effect.EffectRadiusIndex        = static_cast<uint32_t>(std::stoul(row[15]));
            effect.EffectRadiusMaxIndex     = static_cast<uint32_t>(std::stoul(row[16]));
            effect.EffectRealPointsPerLevel = std::stof(row[17]);
            effect.EffectSpellClassMask[0]  = static_cast<uint32_t>(std::stoul(row[18]));
            effect.EffectSpellClassMask[1]  = static_cast<uint32_t>(std::stoul(row[19]));
            effect.EffectSpellClassMask[2]  = static_cast<uint32_t>(std::stoul(row[20]));
            effect.EffectTriggerSpell       = static_cast<uint32_t>(std::stoul(row[21]));
            effect.EffectImplicitTargetA    = static_cast<uint32_t>(std::stoul(row[22]));
            effect.EffectImplicitTargetB    = static_cast<uint32_t>(std::stoul(row[23]));
            effect.SpellID                  = static_cast<uint32_t>(std::stoul(row[24]));
            effect.EffectIndex              = static_cast<uint32_t>(std::stoul(row[25]));
            m_SpellEffectEntries.emplace(entry, effect);
        }
        mysql_free_result(result);
    }
    return true;
}

#endif // SPELLWORK_BUILD_SQL
