#include "DBCStructures.hpp"

SpellEffectEntry::SpellEffectEntry(DBCFileLoader::Record const& record)
{
    uint8_t colId = 0;

    Id                          = record.getUInt(colId++);
    Effect                      = record.getUInt(colId++);
    EffectAmplitude             = record.getFloat(colId++);
    EffectAura                  = record.getUInt(colId++);
    EffectAuraPeriod            = record.getUInt(colId++);
    EffectBasePoints            = record.getInt(colId++);
    EffectBonusCoefficient      = record.getFloat(colId++);
    EffectChainAmplitude        = record.getFloat(colId++);
    EffectChainTargets          = record.getUInt(colId++);
    EffectDieSides              = record.getInt(colId++);
    EffectItemType              = record.getUInt(colId++);
    EffectMechanic              = record.getUInt(colId++);
    EffectMiscValue             = record.getInt(colId++);
    EffectMiscValueB            = record.getInt(colId++);
    EffectPointsPerResource     = record.getFloat(colId++);
    EffectRadiusIndex           = record.getUInt(colId++);
    EffectRadiusMaxIndex        = record.getUInt(colId++);
    EffectRealPointsPerLevel    = record.getFloat(colId++);

    for (auto& classMask : EffectSpellClassMask)
    {
        classMask = record.getUInt(colId++);
    }

    EffectTriggerSpell          = record.getUInt(colId++);
    EffectImplicitTargetA       = record.getUInt(colId++);
    EffectImplicitTargetB       = record.getUInt(colId++);
    SpellID                     = record.getUInt(colId++);
    EffectIndex                 = record.getUInt(colId++);
    //EffectAttributes            = record.getUInt(id++);
}

SpellCategoryEntry::SpellCategoryEntry(DBCFileLoader::Record const& record)
{
    Id = record.getUInt(0);
    //Flags = record.getUInt(1);
    //UsesPerWeek = record.getUInt(2);
    Name = record.getString(3);
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
    id                          = record.getUInt(0);
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
    id                  = record.getUInt(0);
    //categoryId          = record.getInt(1);
    name                = record.getString(2);
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
    ID                  = record.getUInt(0);
    minRangeHostile     = record.getFloat(1);
    minRangeFriend      = record.getFloat(2);
    maxRangeHostile     = record.getFloat(3);
    maxRangeFriend      = record.getFloat(4);
    //type                = record.getUInt(5);
    Name                = record.getString(6);
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
    ID                  = record.getUInt(0);
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
    ID              = record.getUInt(0);
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
    AreaGroupId = record.getUInt(i++);
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
    AreaName            = record.getString(11);
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
    Name = record.getString(1);
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
    Id                          = record.getUInt(0);

    // 1 - 11
    for (uint8_t i = 0; i < 11; ++i)
    {
        Attributes[i] = record.getUInt(1 + i);
    }

    CastingTimeIndex            = record.getUInt(12);
    DurationIndex               = record.getUInt(13);
    powerType                   = record.getUInt(14);
    rangeIndex                  = record.getUInt(15);
    speed                       = record.getFloat(16);

    // 17 - 18
    for (uint8_t i = 0; i < 2; ++i)
    {
        SpellVisual[i] = record.getUInt(17 + i);
    }

    SpellIconID                 = record.getUInt(19);
    ActiveIconID                = record.getUInt(20);
    SpellName                   = record.getString(21);
    Rank                        = record.getString(22);
    Description                 = record.getString(23);
    ToolTip                     = record.getString(24);
    SchoolMask                  = record.getUInt(25);
    //runeCostID                  = record.getUInt(26);
    //spellMissileID              = record.getUInt(27);
    //spellDescriptionVariableID  = record.getUInt(28);
    //SpellDifficultyId           = record.getUInt(29);
    //SpellCoef                   = record.getFloat(30);
    SpellScalingId              = record.getUInt(31);
    SpellAuraOptionsId          = record.getUInt(32);
    SpellAuraRestrictionsId     = record.getUInt(33);
    SpellCastingRequirementsId  = record.getUInt(34);
    SpellCategoriesId           = record.getUInt(35);
    SpellClassOptionsId         = record.getUInt(36);
    SpellCooldownsId            = record.getUInt(37);
    //unkIndex7                   = record.getUInt(38);
    SpellEquippedItemsId        = record.getUInt(39);
    SpellInterruptsId           = record.getUInt(40);
    SpellLevelsId               = record.getUInt(41);
    SpellPowerId                = record.getUInt(42);
    SpellReagentsId             = record.getUInt(43);
    SpellShapeshiftId           = record.getUInt(44);
    SpellTargetRestrictionsId   = record.getUInt(45);
    //SpellTotemsId               = record.getUInt(46);
    //ResearchProject             = record.getUInt(47);

    if (Description.empty() || Description.size() <= 1)
    {
        Description = "-- No description --";
    }

    m_spellNameUpper = QString(SpellName.c_str()).toUpper();
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

    Name = record.getString(23);
    //Description = record.getString(24);
    //Expansion = record.getUInt(25);
}
