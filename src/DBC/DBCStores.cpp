#include "DBCStores.hpp"
#ifdef SPELLWORK_BUILD_SQL
#include "SQL/sqlConnection.hpp"
#endif // SPELLWORK_BUILD_SQL
#include "appSettings.hpp"

Q_LOGGING_CATEGORY(DBCStores, "spellwork.dbcstores");

template<typename T>
bool OpenAndReadDBC(const std::string_view& path, const std::string_view& dbcFileName, std::map<uint32_t, T>& storage)
{
    DBCFileLoader dbcFile(std::string(path) + "//" + std::string(dbcFileName), T::GetDBCFormat());
    if (!dbcFile.IsLoaded())
    {
        return false;
    }

    for (uint32_t i = 0; i < dbcFile.GetNumRows(); ++i)
    {
        storage.emplace(dbcFile.getRecord(i).getUInt(0), dbcFile.getRecord(i));
    }

    return true;
}

bool DBCStore::LoadData()
{
    if (!LoadDBCDatas())
    {
        return false;
    }

    if (!sSpellWorkConfig->GetAppConfig().loadDBCSpells && !sSpellWorkConfig->GetAppConfig().loadSQLSpells)
    {
        return false;
    }

    if (sSpellWorkConfig->GetSQLConfig().enable && sSpellWorkConfig->GetAppConfig().loadSQLSpells && !LoadSqlDBCData())
    {
        return false;
    }

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
    const auto& dbcFolderPath = sSpellWorkConfig->GetAppConfig().dbcFilePath;
    if (!OpenAndReadDBC(dbcFolderPath, "SpellCategory.dbc",             m_SpellCategoryEntries) ||
        !OpenAndReadDBC(dbcFolderPath, "SpellCategories.dbc",           m_SpellCategories) ||
        !OpenAndReadDBC(dbcFolderPath, "SpellClassOptions.dbc",         m_SpellClassOptions) ||
        !OpenAndReadDBC(dbcFolderPath, "SpellTargetRestrictions.dbc",   m_SpellTargetRestrictions) ||
        !OpenAndReadDBC(dbcFolderPath, "SpellShapeshift.dbc",           m_SpellShapeshiftEntries) ||
        !OpenAndReadDBC(dbcFolderPath, "SkillLineAbility.dbc",          m_SkillLineAbilityEntries) ||
        !OpenAndReadDBC(dbcFolderPath, "SkillLine.dbc",                 m_SkillLineEntries) ||
        !OpenAndReadDBC(dbcFolderPath, "SkillLineAbility.dbc",          m_SkillLineAbilityEntries) ||
        !OpenAndReadDBC(dbcFolderPath, "SpellReagents.dbc",             m_SpellReagentsEntries) ||
        !OpenAndReadDBC(dbcFolderPath, "SpellLevels.dbc",               m_SpellLevelsEntries) ||
        !OpenAndReadDBC(dbcFolderPath, "SpellEquippedItems.dbc",        m_SpellEquippedItemsEntries) ||
        !OpenAndReadDBC(dbcFolderPath, "SpellRange.dbc",                m_SpellRangeEntries) ||
        !OpenAndReadDBC(dbcFolderPath, "SpellAuraOptions.dbc",          m_SpellAuraOptionsEntries) ||
        !OpenAndReadDBC(dbcFolderPath, "SpellCastTimes.dbc",            m_SpellCastTimesEntries) ||
        !OpenAndReadDBC(dbcFolderPath, "SpellCooldowns.dbc",            m_SpellCooldownsEntries) ||
        !OpenAndReadDBC(dbcFolderPath, "SpellDuration.dbc",             m_SpellDurationEntries) ||
        !OpenAndReadDBC(dbcFolderPath, "SpellPower.dbc",                m_SpellPowerEntries) ||
        !OpenAndReadDBC(dbcFolderPath, "SpellInterrupts.dbc",           m_SpellInterruptsEntries) ||
        !OpenAndReadDBC(dbcFolderPath, "SpellAuraRestrictions.dbc",     m_SpellAuraRestrictionsEntries) ||
        !OpenAndReadDBC(dbcFolderPath, "AreaGroup.dbc",                 m_AreaGroupEntries) ||
        !OpenAndReadDBC(dbcFolderPath, "AreaTable.dbc",                 m_AreaTableEntries) ||
        !OpenAndReadDBC(dbcFolderPath, "SpellCastingRequirements.dbc",  m_SpellCastingRequirementsEntries) ||
        !OpenAndReadDBC(dbcFolderPath, "gtSpellScaling.dbc",            m_GtSpellScalingEntries) ||
        !OpenAndReadDBC(dbcFolderPath, "OverrideSpellData.dbc",         m_OverrideSpellDataEntries) ||
        !OpenAndReadDBC(dbcFolderPath, "ScreenEffect.dbc",              m_ScreenEffectEntries) ||
        !OpenAndReadDBC(dbcFolderPath, "SpellRadius.dbc",               m_SpellRadiusEntries) ||
        !OpenAndReadDBC(dbcFolderPath, "Faction.dbc",                   m_FactionEntries) ||
        (sSpellWorkConfig->GetAppConfig().loadDBCSpells && (!OpenAndReadDBC(dbcFolderPath, "Spell.dbc", m_spellEntries) || !OpenAndReadDBC(dbcFolderPath, "SpellEffect.dbc", m_SpellEffectEntries)))
    )
    {
        return false;
    }

    return true;
}

bool DBCStore::LoadSqlDBCData()
{
#ifdef SPELLWORK_BUILD_SQL
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

            m_spellEntries.try_emplace(entry, spell);
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
            m_SpellEffectEntries.try_emplace(entry, effect);
            ++count;
        }
        mysql_free_result(result);

        qCDebug(DBCStores) << "DBCStore::LoadSqlDBCData: loaded " << count << " entries from spelleffect_dbc";
    }
    return true;
#else
    return true;
#endif // SPELLWORK_BUILD_SQL
}

