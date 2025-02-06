#pragma once
#include <QString>
#include <array>
#include <cstdint>
#include <map>

#include "DBCFileLoader.hpp"
#include "Enums/SpellEnums.hpp"
#ifdef SPELLWORK_BUILD_SQL
#include "mysql/mysql.h"
#endif // SPELLWORK_BUILD_SQL

enum class CompareTypes;

enum DBCBaseEnums : uint8_t
{
    // 0 - regular/10man normal, 1 - heroic/25man normal, 2 - 10man heroic, 3 - 25man heroic
    MAX_DUNGEON_DIFFICULTY  = 4,

    MAX_SPELL_FAMILY_FLAGS  = 3,
};

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
struct SpellRadiusEntry;
struct SpellEffectEntry
{
    SpellEffectEntry() = default;
    SpellEffectEntry(DBCFileLoader::Record const& record);

#ifdef SPELLWORK_BUILD_SQL
    SpellEffectEntry(const MYSQL_ROW& result);
#endif // SPELLWORK_BUILD_SQL

    inline bool HasSpellClassMask() const { return getEffectSpellClassMaskA() != 0 || getEffectSpellClassMaskB() != 0 || getEffectSpellClassMaskC() != 0; }
    static constexpr const char* GetDBCFormat()
    {
        return "iifiiiffiiiiiifiifiiiiiiiix";
    }

    // Generates extra effect details by given format
    void GenerateExtraInfo();
    bool HasExtraInfo() const { return !m_extraInformation.isEmpty(); }
    const QString& GetExtraInfo() const { return m_extraInformation; };

    const auto getId() const { return _fields[0].uint32Val; }                     // 0
    const auto getEffect() const { return _fields[1].uint32Val; }                 // 1
    const auto getEffectAmplitude() const { return _fields[2].floatVal; }         // 2
    const auto getEffectAura() const { return _fields[3].uint32Val; }             // 3
    const auto getEffectAuraPeriod() const { return _fields[4].uint32Val; }       // 4
    const auto getEffectBasePoints() const { return _fields[5].int32Val; }        // 5
    const auto getEffectBonusCoefficient() const { return _fields[6].floatVal; }  // 6
    const auto getEffectChainAmplitude() const { return _fields[7].floatVal; }    // 7
    const auto getEffectChainTargets() const { return _fields[8].uint32Val; }     // 8
    const auto getEffectDieSides() const { return _fields[9].int32Val; }          // 9
    const auto getEffectItemType() const { return _fields[10].uint32Val; }        // 10
    const auto getEffectMechanic() const { return _fields[11].uint32Val; }        // 11
    const auto getEffectMiscValue() const { return _fields[12].int32Val; }        // 12
    const auto getEffectMiscValueB() const { return _fields[13].int32Val; }       // 13
    const auto getEffectPointsPerResource() const { return _fields[14].floatVal; }// 14
    const auto getEffectMinRadiusIndex() const { return _fields[15].uint32Val; }     // 15
    const auto getEffectMaxRadiusIndex() const { return _fields[16].uint32Val; }  // 16
    const auto getEffectRealPointsPerLevel() const { return _fields[17].floatVal; } // 17
    const uint32_t getEffectSpellClassMaskA() const { return _fields[18].uint32Val; } // 18
    const uint32_t getEffectSpellClassMaskB() const { return _fields[19].uint32Val; } // 19
    const uint32_t getEffectSpellClassMaskC() const { return _fields[20].uint32Val; } // 20
    const auto getEffectTriggerSpell() const { return _fields[21].uint32Val; }    // 21
    const auto getEffectImplicitTargetA() const { return _fields[22].uint32Val; } // 22
    const auto getEffectImplicitTargetB() const { return _fields[23].uint32Val; } // 23
    const auto getSpellID() const { return _fields[24].uint32Val; }               // 24
    const auto getEffectIndex() const { return _fields[25].uint32Val; }           // 25
    const auto getEffectAttributes() const { return _fields[26].uint32Val; }      // 26

