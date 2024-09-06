#include "DBCStructures.hpp"
#include "ValueComparition.hpp"

SpellEffectEntry::SpellEffectEntry(DBCFileLoader::Record const& record)
{
    uint8_t colId = 0;

    _getId() = record.getUInt(colId++);
    _getEffect() = record.getUInt(colId++);
    _getEffectAmplitude() = record.getFloat(colId++);
    _getEffectAura() = record.getUInt(colId++);
    _getEffectAuraPeriod() = record.getUInt(colId++);
    _getEffectBasePoints() = record.getInt(colId++);
    _getEffectBonusCoefficient() = record.getFloat(colId++);
    _getEffectChainAmplitude() = record.getFloat(colId++);
    _getEffectChainTargets() = record.getUInt(colId++);
    _getEffectDieSides() = record.getInt(colId++);
    _getEffectItemType() = record.getUInt(colId++);
    _getEffectMechanic() = record.getUInt(colId++);
    _getEffectMiscValue() = record.getInt(colId++);
    _getEffectMiscValueB() = record.getInt(colId++);
    _getEffectPointsPerResource() = record.getFloat(colId++);
    _getEffectRadiusIndex() = record.getUInt(colId++);
    _getEffectRadiusMaxIndex() = record.getUInt(colId++);
    _getEffectRealPointsPerLevel() = record.getFloat(colId++);
    _getEffectSpellClassMaskA() = record.getUInt(colId++);
    _getEffectSpellClassMaskB() = record.getUInt(colId++);
    _getEffectSpellClassMaskC() = record.getUInt(colId++);

    _getEffectTriggerSpell() = record.getUInt(colId++);
    _getEffectImplicitTargetA() = record.getUInt(colId++);
    _getEffectImplicitTargetB() = record.getUInt(colId++);
    _getSpellID() = record.getUInt(colId++);
    _getEffectIndex() = record.getUInt(colId++);
    _getEffectAttributes() = record.getUInt(colId++);
}

SpellEffectEntry::SpellEffectEntry(const MYSQL_ROW& row)
{
    _getId() = std::stoul(row[0]);
    _getEffect() = std::stoul(row[1]);
    _getEffectAmplitude() = std::atof(row[2]);
    _getEffectAura() = std::stoul(row[3]);
    _getEffectAuraPeriod() = std::stoul(row[4]);
    _getEffectBasePoints() = std::stoi(row[5]);
    _getEffectBonusCoefficient() = std::atof(row[6]);
    _getEffectChainAmplitude() = std::atof(row[7]);
    _getEffectChainTargets() = std::stoul(row[8]);
    _getEffectDieSides() = std::stoi(row[9]);
    _getEffectItemType() = std::stoul(row[10]);
    _getEffectMechanic() = std::stoul(row[11]);
    _getEffectMiscValue() = std::stoi(row[12]);
    _getEffectMiscValueB() = std::stoi(row[13]);
    _getEffectPointsPerResource() = std::atof(row[14]);
    _getEffectRadiusIndex() = std::stoul(row[15]);
    _getEffectRadiusMaxIndex() = std::stoul(row[16]);
    _getEffectRealPointsPerLevel() = std::atof(row[17]);
    _getEffectSpellClassMaskA() = std::stoul(row[18]);
    _getEffectSpellClassMaskB() = std::stoul(row[19]);
    _getEffectSpellClassMaskC() = std::stoul(row[20]);
    _getEffectTriggerSpell() = std::stoul(row[21]);
    _getEffectImplicitTargetA() = std::stoul(row[22]);
    _getEffectImplicitTargetB() = std::stoul(row[23]);
    _getSpellID() = std::stoul(row[24]);
    _getEffectIndex() = std::stoul(row[25]);
}

SpellCategoryEntry::SpellCategoryEntry(DBCFileLoader::Record const& record)
{
    Id = record.getUInt(0);
    //Flags = record.getUInt(1);
    //UsesPerWeek = record.getUInt(2);
    Name = QString::fromStdString(record.getString(3));
}

