#pragma once

#include "DBCFileLoader.hpp"
#include "../Enums/SpellEnums.hpp"
#include <QString>
#include <qdebug.h>

// SpellEffect.dbc
struct SpellEffectEntry
{
    SpellEffectEntry() = default;
    explicit SpellEffectEntry(DBCFileLoader::Record const& record);

    uint32_t    Id{};                                           // 0
    uint32_t    Effect{};                                       // 1
    float       EffectAmplitude{};                              // 2
    uint32_t    EffectAura{};                                   // 3
    uint32_t    EffectAuraPeriod{};                             // 4
    int32_t     EffectBasePoints{};                             // 5
    float       EffectBonusCoefficient{};                       // 6
    float       EffectChainAmplitude{};                         // 7
    uint32_t    EffectChainTargets{};                           // 8
    int32_t     EffectDieSides{};                               // 9
    uint32_t    EffectItemType{};                               // 10
    uint32_t    EffectMechanic{};                               // 11
    int32_t     EffectMiscValue{};                              // 12
    int32_t     EffectMiscValueB{};                             // 13
    float       EffectPointsPerResource{};                      // 14
    uint32_t    EffectRadiusIndex{};                            // 15
    uint32_t    EffectRadiusMaxIndex{};                         // 16
    float       EffectRealPointsPerLevel{};                     // 17
    std::array<uint32_t, 3> EffectSpellClassMask{};             // 18 - 20
    uint32_t    EffectTriggerSpell{};                           // 21
    uint32_t    EffectImplicitTargetA{};                        // 22
    uint32_t    EffectImplicitTargetB{};                        // 23
    uint32_t    SpellID{};                                      // 24
    uint32_t    EffectIndex{};                                  // 25
    //uint32_t    EffectAttributes{};                             // 26

    inline bool HasSpellClassMask() const { return std::any_of(EffectSpellClassMask.begin(), EffectSpellClassMask.end(), [](uint32_t val) { return val != 0; }); }
    static char const* GetDBCFormat()
    {
        return "iifiiiffiiiiiifiifiiiiiiiix";
    }

    // Generates extra effect details by given format
    std::shared_ptr<QString> GenerateExtraDetails(const QString& format) const;
};

// SpellCategory.dbc
struct SpellCategoryEntry
{
    SpellCategoryEntry() = default;
    explicit SpellCategoryEntry(DBCFileLoader::Record const& record);

    uint32_t Id{};                                              // 0
    //uint32_t Flags{};                                           // 1
    //uint32_t UsesPerWeek{};                                     // 2
    std::string Name;                                           // 3

    static char const* GetDBCFormat()
    {
        return "ixxs";
    }
};

// SpellCategories.dbc
struct SpellCategoriesEntry
{
    SpellCategoriesEntry() = default;
    explicit SpellCategoriesEntry(DBCFileLoader::Record const& record);

    uint32_t    Id{};                                           // 0        m_ID
    uint32_t    Category{};                                     // 1        m_category
    uint32_t    DefenseType{};                                  // 2      m_defenseType
    uint32_t    DispelType{};                                   // 3        m_dispelType
    uint32_t    Mechanic{};                                     // 4        m_mechanic
    uint32_t    PreventionType{};                               // 5      m_preventionType
    //uint32_t    StartRecoveryCategory{};                        // 6      m_startRecoveryCategory

    static char const* GetDBCFormat()
    {
        return "iiiiiix";
    }
};

// SpellClassOptions.dbc
struct SpellClassOptionsEntry
{
    SpellClassOptionsEntry() = default;
    explicit SpellClassOptionsEntry(DBCFileLoader::Record const& record);

    uint32_t    Id{};                                         // 0       m_ID
    uint32_t    modalNextSpell{};                             // 1       m_modalNextSpell not used
    std::array<uint32_t, 3> SpellFamilyFlags{};               // 2-4
    uint32_t    SpellFamilyName{};                            // 5       m_spellClassSet
    //std::string     Description;                            // 6       4.0.0

    static char const* GetDBCFormat()
    {
        return "iiiiix";
    }
};

// SpellTargetRestrictions.dbc
struct SpellTargetRestrictionsEntry
{
    SpellTargetRestrictionsEntry() = default;
    explicit SpellTargetRestrictionsEntry(DBCFileLoader::Record const& record);

