#include "DBCStructures.hpp"
#include <iostream>

SpellEffectEntry::SpellEffectEntry(DBCFileLoader::Record const& record)
{
    uint8_t id = 0;

    Id                          = record.getUInt(id++);
    Effect                      = record.getUInt(id++);
    EffectAmplitude             = record.getFloat(id++);
    EffectAura                  = record.getUInt(id++);
    EffectAuraPeriod            = record.getUInt(id++);
    EffectBasePoints            = record.getInt(id++);
    EffectBonusCoefficient      = record.getFloat(id++);
    EffectChainAmplitude        = record.getFloat(id++);
    EffectChainTargets          = record.getUInt(id++);
    EffectDieSides              = record.getInt(id++);
    EffectItemType              = record.getUInt(id++);
    EffectMechanic              = record.getUInt(id++);
    EffectMiscValue             = record.getInt(id++);
    EffectMiscValueB            = record.getInt(id++);
    EffectPointsPerResource     = record.getFloat(id++);
    EffectRadiusIndex           = record.getUInt(id++);
    EffectRadiusMaxIndex        = record.getUInt(id++);
    EffectRealPointsPerLevel    = record.getFloat(id++);

    for (uint32_t& classMask : EffectSpellClassMask)
    {
        classMask = record.getUInt(id++);
    }

    EffectTriggerSpell          = record.getUInt(id++);
    EffectImplicitTargetA       = record.getUInt(id++);
    EffectImplicitTargetB       = record.getUInt(id++);
    SpellID                     = record.getUInt(id++);
    EffectIndex                 = record.getUInt(id++);
    EffectAttributes            = record.getUInt(id++);
}

SpellCategoryEntry::SpellCategoryEntry(DBCFileLoader::Record const& record)
{
    Id = record.getUInt(0);
    Flags = record.getUInt(1);
    UsesPerWeek = record.getUInt(2);
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
    StartRecoveryCategory       = record.getUInt(6);
}

SpellClassOptionsEntry::SpellClassOptionsEntry(DBCFileLoader::Record const& record)
{
    Id                  = record.getUInt(0);
    modalNextSpell      = record.getUInt(1);
    SpellFamilyFlags[0] = record.getUInt(2);
    SpellFamilyFlags[1] = record.getUInt(3);
    SpellFamilyFlags[2] = record.getUInt(4);
    SpellFamilyName     = record.getUInt(5);
    Description         = record.getString(6);
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
    Id                  = record.getUInt(0);
    StancesNot          = record.getUInt(1);
    unk_320_2           = record.getUInt(2);
    Stances             = record.getUInt(3);
    unk_320_3           = record.getUInt(4);
    StanceBarOrder      = record.getUInt(5);
}

SkillLineAbilityEntry::SkillLineAbilityEntry(DBCFileLoader::Record const& record)
{
    id                  = record.getUInt(0);
    skillId             = record.getUInt(1);
    spellId             = record.getUInt(2);
    racemask            = record.getUInt(3);
    classmask           = record.getUInt(4);
    racemaskNot         = record.getUInt(5);
    classmaskNot        = record.getUInt(6);
    req_skill_value     = record.getUInt(7);
    forward_spellid     = record.getUInt(8);
    learnOnGetSkill     = record.getUInt(9);
    max_value           = record.getUInt(10);
    min_value           = record.getUInt(11);
    character_points[0] = record.getUInt(12);
    character_points[1] = record.getUInt(13);
}

SkillLineEntry::SkillLineEntry(DBCFileLoader::Record const& record)
{
    id                  = record.getUInt(0);
    categoryId          = record.getInt(1);
    name                = record.getString(2);
    description         = record.getString(3);
    spellIcon           = record.getUInt(4);
    alternateVerb       = record.getString(5);
    canLink             = record.getUInt(6);
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
    type                = record.getUInt(5);
    Name                = record.getString(6);
    ShortName           = record.getString(7);
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
    manaPerSecond                   = record.getUInt(4);
    manaPerSecondPerLevel           = record.getUInt(5);
    PowerDisplayId                  = record.getUInt(6);
    ManaCostPercentageFloat         = record.getFloat(7);
}

SpellInterruptsEntry::SpellInterruptsEntry(DBCFileLoader::Record const& record)
{
    Id                              = record.getUInt(0);
    AuraInterruptFlags              = record.getUInt(1);
    unk3                            = record.getUInt(2);
    ChannelInterruptFlags           = record.getUInt(3);
    unk5                            = record.getUInt(4);
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
    ID = record.getUInt(0);
    mapid = record.getUInt(1);
    zone = record.getUInt(2);
    exploreFlag = record.getUInt(3);
    flags = record.getUInt(4);
    unk5 = record.getUInt(5);
    unk6 = record.getUInt(6);
    unk7 = record.getUInt(7);
    unk8 = record.getUInt(8);
    unk9 = record.getUInt(9);
    area_level = record.getInt(10);
    area_name = record.getString(11);
    team = record.getUInt(12);

    LiquidTypeOverride[0] = record.getUInt(13);
    LiquidTypeOverride[1] = record.getUInt(14);
    LiquidTypeOverride[2] = record.getUInt(15);
    LiquidTypeOverride[3] = record.getUInt(16);

    MaxDepth = record.getFloat(17);
    AmbientMultiplier = record.getFloat(18);
    LightId = record.getUInt(19);
    unk20 = record.getUInt(20);
    unk21 = record.getUInt(21);
    unk22 = record.getUInt(22);
    unk23 = record.getUInt(23);
    unk24 = record.getUInt(24);
    unk25 = record.getUInt(25);
}