SpellCategoriesEntry::SpellCategoriesEntry(DBCFileLoader::Record const& record)
{
    Id                          = record.getUInt(0);
    Category                    = record.getUInt(1);
    DefenseType                 = record.getUInt(2);
    DispelType                  = record.getUInt(3);
    Mechanic                    = record.getUInt(4);
    PreventionType              = record.getUInt(5);
    //StartRecoveryCategory       = record.getUInt(6);
}

SpellClassOptionsEntry::SpellClassOptionsEntry(DBCFileLoader::Record const& record)
{
    Id                  = record.getUInt(0);
    modalNextSpell      = record.getUInt(1);
    SpellFamilyFlags[0] = record.getUInt(2);
    SpellFamilyFlags[1] = record.getUInt(3);
    SpellFamilyFlags[2] = record.getUInt(4);
    SpellFamilyName     = record.getUInt(5);
    //Description         = record.getString(6);
}

SpellTargetRestrictionsEntry::SpellTargetRestrictionsEntry(DBCFileLoader::Record const& record)
{
    Id                  = record.getUInt(0);
    ConeAngle           = record.getFloat(1);
    MaxAffectedTargets  = record.getUInt(2);
    MaxTargetLevel      = record.getUInt(3);
    TargetCreatureType  = record.getUInt(4);
    Targets             = record.getUInt(5);
}

SpellShapeshiftEntry::SpellShapeshiftEntry(DBCFileLoader::Record const& record)
{
    uint8_t colId = 0;
    Id                  = record.getUInt(colId++);

    for (auto& mask : ShapeshiftMask)
    {
        mask = record.getUInt(colId++);
    }

    for (auto& excludeMask : ShapeshiftExclude)
    {
        excludeMask = record.getUInt(colId++);
    }
}

SkillLineAbilityEntry::SkillLineAbilityEntry(DBCFileLoader::Record const& record)
{
    Id                          = record.getUInt(0);
    SkillLine                   = record.getUInt(1);
    Spell                       = record.getUInt(2);
    //RaceMask                   = record.getUInt(3);
    //ClassMask                  = record.getUInt(4);
    //ExcludeRace                = record.getUInt(5);
    //ExcludeClass               = record.getUInt(6);
    MinSkillLineRank            = record.getUInt(7);
    SupercededBySpell           = record.getUInt(8);
    //AcquireMethod            = record.getUInt(9);
    TrivialSkillLineRankHigh    = record.getUInt(10);
    TrivialSkillLineRankLow     = record.getUInt(11);
    NumSkillUps                 = record.getUInt(12);
    //UniqueBit                   = record.getUInt(13);
}

SkillLineEntry::SkillLineEntry(DBCFileLoader::Record const& record)
{
    Id                  = record.getUInt(0);
    //categoryId          = record.getInt(1);
    name                = QString::fromStdString(record.getString(2));
    //description         = record.getString(3);
    //spellIcon           = record.getUInt(4);
    //alternateVerb       = record.getString(5);
    //canLink             = record.getUInt(6);
}

SpellReagentsEntry::SpellReagentsEntry(DBCFileLoader::Record const& record)
{
    uint8_t id = 0;
    Id = record.getUInt(id++);
    for (int32_t& regent : Reagent)
    {
        regent = record.getInt(id++);
    }

    for (uint32_t& regentAmount : ReagentCount)
    {
        regentAmount = record.getUInt(id++);
    }
}

SpellLevelsEntry::SpellLevelsEntry(DBCFileLoader::Record const& record)
{
    Id          = record.getUInt(0);
    baseLevel   = record.getUInt(1);
    maxLevel    = record.getUInt(2);
    spellLevel  = record.getUInt(3);
}

SpellEquippedItemsEntry::SpellEquippedItemsEntry(DBCFileLoader::Record const& record)
{
    Id                                      = record.getUInt(0);
    EquippedItemClass                       = record.getUInt(1);
    EquippedItemInventoryTypeMask           = record.getInt(2);
    EquippedItemSubClassMask                = record.getInt(3);
}

SpellRangeEntry::SpellRangeEntry(DBCFileLoader::Record const& record)
{
    Id                  = record.getUInt(0);
    minRangeHostile     = record.getFloat(1);
    minRangeFriend      = record.getFloat(2);
    maxRangeHostile     = record.getFloat(3);
    maxRangeFriend      = record.getFloat(4);
    //type                = record.getUInt(5);
    Name                = QString::fromStdString(record.getString(6));
    //ShortName           = record.getString(7);
}