    uint32_t    Id{};                                           // 0        m_ID
    float       ConeAngle{};                                    // 1
    uint32_t    MaxAffectedTargets{};                           // 2        m_maxTargets
    uint32_t    MaxTargetLevel{};                               // 3        m_maxTargetLevel
    uint32_t    TargetCreatureType{};                           // 4       m_targetCreatureType
    uint32_t    Targets{};                                      // 5       m_targets

    static char const* GetDBCFormat()
    {
        return "ifiiii";
    }
};

// SpellShapeshift.dbc
struct SpellShapeshiftEntry
{
    SpellShapeshiftEntry() = default;
    explicit SpellShapeshiftEntry(DBCFileLoader::Record const& record);

    uint32_t    Id{};                                           // 0 - m_ID
    std::array<uint32_t, 2> ShapeshiftExclude{};                // 1 - 2
    std::array<uint32_t, 2> ShapeshiftMask{};                   // 3 - 4
    //uint32_t    StanceBarOrder{};                               // 5 - m_stanceBarOrder not used

    static char const* GetDBCFormat()
    {
        return "iiiiii";
    }
};

// SkillLineAbility.dbc
struct SkillLineAbilityEntry
{
    SkillLineAbilityEntry() = default;
    explicit SkillLineAbilityEntry(DBCFileLoader::Record const& record);

    uint32_t    id{};                                           // 0        m_ID
    uint32_t    skillId{};                                      // 1        m_skillLine
    uint32_t    spellId{};                                      // 2        m_spell
    //uint32_t    racemask{};                                     // 3        m_raceMask
    //uint32_t    classmask{};                                    // 4        m_classMask
    //uint32_t    racemaskNot{};                                  // 5        m_excludeRace
    //uint32_t    classmaskNot{};                                 // 6        m_excludeClass
    uint32_t    req_skill_value{};                              // 7        m_minSkillLineRank
    uint32_t    forward_spellid{};                              // 8        m_supercededBySpell
    //uint32_t    learnOnGetSkill{};                              // 9        m_acquireMethod
    uint32_t    max_value{};                                    // 10       m_trivialSkillLineRankHigh
    uint32_t    min_value{};                                    // 11       m_trivialSkillLineRankLow
    std::array<uint32_t, 2> character_points{};                 // 12-13    m_characterPoints

    static char const* GetDBCFormat()
    {
        return "iiixxxxiixiiii";
    }
};

// SkillLine.dbc
struct SkillLineEntry
{
    SkillLineEntry() = default;
    explicit SkillLineEntry(DBCFileLoader::Record const& record);

    uint32_t    id{};                                           // 0        m_ID
    //int32_t     categoryId{};                                   // 1        m_categoryID
    std::string name;                                           // 3        m_displayName_lang
    //std::string description;                                    // 4        m_description_lang
    //uint32_t    spellIcon{};                                    // 5        m_spellIconID
    //std::string alternateVerb;                                  // 6        m_alternateVerb_lang
    //uint32_t    canLink{};                                      // 7        m_canLink (prof. with recipes)

    static char const* GetDBCFormat()
    {
        return "ixsxxxx";
    }
};

// SpellReagents.dbc
struct SpellReagentsEntry
{
    SpellReagentsEntry() = default;
    explicit SpellReagentsEntry(DBCFileLoader::Record const& record);

    uint32_t    Id{};                                           // 0        m_ID
    std::array<int32_t, MAX_SPELL_REAGENTS> Reagent{};          // 54-61    m_reagent
    std::array<uint32_t, MAX_SPELL_REAGENTS> ReagentCount{};    // 62-69    m_reagentCount

    static char const* GetDBCFormat()
    {
        return "iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii";
    }
};

// SpellLevels.dbc
struct SpellLevelsEntry
{
    SpellLevelsEntry() = default;
    explicit SpellLevelsEntry(DBCFileLoader::Record const& record);

    uint32_t    Id{};                                           // 0        m_ID
    uint32_t    baseLevel{};                                    // 1       m_baseLevel
    uint32_t    maxLevel{};                                     // 2       m_maxLevel
    uint32_t    spellLevel{};                                   // 3       m_spellLevel

    static char const* GetDBCFormat()
    {
        return "iiii";
    }
};

// SpellEquippedItems.dbc
struct SpellEquippedItemsEntry
{
    SpellEquippedItemsEntry() = default;
    explicit SpellEquippedItemsEntry(DBCFileLoader::Record const& record);

