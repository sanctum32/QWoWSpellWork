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
        !OpenAndReadDBC(dbcFolderPath, "gtNPCManaCostScaler.dbc",       m_GtNPCManaCostScalerEntries) ||
        !OpenAndReadDBC(dbcFolderPath, "OverrideSpellData.dbc",         m_OverrideSpellDataEntries) ||
        !OpenAndReadDBC(dbcFolderPath, "ScreenEffect.dbc",              m_ScreenEffectEntries) ||
        !OpenAndReadDBC(dbcFolderPath, "SpellRadius.dbc",               m_SpellRadiusEntries) ||
        !OpenAndReadDBC(dbcFolderPath, "Faction.dbc",                   m_FactionEntries) ||
        !OpenAndReadDBC(dbcFolderPath, "SpellScaling.dbc",              m_SpellScalingEntries) ||
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
        query << " FROM " << sSpellWorkConfig->GetSQLConfig().worldDB.toStdString() << ".`spell_dbc` WHERE `Id` > 0";

        if (mysql_query(connection, query.str().c_str()) != 0)
        {
            qCDebug(DataStores) << "DataStores::LoadSqlDBCData: failed to execute spell_dbc query. Error: " << mysql_error(connection);
            return false;
        }

        auto* result = mysql_store_result(connection);
        if (result == nullptr)
        {
            qCDebug(DataStores) << "DataStores::LoadSqlDBCData: failed to fetch result data from spell_dbc query; Error: " << mysql_error(connection);
            return false;
        }

        uint32_t count = 0;
        while (auto row = mysql_fetch_row(result))
        {
            m_spellEntries.try_emplace(static_cast<uint32_t>(std::stoul(row[0])), row);
            ++count;
        }

        mysql_free_result(result);

        qCDebug(DataStores) << "DataStores::LoadSqlDBCData: loaded " << count << " entries from spell_dbc";
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
        query << " FROM " << sSpellWorkConfig->GetSQLConfig().worldDB.toStdString() << ".`spelleffect_dbc` WHERE `Id` > 0";

        if (mysql_query(connection, query.str().c_str()) != 0)
        {
            qCDebug(DataStores) << "DataStores::LoadSqlDBCData: failed to execute spelleffect_dbc query. Error: " << mysql_error(connection);
            return false;
        }

        auto* result = mysql_store_result(connection);
        if (result == nullptr)
        {
            qCDebug(DataStores) << "DataStores::LoadSqlDBCData: failed to fetch result data from spell_dbc query; Error: " << mysql_error(connection);
            return false;
        }

        uint32_t count = 0;
        while (auto row = mysql_fetch_row(result))
        {
            m_SpellEffectEntries.try_emplace(static_cast<uint32_t>(std::stoul(row[0])), row);
            ++count;
        }
        mysql_free_result(result);

        qCDebug(DataStores) << "DataStores::LoadSqlDBCData: loaded " << count << " entries from spelleffect_dbc";
    }
    return true;
#else
    return true;
#endif // SPELLWORK_BUILD_SQL
}

