#ifndef DBC_STRUCTURES_H
#define DBC_STRUCTURES_H

#include "DBCFileLoader.hpp"
#include "../Enums/SpellEnums.hpp"
#include <QString>
#include <qdebug.h>

// SpellEffect.dbc
struct SpellEffectEntry
{
    SpellEffectEntry() = default;
    explicit SpellEffectEntry(DBCFileLoader::Record const& record);

    uint32_t    Id;                                           // 0
    uint32_t    Effect;                                       // 1
    float       EffectAmplitude;                              // 2
    uint32_t    EffectAura;                                   // 3
    uint32_t    EffectAuraPeriod;                             // 4
    int32_t     EffectBasePoints;                             // 5
    float       EffectBonusCoefficient;                       // 6
    float       EffectChainAmplitude;                         // 7
    uint32_t    EffectChainTargets;                           // 8
    int32_t     EffectDieSides;                               // 9
    uint32_t    EffectItemType;                               // 10
    uint32_t    EffectMechanic;                               // 11
    int32_t     EffectMiscValue;                              // 12
    int32_t     EffectMiscValueB;                             // 13
    float       EffectPointsPerResource;                      // 14
    uint32_t    EffectRadiusIndex;                            // 15
    uint32_t    EffectRadiusMaxIndex;                         // 16
    float       EffectRealPointsPerLevel;                     // 17
    uint32_t    EffectSpellClassMask[3];                      // 18 - 20
    uint32_t    EffectTriggerSpell;                           // 21
    uint32_t    EffectImplicitTargetA;                        // 22
    uint32_t    EffectImplicitTargetB;                        // 23
    uint32_t    SpellID;                                      // 24
    uint32_t    EffectIndex;                                  // 25
    uint32_t    EffectAttributes;                             // 26

    static char const* GetDBCFormat()
    {
        return "iifiiiffiiiiiifiifiiiiiiiii";
    }

    // Generates extra effect details by given format
    std::shared_ptr<QString> GenerateExtraDetails(const QString& format) const;
};

// SpellCategory.dbc
struct SpellCategoryEntry
{
    SpellCategoryEntry() = default;
    explicit SpellCategoryEntry(DBCFileLoader::Record const& record);

    uint32_t Id{0};                                          // 0
    uint32_t Flags{0};                                       // 1
    uint32_t UsesPerWeek{0};                                 // 2
    std::string Name;                                        // 3

    static char const* GetDBCFormat()
    {
        return "iiis";
    }
};

// SpellCategories.dbc
struct SpellCategoriesEntry
{
    SpellCategoriesEntry() = default;
    explicit SpellCategoriesEntry(DBCFileLoader::Record const& record);

    uint32_t    Id{0};                                           // 0        m_ID
    uint32_t    Category{0};                                     // 1        m_category
    uint32_t    DefenseType{0};                                  // 2      m_defenseType
    uint32_t    DispelType{0};                                       // 3        m_dispelType
    uint32_t    Mechanic{0};                                     // 4        m_mechanic
    uint32_t    PreventionType{0};                               // 5      m_preventionType
    uint32_t    StartRecoveryCategory{0};                        // 6      m_startRecoveryCategory

    static char const* GetDBCFormat()
    {
        return "iiiiiii";
    }
};

// SpellClassOptions.dbc
struct SpellClassOptionsEntry
{
    SpellClassOptionsEntry() = default;
    explicit SpellClassOptionsEntry(DBCFileLoader::Record const& record);

    uint32_t    Id{0};                                         // 0       m_ID
    uint32_t    modalNextSpell{0};                             // 1       m_modalNextSpell not used
    uint32_t    SpellFamilyFlags[3]{0, 0, 0};                  // 2-4
    uint32_t    SpellFamilyName{0};                            // 5       m_spellClassSet
    std::string     Description;                               // 6       4.0.0

    static char const* GetDBCFormat()
    {
        return "iiiiis";
    }
};

// SpellTargetRestrictions.dbc
struct SpellTargetRestrictionsEntry
{
    SpellTargetRestrictionsEntry() = default;
    explicit SpellTargetRestrictionsEntry(DBCFileLoader::Record const& record);