    uint32_t    Id{};                                           // 0        m_ID
    int32_t     EquippedItemClass{};                            // 70       m_equippedItemClass (value)
    int32_t     EquippedItemInventoryTypeMask{};                // 72       m_equippedItemInvTypes (mask)
    int32_t     EquippedItemSubClassMask{};                     // 71       m_equippedItemSubclass (mask)

    static char const* GetDBCFormat()
    {
        return "iiii";
    }
};

// SpellRange.dbc
struct SpellRangeEntry
{
    SpellRangeEntry() = default;
    explicit SpellRangeEntry(DBCFileLoader::Record const& record);

    uint32_t  ID{};
    float     minRangeHostile{};
    float     minRangeFriend{};
    float     maxRangeHostile{};
    float     maxRangeFriend{};                               //friend means unattackable unit here
    //uint32_t  type{};
    std::string   Name;                                         // 6-21     m_displayName_lang
    //std::string   ShortName;                                    // 23-38    m_displayNameShort_lang

    static char const* GetDBCFormat()
    {
        return "iffffxsx";
    }
};

// SpellAuraOptions.dbc
struct SpellAuraOptionsEntry
{
    SpellAuraOptionsEntry() = default;
    explicit SpellAuraOptionsEntry(DBCFileLoader::Record const& record);

    uint32_t    Id{};                                           // 0       m_ID
    uint32_t    StackAmount{};                                  // 1       m_cumulativeAura
    uint32_t    procChance{};                                   // 2       m_procChance
    uint32_t    procCharges{};                                  // 3       m_procCharges
    uint32_t    procFlags{};                                    // 4       m_procTypeMask

    static char const* GetDBCFormat()
    {
        return "iiiii";
    }
};

// SpellCastTimes.dbc
struct SpellCastTimesEntry
{
    SpellCastTimesEntry() = default;
    explicit SpellCastTimesEntry(DBCFileLoader::Record const& record);

    uint32_t    ID{};                                         // 0
    int32_t     CastTime{};                                   // 1
    float       CastTimePerLevel{};                           // 2 unsure / per skill?
    int32_t     MinCastTime{};                                // 3 unsure

    static char const* GetDBCFormat()
    {
        return "iifi";
    }
};

// SpellCooldowns.dbc
struct SpellCooldownsEntry
{
    SpellCooldownsEntry() = default;
    explicit SpellCooldownsEntry(DBCFileLoader::Record const& record);

    uint32_t    Id{};                                           // 0        m_ID
    uint32_t    CategoryRecoveryTime{};                         // 1       m_categoryRecoveryTime
    uint32_t    RecoveryTime{};                                 // 2       m_recoveryTime
    uint32_t    StartRecoveryTime{};                            // 3      m_startRecoveryTime

    static char const* GetDBCFormat()
    {
        return "iiii";
    }
};

// SpellDuration.dbc
struct SpellDurationEntry
{
    SpellDurationEntry() = default;
    explicit SpellDurationEntry(DBCFileLoader::Record const& record);

    uint32_t    ID{};                   // 0
    std::array<int32_t, 3> Duration{};  // 1 - 3

    static char const* GetDBCFormat()
    {
        return "iiii";
    }
};

// SpellPower.dbc
struct SpellPowerEntry
{
    SpellPowerEntry() = default;
    explicit SpellPowerEntry(DBCFileLoader::Record const& record);

    uint32_t    Id{};                                           // 0        m_ID
    uint32_t    manaCost{};                                     // 1       m_manaCost
    uint32_t    manaCostPerlevel{};                             // 2       m_manaCostPerLevel
    uint32_t    ManaCostPercentage{};                           // 3       m_manaCostPct
    //uint32_t    manaPerSecond{};                                // 4       m_manaPerSecond
    uint32_t    manaPerSecondPerLevel{};                        // 5       m_manaPerSecondPerLevel
    //uint32_t    PowerDisplayId{};                               // 6       m_powerDisplayID - id from PowerDisplay.dbc, new in 3.1
    //float       ManaCostPercentageFloat{};                      // 7       4.3.0

    static char const* GetDBCFormat()
    {
        return "iiiixixx";
    }
};

// SpellInterrupts.dbc
struct SpellInterruptsEntry
{
    SpellInterruptsEntry() = default;
    explicit SpellInterruptsEntry(DBCFileLoader::Record const& record);

