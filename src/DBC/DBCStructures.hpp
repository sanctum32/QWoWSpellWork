#pragma once
#include <QString>
#include <array>
#include <cstdint>
#include <map>
#include <memory>

#include "DBCFileLoader.hpp"
#include "Enums/SpellEnums.hpp"
#include "mysql/mysql.h"

enum class CompareTypes;

struct DbcEntryValues
{
    DbcEntryValues() = default;

    uint32_t uint32Val{};
    int32_t int32Val{};
    float floatVal{};
    QString textVal;

    DbcEntryValues& operator=(uint32_t val) { uint32Val = val; return *this; }
    DbcEntryValues& operator=(int32_t val) { int32Val = val; return *this; }
    DbcEntryValues& operator=(float val) { floatVal = val; return *this; }
    DbcEntryValues& operator=(const std::string& val) { textVal = val.c_str(); return *this; }
};

// SpellEffect.dbc
struct SpellEffectEntry
{
    SpellEffectEntry() = default;
    SpellEffectEntry(DBCFileLoader::Record const& record);
    SpellEffectEntry(const MYSQL_ROW& result);

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
    explicit SpellCategoryEntry(DBCFileLoader::Record const& record);

    uint32_t    Id{};                                           // 0
    //uint32_t Flags{};                                         // 1
    //uint32_t UsesPerWeek{};                                   // 2
private:
    QString Name;                                               // 3
public:
    QStringView GetName() const { return Name; }

    static char const* GetDBCFormat()
    {
        return "ixxs";
    }
};

// SpellCategories.dbc
struct SpellCategoriesEntry
{
    explicit SpellCategoriesEntry(DBCFileLoader::Record const& record);

    uint32_t    Id{};                                           // 0
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
    explicit SpellClassOptionsEntry(DBCFileLoader::Record const& record);

    uint32_t    Id{};                                         // 0
    uint32_t    modalNextSpell{};                             // 1       m_modalNextSpell not used
    std::array<uint32_t, 3> SpellFamilyFlags{};               // 2-4
    uint32_t    SpellFamilyName{};                            // 5       m_spellClassSet
    //QString     Description;                                // 6       4.0.0

    static char const* GetDBCFormat()
    {
        return "iiiiix";
    }
};

// SpellTargetRestrictions.dbc
struct SpellTargetRestrictionsEntry
{
    explicit SpellTargetRestrictionsEntry(DBCFileLoader::Record const& record);

    uint32_t    Id{};                                           // 0
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
    explicit SpellShapeshiftEntry(DBCFileLoader::Record const& record);

    uint32_t    Id{};                                           // 0
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
    explicit SkillLineAbilityEntry(DBCFileLoader::Record const& record);

    uint32_t    Id{};                                           // 0
    uint32_t    SkillLine{};                                    // 1        m_skillLine
    uint32_t    Spell{};                                        // 2        m_spell
    //uint32_t    RaceMask{};                                   // 3        m_raceMask
    //uint32_t    ClassMask{};                                  // 4        m_classMask
    //uint32_t    ExcludeRace{};                                // 5        m_excludeRace
    //uint32_t    ExcludeClass{};                               // 6        m_excludeClass
    uint32_t    MinSkillLineRank{};                             // 7        m_minSkillLineRank
    uint32_t    SupercededBySpell{};                            // 8        m_supercededBySpell
    //uint32_t    AcquireMethod{};                              // 9        m_acquireMethod
    uint32_t    TrivialSkillLineRankHigh{};                     // 10
    uint32_t    TrivialSkillLineRankLow{};                      // 11
    uint32_t    NumSkillUps;                                    // 12
    //uint32_t    UniqueBit;                                      // 13

    static char const* GetDBCFormat()
    {
        return "iiixxxxiixiiix";
    }
};

// SkillLine.dbc
struct SkillLineEntry
{
    explicit SkillLineEntry(DBCFileLoader::Record const& record);