    uint32_t    Id;                                           // 0        m_ID
    float       ConeAngle;                                    // 1
    uint32_t    MaxAffectedTargets;                           // 2        m_maxTargets
    uint32_t    MaxTargetLevel;                               // 3        m_maxTargetLevel
    uint32_t    TargetCreatureType;                           // 4       m_targetCreatureType
    uint32_t    Targets;                                      // 5       m_targets

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

    uint32_t    Id;                                           // 0 - m_ID
    uint32_t    StancesNot;                                   // 3 - m_shapeshiftExclude
    uint32_t    unk_320_2;                                    // 2 - 3.2.0
    uint32_t    Stances;                                      // 1 - m_shapeshiftMask
    uint32_t    unk_320_3;                                    // 4 - 3.2.0
    uint32_t    StanceBarOrder;                               // 5 - m_stanceBarOrder not used

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

    uint32_t    id;                                           // 0        m_ID
    uint32_t    skillId;                                      // 1        m_skillLine
    uint32_t    spellId;                                      // 2        m_spell
    uint32_t    racemask;                                     // 3        m_raceMask
    uint32_t    classmask;                                    // 4        m_classMask
    uint32_t    racemaskNot;                                  // 5        m_excludeRace
    uint32_t    classmaskNot;                                 // 6        m_excludeClass
    uint32_t    req_skill_value;                              // 7        m_minSkillLineRank
    uint32_t    forward_spellid;                              // 8        m_supercededBySpell
    uint32_t    learnOnGetSkill;                              // 9        m_acquireMethod
    uint32_t    max_value;                                    // 10       m_trivialSkillLineRankHigh
    uint32_t    min_value;                                    // 11       m_trivialSkillLineRankLow
    uint32_t    character_points[2];                          // 12-13    m_characterPoints

    static char const* GetDBCFormat()
    {
        return "iiiiiiiiiiiiii";
    }
};

// SkillLine.dbc
struct SkillLineEntry
{
    SkillLineEntry() = default;
    explicit SkillLineEntry(DBCFileLoader::Record const& record);

    uint32_t    id;                                         // 0        m_ID
    int32_t     categoryId;                                 // 1        m_categoryID
    std::string name;                                       // 3        m_displayName_lang
    std::string description;                                // 4        m_description_lang
    uint32_t    spellIcon;                                  // 5        m_spellIconID
    std::string alternateVerb;                              // 6        m_alternateVerb_lang
    uint32_t    canLink;                                    // 7        m_canLink (prof. with recipes)

    static char const* GetDBCFormat()
    {
        return "iissisi";
    }
};

// SpellReagents.dbc
struct SpellReagentsEntry
{
    SpellReagentsEntry() = default;
    explicit SpellReagentsEntry(DBCFileLoader::Record const& record);

    uint32_t    Id;                                           // 0        m_ID
    std::array<int32_t, MAX_SPELL_REAGENTS> Reagent;          // 54-61    m_reagent
    uint32_t    ReagentCount[MAX_SPELL_REAGENTS];             // 62-69    m_reagentCount

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

    uint32_t    Id;                                           // 0        m_ID
    uint32_t    baseLevel;                                    // 1       m_baseLevel
    uint32_t    maxLevel;                                     // 2       m_maxLevel
    uint32_t    spellLevel;                                   // 3       m_spellLevel

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

    uint32_t    Id;                                           // 0        m_ID
    int32_t     EquippedItemClass;                            // 70       m_equippedItemClass (value)
    int32_t     EquippedItemInventoryTypeMask;                // 72       m_equippedItemInvTypes (mask)
    int32_t     EquippedItemSubClassMask;                     // 71       m_equippedItemSubclass (mask)

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

    uint32_t  ID;
    float     minRangeHostile;
    float     minRangeFriend;
    float     maxRangeHostile;
    float     maxRangeFriend;                               //friend means unattackable unit here
    uint32_t  type;
    std::string   Name;                                         // 6-21     m_displayName_lang
    std::string   ShortName;                                    // 23-38    m_displayNameShort_lang

    static char const* GetDBCFormat()
    {
        return "iffffiss";
    }
};

// SpellAuraOptions.dbc
struct SpellAuraOptionsEntry
{
    SpellAuraOptionsEntry() = default;
    explicit SpellAuraOptionsEntry(DBCFileLoader::Record const& record);

