#include "DB2Structures.hpp"

ItemSparseEntry::ItemSparseEntry(const DB2FileLoader::Record &record)
{
    ID                  = record.getUInt(0);
    Quality             = record.getUInt(1);
    Flags               = record.getUInt(2);
    Flags2              = record.getUInt(3);
    PriceRandomValue    = record.getFloat(4);
    PriceVariance       = record.getFloat(5);
    BuyCount            = record.getUInt(6);
    BuyPrice            = record.getUInt(7);
    SellPrice           = record.getUInt(8);
    InventoryType       = record.getUInt(9);
    AllowableClass      = record.getInt(10);
    AllowableRace       = record.getInt(11);
    ItemLevel           = record.getUInt(12);
    RequiredLevel       = record.getUInt(13);
    RequiredSkill       = record.getUInt(14);
    RequiredSkillRank   = record.getUInt(15);
    RequiredSpell       = record.getInt(16);
    RequiredHonorRank   = record.getUInt(17);
    RequiredCityRank    = record.getUInt(18);
    RequiredReputationFaction = record.getUInt(19);
    RequiredReputationRank = record.getUInt(20);
    MaxCount            = record.getInt(21);
    Stackable           = record.getInt(22);
    ContainerSlots      = record.getUInt(23);

    // 24 - 33
    for (size_t i = 0; i < ItemStatType.size(); ++i)
    {
        ItemStatType.at(i) = record.getInt(24 + i);
    }

    // 34 - 43
    for (size_t i = 0; i < ItemStatValue.size(); ++i)
    {
        ItemStatValue.at(i) = record.getInt(34 + i);
    }

    // 44 - 53
    for (size_t i = 0; i < ItemStatAllocation.size(); ++i)
    {
        ItemStatAllocation.at(i) = record.getInt(44 + i);
    }

    // 54 - 63
    for (size_t i = 0; i < ItemStatSocketCostMultiplier.size(); ++i)
    {
        ItemStatSocketCostMultiplier.at(i) = record.getInt(54 + i);
    }

    ScalingStatDistribution = record.getInt(64);
    DamageType          = record.getInt(65);
    Delay               = record.getUInt(66);
    RangedModRange      = record.getFloat(67);

    // 68 - 72
    for (size_t i = 0; SpellID.size(); ++i)
    {
        SpellID.at(i) = record.getInt(68 + i);
    }

    // 73 - 77
    for (size_t i = 0; i < SpellTrigger.size(); ++i)
    {
        SpellTrigger.at(i) = record.getInt(73 + i);
    }

    // 78 - 82
    for (size_t i = 0; i < SpellCharges.size(); ++i)
    {
        SpellCharges.at(i) = record.getInt(78 + i);
    }

    // 83 - 87
    for (size_t i = 0; i < SpellCooldown.size(); ++i)
    {
        SpellCooldown.at(i) = record.getInt(83 + i);
    }

    // 88 - 92
    for (size_t i = 0; i < SpellCategory.size(); ++i)
    {
        SpellCategory.at(i) = record.getInt(88 + i);
    }

    // 93 - 97
    for (size_t i = 0; i < SpellCategoryCooldown.size(); ++i)
    {
        SpellCategoryCooldown.at(i) = record.getInt(93 + i);
    }

    Bonding         = record.getInt(98);
    Display         = QString::fromStdString(record.getString(99));
    Display1        = QString::fromStdString(record.getString(100));
    Display2        = QString::fromStdString(record.getString(101));
    Display3        = QString::fromStdString(record.getString(102));
    Description     = QString::fromStdString(record.getString(103));
    PageText        = record.getUInt(104);
    LanguageID      = record.getInt(105);
    PageMaterial    = record.getInt(106);
    StartQuest      = record.getInt(107);

    LockID          = record.getUInt(108);
    Material        = record.getInt(109);
    SheatheType     = record.getInt(110);
    RandomProperty  = record.getInt(111);
    RandomSuffix    = record.getUInt(112);
    ItemSet         = record.getUInt(113);
    AreaID          = record.getUInt(114);
    MapID           = record.getInt(115);
    BagFamily       = record.getInt(116);
    TotemCategory   = record.getInt(117);

    // 118 - 120
    for (size_t i = 0; i < SocketColor.size(); ++i)
    {
        SocketColor.at(i) = record.getInt(118 + i);
    }

    // 121 - 124
    for (size_t i = 0; i < Content.size(); ++i)
    {
        Content.at(i) = record.getInt(121 + i);
    }

    SocketBonus         = record.getInt(125);
    GemProperties       = record.getInt(126);
    ArmorDamageModifier = record.getFloat(127);
    Duration            = record.getInt(128);
    ItemLimitCategory   = record.getUInt(129);
    HolidayID           = record.getInt(130);
    StatScalingFactor   = record.getFloat(131);
    CurrencySubstitutionID = record.getInt(132);
    CurrencySubstitutionCount = record.getInt(133);
}