    uint32_t    Id{};                                           // 0
    //int32_t     categoryId{};                                  // 1        m_categoryID
private:
    QString     name;                                           // 3        m_displayName_lang
public:
    QStringView GetName() const { return name; }
    //QString description;                                       // 4        m_description_lang
    //uint32_t    spellIcon{};                                   // 5        m_spellIconID
    //QString alternateVerb;                                     // 6        m_alternateVerb_lang
    //uint32_t    canLink{};                                     // 7        m_canLink (prof. with recipes)

    static char const* GetDBCFormat()
    {
        return "ixsxxxx";
    }
};

// SpellReagents.dbc
struct SpellReagentsEntry
{
    explicit SpellReagentsEntry(DBCFileLoader::Record const& record);

    uint32_t    Id{};                                           // 0
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
    explicit SpellLevelsEntry(DBCFileLoader::Record const& record);

    uint32_t    Id{};                                           // 0
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
    explicit SpellEquippedItemsEntry(DBCFileLoader::Record const& record);

    uint32_t    Id{};                                           // 0
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
    explicit SpellRangeEntry(DBCFileLoader::Record const& record);

    uint32_t    Id{};                                       // 0
    float     minRangeHostile{};                            // 1
    float     minRangeFriend{};                             // 2
    float     maxRangeHostile{};                            // 3
    float     maxRangeFriend{};                             // 4 friend means unattackable unit here
    //uint32_t  type{};                                      // 5
private:
    QString   Name;                                         // 6-21     m_displayName_lang
public:
    QStringView GetName() const { return Name; }
    //QString   ShortName;                                   // 23-38    m_displayNameShort_lang

    static char const* GetDBCFormat()
    {
        return "iffffxsx";
    }
};

// SpellAuraOptions.dbc
struct SpellAuraOptionsEntry
{
    explicit SpellAuraOptionsEntry(DBCFileLoader::Record const& record);

    uint32_t    Id{};                                           // 0
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
    explicit SpellCastTimesEntry(DBCFileLoader::Record const& record);

    uint32_t    Id{};                                           // 0
    int32_t     CastTime{};                                     // 1
    float       CastTimePerLevel{};                             // 2 unsure / per skill?
    int32_t     MinCastTime{};                                  // 3 unsure

    static char const* GetDBCFormat()
    {
        return "iifi";
    }
};

// SpellCooldowns.dbc
struct SpellCooldownsEntry
{
    explicit SpellCooldownsEntry(DBCFileLoader::Record const& record);

    uint32_t    Id{};                                           // 0
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
    explicit SpellDurationEntry(DBCFileLoader::Record const& record);

    uint32_t    Id{};                                           // 0
    std::array<int32_t, 3> Duration{};  // 1 - 3

    static char const* GetDBCFormat()
    {
        return "iiii";
    }
};

// SpellPower.dbc
struct SpellPowerEntry
{
    explicit SpellPowerEntry(DBCFileLoader::Record const& record);

    uint32_t    Id{};                                           // 0
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
    explicit SpellInterruptsEntry(DBCFileLoader::Record const& record);

    uint32_t    Id{};                                           // 0
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
    explicit SpellAuraRestrictionsEntry(DBCFileLoader::Record const& record);

    uint32_t    Id{};                                           // 0
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
    explicit AreaGroupEntry(DBCFileLoader::Record const& record);

    uint32_t    Id{};                                           // 0
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
    explicit AreaTableEntry(DBCFileLoader::Record const& record);

    uint32_t    Id{};                                           // 0
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
private:
    QString AreaName;                                             // 11
public:
    QStringView GetName() const { return AreaName; }
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
    explicit SpellCastingRequirementsEntry(DBCFileLoader::Record const& record);

    uint32_t    Id{};                                           // 0
    //uint32_t FacingCasterFlags{};                              // 1
    //uint32_t MinFactionID{};                                   // 2
    //uint32_t MinReputation{};                                  // 3
    int32_t  RequiredAreasID{};                                 // 4
    //uint32_t RequiredAuraVision{};                             // 5
    uint32_t RequiresSpellFocus{};                              // 6

