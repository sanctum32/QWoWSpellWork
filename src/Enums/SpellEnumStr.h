#ifndef SPELLENUMSTR_H
#define SPELLENUMSTR_H
#include "SpellEnums.h"
#include <array>

#define printEnum(p) #p

constexpr std::array<char const*, MAX_SPELL_DAMAGE_CLASS> SpellDmgClassStr={
    printEnum(SPELL_DAMAGE_CLASS_NONE),
    printEnum(SPELL_DAMAGE_CLASS_MAGIC),
    printEnum(SPELL_DAMAGE_CLASS_MELEE),
    printEnum(SPELL_DAMAGE_CLASS_RANGED)
};

constexpr std::array<char const*, MAX_SPELL_PREVENTION_TYPE> SpellPreventionTypeStr={
    printEnum(SPELL_PREVENTION_TYPE_NONE),
    printEnum(SPELL_PREVENTION_TYPE_SILENCE),
    printEnum(SPELL_PREVENTION_TYPE_PACIFY),
    printEnum(SPELL_PREVENTION_TYPE_UNK),
    printEnum(SPELL_PREVENTION_TYPE_NO_ACTIONS)
};

constexpr std::array<char const*, MAX_SPELL_CAST_TARGET_FLAGS> SpellCastTargetFlagsStr={
    printEnum(TARGET_FLAG_NONE),
    printEnum(TARGET_FLAG_UNUSED_1),
    printEnum(TARGET_FLAG_UNIT),
    printEnum(TARGET_FLAG_UNIT_RAID),
    printEnum(TARGET_FLAG_UNIT_PARTY),
    printEnum(TARGET_FLAG_ITEM),
    printEnum(TARGET_FLAG_SOURCE_LOCATION),
    printEnum(TARGET_FLAG_DEST_LOCATION),
    printEnum(TARGET_FLAG_UNIT_ENEMY),
    printEnum(TARGET_FLAG_UNIT_ALLY),
    printEnum(TARGET_FLAG_CORPSE_ENEMY),
    printEnum(TARGET_FLAG_UNIT_DEAD),
    printEnum(TARGET_FLAG_GAMEOBJECT),
    printEnum(TARGET_FLAG_TRADE_ITEM),
    printEnum(TARGET_FLAG_STRING),
    printEnum(TARGET_FLAG_GAMEOBJECT_ITEM),
    printEnum(TARGET_FLAG_CORPSE_ALLY),
    printEnum(TARGET_FLAG_UNIT_MINIPET),
    printEnum(TARGET_FLAG_GLYPH_SLOT),
    printEnum(TARGET_FLAG_DEST_TARGET),
    printEnum(TARGET_FLAG_EXTRA_TARGETS),
    printEnum(TARGET_FLAG_UNIT_PASSENGER),
};

constexpr std::array<char const*, MAX_CREATURE_TYPE> CreatureTypeStr={
    printEnum(CREATURE_TYPE_BEAST),
    printEnum(CREATURE_TYPE_DRAGONKIN),
    printEnum(CREATURE_TYPE_DEMON),
    printEnum(CREATURE_TYPE_ELEMENTAL),
    printEnum(CREATURE_TYPE_GIANT),
    printEnum(CREATURE_TYPE_UNDEAD),
    printEnum(CREATURE_TYPE_HUMANOID),
    printEnum(CREATURE_TYPE_CRITTER),
    printEnum(CREATURE_TYPE_MECHANICAL),
    printEnum(CREATURE_TYPE_NOT_SPECIFIED),
    printEnum(CREATURE_TYPE_TOTEM),
    printEnum(CREATURE_TYPE_NON_COMBAT_PET),
    printEnum(CREATURE_TYPE_GAS_CLOUD)
};

//ShapeshiftForm