SpellAuraOptionsEntry::SpellAuraOptionsEntry(DBCFileLoader::Record const& record)
{
    Id                  = record.getUInt(0);
    StackAmount         = record.getUInt(1);
    procChance          = record.getUInt(2);
    procCharges         = record.getUInt(3);
    procFlags           = record.getUInt(4);
}

SpellCastTimesEntry::SpellCastTimesEntry(DBCFileLoader::Record const& record)
{
    Id                  = record.getUInt(0);
    CastTime            = record.getInt(1);
    CastTimePerLevel    = record.getFloat(2);
    MinCastTime         = record.getInt(3);
}

SpellCooldownsEntry::SpellCooldownsEntry(DBCFileLoader::Record const& record)
{
    Id                      = record.getUInt(0);
    CategoryRecoveryTime    = record.getUInt(1);
    RecoveryTime            = record.getUInt(2);
    StartRecoveryTime       = record.getUInt(3);
}

SpellDurationEntry::SpellDurationEntry(DBCFileLoader::Record const& record)
{
    Id              = record.getUInt(0);
    Duration[0]     = record.getInt(1);
    Duration[1]     = record.getInt(2);
    Duration[2]     = record.getInt(3);
}

SpellPowerEntry::SpellPowerEntry(DBCFileLoader::Record const& record)
{
    Id                              = record.getUInt(0);
    manaCost                        = record.getUInt(1);
    manaCostPerlevel                = record.getUInt(2);
    ManaCostPercentage              = record.getUInt(3);
    //manaPerSecond                   = record.getUInt(4);
    manaPerSecondPerLevel           = record.getUInt(5);
    //PowerDisplayId                  = record.getUInt(6);
    //ManaCostPercentageFloat         = record.getFloat(7);
}

SpellInterruptsEntry::SpellInterruptsEntry(DBCFileLoader::Record const& record)
{
    Id                              = record.getUInt(0);
    AuraInterruptFlags[0]           = record.getUInt(1);
    AuraInterruptFlags[1]           = record.getUInt(2);
    ChannelInterruptFlags[0]        = record.getUInt(3);
    ChannelInterruptFlags[1]        = record.getUInt(4);
    InterruptFlags                  = record.getUInt(5);
}

SpellAuraRestrictionsEntry::SpellAuraRestrictionsEntry(DBCFileLoader::Record const& record)
{
    Id                      = record.getUInt(0);
    CasterAuraState         = record.getUInt(1);
    TargetAuraState         = record.getUInt(2);
    CasterAuraStateNot      = record.getUInt(3);
    TargetAuraStateNot      = record.getUInt(4);
    casterAuraSpell         = record.getUInt(5);
    targetAuraSpell         = record.getUInt(6);
    excludeCasterAuraSpell  = record.getUInt(7);
    excludeTargetAuraSpell  = record.getUInt(8);
}

AreaGroupEntry::AreaGroupEntry(DBCFileLoader::Record const& record)
{
    uint8_t i = 0;
    Id = record.getUInt(i++);
    for (uint32_t& areaId : AreaId)
    {
        areaId = record.getUInt(i++);
    }

    nextGroup = record.getUInt(i++);
}

AreaTableEntry::AreaTableEntry(DBCFileLoader::Record const& record)
{
    Id                  = record.getUInt(0);
    ContinentID         = record.getUInt(1);
    //ParentAreaID        = record.getUInt(2);
    //AreaBit             = record.getUInt(3);
    //Flags               = record.getUInt(4);
    //SoundProviderPref   = record.getUInt(5);
    //SoundProviderPrefUnderwater = record.getUInt(6);
    //AmbienceID          = record.getUInt(7);
    //ZoneMusic           = record.getUInt(8);
    //IntroSound          = record.getUInt(9);
    //ExplorationLevel    = record.getUInt(10);
    AreaName            = QString::fromStdString(record.getString(11));
    //FactionGroupMask    = record.getUInt(12);
    //LiquidTypeID[0]     = record.getUInt(13);
    //LiquidTypeID[0]     = record.getUInt(14);
    //LiquidTypeID[0]     = record.getUInt(15);
    //LiquidTypeID[0]     = record.getUInt(16);
    //MinElevation        = record.getFloat(17);
    //AmbientMultiplier   = record.getFloat(18);
    //LightID             = record.getUInt(19);
    //MountFlags          = record.getUInt(20);
    //UwIntroSound        = record.getUInt(21);
    //UwZoneMusic         = record.getUInt(22);
    //UwAmbience          = record.getUInt(23);
    //World_pvp_ID        = record.getUInt(24);
    //PvpCombatWorldStateID = record.getInt(25);
}

