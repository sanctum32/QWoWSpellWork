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

#undef printEnum

#endif // SPELLENUMSTR_H
