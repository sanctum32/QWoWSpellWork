#include "DataStorage.hpp"
#include "DB2FileLoader.hpp"
#include "JsonData.hpp"
#include "SharedDefines.hpp"
#include "appSettings.hpp"

Q_LOGGING_CATEGORY(DataStores, "spellwork.dataStores");
Q_LOGGING_CATEGORY(SQL, "spellwork.sql");

template<typename T>
bool OpenAndReadDBC(const QString& path, const QString& dbcFileName, std::map<uint32_t, T>& storage)
{
    DBCFileLoader dbcFile(path.toStdString() + "//" + dbcFileName.toStdString(), T::GetDBCFormat());
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
bool OpenAndReadDB2(const QString& path, const QString& db2FileName, std::map<uint32_t, T>& storage)
{
    DB2FileLoader db2File(path.toStdString() + "//" + db2FileName.toStdString(), T::GetDB2Format());
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

const SpellDifficultyEntry* DataStorage::GetSpellDifficultyByContainedEntry(uint32_t spellId) const
{
    // Database entries uses direct id for difficulty data
    auto itr = m_SpellDifficultyEntries.find(spellId);

    // continue search in dbc storage and find first entry which contains spell id
    if (itr == m_SpellDifficultyEntries.end())
    {
        itr = std::ranges::find_if(m_SpellDifficultyEntries, [spellId](const auto& diffItr)
        {
            for (const auto& diffSpellId : diffItr.second.DifficultySpellID)
            {
                if (diffSpellId == spellId)
                {
                    return true;
                }
            }

            return false;
        });
    }

    return itr != m_SpellDifficultyEntries.end() ? &itr->second : nullptr;
}

#ifdef SPELLWORK_BUILD_SQL
template<class T>
void LoadSQLData(const char* tableName, const char* query, T& container, const SQLSettings& sqlSettings, bool targetWorldDB)
{
    MYSQL* sqlConn = mysql_init(nullptr);
    if (sqlConn == nullptr)
    {
        qCDebug(SQL) << "Failed to initialize connection. Error: " << mysql_error(sqlConn);
        return;
    }

    if (mysql_real_connect(sqlConn,
                           sqlSettings.hostname.toStdString().c_str(),
                           sqlSettings.username.toStdString().c_str(),
                           sqlSettings.password.toStdString().c_str(),
                           targetWorldDB ? sqlSettings.worldDB.toStdString().c_str() : sqlSettings.hotfixDB.toStdString().c_str(),
                           sqlSettings.port,
                           nullptr, 0) == nullptr)
    {
        qCDebug(SQL) << "Failed to connect. Error: " << mysql_error(sqlConn);
        return;
    }

    if (mysql_query(sqlConn, query) != 0)
    {
        qCDebug(DataStores) << "failed to data from \"" << tableName << "\" SQL table. Error: " << mysql_error(sqlConn);
        return;
    }

    auto* result = mysql_store_result(sqlConn);
    if (result == nullptr)
    {
        qCDebug(DataStores) << "failed to data from \"" << tableName << "\" SQL table. Error: " << mysql_error(sqlConn);
        return;
    }

    uint32_t count = 0;
    while (auto row = mysql_fetch_row(result))
    {
        container.try_emplace(static_cast<uint32_t>(std::stoul(row[0])), row);
        ++count;
    }

    mysql_free_result(result);
    qCDebug(DataStores) << "Loaded " << count << " entries from SQL table \"" << tableName << "\"";
    mysql_close(sqlConn);
}

#endif // SPELLWORK_BUILD_SQL

void DataStorage::LoadDBC()
{
    const auto& dbcPath = sSpellWorkConfig->GetAppConfig().dbcFilePath;

    // Load essential dbc data
    OpenAndReadDBC(dbcPath, "SpellCategory.dbc",             m_SpellCategoryEntries);
    OpenAndReadDBC(dbcPath, "SpellCategories.dbc",           m_SpellCategories);
    OpenAndReadDBC(dbcPath, "SpellClassOptions.dbc",         m_SpellClassOptions);
    OpenAndReadDBC(dbcPath, "SpellTargetRestrictions.dbc",   m_SpellTargetRestrictions);
    OpenAndReadDBC(dbcPath, "SpellShapeshift.dbc",           m_SpellShapeshiftEntries);
    OpenAndReadDBC(dbcPath, "SkillLineAbility.dbc",          m_SkillLineAbilityEntries);
    OpenAndReadDBC(dbcPath, "SkillLine.dbc",                 m_SkillLineEntries);
    OpenAndReadDBC(dbcPath, "SkillLineAbility.dbc",          m_SkillLineAbilityEntries);
    OpenAndReadDBC(dbcPath, "SpellReagents.dbc",             m_SpellReagentsEntries);
    OpenAndReadDBC(dbcPath, "SpellLevels.dbc",               m_SpellLevelsEntries);
    OpenAndReadDBC(dbcPath, "SpellEquippedItems.dbc",        m_SpellEquippedItemsEntries);
    OpenAndReadDBC(dbcPath, "SpellRange.dbc",                m_SpellRangeEntries);
    OpenAndReadDBC(dbcPath, "SpellAuraOptions.dbc",          m_SpellAuraOptionsEntries);
    OpenAndReadDBC(dbcPath, "SpellCastTimes.dbc",            m_SpellCastTimesEntries);
    OpenAndReadDBC(dbcPath, "SpellCooldowns.dbc",            m_SpellCooldownsEntries);
    OpenAndReadDBC(dbcPath, "SpellDuration.dbc",             m_SpellDurationEntries);
    OpenAndReadDBC(dbcPath, "SpellPower.dbc",                m_SpellPowerEntries);
    OpenAndReadDBC(dbcPath, "SpellInterrupts.dbc",           m_SpellInterruptsEntries);
    OpenAndReadDBC(dbcPath, "SpellAuraRestrictions.dbc",     m_SpellAuraRestrictionsEntries);
    OpenAndReadDBC(dbcPath, "AreaGroup.dbc",                 m_AreaGroupEntries);
    OpenAndReadDBC(dbcPath, "AreaTable.dbc",                 m_AreaTableEntries);
    OpenAndReadDBC(dbcPath, "SpellCastingRequirements.dbc",  m_SpellCastingRequirementsEntries);
    OpenAndReadDBC(dbcPath, "gtSpellScaling.dbc",            m_GtSpellScalingEntries);
    OpenAndReadDBC(dbcPath, "gtNPCManaCostScaler.dbc",       m_GtNPCManaCostScalerEntries);
    OpenAndReadDBC(dbcPath, "OverrideSpellData.dbc",         m_OverrideSpellDataEntries);
    OpenAndReadDBC(dbcPath, "ScreenEffect.dbc",              m_ScreenEffectEntries);
    OpenAndReadDBC(dbcPath, "SpellRadius.dbc",               m_SpellRadiusEntries);
    OpenAndReadDBC(dbcPath, "Faction.dbc",                   m_FactionEntries);
    OpenAndReadDBC(dbcPath, "SpellScaling.dbc",              m_SpellScalingEntries);
    OpenAndReadDBC(dbcPath, "SummonProperties.dbc",          m_SummonPropertiesEntries);
    OpenAndReadDBC(dbcPath, "Spell.dbc",                     m_spellEntries);
    OpenAndReadDBC(dbcPath, "SpellEffect.dbc",               m_SpellEffectEntries);
    OpenAndReadDBC(dbcPath, "SpellDifficulty.dbc",           m_SpellDifficultyEntries);

#ifdef SPELLWORK_BUILD_SQL
    if (!sSpellWorkConfig->GetSQLConfig().enable)
    {
        return;
    }

    // Load spell_dbc
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

    LoadSQLData("spell_dbc", query.str().c_str(), m_spellEntries, sSpellWorkConfig->GetSQLConfig(), true);

    // Load spelleffect_dbc
    query.clear();
    query.str("");
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

    LoadSQLData("spelleffect_dbc", query.str().c_str(), m_spellEntries, sSpellWorkConfig->GetSQLConfig(), true);

    // Load spelldifficulty_dbc
    query.clear();
    query.str("");
    query << "SELECT ";
    query << "`id`, ";                   // 0
    query << "`spellid0`, ";             // 1
    query << "`spellid1`, ";             // 2
    query << "`spellid2`, ";             // 3
    query << "`spellid3` ";              // 4
    query << "FROM " << sSpellWorkConfig->GetSQLConfig().worldDB.toStdString() << ".`spelldifficulty_dbc`";

    LoadSQLData("spelldifficulty_dbc", query.str().c_str(), m_SpellDifficultyEntries, sSpellWorkConfig->GetSQLConfig(), true);

#endif //SPELLWORK_BUILD_SQL
}

void DataStorage::LoadDB2()
{
    const auto& dbcPath = sSpellWorkConfig->GetAppConfig().dbcFilePath;
    OpenAndReadDB2(dbcPath, "Item-sparse.db2", m_ItemSparseEntries);

#ifdef SPELLWORK_BUILD_SQL
    if (!sSpellWorkConfig->GetSQLConfig().enable)
    {
        return;
    }

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

    LoadSQLData("item_sparse", query.str().c_str(), m_ItemSparseEntries, sSpellWorkConfig->GetSQLConfig(), false);
#endif // SPELLWORK_BUILD_SQL
}

void DataStorage::GenerateExtraDataInfo()
{
    for (auto& spellEntry : m_spellEntries)
    {
        auto& spellInfo = spellEntry.second;
        spellInfo.m_scalingEntry = GetSpellScalingEntry(spellInfo.getSpellScalingId());
        spellInfo.m_spellCastingTimeEntry = GetSpellCastTimesEntry(spellInfo.getCastingTimeIndex());
        spellInfo.m_spellDurationEntry = GetSpellDurationEntry(spellInfo.getDurationIndex());
        spellInfo.m_spellRangeEntry = GetSpellRangeEntry(spellInfo.getRangeIndex());
        spellInfo.m_spellAuraOptionsEntry = GetSpellAuraOptionsEntry(spellInfo.getSpellAuraOptionsId());
        spellInfo.m_spellRestrictionsEntry = GetSpellAuraRestrictionsEntry(spellInfo.getSpellAuraRestrictionsId());
        spellInfo.m_spellCastingReqEntry = GetSpellCastingRequirementsEntry(spellInfo.getSpellCastingRequirementsId());
        spellInfo.m_spellCategoriesEntry = GetSpellCategoriesEntry(spellInfo.getSpellCategoriesId());
        spellInfo.m_spellClassOptionsEntry = GetSpellClassOptionsEntry(spellInfo.getSpellClassOptionsId());
        spellInfo.m_spellCooldownEntry = GetSpellCooldownsEntry(spellInfo.getSpellCooldownsId());
        spellInfo.m_spellEquipedItemsEntry = GetSpellEquippedItemsEntry(spellInfo.getSpellEquippedItemsId());
        spellInfo.m_spellInterruptsEntry = GetSpellInterruptsEntry(spellInfo.getSpellInterruptsId());
        spellInfo.m_spellLevelsEntry = GetSpellLevelsEntry(spellInfo.getSpellLevelsId());
        spellInfo.m_spellPowerEntry = GetSpellPowerEntry(spellInfo.getSpellPowerId());
        spellInfo.m_spellReagentsEntry = GetSpellReagentsEntry(spellInfo.getSpellReagentsId());
        spellInfo.m_spellShapeshiftEntry = GetSpellShapeshiftEntry(spellInfo.getSpellShapeshiftId());
        spellInfo.m_spellTargetRestrictionsEntry = GetSpellTargetRestrictionsEntry(spellInfo.getSpellTargetRestrictionsId());
        spellInfo.m_spellDifficultyEntry = GetSpellDifficultyByContainedEntry(spellInfo.getId());

        // Generate spell attributes string
        {
            bool lineAdded = false;
            for (uint8_t attributeId = 0; attributeId < MAX_SPELL_ATTRIBUTES; ++attributeId)
            {
                const uint32_t attributeMask = spellInfo.GetAttribute(attributeId);
                if (attributeMask == 0)
                {
                    continue;
                }

                if (!lineAdded)
                {
                    spellInfo.m_AttributesStr += printLine;
                    lineAdded = true;
                }

                QString attributeStr;
                for (uint8_t id = 0; id <= MAX_UINT32_BITMASK_INDEX; ++id)
                {
                    const uint32_t mask = 1u << id;
                    if ((mask & attributeMask) == 0)
                    {
                        continue;
                    }

                    if (!attributeStr.isEmpty())
                    {
                        attributeStr += ", ";
                    }

                    attributeStr += sSpellWorkJson->GetSpellAttributeName(attributeId, mask);
                }

                spellInfo.m_AttributesStr += QString("Attributes%1: %2<br><br>")
                    .arg(attributeId)
                    .arg(attributeStr);
            }
        }
    }

    for (auto& spellEffectItr : m_SpellEffectEntries)
    {
        auto& effectEntry = spellEffectItr.second;
        assert(effectEntry.getEffectIndex() < MAX_SPELL_EFFECTS);

        // link spell effect dbc pointers
        {
            auto spellEntryItr = m_spellEntries.find(effectEntry.getSpellID());
            if (spellEntryItr != m_spellEntries.end())
            {
                spellEntryItr->second.m_spellEffects[effectEntry.getEffectIndex()] = &effectEntry;
            }
        }
    }
}