SpellCastingRequirementsEntry::SpellCastingRequirementsEntry(DBCFileLoader::Record const& record)
{
    Id                  = record.getUInt(0);
    //FacingCasterFlags   = record.getUInt(1);
    //MinFactionID        = record.getUInt(2);
    //MinReputation       = record.getUInt(3);
    RequiredAreasID     = record.getInt(4);
    //RequiredAuraVision  = record.getUInt(5);
    RequiresSpellFocus  = record.getUInt(6);
}

SpellScalingEntry::SpellScalingEntry(DBCFileLoader::Record const& record)
{
    uint8_t id = 0;
    Id                      = record.getUInt(id++);
    CastTimeMin             = record.getInt(id++);
    CastTimeMax             = record.getInt(id++);
    CastTimeMaxLevel        = record.getInt(id++);
    Class                   = record.getInt(id++);

    for (float& multiplier : Coefficient)
    {
        multiplier = record.getFloat(id++);
    }

    for (float& multiplier : Variance)
    {
        multiplier = record.getFloat(id++);
    }

    for (float& multiplier : ComboPointsCoefficient)
    {
        multiplier = record.getFloat(id++);
    }

    NerfFactor                = record.getFloat(id++);
    NerfMaxLevel              = record.getInt(id++);
}

GtSpellScalingEntry::GtSpellScalingEntry(DBCFileLoader::Record const& record)
{
    Id = record.getUInt(0);
    value = record.getFloat(1);
}

OverrideSpellDataEntry::OverrideSpellDataEntry(DBCFileLoader::Record const& record)
{
    uint8_t colId = 0;
    Id = record.getUInt(colId++);
    for (int32_t& _spellId : Spells)
    {
        _spellId = record.getInt(colId++);
    }

    //unk0 = record.getUInt(colId++);
    //SpellBarName = record.getString(colId++);
}

ScreenEffectEntry::ScreenEffectEntry(DBCFileLoader::Record const& record)
{
    Id = record.getUInt(0);
    Name = QString::fromStdString(record.getString(1));
    /*
    Unk0 = record.getUInt(2);
    Unk1 = record.getFloat(3);
    Unk2 = record.getUInt(4);
    Unk3 = record.getUInt(5);
    Unk4 = record.getUInt(6);
    Unk5 = record.getInt(7);
    Unk6 = record.getUInt(8);
    Unk7 = record.getUInt(9);
    Unk8 = record.getInt(10);
    */
}

SpellRadiusEntry::SpellRadiusEntry(DBCFileLoader::Record const& record)
{
    Id = record.getUInt(0);
    RadiusMin = record.getFloat(1);
    RadiusPerLevel = record.getFloat(2);
    RadiusMax = record.getFloat(3);
}