    const auto& GetField(uint8_t index) const { return _fields.at(index); }
    const SpellRadiusEntry* m_spellMinRadiusEntry{};
    const SpellRadiusEntry* m_spellMaxRadiusEntry{};

private:
    std::array<DbcEntryValues, 27> _fields;
    auto& _getId() { return _fields[0].uint32Val; }                     // 0
    auto& _getEffect() { return _fields[1].uint32Val; }                 // 1
    auto& _getEffectAmplitude() { return _fields[2].floatVal; }         // 2
    auto& _getEffectAura() { return _fields[3].uint32Val; }             // 3
    auto& _getEffectAuraPeriod() { return _fields[4].uint32Val; }       // 4
    auto& _getEffectBasePoints() { return _fields[5].int32Val; }        // 5
    auto& _getEffectBonusCoefficient() { return _fields[6].floatVal; }  // 6
    auto& _getEffectChainAmplitude() { return _fields[7].floatVal; }    // 7
    auto& _getEffectChainTargets() { return _fields[8].uint32Val; }     // 8
    auto& _getEffectDieSides() { return _fields[9].int32Val; }          // 9
    auto& _getEffectItemType() { return _fields[10].uint32Val; }        // 10
    auto& _getEffectMechanic() { return _fields[11].uint32Val; }        // 11
    auto& _getEffectMiscValue() { return _fields[12].int32Val; }        // 12
    auto& _getEffectMiscValueB() { return _fields[13].int32Val; }       // 13
    auto& _getEffectPointsPerResource() { return _fields[14].floatVal; }// 14
    auto& _getEffectMinRadiusIndex() { return _fields[15].uint32Val; }     // 15
    auto& _getEffectMaxRadiusIndex() { return _fields[16].uint32Val; }  // 16
    auto& _getEffectRealPointsPerLevel() { return _fields[17].floatVal; } // 17
    auto& _getEffectSpellClassMaskA() { return _fields[18].uint32Val; } // 18
    auto& _getEffectSpellClassMaskB() { return _fields[19].uint32Val; } // 19
    auto& _getEffectSpellClassMaskC() { return _fields[20].uint32Val; } // 20
    auto& _getEffectTriggerSpell() { return _fields[21].uint32Val; }    // 21
    auto& _getEffectImplicitTargetA() { return _fields[22].uint32Val; } // 22
    auto& _getEffectImplicitTargetB() { return _fields[23].uint32Val; } // 23
    auto& _getSpellID() { return _fields[24].uint32Val; }               // 24
    auto& _getEffectIndex() { return _fields[25].uint32Val; }           // 25
    auto& _getEffectAttributes() { return _fields[26].uint32Val; }      // 26

    // Extra information generated by json definitions (field "EffectDetail")
    QString m_extraInformation;
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

    static constexpr const char* GetDBCFormat()
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
    //uint32_t    StartRecoveryCategory{};                      // 6      m_startRecoveryCategory

    static constexpr const char* GetDBCFormat()
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
    std::array<uint32_t, MAX_SPELL_FAMILY_FLAGS> SpellFamilyFlags{};               // 2-4
    uint32_t    SpellFamilyName{};                            // 5       m_spellClassSet
    //QString     Description;                                // 6       4.0.0

    static constexpr const char* GetDBCFormat()
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

    static constexpr const char* GetDBCFormat()
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

    static constexpr const char* GetDBCFormat()
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

    static constexpr const char* GetDBCFormat()
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

    QString     name;                                           // 3        m_displayName_lang

    //QString description;                                       // 4        m_description_lang
    //uint32_t    spellIcon{};                                   // 5        m_spellIconID
    //QString alternateVerb;                                     // 6        m_alternateVerb_lang
    //uint32_t    canLink{};                                     // 7        m_canLink (prof. with recipes)

    static constexpr const char* GetDBCFormat()
    {
        return "ixsxxxx";
    }
};

// SpellReagents.dbc
struct SpellReagentsEntry
{
    explicit SpellReagentsEntry(DBCFileLoader::Record const& record);

    uint32_t    Id{};                                           // 0
    std::array<int32_t, MAX_SPELL_REAGENTS> Reagents{};           // 1 - 8
    std::array<uint32_t, MAX_SPELL_REAGENTS> ReagentCount{};      // 9 - 16

    static constexpr const char* GetDBCFormat()
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

    static constexpr const char* GetDBCFormat()
    {
        return "iiii";
    }
};

// SpellEquippedItems.dbc
struct SpellEquippedItemsEntry
{
    explicit SpellEquippedItemsEntry(DBCFileLoader::Record const& record);

    uint32_t    Id{};                                           // 0
    int32_t     EquippedItemClass{};                            // 1
    int32_t     EquippedItemInventoryTypeMask{};                // 2
    int32_t     EquippedItemSubClassMask{};                     // 3

    static constexpr const char* GetDBCFormat()
    {
        return "iiii";
    }
};