void DataStorage::LoadSqlDB2Data()
{
#ifdef SPELLWORK_BUILD_SQL
    auto* connection = sSpellWorkSQL->GetConnection();
    if (connection == nullptr)
    {
        return;
    }

    {
        std::stringstream query;
        query << "SELECT "
        /*<< "ID, "                           // 0
        << "Quality, "                      // 1
        << "Flags1, "                       // 2
        << "Flags2, "                       // 3
        << "PriceRandomValue, "             // 4
        << "PriceVariance, "                // 5
        << "BuyCount, "                     // 6
        << "BuyPrice, "                     // 7
        << "SellPrice, "                    // 8
        << "InventoryType, "                // 9
        << "AllowableClass, "               // 10
        << "AllowableRace, "                // 11
        << "ItemLevel, "                    // 12
        << "RequiredLevel, "                // 13
        << "RequiredSkill, "                // 14
        << "RequiredSkillRank, "            // 15
        << "RequiredSpell, "                // 16
        << "RequiredHonorRank, "            // 17
        << "RequiredCityRank, "             // 18
        << "RequiredReputationFaction, "    // 19
        << "RequiredReputationRank, "       // 20
        << "MaxCount, "                     // 21
        << "Stackable, "                    // 22
        << "ContainerSlots, "               // 23
        << "ItemStatType1, "                // 24
        << "ItemStatType2, "                // 25
        << "ItemStatType3, "                // 26
        << "ItemStatType4, "                // 27
        << "ItemStatType5, "                // 28
        << "ItemStatType6, "                // 29
        << "ItemStatType7, "                // 30
        << "ItemStatType8, "                // 31
        << "ItemStatType9, "                // 32
        << "ItemStatType10, "               // 33
        << "ItemStatValue1, "               // 34
        << "ItemStatValue2, "               // 35
        << "ItemStatValue3, "               // 36
        << "ItemStatValue4, "               // 37
        << "ItemStatValue5, "               // 38
        << "ItemStatValue6, "               // 39
        << "ItemStatValue7, "               // 40
        << "ItemStatValue8, "               // 41
        << "ItemStatValue9, "               // 42
        << "ItemStatValue10, "              // 43
        << "ItemStatAllocation1, "          // 44
        << "ItemStatAllocation2, "          // 45
        << "ItemStatAllocation3, "          // 46
        << "ItemStatAllocation4, "          // 47
        << "ItemStatAllocation5, "          // 48
        << "ItemStatAllocation6, "          // 49
        << "ItemStatAllocation7, "          // 50
        << "ItemStatAllocation8, "          // 51
        << "ItemStatAllocation9, "          // 52
        << "ItemStatAllocation10, "         // 53
        << "ItemStatSocketCostMultiplier1, "    // 54
        << "ItemStatSocketCostMultiplier2, "    // 55
        << "ItemStatSocketCostMultiplier3, "    // 56
        << "ItemStatSocketCostMultiplier4, "    // 57
        << "ItemStatSocketCostMultiplier5, "    // 58
        << "ItemStatSocketCostMultiplier6, "    // 59
        << "ItemStatSocketCostMultiplier7, "    // 60
        << "ItemStatSocketCostMultiplier8, "    // 61
        << "ItemStatSocketCostMultiplier9, "    // 62
        << "ItemStatSocketCostMultiplier10, "   // 63
        << "ScalingStatDistribution, "      // 64
        << "DamageType, "                   // 65
        << "Delay, "                        // 66
        << "RangedModRange, "               // 67
        << "SpellID1, "                     // 68
        << "SpellID2, "                     // 69
        << "SpellID3, "                     // 70
        << "SpellID4, "                     // 71
        << "SpellID5, "                     // 72
        << "SpellTrigger1, "                // 73
        << "SpellTrigger2, "                // 74
        << "SpellTrigger3, "                // 75
        << "SpellTrigger4, "                // 76
        << "SpellTrigger5, "                // 77
        << "SpellCharges1, "                // 78
        << "SpellCharges2, "                // 79
        << "SpellCharges3, "                // 80
        << "SpellCharges4, "                // 81
        << "SpellCharges5, "                // 82
        << "SpellCooldown1, "               // 83
        << "SpellCooldown2, "               // 84
        << "SpellCooldown3, "               // 85
        << "SpellCooldown4, "               // 86
        << "SpellCooldown5, "               // 87
        << "SpellCategory1, "               // 88
        << "SpellCategory2, "               // 89
        << "SpellCategory3, "               // 90
        << "SpellCategory4, "               // 91
        << "SpellCategory5, "               // 92
        << "SpellCategoryCooldown1, "       // 93
        << "SpellCategoryCooldown2, "       // 94
        << "SpellCategoryCooldown3, "       // 95
        << "SpellCategoryCooldown4, "       // 96
        << "SpellCategoryCooldown5, "       // 97
        << "Bonding, "                      // 98
        << "Display, "                      // 99
        << "Display1, "                     // 100
        << "Display2, "                     // 101
        << "Display3, "                     // 102
        << "Description, "                  // 103
        << "PageText, "                     // 104
        << "LanguageID, "                   // 105
        << "PageMaterial, "                 // 106
        << "StartQuest, "                   // 107
        << "LockID, "                       // 108
        << "Material, "                     // 109
        << "SheatheType, "                  // 110
        << "RandomProperty, "               // 111
        << "RandomSuffix, "                 // 112
        << "ItemSet, "                      // 113
        << "AreaID, "                       // 114
        << "MapID, "                        // 115
        << "BagFamily, "                    // 116
        << "TotemCategory, "                // 117
        << "SocketColor1, "                 // 118
        << "SocketColor2, "                 // 119
        << "SocketColor3, "                 // 120
        << "Content1, "                     // 121
        << "Content2, "                     // 122
        << "Content3, "                     // 123
        << "SocketBonus, "                  // 124
        << "GemProperties, "                // 125
        << "ArmorDamageModifier, "          // 126
        << "Duration, "                     // 127
        << "ItemLimitCategory, "            // 128
        << "HolidayID, "                    // 129
        << "StatScalingFactor, "            // 130
        << "CurrencySubstitutionID, "       // 131
        << "CurrencySubstitutionCount"      // 132
        */
        << "ID, "    // 0
        << "Display" // 1
        << " FROM " << sSpellWorkConfig->GetSQLConfig().hotfixDB.toStdString() << ".`item_sparse` WHERE `ID` > 0";

        if (mysql_query(connection, query.str().c_str()) != 0)
        {
            qCDebug(DataStores) << "DataStores::LoadSqlDB2Data: failed to execute query on table \"item_sparse\". Error: " << mysql_error(connection);
            return;
        }

        auto* result = mysql_store_result(connection);
        if (result == nullptr)
        {
            qCDebug(DataStores) << "DataStores::LoadSqlDB2Data: failed to fetch result data from table \"item_sparse\" query; Error: " << mysql_error(connection);
            return;
        }

        uint32_t count = 0;
        while (auto row = mysql_fetch_row(result))
        {
            m_ItemSparseEntries.try_emplace(static_cast<uint32_t>(std::stoul(row[0])), row);
            ++count;
        }
        mysql_free_result(result);

        qCDebug(DataStores) << "DataStores::LoadSqlDB2Data: loaded " << count << " entries from \"item_sparse\" table";
    }
    return;
#endif // SPELLWORK_BUILD_SQL
}

bool DataStorage::LoadDB2Datas()
{
    const auto& dbcFolderPath = sSpellWorkConfig->GetAppConfig().dbcFilePath;
    if (!(OpenAndReadDB2(dbcFolderPath, "Item-sparse.db2", m_ItemSparseEntries)))
    {
        return false;
    }

    LoadSqlDB2Data();
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