SpellEntry::SpellEntry(DBCFileLoader::Record const& record)
{
    _getID()                    = record.getUInt(0);
    _getAttribute0()            = record.getUInt(1);
    _getAttribute1()            = record.getUInt(2);
    _getAttribute2()            = record.getUInt(3);
    _getAttribute3()            = record.getUInt(4);
    _getAttribute4()            = record.getUInt(5);
    _getAttribute5()            = record.getUInt(6);
    _getAttribute6()            = record.getUInt(7);
    _getAttribute7()            = record.getUInt(8);
    _getAttribute8()            = record.getUInt(9);
    _getAttribute9()            = record.getUInt(10);
    _getAttribute9()            = record.getUInt(11);
    _getCastingTimeIndex()      = record.getUInt(12);
    _getDurationIndex()         = record.getUInt(13);
    _getPowerType()             = record.getUInt(14);
    _getRangeIndex()            = record.getUInt(15);
    _getSpeed()                 = record.getFloat(16);
    _getSpellVisual1()          = record.getUInt(17);
    _getSpellVisual1()          = record.getUInt(18);
    _getSpellIconID()                 = record.getUInt(19);
    _getActiveIconID()                = record.getUInt(20);
    _getSpellName()                   = record.getString(21);
    _getRank()                        = record.getString(22);
    _getDescription()                 = record.getString(23);
    _getToolTip()                     = record.getString(24);
    _getSchoolMask()                  = record.getUInt(25);
    //_getRuneCostID()                  = record.getUInt(26);
    //_getSpellMissileID()              = record.getUInt(27);
    //_getSpellDescriptionVariableID()  = record.getUInt(28);
    //_getSpellDifficultyId()           = record.getUInt(29);
    //_getSpellCoef()                   = record.getFloat(30);
    _getSpellScalingId()              = record.getUInt(31);
    _getSpellAuraOptionsId()          = record.getUInt(32);
    _getSpellAuraRestrictionsId()     = record.getUInt(33);
    _getSpellCastingRequirementsId()  = record.getUInt(34);
    _getSpellCategoriesId()           = record.getUInt(35);
    _getSpellClassOptionsId()         = record.getUInt(36);
    _getSpellCooldownsId()            = record.getUInt(37);
    //_getUnkIndex7()                   = record.getUInt(38);
    _getSpellEquippedItemsId()        = record.getUInt(39);
    _getSpellInterruptsId()           = record.getUInt(40);
    _getSpellLevelsId()               = record.getUInt(41);
    _getSpellPowerId()                = record.getUInt(42);
    _getSpellReagentsId()             = record.getUInt(43);
    _getSpellShapeshiftId()           = record.getUInt(44);
    _getSpellTargetRestrictionsId()   = record.getUInt(45);
    //SpellTotemsId()               = record.getUInt(46);
    _getResearchProject()             = record.getUInt(47);

    if (getDescription().isEmpty())
    {
        _getDescription() = "-- No description --";
    }
}

SpellEntry::SpellEntry(const MYSQL_ROW& row)
{
    m_IsServerSide = true;
    _getID() = static_cast<uint32_t>(std::stoul(row[0]));
    _getAttribute0() = static_cast<uint32_t>(std::stoul(row[1]));
    _getAttribute1() = static_cast<uint32_t>(std::stoul(row[2]));
    _getAttribute2() = static_cast<uint32_t>(std::stoul(row[3]));
    _getAttribute3() = static_cast<uint32_t>(std::stoul(row[4]));
    _getAttribute4() = static_cast<uint32_t>(std::stoul(row[5]));
    _getAttribute5() = static_cast<uint32_t>(std::stoul(row[6]));
    _getAttribute6() = static_cast<uint32_t>(std::stoul(row[7]));
    _getAttribute7() = static_cast<uint32_t>(std::stoul(row[8]));
    _getAttribute8() = static_cast<uint32_t>(std::stoul(row[9]));
    _getAttribute9() = static_cast<uint32_t>(std::stoul(row[10]));
    _getAttribute10() = static_cast<uint32_t>(std::stoul(row[11]));

    _getCastingTimeIndex()      = static_cast<uint32_t>(std::stoul(row[12]));
    _getDurationIndex()         = static_cast<uint32_t>(std::stoul(row[13]));
    _getRangeIndex()            = static_cast<uint32_t>(std::stoul(row[14]));
    _getSchoolMask()            = static_cast<uint32_t>(std::stoul(row[15]));
    _getSpellAuraOptionsId()    = static_cast<uint32_t>(std::stoul(row[16]));
    _getSpellCastingRequirementsId() = static_cast<uint32_t>(std::stoul(row[17]));
    _getSpellCategoriesId()     = static_cast<uint32_t>(std::stoul(row[18]));
    _getSpellClassOptionsId()   = static_cast<uint32_t>(std::stoul(row[19]));
    _getSpellEquippedItemsId()  = static_cast<uint32_t>(std::stoul(row[20]));
    _getSpellInterruptsId()     = static_cast<uint32_t>(std::stoul(row[21]));
    _getSpellLevelsId()         = static_cast<uint32_t>(std::stoul(row[22]));
    _getSpellTargetRestrictionsId() = static_cast<uint32_t>(std::stoul(row[23]));
    _getSpellName()             = row[24];
    _getSpellName().textVal += " - Server Side";

    _fields[0] = static_cast<uint32_t>(std::stoul(row[0])); // Id

    // 1 - 11
    for (uint8_t i = 0; i < MAX_SPELL_ATTRIBUTES; ++i)
    {
        _fields[1 + i] = static_cast<uint32_t>(atoi(row[1 + i]));
    }
}