// SpellRange.dbc
struct SpellRangeEntry
{
    explicit SpellRangeEntry(DBCFileLoader::Record const& record);

    uint32_t  Id{};                                         // 0
    std::array<float, 2> RangeMin{};                        // 1 - 2 (hostile, friend)
    std::array<float, 2> RangeMax{};                        // 3 - 4 (hostile, friend)
    //uint32_t  Flags;                                      // 5
    QString   DisplayName;                                  // 6
    //QString DisplayNameShort;                             // 7

    static constexpr const char* GetDBCFormat()
    {
        return "iffffxsx";
    }
};

// SpellAuraOptions.dbc
struct SpellAuraOptionsEntry
{
    explicit SpellAuraOptionsEntry(DBCFileLoader::Record const& record);

    uint32_t    Id{};                                           // 0
    uint32_t    CumulativeAura{};                                  // 1       m_cumulativeAura
    uint32_t    ProcChance{};                                   // 2       m_procChance
    uint32_t    ProcCharges{};                                  // 3       m_procCharges
    uint32_t    ProcTypeMask{};                                    // 4       m_procTypeMask

    static constexpr const char* GetDBCFormat()
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

    static constexpr const char* GetDBCFormat()
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

    static constexpr const char* GetDBCFormat()
    {
        return "iiii";
    }
};

// SpellDuration.dbc
struct SpellDurationEntry
{
    explicit SpellDurationEntry(DBCFileLoader::Record const& record);

    uint32_t    Id{};                                           // 0
    int32_t     Duration{};                                     // 1
    int32_t     DurationPerLevel{};                             // 2
    int32_t     MaxDuration{};                                  // 3

    static constexpr const char* GetDBCFormat()
    {
        return "iiii";
    }
};

// SpellPower.dbc
struct SpellPowerEntry
{
    explicit SpellPowerEntry(DBCFileLoader::Record const& record);

    uint32_t    Id{};                                           // 0
    uint32_t    ManaCost{};                                     // 1       m_manaCost
    uint32_t    ManaCostPerLevel{};                             // 2       m_manaCostPerLevel
    uint32_t    PowerCostPct{};                                 // 3       m_manaCostPct
    uint32_t    ManaPerSecond;                                  // 4
    //uint32     PowerDisplayID;                                 // 5
    //uint32     AltPowerBarID;                                  // 6
    float   PowerCostPct2;                                       // 7

    static constexpr const char* GetDBCFormat()
    {
        return "iiiiixxi";
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

    static constexpr const char* GetDBCFormat()
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

    static constexpr const char* GetDBCFormat()
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

    static constexpr const char* GetDBCFormat()
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

    static constexpr const char* GetDBCFormat()
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

    static constexpr const char* GetDBCFormat()
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

    static constexpr const char* GetDBCFormat()
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

    static constexpr const char* GetDBCFormat()
    {
        return "if";
    }
};

// gtNPCManaCostScaler.dbc
struct GtNPCManaCostScalerEntry
{
    explicit GtNPCManaCostScalerEntry(DBCFileLoader::Record const& record);

    uint32_t    Id{};                                           // 0
    float ratio{};                                              // 1

    static constexpr const char* GetDBCFormat()
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

    static constexpr const char* GetDBCFormat()
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

    static constexpr const char* GetDBCFormat()
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

    static constexpr const char* GetDBCFormat()
    {
        return "ifff";
    }
};

// SpellDifficulty.dbc
struct SpellDifficultyEntry
{
    explicit SpellDifficultyEntry(DBCFileLoader::Record const& record);

#ifdef SPELLWORK_BUILD_SQL
    explicit SpellDifficultyEntry(const MYSQL_ROW& sqlRow);
#endif // SPELLWORK_BUILD_SQL

    uint32_t   Id{};                                                    // 0
    std::array<uint32_t, MAX_DUNGEON_DIFFICULTY> DifficultySpellID;      // 1 - 4 instance modes: 10N, 25N, 10H, 25H or Normal/Heroic if only 1-2 is set, if 3-4 is 0 then Mode-2

    static constexpr const char* GetDBCFormat()
    {
        return "iiiii";
    }
};

struct SpellEntry
{
    SpellEntry() = default;
    explicit SpellEntry(const DBCFileLoader::Record& record);

#ifdef SPELLWORK_BUILD_SQL
    explicit SpellEntry(const MYSQL_ROW& sqlRow);
#endif // SPELLWORK_BUILD_SQL