    uint32_t    Id{};                                           // 0        m_ID
    std::array<uint32_t, 2> AuraInterruptFlags{};               // 1 - 2       m_auraInterruptFlags
    std::array<uint32_t, 2> ChannelInterruptFlags{};            // 3 - 4       m_channelInterruptFlags
    uint32_t    InterruptFlags{};                               // 5       m_interruptFlags

    static char const* GetDBCFormat()
    {
        return "iiiiii";
    }
};

// SpellAuraRestrictions.dbc
struct SpellAuraRestrictionsEntry
{
    SpellAuraRestrictionsEntry() = default;
    explicit SpellAuraRestrictionsEntry(DBCFileLoader::Record const& record);

    uint32_t    Id{};                                           // 0        m_ID
    uint32_t    CasterAuraState{};                              // 1       m_casterAuraState
    uint32_t    TargetAuraState{};                              // 2       m_targetAuraState
    uint32_t    CasterAuraStateNot{};                           // 3       m_excludeCasterAuraState
    uint32_t    TargetAuraStateNot{};                           // 4       m_excludeTargetAuraState
    uint32_t    casterAuraSpell{};                              // 5       m_casterAuraSpell
    uint32_t    targetAuraSpell{};                              // 6       m_targetAuraSpell
    uint32_t    excludeCasterAuraSpell{};                       // 7       m_excludeCasterAuraSpell
    uint32_t    excludeTargetAuraSpell{};                       // 8       m_excludeTargetAuraSpell

    static char const* GetDBCFormat()
    {
        return "iiiiiiiii";
    }
};

// AreaGroup.dbc
struct AreaGroupEntry
{
    AreaGroupEntry() = default;
    explicit AreaGroupEntry(DBCFileLoader::Record const& record);

    uint32_t  AreaGroupId{};                                    // 0
    std::array<uint32_t, MAX_GROUP_AREA_IDS> AreaId{};          // 1-6
    uint32_t  nextGroup{};                                      // 7 index of next group

    static char const* GetDBCFormat()
    {
        return "iiiiiiii";
    }
};

// AreaTable.dbc
struct AreaTableEntry
{
    AreaTableEntry() = default;
    explicit AreaTableEntry(DBCFileLoader::Record const& record);

    uint32_t Id{};                                              // 0
    uint32_t ContinentID{};                                     // 1
    //uint32_t ParentAreaID{};                                    // 2 if 0 then it's zone, else it's zone id of this area
    //uint32_t AreaBit{};                                         // 3
    //uint32_t Flags{};                                           // 4
    //uint32_t SoundProviderPref{};                               // 5
    //uint32_t SoundProviderPrefUnderwater{};                     // 6
    //uint32_t AmbienceID{};                                      // 7
    //uint32_t ZoneMusic{};                                       // 8
    //uint32_t IntroSound{};                                      // 9
    //uint32_t ExplorationLevel{};                                // 10
    std::string AreaName{};                                     // 11
    //uint32_t FactionGroupMask{};                                // 12
    //std::array<uint32_t, 4> LiquidTypeID{};                     // 13-16 liquid override by type
    //float MinElevation{};                                       // 17
    //float AmbientMultiplier{};                                  // 18 client only?
    //uint32_t LightID{};                                         // 19
    //uint32_t MountFlags{};                                      // 20
    //uint32_t UwIntroSound{};                                    // 21 4.0.0
    //uint32_t UwZoneMusic{};                                     // 22 4.0.0
    //uint32_t UwAmbience{};                                      // 23 4.0.0
    //uint32_t World_pvp_ID{};                                    // 24
    //int32_t PvpCombatWorldStateID{};                            // 25- worldStateId

    static char const* GetDBCFormat()
    {
        return "iixxxxxxxxxsxxxxxxxxxxxxxx";
    }
};

// SpellCastingRequirements.dbc
struct SpellCastingRequirementsEntry
{
    SpellCastingRequirementsEntry() = default;
    explicit SpellCastingRequirementsEntry(DBCFileLoader::Record const& record);

    uint32_t Id{};                                             // 0
    //uint32_t FacingCasterFlags{};                            // 1
    //uint32_t MinFactionID{};                                 // 2
    //uint32_t MinReputation{};                                // 3
    int32_t  RequiredAreasID{};                                // 4
    //uint32_t RequiredAuraVision{};                           // 5
    uint32_t RequiresSpellFocus{};                             // 6