    static char const* GetDBCFormat()
    {
        return "ixxxixi";
    }
};

// SpellScaling.dbc
struct SpellScalingEntry
{
    explicit SpellScalingEntry(DBCFileLoader::Record const& record);

    uint32_t    Id{};                                           // 0
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
    explicit GtSpellScalingEntry(DBCFileLoader::Record const& record);

    uint32_t    Id{};                                           // 0
    float value{};                                              // 1

    static char const* GetDBCFormat()
    {
        return "if";
    }
};

constexpr uint8_t MAX_OVERRIDE_SPELL = 10;
struct OverrideSpellDataEntry
{
    explicit OverrideSpellDataEntry(DBCFileLoader::Record const& record);

    uint32_t    Id{};                                           // 0
    std::array<int32_t, MAX_OVERRIDE_SPELL> Spells{};           // 1-10
    //uint32_t      unk0;                                       // 11
    //QString   SpellBarName;                                   // 12

    static char const* GetDBCFormat()
    {
        return "iiiiiiiiiixx";
    }
};

struct ScreenEffectEntry
{
    explicit ScreenEffectEntry(DBCFileLoader::Record const& record);

    uint32_t    Id{};                                           // 0
private:
    QString Name;                                               // 1
public:
    QStringView GetName() const { return Name; }
    //uint32_t    Unk0{};                                       // 2
    //float       Unk1{};                                       // 3
    //uint32_t    Unk2{};                                       // 4
    //uint32_t    Unk3{};                                       // 5
    //uint32_t    Unk4{};                                       // 6
    //int32_t     Unk5{};                                       // 7
    //uint32_t    Unk6{};                                       // 8
    //uint32_t    Unk7{};                                       // 9
    //int32_t     Unk8{};                                       // 11

    static char const* GetDBCFormat()
    {
        return "isxxxxxxxxx";
    }
};

struct SpellRadiusEntry
{
    explicit SpellRadiusEntry(DBCFileLoader::Record const& record);

    uint32_t    Id{};                                           // 0
    float     RadiusMin{};                                      // 1
    float     RadiusPerLevel{};                                 // 2
    float     RadiusMax{};                                      // 3

    static char const* GetDBCFormat()
    {
        return "ifff";
    }
};


struct SpellEntry
{
    SpellEntry() = default;
    explicit SpellEntry(const DBCFileLoader::Record& record);
    explicit SpellEntry(const MYSQL_ROW& sqlRow);

private:
    auto& _getID() { return _fields[0]; }
    auto& _getAttribute0() { return _fields[1]; }
    auto& _getAttribute1() { return _fields[2]; }
    auto& _getAttribute2() { return _fields[3]; }
    auto& _getAttribute3() { return _fields[4]; }
    auto& _getAttribute4() { return _fields[5]; }
    auto& _getAttribute5() { return _fields[6]; }
    auto& _getAttribute6() { return _fields[7]; }
    auto& _getAttribute7() { return _fields[8]; }
    auto& _getAttribute8() { return _fields[9]; }
    auto& _getAttribute9() { return _fields[10]; }
    auto& _getAttribute10() { return _fields[11]; }
    auto& _getCastingTimeIndex() { return _fields[12]; }
    auto& _getDurationIndex() { return _fields[13]; }
    auto& _getPowerType() { return _fields[14]; }
    auto& _getRangeIndex() { return _fields[15]; }
    auto& _getSpeed() { return _fields[16]; }
    auto& _getSpellVisual1() { return _fields[17]; }
    auto& _getSpellVisual2() { return _fields[18]; }
    auto& _getSpellIconID() { return _fields[19]; }
    auto& _getActiveIconID() { return _fields[20]; }
    auto& _getSpellName() { return _fields[21]; }
    auto& _getRank() { return _fields[22]; }
    auto& _getDescription() { return _fields[23]; }
    auto& _getToolTip() { return _fields[24]; }
    auto& _getSchoolMask() { return _fields[25]; }
    auto& _getRuneCostID() { return _fields[26]; }
    auto& _getSpellMissileID() { return _fields[27]; }
    auto& _getSpellDescriptionVariableID() { return _fields[28]; }
    auto& _getSpellDifficultyId() { return _fields[29]; }
    auto& _getSpellCoef() { return _fields[30]; }
    auto& _getSpellScalingId() { return _fields[31]; }
    auto& _getSpellAuraOptionsId() { return _fields[32]; }
    auto& _getSpellAuraRestrictionsId() { return _fields[33]; }
    auto& _getSpellCastingRequirementsId() { return _fields[34]; }
    auto& _getSpellCategoriesId() { return _fields[35]; }
    auto& _getSpellClassOptionsId() { return _fields[36]; }
    auto& _getSpellCooldownsId() { return _fields[37]; }
    //auto& _getUnkIndex7() { return _fields[38]; }
    auto& _getSpellEquippedItemsId() { return _fields[39]; }
    auto& _getSpellInterruptsId() { return _fields[40]; }
    auto& _getSpellLevelsId() { return _fields[41]; }
    auto& _getSpellPowerId() { return _fields[42]; }
    auto& _getSpellReagentsId() { return _fields[43]; }
    auto& _getSpellShapeshiftId() { return _fields[44]; }
    auto& _getSpellTargetRestrictionsId() { return _fields[45]; }
    //auto& _getSpellTotemsId() { return _fields[46]; }
    auto& _getResearchProject() { return _fields[47]; }