    const auto getId() const { return _fields[0].uint32Val; };                 // 0
    const auto getAttribute0() const { return _fields[1].uint32Val; }          // 1
    const auto getAttribute1() const { return _fields[2].uint32Val; }          // 2
    const auto getAttribute2() const { return _fields[3].uint32Val; }          // 3
    const auto getAttribute3() const { return _fields[4].uint32Val; }          // 4
    const auto getAttribute4() const { return _fields[5].uint32Val; }          // 5
    const auto getAttribute5() const { return _fields[6].uint32Val; }          // 6
    const auto getAttribute6() const { return _fields[7].uint32Val; }          // 7
    const auto getAttribute7() const { return _fields[8].uint32Val; }          // 8
    const auto getAttribute8() const { return _fields[9].uint32Val; }          // 9
    const auto getAttribute9() const { return _fields[10].uint32Val; }         // 10
    const auto getAttribute10() const { return _fields[11].uint32Val; }        // 11
    const auto getCastingTimeIndex() const { return _fields[12].uint32Val; }   // 12
    const auto getDurationIndex() const { return _fields[13].uint32Val; }      // 13
    const auto getPowerType() const { return _fields[14].int32Val; }            // 14
    const auto getRangeIndex() const { return _fields[15].uint32Val; }         // 15
    const auto getSpeed() const { return _fields[16].floatVal; }                    // 16
    const auto getSpellVisual1() const { return _fields[17].uint32Val;; }       // 17
    const auto getSpellVisual2() const { return _fields[18].uint32Val;; }       // 18
    const auto getSpellIconID() const { return _fields[19].uint32Val;; }        // 19
    const auto getActiveIconID() const { return _fields[20].uint32Val;; }       // 20
    const auto& getSpellName() const { return _fields[21].textVal; }    // 21
    const auto& getRank() const { return _fields[22].textVal; }         // 22
    const auto& getDescription() const { return _fields[23].textVal; }  // 23
    const auto& getToolTip() const { return _fields[24].textVal; }      // 24
    const auto getSchoolMask() const { return _fields[25].uint32Val; }         // 25
    //const uint32_t getRuneCostID() const { return _fields[26].uint32Val; }         // 26
    //const uint32_t getSpellMissileID() const { return _fields[27].uint32Val; }     // 27
    //const uint32_t getSpellDescriptionVariableID() const { return _fields[28].uint32Val; }  // 28
    //const uint32_t getSpellDifficultyId() const { return _fields[29].uint32Val; }    // 29
    //const float getSpellCoef() const { return _fields[30].floatVal; }                 // 30
    const auto getSpellScalingId() const { return _fields[31].uint32Val; }         // 31
    const auto getSpellAuraOptionsId() const { return _fields[32].uint32Val; }  // 32
    const auto getSpellAuraRestrictionsId() const { return _fields[33].uint32Val; }  // 33
    const auto getSpellCastingRequirementsId() const { return _fields[34].uint32Val; }  // 34
    const auto getSpellCategoriesId() const { return _fields[35].uint32Val; }  // 35
    const auto getSpellClassOptionsId() const { return _fields[36].uint32Val; }  // 36
    const auto getSpellCooldownsId() const { return _fields[37].uint32Val; }  // 37
    //const auto getUnkIndex7() const { return _fields[38].uint32Val; }  // 38
    const auto getSpellEquippedItemsId() const { return _fields[39].uint32Val; }  // 39
    const auto getSpellInterruptsId() const { return _fields[40].uint32Val; }  // 40
    const auto getSpellLevelsId() const { return _fields[41].uint32Val; }  // 41
    const auto getSpellPowerId() const { return _fields[42].uint32Val; }  // 42
    const auto getSpellReagentsId() const { return _fields[43].uint32Val; }  // 43
    const auto getSpellShapeshiftId() const { return _fields[44].uint32Val; }  // 44
    const auto getSpellTargetRestrictionsId() const { return _fields[45].uint32Val; }  // 45
    //const auto getSpellTotemsId() const { return _fields[46].uint32Val; }  // 46
    const auto getResearchProject() const { return _fields[47].uint32Val; }  // 47

    static constexpr const char* GetDBCFormat()
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