constexpr std::array<char const*, MAX_SHAPESHIFT_FORMS> ShapeshiftFormStr={
    printEnum(FORM_CAT),
    printEnum(FORM_TREE),
    printEnum(FORM_TRAVEL),
    printEnum(FORM_AQUA),
    printEnum(FORM_BEAR),
    printEnum(FORM_AMBIENT),
    printEnum(FORM_GHOUL),
    printEnum(FORM_DIREBEAR),
    printEnum(FORM_STEVES_GHOUL),
    printEnum(FORM_THARONJA_SKELETON),
    printEnum(FORM_TEST_OF_STRENGTH),
    printEnum(FORM_BLB_PLAYER),
    printEnum(FORM_SHADOW_DANCE),
    printEnum(FORM_CREATUREBEAR),
    printEnum(FORM_CREATURECAT),
    printEnum(FORM_GHOSTWOLF),
    printEnum(FORM_BATTLESTANCE),
    printEnum(FORM_DEFENSIVESTANCE),
    printEnum(FORM_BERSERKERSTANCE),
    printEnum(FORM_TEST),
    printEnum(FORM_ZOMBIE),
    printEnum(FORM_METAMORPHOSIS),
    printEnum(FORM_UNK1),
    printEnum(FORM_UNK2),
    printEnum(FORM_UNDEAD),
    printEnum(FORM_MASTER_ANGLER),
    printEnum(FORM_FLIGHT_EPIC),
    printEnum(FORM_SHADOW),
    printEnum(FORM_FLIGHT),
    printEnum(FORM_STEALTH),
    printEnum(FORM_MOONKIN),
    printEnum(FORM_SPIRITOFREDEMPTION),
    printEnum(FORM_GLADIATOR_STANCE),
};

constexpr std::array<char const*, MAX_ITEM_CLASS> ItemClassStr={
    printEnum(ITEM_CLASS_CONSUMABLE),
    printEnum(ITEM_CLASS_CONTAINER),
    printEnum(ITEM_CLASS_WEAPON),
    printEnum(ITEM_CLASS_GEM),
    printEnum(ITEM_CLASS_ARMOR),
    printEnum(ITEM_CLASS_REAGENT),
    printEnum(ITEM_CLASS_PROJECTILE),
    printEnum(ITEM_CLASS_TRADE_GOODS),
    printEnum(ITEM_CLASS_GENERIC),
    printEnum(ITEM_CLASS_RECIPE),
    printEnum(ITEM_CLASS_MONEY),
    printEnum(ITEM_CLASS_QUIVER),
    printEnum(ITEM_CLASS_QUEST),
    printEnum(ITEM_CLASS_KEY),
    printEnum(ITEM_CLASS_PERMANENT),
    printEnum(ITEM_CLASS_MISCELLANEOUS),
    printEnum(ITEM_CLASS_GLYPH)
};


constexpr std::array<char const*, MAX_ITEM_SUBCLASS_WEAPON_TYPE> ItemSubclassWeaponStr={
    printEnum(ITEM_SUBCLASS_WEAPON_AXE),
    printEnum(ITEM_SUBCLASS_WEAPON_AXE2),
    printEnum(ITEM_SUBCLASS_WEAPON_BOW),
    printEnum(ITEM_SUBCLASS_WEAPON_GUN),
    printEnum(ITEM_SUBCLASS_WEAPON_MACE),
    printEnum(ITEM_SUBCLASS_WEAPON_MACE2),
    printEnum(ITEM_SUBCLASS_WEAPON_POLEARM),
    printEnum(ITEM_SUBCLASS_WEAPON_SWORD),
    printEnum(ITEM_SUBCLASS_WEAPON_SWORD2),
    printEnum(ITEM_SUBCLASS_WEAPON_Obsolete),
    printEnum(ITEM_SUBCLASS_WEAPON_STAFF),
    printEnum(ITEM_SUBCLASS_WEAPON_EXOTIC),
    printEnum(ITEM_SUBCLASS_WEAPON_EXOTIC2),
    printEnum(ITEM_SUBCLASS_WEAPON_FIST_WEAPON),
    printEnum(ITEM_SUBCLASS_WEAPON_MISCELLANEOUS),
    printEnum(ITEM_SUBCLASS_WEAPON_DAGGER),
    printEnum(ITEM_SUBCLASS_WEAPON_THROWN),
    printEnum(ITEM_SUBCLASS_WEAPON_SPEAR),
    printEnum(ITEM_SUBCLASS_WEAPON_CROSSBOW),
    printEnum(ITEM_SUBCLASS_WEAPON_WAND),
    printEnum(ITEM_SUBCLASS_WEAPON_FISHING_POLE)
};