    static char const* GetDBCFormat()
    {
        return "ixxxixi";
    }
};

// SpellScaling.dbc
struct SpellScalingEntry
{
    SpellScalingEntry() = default;
    explicit SpellScalingEntry(DBCFileLoader::Record const& record);

    uint32_t    Id{};                                           // 0        m_ID
    int32_t     CastTimeMin{};                                  // 1
    int32_t     CastTimeMax{};                                  // 2
    int32_t     CastTimeMaxLevel{};                             // 3
    int32_t     Class{};                                        // 4        (index * 100) + charLevel - 1 => gtSpellScaling.dbc
    std::array<float, 3> Coefficient{};                         // 5-7
    std::array<float, 3> Variance{};                            // 8-10
    std::array<float, 3> ComboPointsCoefficient{};              // 11-13
    float       NerfFactor{};                                   // 14        some coefficient, mostly 1.0f
    int32_t     NerfMaxLevel{};                                 // 15        some level

    static char const* GetDBCFormat()
    {
        return "iiiiiffffffffffi";
    }
};

// gtSpellScaling.dbc
struct GtSpellScalingEntry
{
    GtSpellScalingEntry() = default;
    explicit GtSpellScalingEntry(DBCFileLoader::Record const& record);

    uint32_t Id{};
    float value{};

    static char const* GetDBCFormat()
    {
        return "if";
    }
};

constexpr uint8_t MAX_OVERRIDE_SPELL = 10;
struct OverrideSpellDataEntry
{
    OverrideSpellDataEntry() = default;
    explicit OverrideSpellDataEntry(DBCFileLoader::Record const& record);

    uint32_t      Id{};                           // 0
    std::array<int32_t, MAX_OVERRIDE_SPELL> Spells{};  // 1-10
    //uint32_t      unk0;                         // 11
    //std::string   SpellBarName;                 // 12

    static char const* GetDBCFormat()
    {
        return "iiiiiiiiiixx";
    }
};

struct ScreenEffectEntry
{
    ScreenEffectEntry() = default;
    explicit ScreenEffectEntry(DBCFileLoader::Record const& record);

    uint32_t    Id{};           // 0
    std::string Name;           // 1
    //uint32_t    Unk0{};         // 2
    //float       Unk1{};         // 3
    //uint32_t    Unk2{};         // 4
    //uint32_t    Unk3{};         // 5
    //uint32_t    Unk4{};         // 6
    //int32_t     Unk5{};         // 7
    //uint32_t    Unk6{};         // 8
    //uint32_t    Unk7{};         // 9
    //int32_t     Unk8{};         // 11

    static char const* GetDBCFormat()
    {
        return "isxxxxxxxxx";
    }
};

struct SpellRadiusEntry
{
    SpellRadiusEntry() = default;
    explicit SpellRadiusEntry(DBCFileLoader::Record const& record);

    uint32_t    Id{};               // 0
    float     RadiusMin{};          // 1
    float     RadiusPerLevel{};     // 2
    float     RadiusMax{};          // 3

    static char const* GetDBCFormat()
    {
        return "ifff";
    }
};

struct SpellEntry
{
    SpellEntry() = default;
    explicit SpellEntry(DBCFileLoader::Record const& record);
    SpellEntry(const SpellEntry&) = default;
    SpellEntry& operator=(const SpellEntry&) = default;