    uint32_t GetAttribute(uint8_t attrIndex) const
    {
        switch (attrIndex)
        {
        case 0: return getAttribute0();
        case 1: return getAttribute1();
        case 2: return getAttribute2();
        case 3: return getAttribute3();
        case 4: return getAttribute4();
        case 5: return getAttribute5();
        case 6: return getAttribute6();
        case 7: return getAttribute7();
        case 8: return getAttribute8();
        case 9: return getAttribute9();
        case 10: return getAttribute10();
        default: return 0;
        }
    }
    bool HasAttribute(SpellAttr0 attr) const { return (getAttribute0() & attr) != 0; }
    bool HasAttribute(SpellAttr1 attr) const { return (getAttribute1() & attr) != 0; }
    bool HasAttribute(SpellAttr2 attr) const { return (getAttribute2() & attr) != 0; }
    bool HasAttribute(SpellAttr3 attr) const { return (getAttribute3() & attr) != 0; }
    bool HasAttribute(SpellAttr4 attr) const { return (getAttribute4() & attr) != 0; }
    bool HasAttribute(SpellAttr5 attr) const { return (getAttribute5() & attr) != 0; }
    bool HasAttribute(SpellAttr6 attr) const { return (getAttribute6() & attr) != 0; }
    bool HasAttribute(SpellAttr7 attr) const { return (getAttribute7() & attr) != 0; }
    bool HasAttribute(SpellAttr8 attr) const { return (getAttribute8() & attr) != 0; }
    bool HasAttribute(SpellAttr9 attr) const { return (getAttribute9() & attr) != 0; }
    bool HasAttribute(SpellAttr10 attr) const { return (getAttribute10() & attr) != 0; }

    QString const PrintBaseInfo(int scalingLevel) const;
    QString const PrintSpellEffectInfo(int scalingLevel, int comboPoints) const;

    const auto& GetField(uint8_t index) const { return _fields.at(index); }

    // Linked dbc entries
    std::array<const SpellEffectEntry*, MAX_SPELL_EFFECTS> m_spellEffects{};
    const SpellScalingEntry* m_scalingEntry{};
    const SpellDurationEntry* m_spellDurationEntry{};
    const SpellRangeEntry* m_spellRangeEntry{};
    const SpellCastTimesEntry* m_spellCastingTimeEntry{};
    const SpellAuraOptionsEntry* m_spellAuraOptionsEntry{};
    const SpellAuraRestrictionsEntry* m_spellRestrictionsEntry{};
    const SpellCastingRequirementsEntry* m_spellCastingReqEntry{};
    const SpellCategoriesEntry* m_spellCategoriesEntry{};
    const SpellClassOptionsEntry* m_spellClassOptionsEntry{};
    const SpellCooldownsEntry* m_spellCooldownEntry{};
    const SpellEquippedItemsEntry* m_spellEquipedItemsEntry{};
    const SpellInterruptsEntry* m_spellInterruptsEntry{};
    const SpellLevelsEntry* m_spellLevelsEntry{};
    const SpellPowerEntry* m_spellPowerEntry{};
    const SpellReagentsEntry* m_spellReagentsEntry{};
    const SpellShapeshiftEntry* m_spellShapeshiftEntry{};
    const SpellTargetRestrictionsEntry* m_spellTargetRestrictionsEntry{};
    const SpellDifficultyEntry* m_spellDifficultyEntry{};

    QString m_AttributesStr;
    bool m_IsServerSide{false};
private:
    std::array<DbcEntryValues, 48> _fields;
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

    static constexpr const char* GetDBCFormat()
    {
        return "ixxxxxxxxxxxxxxxxxxxxxxsxx";
    }
};

// SummonProperties.dbc
struct SummonPropertiesEntry
{
    explicit SummonPropertiesEntry(DBCFileLoader::Record const& record);
    uint32_t  Id{};                                             // 0
    uint32_t  CategoryId{};                                     // 1, 0 - can't be controlled?, 1 - something guardian?, 2 - pet?, 3 - something controllable?, 4 - taxi/mount?
    //uint32_t  Faction;                                        // 2, 14 rows > 0
    int32_t   SummonTypeNameId{};                               // 3
    //int32_t   Slot;                                           // 4, 0-6
    uint32_t  Flags{};                                          // 5

    static constexpr const char* GetDBCFormat()
    {
        return "iuxuxu";
    }
};

struct DBCFieldAttrInfo
{
    const QString fieldName;
    CompareTypes compareType;
};

extern const std::map<uint8_t /*fieldId*/, DBCFieldAttrInfo /*info*/> SpellEntryFields;
extern const std::map<uint8_t /*fieldId*/, DBCFieldAttrInfo /*info*/> SpellEffectEntryFields;