SpellCastingRequirementsEntry::SpellCastingRequirementsEntry(DBCFileLoader::Record const& record)
{
    Id                      = record.getUInt(0);
    FacingCasterFlags       = record.getUInt(1);
    MinFactionId            = record.getUInt(2);
    MinReputation           = record.getUInt(3);
    AreaGroupId             = record.getInt(4);
    RequiredAuraVision      = record.getUInt(5);
    RequiresSpellFocus      = record.getUInt(6);
}

SpellScalingEntry::SpellScalingEntry(DBCFileLoader::Record const& record)
{
    uint8_t id = 0;
    Id                      = record.getUInt(id++);
    CastTimeMin             = record.getInt(id++);
    CastTimeMax             = record.getInt(id++);
    CastTimeMaxLevel        = record.getInt(id++);
    ScalingClass            = record.getInt(id++);

    for (float& multiplier : Coefficient)
    {
        multiplier = record.getFloat(id++);
    }

    for (float& multiplier : RandomMultiplier)
    {
        multiplier = record.getFloat(id++);
    }

    for (float& multiplier : OtherMultiplier)
    {
        multiplier = record.getFloat(id++);
    }

    CoefBase                = record.getFloat(id++);
    CoefLevelBase           = record.getInt(id++);
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
    for (int32_t& _spellId : spellId)
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
    Unk0 = record.getUInt(2);
    Unk1 = record.getFloat(3);
    Unk2 = record.getUInt(4);
    Unk3 = record.getUInt(5);
    Unk4 = record.getUInt(6);
    Unk5 = record.getInt(7);
    Unk6 = record.getUInt(8);
    Unk7 = record.getUInt(9);
    Unk8 = record.getInt(10);
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
    uint8_t id = 0;
    Id                          = record.getUInt(id++);

    for (uint32_t& attribute : Attributes)
        attribute = record.getUInt(id++);

    CastingTimeIndex            = record.getUInt(id++);
    DurationIndex               = record.getUInt(id++);
    powerType                   = record.getUInt(id++);
    rangeIndex                  = record.getUInt(id++);
    speed                       = record.getFloat(id++);
    SpellVisual1                = record.getUInt(id++);
    SpellVisual2                = record.getUInt(id++);
    SpellIconID                 = record.getUInt(id++);
    activeIconID                = record.getUInt(id++);

    SpellName                   = record.getString(id++);
    _spellName = QString(SpellName.c_str()).toUpper();

    Rank                        = record.getString(id++);
    Description                 = record.getString(id++);

    if (Description.empty() || Description.size() <= 1)
    {
        Description = "-- No description --";
    }

    ToolTip                     = record.getString(id++);
    SchoolMask                  = record.getUInt(id++);
    runeCostID                  = record.getUInt(id++);
    spellMissileID              = record.getUInt(id++);
    spellDescriptionVariableID  = record.getUInt(id++);
    SpellDifficultyId           = record.getUInt(id++);
    SpellCoef                   = record.getFloat(id++);
    SpellScalingId              = record.getUInt(id++);
    SpellAuraOptionsId          = record.getUInt(id++);
    SpellAuraRestrictionsId     = record.getUInt(id++);
    SpellCastingRequirementsId  = record.getUInt(id++);
    SpellCategoriesId           = record.getUInt(id++);
    SpellClassOptionsId         = record.getUInt(id++);
    SpellCooldownsId            = record.getUInt(id++);
    unkIndex7                   = record.getUInt(id++);
    SpellEquippedItemsId        = record.getUInt(id++);
    SpellInterruptsId           = record.getUInt(id++);
    SpellLevelsId               = record.getUInt(id++);
    SpellPowerId                = record.getUInt(id++);
    SpellReagentsId             = record.getUInt(id++);
    SpellShapeshiftId           = record.getUInt(id++);
    SpellTargetRestrictionsId   = record.getUInt(id++);
    SpellTotemsId               = record.getUInt(id++);
    ResearchProject             = record.getUInt(id++);
}

FactionEntry::FactionEntry(DBCFileLoader::Record const& record)
{
    uint8_t i = 0;
    Id                  = record.getUInt(i++);
    ReputationIndex     = record.getInt(i++);

    for (auto& val : ReputationRaceMask)
    {
        val = record.getUInt(i++);
    }

    for (auto& val : ReputationClassMask)
    {
        val = record.getUInt(i++);
    }

    for (auto& val : ReputationBase)
    {
        val = record.getInt(i++);
    }

    for (auto& val : ReputationFlags)
    {
        val = record.getUInt(i++);
    }

    ParentFactionID = record.getUInt(i++);

    for (auto& val : ParentFactionMod)
    {
        val = record.getFloat(i++);
    }

    for (auto& val : ParentFactionCap)
    {
        val = record.getUInt(i++);
    }

    Name = record.getString(i++);
    Description = record.getString(i++);
    Expansion = record.getUInt(i++);
}
