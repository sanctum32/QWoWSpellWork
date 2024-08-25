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

#undef printEnum

#endif // SPELLENUMSTR_H