constexpr std::array<char const*, MAX_ITEM_SUBCLASS_ARMOR_TYPE> ItemSubclassArmorStr={
    printEnum(ITEM_SUBCLASS_ARMOR_MISCELLANEOUS),
    printEnum(ITEM_SUBCLASS_ARMOR_CLOTH),
    printEnum(ITEM_SUBCLASS_ARMOR_LEATHER),
    printEnum(ITEM_SUBCLASS_ARMOR_MAIL),
    printEnum(ITEM_SUBCLASS_ARMOR_PLATE),
    printEnum(ITEM_SUBCLASS_ARMOR_BUCKLER),
    printEnum(ITEM_SUBCLASS_ARMOR_SHIELD),
    printEnum(ITEM_SUBCLASS_ARMOR_LIBRAM),
    printEnum(ITEM_SUBCLASS_ARMOR_IDOL),
    printEnum(ITEM_SUBCLASS_ARMOR_TOTEM),
    printEnum(ITEM_SUBCLASS_ARMOR_SIGIL),
    printEnum(ITEM_SUBCLASS_ARMOR_RELIC)
};

constexpr std::array<char const*, MAX_ITEM_SUBCLASS_JUNK_TYPE> ItemSubclassJunkStr={
    printEnum(ITEM_SUBCLASS_JUNK),
    printEnum(ITEM_SUBCLASS_JUNK_REAGENT),
    printEnum(ITEM_SUBCLASS_JUNK_PET),
    printEnum(ITEM_SUBCLASS_JUNK_HOLIDAY),
    printEnum(ITEM_SUBCLASS_JUNK_OTHER),
    printEnum(ITEM_SUBCLASS_JUNK_MOUNT),
    printEnum(ITEM_SUBCLASS_JUNK_UNK12)
};

constexpr std::array<char const*, MAX_INVENTORY_TYPE> InventoryTypeStr={
    printEnum(INVTYPE_NON_EQUIP),
    printEnum(INVTYPE_HEAD),
    printEnum(INVTYPE_NECK),
    printEnum(INVTYPE_SHOULDERS),
    printEnum(INVTYPE_BODY),
    printEnum(INVTYPE_CHEST),
    printEnum(INVTYPE_WAIST),
    printEnum(INVTYPE_LEGS),
    printEnum(INVTYPE_FEET),
    printEnum(INVTYPE_WRISTS),
    printEnum(INVTYPE_HANDS),
    printEnum(INVTYPE_FINGER),
    printEnum(INVTYPE_TRINKET),
    printEnum(INVTYPE_WEAPON),
    printEnum(INVTYPE_SHIELD),
    printEnum(INVTYPE_RANGED),
    printEnum(INVTYPE_CLOAK),
    printEnum(INVTYPE_2HWEAPON),
    printEnum(INVTYPE_BAG),
    printEnum(INVTYPE_TABARD),
    printEnum(INVTYPE_ROBE),
    printEnum(INVTYPE_WEAPONMAINHAND),
    printEnum(INVTYPE_WEAPONOFFHAND),
    printEnum(INVTYPE_HOLDABLE),
    printEnum(INVTYPE_AMMO),
    printEnum(INVTYPE_THROWN),
    printEnum(INVTYPE_RANGEDRIGHT),
    printEnum(INVTYPE_QUIVER),
    printEnum(INVTYPE_RELIC),
};

constexpr std::array<char const*, MAX_DISPEL_TYPE> DispelTypeStr={
    printEnum(DISPEL_NONE),
    printEnum(DISPEL_MAGIC),
    printEnum(DISPEL_CURSE),
    printEnum(DISPEL_DISEASE),
    printEnum(DISPEL_POISON),
    printEnum(DISPEL_STEALTH),
    printEnum(DISPEL_INVISIBILITY),
    printEnum(DISPEL_ALL),
    printEnum(DISPEL_SPE_NPC_ONLY),
    printEnum(DISPEL_ENRAGE),
    printEnum(DISPEL_ZG_TICKET),
    printEnum(DESPEL_OLD_UNUSED)
};