    const auto& _getID() const { return _fields[0]; }
    const auto& _getAttribute0() const { return _fields[1]; }
    const auto& _getAttribute1() const { return _fields[2]; }
    const auto& _getAttribute2() const { return _fields[3]; }
    const auto& _getAttribute3() const { return _fields[4]; }
    const auto& _getAttribute4() const { return _fields[5]; }
    const auto& _getAttribute5() const { return _fields[6]; }
    const auto& _getAttribute6() const { return _fields[7]; }
    const auto& _getAttribute7() const { return _fields[8]; }
    const auto& _getAttribute8() const { return _fields[9]; }
    const auto& _getAttribute9() const { return _fields[10]; }
    const auto& _getAttribute10() const { return _fields[11]; }
    const auto& _getCastingTimeIndex() const { return _fields[12]; }
    const auto& _getDurationIndex() const { return _fields[13]; }
    const auto& _getPowerType() const { return _fields[14]; }
    const auto& _getRangeIndex() const { return _fields[15]; }
    const auto& _getSpeed() const { return _fields[16]; }
    const auto& _getSpellVisual1() const { return _fields[17]; }
    const auto& _getSpellVisual2() const { return _fields[18]; }
    const auto& _getSpellIconID() const { return _fields[19]; }
    const auto& _getActiveIconID() const { return _fields[20]; }
    const auto& _getSpellName() const { return _fields[21]; }
    const auto& _getRank() const { return _fields[22]; }
    const auto& _getDescription() const { return _fields[23]; }
    const auto& _getToolTip() const { return _fields[24]; }
    const auto& _getSchoolMask() const { return _fields[25]; }
    const auto& _getRuneCostID() const { return _fields[26]; }
    const auto& _getSpellMissileID() const { return _fields[27]; }
    const auto& _getSpellDescriptionVariableID() const { return _fields[28]; }
    const auto& _getSpellDifficultyId() const { return _fields[29]; }
    const auto& _getSpellCoef() const { return _fields[30]; }
    const auto& _getSpellScalingId() const { return _fields[31]; }
    const auto& _getSpellAuraOptionsId() const { return _fields[32]; }
    const auto& _getSpellAuraRestrictionsId() const { return _fields[33]; }
    const auto& _getSpellCastingRequirementsId() const { return _fields[34]; }
    const auto& _getSpellCategoriesId() const { return _fields[35]; }
    const auto& _getSpellClassOptionsId() const { return _fields[36]; }
    const auto& _getSpellCooldownsId() const { return _fields[37]; }
    //const auto& _getUnkIndex7() const { return _fields[38]; }
    const auto& _getSpellEquippedItemsId() const { return _fields[39]; }
    const auto& _getSpellInterruptsId() const { return _fields[40]; }
    const auto& _getSpellLevelsId() const { return _fields[41]; }
    const auto& _getSpellPowerId() const { return _fields[42]; }
    const auto& _getSpellReagentsId() const { return _fields[43]; }
    const auto& _getSpellShapeshiftId() const { return _fields[44]; }
    const auto& _getSpellTargetRestrictionsId() const { return _fields[45]; }
    //const auto& _getSpellTotemsId() const { return _fields[46]; }
    const auto& _getResearchProject() const { return _fields[47]; }
public:
    const uint32_t getId() const { return _getID().uint32Val; };                 // 0
    const uint32_t getAttribute0() const { return _getAttribute0().uint32Val; }          // 1
    const uint32_t getAttribute1() const { return _getAttribute1().uint32Val; }          // 2
    const uint32_t getAttribute2() const { return _getAttribute2().uint32Val; }          // 3
    const uint32_t getAttribute3() const { return _getAttribute3().uint32Val; }          // 4
    const uint32_t getAttribute4() const { return _getAttribute4().uint32Val; }          // 5
    const uint32_t getAttribute5() const { return _getAttribute5().uint32Val; }          // 6
    const uint32_t getAttribute6() const { return _getAttribute6().uint32Val; }          // 7
    const uint32_t getAttribute7() const { return _getAttribute7().uint32Val; }          // 8
    const uint32_t getAttribute8() const { return _getAttribute8().uint32Val; }          // 9
    const uint32_t getAttribute9() const { return _getAttribute9().uint32Val; }         // 10
    const uint32_t getAttribute10() const { return _getAttribute10().uint32Val; }        // 11
    const uint32_t getCastingTimeIndex() const { return _getCastingTimeIndex().uint32Val; }   // 12
    const uint32_t getDurationIndex() const { return _getDurationIndex().uint32Val; }      // 13
    const int32_t getPowerType() const { return _getPowerType().int32Val; }            // 14
    const uint32_t getRangeIndex() const { return _getRangeIndex().uint32Val; }         // 15
    const float getSpeed() const { return _getSpeed().floatVal; }                    // 16
    const uint32_t getSpellVisual1() const { return _getSpellVisual1().uint32Val;; }       // 17
    const uint32_t getSpellVisual2() const { return _getSpellVisual2().uint32Val;; }       // 18
    const uint32_t getSpellIconID() const { return _getSpellIconID().uint32Val;; }        // 19
    const uint32_t getActiveIconID() const { return _getActiveIconID().uint32Val;; }       // 20
    const QString& getSpellName() const { return _getSpellName().textVal; }    // 21
    const QString& getRank() const { return _getRank().textVal; }         // 22
    const QString& getDescription() const { return _getDescription().textVal; }  // 23
    const QString& getToolTip() const { return _getToolTip().textVal; }      // 24
    const uint32_t getSchoolMask() const { return _getSchoolMask().uint32Val; }         // 25
    //const uint32_t getRuneCostID() const { return _getRuneCostID().uint32Val; }         // 26
    //const uint32_t getSpellMissileID() const { return _getSpellMissileID(.uint32Val; }     // 27
    //const uint32_t getSpellDescriptionVariableID() const { return _getSpellDescriptionVariableID().uint32Val; }  // 28
    //const uint32_t getSpellDifficultyId() const { return _getSpellDifficultyId().uint32Val; }    // 29
    //const float getSpellCoef() const { return std::get<2>(_getSpellCoef().floatVal; }                 // 30
    const uint32_t getSpellScalingId() const { return _getSpellScalingId().uint32Val; }         // 31
    const uint32_t getSpellAuraOptionsId() const { return _getSpellAuraOptionsId().uint32Val; }  // 32
    const uint32_t getSpellAuraRestrictionsId() const { return _getSpellAuraRestrictionsId().uint32Val; }  // 33
    const uint32_t getSpellCastingRequirementsId() const { return _getSpellCastingRequirementsId().uint32Val; }  // 34
    const uint32_t getSpellCategoriesId() const { return _getSpellCategoriesId().uint32Val; }  // 35
    const uint32_t getSpellClassOptionsId() const { return _getSpellClassOptionsId().uint32Val; }  // 36
    const uint32_t getSpellCooldownsId() const { return _getSpellCooldownsId().uint32Val; }  // 37
    //const uint32_t getUnkIndex7() const { return _getUnkIndex7().uint32Val; }  // 38
    const uint32_t getSpellEquippedItemsId() const { return _getSpellEquippedItemsId().uint32Val; }  // 39
    const uint32_t getSpellInterruptsId() const { return _getSpellInterruptsId().uint32Val; }  // 40
    const uint32_t getSpellLevelsId() const { return _getSpellLevelsId().uint32Val; }  // 41
    const uint32_t getSpellPowerId() const { return _getSpellPowerId().uint32Val; }  // 42
    const uint32_t getSpellReagentsId() const { return _getSpellReagentsId().uint32Val; }  // 43
    const uint32_t getSpellShapeshiftId() const { return _getSpellShapeshiftId().uint32Val; }  // 44
    const uint32_t getSpellTargetRestrictionsId() const { return _getSpellTargetRestrictionsId().uint32Val; }  // 45
    //const uint32_t getSpellTotemsId() const { return _getSpellTotemsId().uint32Val; }  // 46
    const uint32_t getResearchProject() const { return _getResearchProject().uint32Val; }  // 47