    uint32_t    Id;                                           // 0       m_ID
    uint32_t    StackAmount;                                  // 1       m_cumulativeAura
    uint32_t    procChance;                                   // 2       m_procChance
    uint32_t    procCharges;                                  // 3       m_procCharges
    uint32_t    procFlags;                                    // 4       m_procTypeMask

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

    uint32_t    ID;                                         // 0
    int32_t     CastTime;                                   // 1
    float       CastTimePerLevel;                           // 2 unsure / per skill?
    int32_t     MinCastTime;                                // 3 unsure

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

    uint32_t    Id;                                           // 0        m_ID
    uint32_t    CategoryRecoveryTime;                         // 31       m_categoryRecoveryTime
    uint32_t    RecoveryTime;                                 // 30       m_recoveryTime
    uint32_t    StartRecoveryTime;                            // 146      m_startRecoveryTime

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

    uint32_t    ID;
    int32_t     Duration[3];

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

    uint32_t    Id;                                           // 0        m_ID
    uint32_t    manaCost;                                     // 1       m_manaCost
    uint32_t    manaCostPerlevel;                             // 2       m_manaCostPerLevel
    uint32_t    ManaCostPercentage;                           // 3       m_manaCostPct
    uint32_t    manaPerSecond;                                // 4       m_manaPerSecond
    uint32_t    manaPerSecondPerLevel;                        // 5       m_manaPerSecondPerLevel
    uint32_t    PowerDisplayId;                               // 6       m_powerDisplayID - id from PowerDisplay.dbc, new in 3.1
    float       ManaCostPercentageFloat;                      // 7       4.3.0

    static char const* GetDBCFormat()
    {
        return "iiiiiiif";
    }
};

// SpellInterrupts.dbc
struct SpellInterruptsEntry
{
    SpellInterruptsEntry() = default;
    explicit SpellInterruptsEntry(DBCFileLoader::Record const& record);

    uint32_t    Id;                                           // 0        m_ID
    uint32_t    AuraInterruptFlags;                           // 1       m_auraInterruptFlags
    uint32_t    unk3;                                         // 2       4.0.0
    uint32_t    ChannelInterruptFlags;                        // 3       m_channelInterruptFlags
    uint32_t    unk5;                                         // 4       4.0.0
    uint32_t    InterruptFlags;                               // 5       m_interruptFlags

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

    uint32_t    Id;                                           // 0        m_ID
    uint32_t    CasterAuraState;                              // 1       m_casterAuraState
    uint32_t    TargetAuraState;                              // 2       m_targetAuraState
    uint32_t    CasterAuraStateNot;                           // 3       m_excludeCasterAuraState
    uint32_t    TargetAuraStateNot;                           // 4       m_excludeTargetAuraState
    uint32_t    casterAuraSpell;                              // 5       m_casterAuraSpell
    uint32_t    targetAuraSpell;                              // 6       m_targetAuraSpell
    uint32_t    excludeCasterAuraSpell;                       // 7       m_excludeCasterAuraSpell
    uint32_t    excludeTargetAuraSpell;                       // 8       m_excludeTargetAuraSpell

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

    uint32_t  AreaGroupId;                                    // 0
    uint32_t  AreaId[MAX_GROUP_AREA_IDS];                     // 1-6
    uint32_t  nextGroup;                                      // 7 index of next group

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

    uint32_t  ID;                                             // 0
    uint32_t  mapid;                                          // 1
    uint32_t  zone;                                           // 2 if 0 then it's zone, else it's zone id of this area
    uint32_t  exploreFlag;                                    // 3, main index
    uint32_t  flags;                                          // 4,
    uint32_t unk5;                                          // 5,
    uint32_t unk6;                                          // 6,
    uint32_t unk7;                                          // 7,
    uint32_t unk8;                                          // 8,
    uint32_t unk9;                                          // 9,
    int32_t   area_level;                                     // 10
    std::string   area_name;                                      // 11
    uint32_t  team;                                           // 12
    uint32_t  LiquidTypeOverride[4];                          // 13-16 liquid override by type
    float   MaxDepth;                                       // 17,
    float   AmbientMultiplier;                              // 18 client only?
    uint32_t  LightId;                                        // 19
    uint32_t unk20;                                         // 20 4.0.0 - Mounting related
    uint32_t unk21;                                         // 21 4.0.0
    uint32_t unk22;                                         // 22 4.0.0
    uint32_t unk23;                                         // 23 4.0.0
    uint32_t unk24;                                         // 24 - worldStateId
    int32_t  unk25;                                         // 25

