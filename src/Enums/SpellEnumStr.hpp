#ifndef SPELLENUMSTR_H
#define SPELLENUMSTR_H
#include "SpellEnums.hpp"
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

#undef printEnum

#endif // SPELLENUMSTR_H