constexpr std::array<char const*, MAX_MECHANIC_TYPE> MechanicsStr={
    printEnum(MECHANIC_NONE),
    printEnum(MECHANIC_CHARM),
    printEnum(MECHANIC_DISORIENTED),
    printEnum(MECHANIC_DISARM),
    printEnum(MECHANIC_DISTRACT),
    printEnum(MECHANIC_FEAR),
    printEnum(MECHANIC_GRIP),
    printEnum(MECHANIC_ROOT),
    printEnum(MECHANIC_SLOW_ATTACK),
    printEnum(MECHANIC_SILENCE),
    printEnum(MECHANIC_SLEEP),
    printEnum(MECHANIC_SNARE),
    printEnum(MECHANIC_STUN),
    printEnum(MECHANIC_FREEZE),
    printEnum(MECHANIC_KNOCKOUT),
    printEnum(MECHANIC_BLEED),
    printEnum(MECHANIC_BANDAGE),
    printEnum(MECHANIC_POLYMORPH),
    printEnum(MECHANIC_BANISH),
    printEnum(MECHANIC_SHIELD),
    printEnum(MECHANIC_SHACKLE),
    printEnum(MECHANIC_MOUNT),
    printEnum(MECHANIC_INFECTED),
    printEnum(MECHANIC_TURN),
    printEnum(MECHANIC_HORROR),
    printEnum(MECHANIC_INVULNERABILITY),
    printEnum(MECHANIC_INTERRUPT),
    printEnum(MECHANIC_DAZE),
    printEnum(MECHANIC_DISCOVERY),
    printEnum(MECHANIC_IMMUNE_SHIELD),
    printEnum(MECHANIC_SAPPED),
    printEnum(MECHANIC_ENRAGED),
    printEnum(MECHANIC_WOUNDED)
};

constexpr std::array<char const*, MAX_POWER_TYPES> PowersStr={
    printEnum(POWER_MANA),
    printEnum(POWER_RAGE),
    printEnum(POWER_FOCUS),
    printEnum(POWER_ENERGY),
    printEnum(POWER_UNUSED),
    printEnum(POWER_RUNES),
    printEnum(POWER_RUNIC_POWER),
    printEnum(POWER_SOUL_SHARDS),
    printEnum(POWER_ECLIPSE),
    printEnum(POWER_HOLY_POWER),
    printEnum(POWER_ALTERNATE_POWER),
    printEnum(MAX_POWERS),
    printEnum(POWER_ALL),
    printEnum(POWER_HEALTH)
};

// Spell aura states MAX_AURA_STATE_TYPES
constexpr std::array<char const*, MAX_AURA_STATE_TYPES> AuraStateTypeStr={
    printEnum(AURA_STATE_NONE),
    printEnum(AURA_STATE_DEFENSE),
    printEnum(AURA_STATE_HEALTHLESS_20_PERCENT),
    printEnum(AURA_STATE_BERSERKING),
    printEnum(AURA_STATE_FROZEN),
    printEnum(AURA_STATE_JUDGEMENT),
    printEnum(AURA_STATE_UNKNOWN6),
    printEnum(AURA_STATE_HUNTER_PARRY),
    printEnum(AURA_STATE_UNKNOWN8),
    printEnum(AURA_STATE_UNKNOWN9),
    printEnum(AURA_STATE_WARRIOR_VICTORY_RUSH),
    printEnum(AURA_STATE_UNKNOWN11),
    printEnum(AURA_STATE_FAERIE_FIRE),
    printEnum(AURA_STATE_HEALTHLESS_35_PERCENT),
    printEnum(AURA_STATE_CONFLAGRATE),
    printEnum(AURA_STATE_SWIFTMEND),
    printEnum(AURA_STATE_DEADLY_POISON),
    printEnum(AURA_STATE_ENRAGE),
    printEnum(AURA_STATE_BLEEDING),
    printEnum(AURA_STATE_UNKNOWN19),
    printEnum(AURA_STATE_UNKNOWN20),
    printEnum(AURA_STATE_UNKNOWN21),
    printEnum(AURA_STATE_UNKNOWN22),
    printEnum(AURA_STATE_HEALTH_ABOVE_75_PERCENT)
};