    static char const* GetDBCFormat()
    {
        return "iiiiiiiiiisiiiiiffiiiiiii";
    }
};

// SpellCastingRequirements.dbc
struct SpellCastingRequirementsEntry
{
    SpellCastingRequirementsEntry() = default;
    explicit SpellCastingRequirementsEntry(DBCFileLoader::Record const& record);

    uint32_t    Id;                                         // 0        m_ID
    uint32_t    FacingCasterFlags;                          // 1       m_facingCasterFlags
    uint32_t    MinFactionId;                               // 2      m_minFactionID not used
    uint32_t    MinReputation;                              // 3      m_minReputation not used
    int32_t     AreaGroupId;                                // 4      m_requiredAreaGroupId
    uint32_t    RequiredAuraVision;                         // 5      m_requiredAuraVision not used
    uint32_t    RequiresSpellFocus;                         // 6       m_requiresSpellFocus

    static char const* GetDBCFormat()
    {
        return "iiiiiii";
    }
};

// SpellScaling.dbc
struct SpellScalingEntry
{
    SpellScalingEntry() = default;
    explicit SpellScalingEntry(DBCFileLoader::Record const& record);

    uint32_t    Id;                                           // 0        m_ID
    int32_t     CastTimeMin;                                  // 1
    int32_t     CastTimeMax;                                  // 2
    int32_t     CastTimeMaxLevel;                             // 3
    int32_t     ScalingClass;                                 // 4        (index * 100) + charLevel - 1 => gtSpellScaling.dbc
    float       Coefficient[3];                                // 5-7
    float       RandomMultiplier[3];                          // 8-10
    float       OtherMultiplier[3];                           // 11-13
    float       CoefBase;                                     // 14        some coefficient, mostly 1.0f
    int32_t     CoefLevelBase;                                // 15        some level

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

    uint32_t Id;
    float value;

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

    uint32_t      Id{0};                           // 0
    std::array<int32_t, MAX_OVERRIDE_SPELL> spellId{0};  // 1-10
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

    uint32_t    Id;
    std::string Name;
    uint32_t    Unk0;
    float       Unk1;
    uint32_t    Unk2;
    uint32_t    Unk3;
    uint32_t    Unk4;
    int32_t     Unk5;
    uint32_t    Unk6;
    uint32_t    Unk7;
    int32_t     Unk8;

    static char const* GetDBCFormat()
    {
        return "isifiiiiiii";
    }
};

struct SpellRadiusEntry
{
    SpellRadiusEntry() = default;
    explicit SpellRadiusEntry(DBCFileLoader::Record const& record);

    uint32_t    Id;
    float     RadiusMin;
    float     RadiusPerLevel;
    float     RadiusMax;

    static char const* GetDBCFormat()
    {
        return "ifff";
    }
};

struct SpellEntry
{
    SpellEntry() = default;
    explicit SpellEntry(DBCFileLoader::Record const& record);

