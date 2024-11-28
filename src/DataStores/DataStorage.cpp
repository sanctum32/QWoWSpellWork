#include "DataStorage.hpp"
#include "DB2FileLoader.hpp"
#ifdef SPELLWORK_BUILD_SQL
#include "SQL/sqlConnection.hpp"
#endif // SPELLWORK_BUILD_SQL
#include "appSettings.hpp"

Q_LOGGING_CATEGORY(DataStores, "spellwork.dataStores");

template<typename T>
bool OpenAndReadDBC(std::string_view path, std::string_view dbcFileName, std::map<uint32_t, T>& storage)
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

template<typename T>
bool OpenAndReadDB2(std::string_view path, std::string_view db2FileName, std::map<uint32_t, T>& storage)
{
    DB2FileLoader db2File(std::string(path) + "//" + std::string(db2FileName), T::GetDB2Format());
    if (!db2File.IsLoaded())
    {
        return false;
    }

    for (uint32_t i = 0; i < db2File.GetNumRows(); ++i)
    {
        storage.emplace(db2File.getRecord(i).getUInt(0), db2File.getRecord(i));
    }

    return true;
}

bool DataStorage::LoadDBCData()
{
    if (!sSpellWorkConfig->GetAppConfig().loadDBCSpells && !sSpellWorkConfig->GetAppConfig().loadSQLSpells)
    {
        return false;
    }

    bool isDBCLoaded = true;
    bool isSQLLoaded = false;
    if (sSpellWorkConfig->GetAppConfig().loadDBCSpells)
    {
        isDBCLoaded = LoadDBCDatas();
    }

    if (sSpellWorkConfig->GetSQLConfig().enable && sSpellWorkConfig->GetAppConfig().loadSQLSpells)
    {
        isSQLLoaded = LoadSqlDBCData();;
    }

    if (!isDBCLoaded && !isSQLLoaded)
    {
        return false;
    }

    return true;
}

bool DataStorage::LoadDBCDatas()
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

bool DataStorage::LoadSqlDBCData()
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
        query << " FROM `spell_dbc` WHERE `Id` > 0";

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
            m_spellEntries.try_emplace(static_cast<uint32_t>(std::stoul(row[0])), row);
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
        query << " FROM `spelleffect_dbc` WHERE `Id` > 0";

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
            m_SpellEffectEntries.try_emplace(static_cast<uint32_t>(std::stoul(row[0])), row);
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

bool DataStorage::LoadDB2Datas()
{
    const auto& dbcFolderPath = sSpellWorkConfig->GetAppConfig().dbcFilePath;
    if (!OpenAndReadDB2(dbcFolderPath, "Item-sparse.db2", m_ItemSparseEntries))
    {
        return false;
    }

    return true;
}

void DataStorage::GenerateExtraDataInfo()
{
    for (auto& spellEffectItr : m_SpellEffectEntries)
    {
        auto& effectEntry = spellEffectItr.second;
        assert(effectEntry.getEffectIndex() < MAX_SPELL_EFFECTS);

        // link spell related pointers
        auto spellEntryItr = m_spellEntries.find(effectEntry.getSpellID());
        if (spellEntryItr != m_spellEntries.end())
        {
            spellEntryItr->second.m_spellEffects[effectEntry.getEffectIndex()] = &effectEntry;
        }

        // Generate effect extra details
        effectEntry.GenerateExtraInfo();
    }
}