constexpr std::array<char const*, UNIT_MOD_END> UnitModsStr={
    printEnum(UNIT_MOD_STAT_STRENGTH),
    printEnum(UNIT_MOD_STAT_AGILITY),
    printEnum(UNIT_MOD_STAT_STAMINA),
    printEnum(UNIT_MOD_STAT_INTELLECT),
    printEnum(UNIT_MOD_STAT_SPIRIT),
    printEnum(UNIT_MOD_HEALTH),
    printEnum(UNIT_MOD_MANA),
    printEnum(UNIT_MOD_RAGE),
    printEnum(UNIT_MOD_FOCUS),
    printEnum(UNIT_MOD_ENERGY),
    printEnum(UNIT_MOD_UNUSED),
    printEnum(UNIT_MOD_RUNE),
    printEnum(UNIT_MOD_RUNIC_POWER),
    printEnum(UNIT_MOD_SOUL_SHARDS),
    printEnum(UNIT_MOD_ECLIPSE),
    printEnum(UNIT_MOD_HOLY_POWER),
    printEnum(UNIT_MOD_ALTERNATE_POWER),
    printEnum(UNIT_MOD_ARMOR),
    printEnum(UNIT_MOD_RESISTANCE_HOLY),
    printEnum(UNIT_MOD_RESISTANCE_FIRE),
    printEnum(UNIT_MOD_RESISTANCE_NATURE),
    printEnum(UNIT_MOD_RESISTANCE_FROST),
    printEnum(UNIT_MOD_RESISTANCE_SHADOW),
    printEnum(UNIT_MOD_RESISTANCE_ARCANE),
    printEnum(UNIT_MOD_ATTACK_POWER),
    printEnum(UNIT_MOD_ATTACK_POWER_POS),
    printEnum(UNIT_MOD_ATTACK_POWER_NEG),
    printEnum(UNIT_MOD_ATTACK_POWER_RANGED),
    printEnum(UNIT_MOD_ATTACK_POWER_RANGED_POS),
    printEnum(UNIT_MOD_ATTACK_POWER_RANGED_NEG),
    printEnum(UNIT_MOD_DAMAGE_MAINHAND),
    printEnum(UNIT_MOD_DAMAGE_OFFHAND),
    printEnum(UNIT_MOD_DAMAGE_RANGED)
};

constexpr std::array<char const*, MAX_COMBAT_RATING> CombatRatingStr={
    printEnum(CR_WEAPON_SKILL),
    printEnum(CR_DEFENSE_SKILL),
    printEnum(CR_DODGE),
    printEnum(CR_PARRY),
    printEnum(CR_BLOCK),
    printEnum(CR_HIT_MELEE),
    printEnum(CR_HIT_RANGED),
    printEnum(CR_HIT_SPELL),
    printEnum(CR_CRIT_MELEE),
    printEnum(CR_CRIT_RANGED),
    printEnum(CR_CRIT_SPELL),
    printEnum(CR_HIT_TAKEN_MELEE),
    printEnum(CR_HIT_TAKEN_RANGED),
    printEnum(CR_HIT_TAKEN_SPELL),
    printEnum(CR_RESILIENCE_CRIT_TAKEN),
    printEnum(CR_RESILIENCE_PLAYER_DAMAGE_TAKEN),
    printEnum(CR_CRIT_TAKEN_SPELL),
    printEnum(CR_HASTE_MELEE),
    printEnum(CR_HASTE_RANGED),
    printEnum(CR_HASTE_SPELL),
    printEnum(CR_WEAPON_SKILL_MAINHAND),
    printEnum(CR_WEAPON_SKILL_OFFHAND),
    printEnum(CR_WEAPON_SKILL_RANGED),
    printEnum(CR_EXPERTISE),
    printEnum(CR_ARMOR_PENETRATION),
    printEnum(CR_MASTERY)
};

#undef printEnum

#endif // SPELLENUMSTR_H