    uint32_t    Id{0};                                        // 0        m_ID
    std::array<uint32_t, MAX_SPELL_ATTRIBUTES> Attributes{};  // 1 - 11   m_attribute
    uint32_t    CastingTimeIndex{0};                          // 12       m_castingTimeIndex
    uint32_t    DurationIndex{0};                             // 13       m_durationIndex
    int32_t     powerType{0};                                 // 14       m_powerType
    uint32_t    rangeIndex{0};                                // 15       m_rangeIndex
    float       speed;                                        // 16       m_speed
    uint32_t    SpellVisual1{0};                              // 17       m_spellVisualID
    uint32_t    SpellVisual2{0};                              // 18       m_spellVisualID
    uint32_t    SpellIconID{0};                               // 19       m_spellIconID
    uint32_t    activeIconID{0};                              // 20       m_activeIconID
    std::string SpellName;                                    // 21       m_name_lang
    std::string Rank;                                         // 22       m_nameSubtext_lang
    std::string Description;                                  // 23       m_description_lang not used
    std::string ToolTip;                                      // 24       m_auraDescription_lang not used
    uint32_t    SchoolMask{0};                                // 25       m_schoolMask
    uint32_t    runeCostID{0};                                // 26       m_runeCostID
    uint32_t  spellMissileID{0};                              // 27       m_spellMissileID not used
    uint32_t  spellDescriptionVariableID{0};                  // 28       m_spellDescriptionVariableID, 3.2.0
    uint32_t  SpellDifficultyId{0};                           // 29       m_spellDifficultyID - id from SpellDifficulty.dbc
    float   SpellCoef{0};                                     // 30
    uint32_t  SpellScalingId{0};                              // 31       SpellScaling.dbc
    uint32_t  SpellAuraOptionsId{0};                          // 32       SpellAuraOptions.dbc
    uint32_t  SpellAuraRestrictionsId{0};                     // 33       SpellAuraRestrictions.dbc
    uint32_t  SpellCastingRequirementsId{0};                  // 34       SpellCastingRequirements.dbc
    uint32_t  SpellCategoriesId{0};                           // 35       SpellCategories.dbc
    uint32_t  SpellClassOptionsId{0};                         // 36       SpellClassOptions.dbc
    uint32_t  SpellCooldownsId{0};                            // 37       SpellCooldowns.dbc
    uint32_t  unkIndex7{0};                                   // 38       all zeros...
    uint32_t  SpellEquippedItemsId{0};                        // 39       SpellEquippedItems.dbc
    uint32_t  SpellInterruptsId{0};                           // 40       SpellInterrupts.dbc
    uint32_t  SpellLevelsId{0};                               // 41       SpellLevels.dbc
    uint32_t  SpellPowerId{0};                                // 42       SpellPower.dbc
    uint32_t  SpellReagentsId{0};                             // 43       SpellReagents.dbc
    uint32_t  SpellShapeshiftId{0};                           // 44       SpellShapeshift.dbc
    uint32_t  SpellTargetRestrictionsId{0};                   // 45       SpellTargetRestrictions.dbc
    uint32_t  SpellTotemsId{0};                               // 46       SpellTotems.dbc
    uint32_t  ResearchProject{0};                             // 47       ResearchProject.dbc

    static char const* GetDBCFormat()
    {
        return "iiiiiiiiiiiiiiifiiiissssiiiiifiiiiiiiiiiiiiiiii";
    }

    inline std::string GetSpellNameRank() const
    {
        if (Rank.empty())
            return SpellName.c_str();

        return std::string(SpellName + ", Rank name: " + Rank);
    }

    QString const PrintBaseInfo(uint32_t scalingLevel) const;
    QString const PrintSpellEffectInfo(uint32_t scalingLevel) const;

    QString _spellName;

    std::array<const SpellEffectEntry*, MAX_SPELL_EFFECTS> m_spellEffects{};
};

struct FactionEntry
{
    FactionEntry() = default;
    explicit FactionEntry(DBCFileLoader::Record const& record);

    uint32_t  Id{0};                                          // 0
    int32_t   ReputationIndex{0};                             // 1
    uint32_t  ReputationRaceMask[4]{0};                       // 2 - 5
    uint32_t  ReputationClassMask[4]{0};                      // 6 - 9
    int32_t   ReputationBase[4]{0};                           // 10 - 13
    uint32_t  ReputationFlags[4]{0};                          // 14 - 17
    uint32_t  ParentFactionID{0};                             // 18
    float     ParentFactionMod[2]{0.0f};                      // 19 - 20 Faction gains incoming rep * spilloverRateIn and  Faction outputs rep * spilloverRateOut as spillover reputation
    uint32_t  ParentFactionCap[2]{0};                         // 21 - 22 The highest rank the faction will profit from incoming spillover and It does not seem to be the max standing at which a faction outputs spillover ...so no idea
    std::string   Name;                                       // 23
    std::string   Description;                                // 24
    uint32_t  Expansion{0};                                   // 25

    static char const* GetDBCFormat()
    {
        return "iiiiiiiiiiiiiiiiiiiffiissi";
    }
};

#endif // DBC_H
