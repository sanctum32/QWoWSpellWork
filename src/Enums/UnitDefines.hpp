#pragma once

enum CombatRating
{
    CR_WEAPON_SKILL                     = 0,
    CR_DEFENSE_SKILL                    = 1, // Removed in 4.0.1
    CR_DODGE                            = 2,
    CR_PARRY                            = 3,
    CR_BLOCK                            = 4,
    CR_HIT_MELEE                        = 5,
    CR_HIT_RANGED                       = 6,
    CR_HIT_SPELL                        = 7,
    CR_CRIT_MELEE                       = 8,
    CR_CRIT_RANGED                      = 9,
    CR_CRIT_SPELL                       = 10,
    CR_HIT_TAKEN_MELEE                  = 11, // Deprecated since Cataclysm
    CR_HIT_TAKEN_RANGED                 = 12, // Deprecated since Cataclysm
    CR_HIT_TAKEN_SPELL                  = 13, // Deprecated since Cataclysm
    CR_RESILIENCE_CRIT_TAKEN            = 14,
    CR_RESILIENCE_PLAYER_DAMAGE_TAKEN   = 15,
    CR_CRIT_TAKEN_SPELL                 = 16, // Deprecated since Cataclysm
    CR_HASTE_MELEE                      = 17,
    CR_HASTE_RANGED                     = 18,
    CR_HASTE_SPELL                      = 19,
    CR_WEAPON_SKILL_MAINHAND            = 20,
    CR_WEAPON_SKILL_OFFHAND             = 21,
    CR_WEAPON_SKILL_RANGED              = 22,
    CR_EXPERTISE                        = 23,
    CR_ARMOR_PENETRATION                = 24,
    CR_MASTERY                          = 25,
};

enum UnitMods
{
    UNIT_MOD_STAT_STRENGTH                                  = 0,    // UNIT_MOD_STAT_STRENGTH..UNIT_MOD_STAT_SPIRIT must be in existed order, it's accessed by index values of Stats enum.
    UNIT_MOD_STAT_AGILITY                                   = 1,
    UNIT_MOD_STAT_STAMINA                                   = 2,
    UNIT_MOD_STAT_INTELLECT                                 = 3,
    UNIT_MOD_STAT_SPIRIT                                    = 4,
    UNIT_MOD_HEALTH                                         = 5,
    UNIT_MOD_MANA                                           = 6,    // UNIT_MOD_MANA..UNIT_MOD_RUNIC_POWER must be in existed order, it's accessed by index values of Powers enum.
    UNIT_MOD_RAGE                                           = 7,
    UNIT_MOD_FOCUS                                          = 8,
    UNIT_MOD_ENERGY                                         = 9,
    UNIT_MOD_UNUSED                                         = 10,   // Old UNIT_MOD_HAPPINESS
    UNIT_MOD_RUNE                                           = 11,
    UNIT_MOD_RUNIC_POWER                                    = 12,
    UNIT_MOD_SOUL_SHARDS                                    = 13,
    UNIT_MOD_ECLIPSE                                        = 16,
    UNIT_MOD_HOLY_POWER                                     = 15,
    UNIT_MOD_ALTERNATE_POWER                                = 16,   // Atramedes etc.
    UNIT_MOD_ARMOR                                          = 17,   // UNIT_MOD_ARMOR..UNIT_MOD_RESISTANCE_ARCANE must be in existed order, it's accessed by index values of SpellSchools enum.
    UNIT_MOD_RESISTANCE_HOLY                                = 18,
    UNIT_MOD_RESISTANCE_FIRE                                = 19,
    UNIT_MOD_RESISTANCE_NATURE                              = 20,
    UNIT_MOD_RESISTANCE_FROST                               = 21,
    UNIT_MOD_RESISTANCE_SHADOW                              = 22,
    UNIT_MOD_RESISTANCE_ARCANE                              = 23,
    UNIT_MOD_ATTACK_POWER                                   = 24,
    UNIT_MOD_ATTACK_POWER_POS                               = 25,
    UNIT_MOD_ATTACK_POWER_NEG                               = 26,
    UNIT_MOD_ATTACK_POWER_RANGED                            = 27,
    UNIT_MOD_ATTACK_POWER_RANGED_POS                        = 28,
    UNIT_MOD_ATTACK_POWER_RANGED_NEG                        = 29,
    UNIT_MOD_DAMAGE_MAINHAND                                = 30,
    UNIT_MOD_DAMAGE_OFFHAND                                 = 31,
    UNIT_MOD_DAMAGE_RANGED                                  = 32,
};
