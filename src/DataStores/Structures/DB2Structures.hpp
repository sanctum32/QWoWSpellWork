#pragma once

#include "DB2FileLoader.hpp"

#ifdef SPELLWORK_BUILD_SQL
#include "mysql.h"
#endif // SPELLWORK_BUILD_SQL

#include <QString>

enum : uint8_t
{
    MAX_ITEM_PROTO_SOCKETS  = 3,
    MAX_ITEM_PROTO_SPELLS   = 5,
    MAX_ITEM_PROTO_STATS    = 10
};

// Item-sparse.db2
struct ItemSparseEntry
{
    ItemSparseEntry() = default;
    explicit ItemSparseEntry(DB2FileLoader::Record const& record);
#ifdef SPELLWORK_BUILD_SQL
    explicit ItemSparseEntry(const MYSQL_ROW& row);
#endif // SPELLWORK_BUILD_SQL

    uint32_t     ID{};                                                    // 0
    /*
    uint32_t     Quality{};                                               // 1
    uint32_t     Flags{};                                                 // 2
    uint32_t     Flags2{};                                                // 3
    float        PriceRandomValue{};                                      // 4
    float        PriceVariance{};                                         // 5
    uint32_t     BuyCount{};                                              // 6
    uint32_t     BuyPrice{};                                              // 7
    uint32_t     SellPrice{};                                             // 8
    uint32_t     InventoryType{};                                         // 9
    int32_t      AllowableClass{};                                        // 10
    int32_t      AllowableRace{};                                         // 11
    uint32_t     ItemLevel{};                                             // 12
    uint32_t     RequiredLevel{};                                         // 13
    uint32_t     RequiredSkill{};                                         // 14
    uint32_t     RequiredSkillRank{};                                     // 15
    int32_t      RequiredSpell{};                                         // 16
    uint32_t     RequiredHonorRank{};                                     // 17
    uint32_t     RequiredCityRank{};                                      // 18
    uint32_t     RequiredReputationFaction{};                             // 19
    uint32_t     RequiredReputationRank{};                                // 20
    int32_t      MaxCount{};                                              // 21
    int32_t      Stackable{};                                             // 22
    uint32_t     ContainerSlots{};                                        // 23
    std::array<int32_t, MAX_ITEM_PROTO_STATS> ItemStatType{};             // 24 - 33
    std::array<int32_t, MAX_ITEM_PROTO_STATS> ItemStatValue{};            // 34 - 43
    std::array<int32_t, MAX_ITEM_PROTO_STATS> ItemStatAllocation{};       // 44 - 53
    std::array<int32_t, MAX_ITEM_PROTO_STATS> ItemStatSocketCostMultiplier{}; // 54 - 63
    int32_t      ScalingStatDistribution{};                               // 64
    int32_t      DamageType{};                                            // 65
    uint32_t     Delay{};                                                 // 66
    float        RangedModRange{};                                        // 67
    std::array<int32_t, MAX_ITEM_PROTO_SPELLS> SpellID{};                 // 68 - 72
    std::array<int32_t, MAX_ITEM_PROTO_SPELLS> SpellTrigger{};            // 73 - 77
    std::array<int32_t, MAX_ITEM_PROTO_SPELLS> SpellCharges{};            // 78 - 82
    std::array<int32_t, MAX_ITEM_PROTO_SPELLS> SpellCooldown{};           // 83 - 87
    std::array<int32_t, MAX_ITEM_PROTO_SPELLS> SpellCategory{};           // 88 - 92
    std::array<int32_t, MAX_ITEM_PROTO_SPELLS> SpellCategoryCooldown{};   // 93 - 97
    int32_t      Bonding;                                               // 98
    */
    QString      Display;                                               // 99
    /*
    QString      Display1;                                              // 100
    QString      Display2;                                              // 101
    QString      Display3;                                              // 102
    QString      Description;                                           // 103
    uint32_t     PageText{};                                              // 104
    int32_t      LanguageID{};                                            // 105
    int32_t      PageMaterial{};                                          // 106
    int32_t      StartQuest{};                                            // 107
    uint32_t     LockID{};                                                // 108
    int32_t      Material{};                                              // 109
    int32_t      SheatheType{};                                           // 110
    int32_t      RandomProperty{};                                        // 111
    uint32_t     RandomSuffix{};                                          // 112
    uint32_t     ItemSet{};                                               // 113
    uint32_t     AreaID{};                                                // 114
    int32_t      MapID{};                                                 // 115
    int32_t      BagFamily{};                                             // 116
    int32_t      TotemCategory{};                                         // 117
    std::array<int32_t, MAX_ITEM_PROTO_SOCKETS> SocketColor{};            // 118 - 120
    std::array<uint32_t, MAX_ITEM_PROTO_SOCKETS> Content{};               // 121 - 123
    int32_t      SocketBonus{};                                           // 124
    int32_t      GemProperties{};                                         // 125
    float        ArmorDamageModifier{};                                   // 126
    int32_t      Duration{};                                              // 127
    uint32_t     ItemLimitCategory{};                                     // 128
    int32_t      HolidayID{};                                             // 129
    float        StatScalingFactor;                                     // 130
    int32_t      CurrencySubstitutionID{};                                // 131
    int32_t      CurrencySubstitutionCount{};                             // 132
    */

    const QString& GetName() const { return Display; }
    static constexpr const char* GetDB2Format()
    {
        //return "iiiiffiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiifiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiisssssiiiiiiiiiiiiiiiiiiiiiifiiifii";
        return "ixxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxsxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
    }
};