    static char const* GetDBCFormat()
    {
        return "iiiiiiiiiiiiiiifiiiissssixxxxxiiiiiiixiiiiiiixi";
    }

    inline const QString GetSpellNameRank() const
    {
        if (getRank().isEmpty())
        {
            return getSpellName();
        }

        return QString("%1, Rank name: %2").arg(getSpellName(), getRank());
    }

    QString const PrintBaseInfo(uint32_t scalingLevel) const;
    QString const PrintSpellEffectInfo(uint32_t scalingLevel) const;

    const auto& GetField(uint8_t index) const { return _fields.at(index); }

    // Other data
    std::array<const SpellEffectEntry*, MAX_SPELL_EFFECTS> m_spellEffects{};
    bool m_IsServerSide{false};

private:
    std::array<DbcEntryValues, 47> _fields;
};

struct FactionEntry
{
    explicit FactionEntry(DBCFileLoader::Record const& record);

    uint32_t    Id{};                                           // 0
    //int32_t   ReputationIndex{};                               // 1
    //std::array<uint32_t, 4> ReputationRaceMask{};              // 2 - 5
    //std::array<uint32_t, 4> ReputationClassMask{};             // 6 - 9
    //std::array<int32_t, 4>  ReputationBase{};                  // 10 - 13
    //std::array<uint32_t, 4> ReputationFlags{};                 // 14 - 17
    //uint32_t  ParentFactionID{};                               // 18
    //std::array<float, 2> ParentFactionMod{};                   // 19 - 20 Faction gains incoming rep * spilloverRateIn and  Faction outputs rep * spilloverRateOut as spillover reputation
    //std::array<uint32_t, 2> ParentFactionCap{};                // 21 - 22 The highest rank the faction will profit from incoming spillover and It does not seem to be the max standing at which a faction outputs spillover ...so no idea
    QString   Name;                                             // 23
    //QString   Description;                                     // 24
    //uint32_t  Expansion{};                                     // 25

    static char const* GetDBCFormat()
    {
        return "ixxxxxxxxxxxxxxxxxxxxxxsxx";
    }
};

// For advanced filter
struct SpellEntryAttributeInfo
{
    QString fieldName;
    CompareTypes cmpType;
};

extern const std::map<uint8_t /*fieldId*/, SpellEntryAttributeInfo /*info*/> SpellEntryFields;
