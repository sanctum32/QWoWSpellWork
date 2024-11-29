#include "DB2Structures.hpp"

ItemSparseEntry::ItemSparseEntry(const DB2FileLoader::Record &record)
{
    ID                  = record.getUInt(0);
    /*Quality             = record.getUInt(1);
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
    for (size_t i = 0; i < SpellID.size(); ++i)
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
    */
    Display         = QString::fromStdString(record.getString(99));
    /*
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

    // 121 - 123
    for (size_t i = 0; i < Content.size(); ++i)
    {
        Content.at(i) = record.getInt(121 + i);
    }

    SocketBonus         = record.getInt(124);
    GemProperties       = record.getInt(125);
    ArmorDamageModifier = record.getFloat(126);
    Duration            = record.getInt(127);
    ItemLimitCategory   = record.getUInt(128);
    HolidayID           = record.getInt(129);
    StatScalingFactor   = record.getFloat(130);
    CurrencySubstitutionID = record.getInt(131);
    CurrencySubstitutionCount = record.getInt(132);
    */
}

ItemSparseEntry::ItemSparseEntry(const MYSQL_ROW &row)
{
    /*ID                  = static_cast<uint32_t>(std::stoul(row[0]));
    Quality             = static_cast<uint32_t>(std::stoul(row[1]));
    Flags               = static_cast<uint32_t>(std::stoul(row[2]));
    Flags2              = static_cast<uint32_t>(std::stoul(row[3]));
    PriceRandomValue    = std::stof(row[4]);
    PriceVariance       = std::stof(row[5]);
    BuyCount            = static_cast<uint32_t>(std::stoul(row[6]));
    BuyPrice            = static_cast<uint32_t>(std::stoul(row[7]));
    SellPrice           = static_cast<uint32_t>(std::stoul(row[8]));
    InventoryType       = static_cast<uint32_t>(std::stoul(row[9]));
    AllowableClass      = static_cast<int32_t>(std::stoi(row[10]));
    AllowableRace       = static_cast<int32_t>(std::stoi(row[11]));
    ItemLevel           = static_cast<uint32_t>(std::stoul(row[12]));
    RequiredLevel       = static_cast<uint32_t>(std::stoul(row[13]));
    RequiredSkill       = static_cast<uint32_t>(std::stoul(row[14]));
    RequiredSkillRank   = static_cast<uint32_t>(std::stoul(row[15]));
    RequiredSpell       = static_cast<int32_t>(std::stoi(row[16]));
    RequiredHonorRank   = static_cast<uint32_t>(std::stoul(row[17]));
    RequiredCityRank    = static_cast<uint32_t>(std::stoul(row[18]));
    RequiredReputationFaction = static_cast<uint32_t>(std::stoul(row[19]));
    RequiredReputationRank = static_cast<uint32_t>(std::stoul(row[20]));
    MaxCount            = static_cast<int32_t>(std::stoi(row[21]));
    Stackable           = static_cast<int32_t>(std::stoi(row[22]));
    ContainerSlots      = static_cast<uint32_t>(std::stoul(row[23]));

    // 24 - 33
    for (size_t i = 0; i < ItemStatType.size(); ++i)
    {
        ItemStatType.at(i) = static_cast<int32_t>(std::stoi(row[24 + i]));
    }

    // 34 - 43
    for (size_t i = 0; i < ItemStatValue.size(); ++i)
    {
        ItemStatValue.at(i) = static_cast<int32_t>(std::stoi(row[34 + i]));
    }

    // 44 - 53
    for (size_t i = 0; i < ItemStatAllocation.size(); ++i)
    {
        ItemStatAllocation.at(i) = static_cast<int32_t>(std::stoi(row[44 + i]));
    }

    // 54 - 63
    for (size_t i = 0; i < ItemStatSocketCostMultiplier.size(); ++i)
    {
        ItemStatSocketCostMultiplier.at(i) = static_cast<int32_t>(std::stoi(row[54 + i]));
    }

    ScalingStatDistribution = static_cast<int32_t>(std::stoi(row[64]));
    DamageType          = static_cast<int32_t>(std::stoi(row[65]));
    Delay               = static_cast<uint32_t>(std::stoul(row[66]));
    RangedModRange      = static_cast<uint32_t>(std::stoul(row[67]));

    // 68 - 72
    for (size_t i = 0; i < SpellID.size(); ++i)
    {
        SpellID.at(i) = static_cast<int32_t>(std::stoi(row[68 + i]));
    }

    // 73 - 77
    for (size_t i = 0; i < SpellTrigger.size(); ++i)
    {
        SpellTrigger.at(i) = static_cast<int32_t>(std::stoi(row[73 + i]));
    }

    // 78 - 82
    for (size_t i = 0; i < SpellCharges.size(); ++i)
    {
        SpellCharges.at(i) = static_cast<int32_t>(std::stoi(row[78 + i]));
    }

    // 83 - 87
    for (size_t i = 0; i < SpellCooldown.size(); ++i)
    {
        SpellCooldown.at(i) = static_cast<int32_t>(std::stoi(row[83 + i]));
    }

    // 88 - 92
    for (size_t i = 0; i < SpellCategory.size(); ++i)
    {
        SpellCategory.at(i) = static_cast<int32_t>(std::stoi(row[88 + i]));
    }

    // 93 - 97
    for (size_t i = 0; i < SpellCategoryCooldown.size(); ++i)
    {
        SpellCategoryCooldown.at(i) = static_cast<int32_t>(std::stoi(row[93 + i]));
    }

    Bonding         = static_cast<int32_t>(std::stoi(row[98]));
    Display         = QString(row[99]);
    Display1        = QString::fromStdString(row[100]);
    Display2        = QString::fromStdString(row[101]);
    Display3        = QString::fromStdString(row[102]);
    Description     = QString::fromStdString(row[103]);
    PageText        = static_cast<uint32_t>(std::stoul(row[104]));
    LanguageID      = static_cast<int32_t>(std::stoi(row[105]));
    PageMaterial    = static_cast<int32_t>(std::stoi(row[106]));
    StartQuest      = static_cast<int32_t>(std::stoi(row[107]));

    LockID          = static_cast<uint32_t>(std::stoul(row[108]));
    Material        = static_cast<int32_t>(std::stoi(row[109]));
    SheatheType     = static_cast<int32_t>(std::stoi(row[110]));
    RandomProperty  = static_cast<int32_t>(std::stoi(row[111]));
    RandomSuffix    = static_cast<uint32_t>(std::stoul(row[112]));
    ItemSet         = static_cast<uint32_t>(std::stoul(row[113]));
    AreaID          = static_cast<uint32_t>(std::stoul(row[114]));
    MapID           = static_cast<int32_t>(std::stoi(row[115]));
    BagFamily       = static_cast<int32_t>(std::stoi(row[116]));
    TotemCategory   = static_cast<int32_t>(std::stoi(row[117]));

    // 118 - 120
    for (size_t i = 0; i < SocketColor.size(); ++i)
    {
        SocketColor.at(i) = static_cast<int32_t>(std::stoi(row[118 + i]));
    }

    // 121 - 123
    for (size_t i = 0; i < Content.size(); ++i)
    {
        Content.at(i) = static_cast<int32_t>(std::stoi(row[121 + i]));
    }

    SocketBonus         = static_cast<int32_t>(std::stoi(row[124]));
    GemProperties       = static_cast<int32_t>(std::stoi(row[125]));
    ArmorDamageModifier = std::stof(row[126]);
    Duration            = static_cast<int32_t>(std::stoi(row[127]));
    ItemLimitCategory   = static_cast<int32_t>(std::stoul(row[128]));
    HolidayID           = static_cast<int32_t>(std::stoi(row[129]));
    StatScalingFactor   = std::stof(row[130]);
    CurrencySubstitutionID = static_cast<int32_t>(std::stoi(row[131]));
    CurrencySubstitutionCount = static_cast<int32_t>(std::stoi(row[132]));*/

    ID = static_cast<uint32_t>(std::stoul(row[0]));
    Display         = QString(row[1]);
}