FactionEntry::FactionEntry(DBCFileLoader::Record const& record)
{

    Id                  = record.getUInt(0);
    //ReputationIndex     = record.getInt(1);

    //2 - 5
    //for (uint8_t i = 0; i < 4; ++i)
    //{
    //    ReputationRaceMask[2 + i] = record.getUInt(2 + i);
    //    ++i;
    //}

    // 6 - 9
    //for (uint8_t i = 0; i < 4; ++i)
    //{
    //    ReputationClassMask[i] = record.getUInt(6 + i);
    //}

    // 10 - 13
    //for (uint8_t i = 0; i < 4; ++i)
    //{
    //    ReputationBase[i] = record.getInt(10 + i);
    //}

    // 14 - 17
    //for (uint8_t i = 0; i < 4; ++i)
    //{
    //    ReputationFlags[i] = record.getUInt(14 + i);
    //}

    //ParentFactionID = record.getUInt(18);

    // 19 - 20
    //for (uint8_t i = 0; i < 2; ++i)
    //{
    //    ParentFactionMod[i] = record.getFloat(19 + i);
    //}

    // 21 - 22
    //for (uint8_t i = 0; i < 2; ++i)
    //{
    //    ParentFactionCap[i] = record.getUInt(21 + i);
    //}

    Name = QString::fromStdString(record.getString(23));
    //Description = record.getString(24);
    //Expansion = record.getUInt(25);
}

const std::map<uint8_t /*fieldId*/, DBCFieldAttrInfo /*info*/> SpellEntryFields =
{
    {0, {"Id", CompareTypes::UnsignedNumber }},
    {1, {"Attributes", CompareTypes::UnsignedNumber}},
    {2, {"AttributesEx", CompareTypes::UnsignedNumber}},
    {3, {"AttributesEx2", CompareTypes::UnsignedNumber}},
    {4, {"AttributesEx3", CompareTypes::UnsignedNumber}},
    {5, {"AttributesEx4", CompareTypes::UnsignedNumber}},
    {6, {"AttributesEx5", CompareTypes::UnsignedNumber}},
    {7, {"AttributesEx6", CompareTypes::UnsignedNumber}},
    {8, {"AttributesEx7", CompareTypes::UnsignedNumber}},
    {9, {"AttributesEx8", CompareTypes::UnsignedNumber}},
    {10, {"AttributesEx9", CompareTypes::UnsignedNumber}},
    {11, {"AttributesEx10", CompareTypes::UnsignedNumber}},
    {12, {"CastingTimeIndex", CompareTypes::UnsignedNumber}},
    {13, {"DurationIndex", CompareTypes::UnsignedNumber}},
    {14, {"powerType", CompareTypes::SignedNumber}},
    {15, {"rangeIndex", CompareTypes::UnsignedNumber}},
    {16, {"speed", CompareTypes::Float}},
    {17, {"SpellVisual1", CompareTypes::UnsignedNumber}},
    {18, {"SpellVisual2", CompareTypes::UnsignedNumber}},
    {19, {"SpellIconID", CompareTypes::UnsignedNumber}},
    {20, {"ActiveIconID", CompareTypes::UnsignedNumber}},
    {21, {"SpellName", CompareTypes::String}},
    {22, {"Rank", CompareTypes::String}},
    {23, {"Description", CompareTypes::String}},
    {24, {"ToolTip", CompareTypes::String}},
    {25, {"SchoolMask", CompareTypes::UnsignedNumber}},
    //{26, {"runeCostID", CompareTypes::Numeric}},
    //{27, {"spellMissileID", CompareTypes::Numeric}},
    //{28, {"spellDescriptionVariableID", CompareTypes::Numeric}},
    //{29, {"SpellDifficultyId", CompareTypes::Numeric}},
    //{30, {"SpellCoef", CompareTypes::Float}},
    {31, {"SpellScalingId", CompareTypes::UnsignedNumber}},
    {32, {"SpellAuraOptionsId", CompareTypes::UnsignedNumber}},
    {33, {"SpellAuraRestrictionsId", CompareTypes::UnsignedNumber}},
    {34, {"SpellCastingRequirementsId", CompareTypes::UnsignedNumber}},
    {35, {"SpellCategoriesId", CompareTypes::UnsignedNumber}},
    {36, {"SpellClassOptionsId", CompareTypes::UnsignedNumber}},
    {37, {"SpellCooldownsId", CompareTypes::UnsignedNumber}},
    //{38, {"unkIndex7", CompareTypes::Numeric}}
    {39, {"SpellEquippedItemsId", CompareTypes::UnsignedNumber}},
    {40, {"SpellInterruptsId", CompareTypes::UnsignedNumber}},
    {41, {"SpellLevelsId", CompareTypes::UnsignedNumber}},
    {42, {"SpellPowerId", CompareTypes::UnsignedNumber}},
    {43, {"SpellReagentsId", CompareTypes::UnsignedNumber}},
    {44, {"SpellShapeshiftId", CompareTypes::UnsignedNumber}},
    {45, {"SpellTargetRestrictionsId", CompareTypes::UnsignedNumber}},
    {46, {"SpellTotemsId", CompareTypes::UnsignedNumber}},
    {47, {"ResearchProject", CompareTypes::UnsignedNumber}}
};