    uint32_t    Id{};                                        // 0        m_ID
    std::array<uint32_t, MAX_SPELL_ATTRIBUTES> Attributes{};  // 1 - 11   m_attribute
    uint32_t    CastingTimeIndex{};                          // 12       m_castingTimeIndex
    uint32_t    DurationIndex{};                             // 13       m_durationIndex
    int32_t     powerType{};                                 // 14       m_powerType
    uint32_t    rangeIndex{};                                // 15       m_rangeIndex
    float       speed{};                                     // 16       m_speed
    std::array<uint32_t, 2> SpellVisual{};                   // 17 - 18       m_spellVisualID
    uint32_t    SpellIconID{};                               // 19       m_spellIconID
    uint32_t    ActiveIconID{};                              // 20       m_activeIconID
    std::string SpellName;                                    // 21       m_name_lang
    std::string Rank;                                         // 22       m_nameSubtext_lang
    std::string Description;                                  // 23       m_description_lang not used
    std::string ToolTip;                                      // 24       m_auraDescription_lang not used
    uint32_t    SchoolMask{};                                // 25       m_schoolMask
    //uint32_t    runeCostID{};                                // 26       m_runeCostID
    //uint32_t  spellMissileID{};                              // 27       m_spellMissileID not used
    //uint32_t  spellDescriptionVariableID{};                  // 28       m_spellDescriptionVariableID, 3.2.0
    //uint32_t  SpellDifficultyId{};                           // 29       m_spellDifficultyID - id from SpellDifficulty.dbc
    //float   SpellCoef{};                                     // 30
    uint32_t  SpellScalingId{};                              // 31       SpellScaling.dbc
    uint32_t  SpellAuraOptionsId{};                          // 32       SpellAuraOptions.dbc
    uint32_t  SpellAuraRestrictionsId{};                     // 33       SpellAuraRestrictions.dbc
    uint32_t  SpellCastingRequirementsId{};                  // 34       SpellCastingRequirements.dbc
    uint32_t  SpellCategoriesId{};                           // 35       SpellCategories.dbc
    uint32_t  SpellClassOptionsId{};                         // 36       SpellClassOptions.dbc
    uint32_t  SpellCooldownsId{};                            // 37       SpellCooldowns.dbc
    //uint32_t  unkIndex7{};                                   // 38       all zeros...
    uint32_t  SpellEquippedItemsId{};                        // 39       SpellEquippedItems.dbc
    uint32_t  SpellInterruptsId{};                           // 40       SpellInterrupts.dbc
    uint32_t  SpellLevelsId{};                               // 41       SpellLevels.dbc
    uint32_t  SpellPowerId{};                                // 42       SpellPower.dbc
    uint32_t  SpellReagentsId{};                             // 43       SpellReagents.dbc
    uint32_t  SpellShapeshiftId{};                           // 44       SpellShapeshift.dbc
    uint32_t  SpellTargetRestrictionsId{};                   // 45       SpellTargetRestrictions.dbc
    //uint32_t  SpellTotemsId{};                               // 46       SpellTotems.dbc
    //uint32_t  ResearchProject{};                             // 47       ResearchProject.dbc

    static char const* GetDBCFormat()
    {
        return "iiiiiiiiiiiiiiifiiiissssixxxxxiiiiiiixiiiiiiixx";
    }

    inline QString GetSpellNameRank() const
    {
        if (Rank.empty())
        {
            return SpellName.c_str();
        }

        return QString("%1, Rank name: %2").arg(SpellName.c_str()).arg(Rank.c_str());
    }

    QString const PrintBaseInfo(uint32_t scalingLevel) const;
    QString const PrintSpellEffectInfo(uint32_t scalingLevel) const;

    // Other data
    QString m_spellNameUpper;   // Used only for search
    std::array<const SpellEffectEntry*, MAX_SPELL_EFFECTS> m_spellEffects{};
    bool m_IsServerSide{false};
};

struct FactionEntry
{
    FactionEntry() = default;
    explicit FactionEntry(DBCFileLoader::Record const& record);

    uint32_t  Id{};                                          // 0
    //int32_t   ReputationIndex{};                             // 1
    //std::array<uint32_t, 4> ReputationRaceMask{};            // 2 - 5
    //std::array<uint32_t, 4> ReputationClassMask{};           // 6 - 9
    //std::array<int32_t, 4>  ReputationBase{};                // 10 - 13
    //std::array<uint32_t, 4> ReputationFlags{};               // 14 - 17
    //uint32_t  ParentFactionID{};                             // 18
    //std::array<float, 2> ParentFactionMod{};                 // 19 - 20 Faction gains incoming rep * spilloverRateIn and  Faction outputs rep * spilloverRateOut as spillover reputation
    //std::array<uint32_t, 2> ParentFactionCap{};                         // 21 - 22 The highest rank the faction will profit from incoming spillover and It does not seem to be the max standing at which a faction outputs spillover ...so no idea
    std::string   Name;                                       // 23
    //std::string   Description;                                // 24
    //uint32_t  Expansion{};                                   // 25

    static char const* GetDBCFormat()
    {
        return "ixxxxxxxxxxxxxxxxxxxxxxsxx";
    }
};