const std::map<uint8_t /*fieldId*/, DBCFieldAttrInfo /*info*/> SpellEffectEntryFields =
{
    {0, {"Id", CompareTypes::UnsignedNumber}},
    {1, {"Effect", CompareTypes::UnsignedNumber}},
    {2, {"EffectAmplitude", CompareTypes::Float}},
    {3, {"EffectAura", CompareTypes::UnsignedNumber}},
    {4, {"EffectAuraPeriod", CompareTypes::UnsignedNumber}},
    {5, {"EffectBasePoints", CompareTypes::SignedNumber}},
    {6, {"EffectBonusCoefficient", CompareTypes::Float}},
    {7, {"EffectChainAmplitude", CompareTypes::Float}},
    {8, {"EffectChainTargets", CompareTypes::UnsignedNumber}},
    {9, {"EffectDieSides", CompareTypes::SignedNumber}},
    {10, {"EffectItemType", CompareTypes::UnsignedNumber}},
    {11, {"EffectMechanic", CompareTypes::UnsignedNumber}},
    {12, {"EffectMiscValue", CompareTypes::SignedNumber}},
    {13, {"EffectMiscValueB", CompareTypes::SignedNumber}},
    {14, {"EffectPointsPerResource", CompareTypes::Float}},
    {15, {"EffectRadiusIndex", CompareTypes::UnsignedNumber}},
    {16, {"EffectRadiusMaxIndex", CompareTypes::UnsignedNumber}},
    {17, {"EffectRealPointsPerLevel", CompareTypes::Float}},
    {18, {"EffectSpellClassMaskA", CompareTypes::UnsignedNumber}},
    {19, {"EffectSpellClassMaskB", CompareTypes::UnsignedNumber}},
    {20, {"EffectSpellClassMaskC", CompareTypes::UnsignedNumber}},
    {21, {"EffectTriggerSpell", CompareTypes::UnsignedNumber}},
    {22, {"EffectImplicitTargetA", CompareTypes::UnsignedNumber}},
    {23, {"EffectImplicitTargetB", CompareTypes::UnsignedNumber}},
    {24, {"SpellID", CompareTypes::UnsignedNumber}},
    {25, {"EffectIndex", CompareTypes::UnsignedNumber}},
    {26, {"EffectAttributes", CompareTypes::UnsignedNumber}}
};
