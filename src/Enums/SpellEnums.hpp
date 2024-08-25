#ifndef SPELLENUMS_H
#define SPELLENUMS_H
#include <cstdint>

enum
{
    MAX_SPELL_ATTRIBUTES                = 11,   // Max spell attributes
    MAX_SPELL_ATTRIBUTES_ID             = 32,   // Max number of each attribute
    MAX_SPELL_DAMAGE_CLASS              = 4,
    MAX_SPELL_PREVENTION_TYPE           = 5,
    MAX_SPELL_CAST_TARGET_FLAGS         = 22,
    MAX_CREATURE_TYPE                   = 14,
    MAX_SHAPESHIFT_FORMS                = 33,
    MAX_SPELL_REAGENTS                  = 8,
    MAX_ITEM_CLASS                      = 17,
    MAX_ITEM_SUBCLASS_WEAPON_TYPE       = 21,
    MAX_ITEM_SUBCLASS_ARMOR_TYPE        = 12,
    MAX_ITEM_SUBCLASS_JUNK_TYPE         = 7,
    MAX_INVENTORY_TYPE                  = 29,
    MAX_DISPEL_TYPE                     = 12,
    MAX_MECHANIC_TYPE                   = 33,
    MAX_POWER_TYPES                     = 14,
    MAX_AURA_STATE_TYPES                = 24,
    MAX_GROUP_AREA_IDS                  = 6,
    MAX_SPELL_EFFECTS                   = 3,    // Total effects of spell
    MAX_SPELL_EFFECT_ID                 = 183,
    MAX_SPELL_TARGET_TYPES              = 128,
    MAX_COMBAT_RATING                   = 26,
};

enum SpellEffects
{
    SPELL_EFFECT_NONE                               = 0,
    SPELL_EFFECT_INSTAKILL                          = 1,
    SPELL_EFFECT_SCHOOL_DAMAGE                      = 2,
    SPELL_EFFECT_DUMMY                              = 3,
    SPELL_EFFECT_PORTAL_TELEPORT                    = 4, // Unused (4.3.4)
    SPELL_EFFECT_TELEPORT_UNITS                     = 5,
    SPELL_EFFECT_APPLY_AURA                         = 6,
    SPELL_EFFECT_ENVIRONMENTAL_DAMAGE               = 7,
    SPELL_EFFECT_POWER_DRAIN                        = 8,
    SPELL_EFFECT_HEALTH_LEECH                       = 9,
    SPELL_EFFECT_HEAL                               = 10,
    SPELL_EFFECT_BIND                               = 11,
    SPELL_EFFECT_PORTAL                             = 12,
    SPELL_EFFECT_RITUAL_BASE                        = 13, // Unused (4.3.4)
    SPELL_EFFECT_RITUAL_SPECIALIZE                  = 14, // Unused (4.3.4)
    SPELL_EFFECT_RITUAL_ACTIVATE_PORTAL             = 15, // Unused (4.3.4)
    SPELL_EFFECT_QUEST_COMPLETE                     = 16,
    SPELL_EFFECT_WEAPON_DAMAGE_NOSCHOOL             = 17,
    SPELL_EFFECT_RESURRECT                          = 18,
    SPELL_EFFECT_ADD_EXTRA_ATTACKS                  = 19,
    SPELL_EFFECT_DODGE                              = 20,
    SPELL_EFFECT_EVADE                              = 21,
    SPELL_EFFECT_PARRY                              = 22,
    SPELL_EFFECT_BLOCK                              = 23,
    SPELL_EFFECT_CREATE_ITEM                        = 24,
    SPELL_EFFECT_WEAPON                             = 25,
    SPELL_EFFECT_DEFENSE                            = 26,
    SPELL_EFFECT_PERSISTENT_AREA_AURA               = 27,
    SPELL_EFFECT_SUMMON                             = 28,
    SPELL_EFFECT_LEAP                               = 29,
    SPELL_EFFECT_ENERGIZE                           = 30,
    SPELL_EFFECT_WEAPON_PERCENT_DAMAGE              = 31,
    SPELL_EFFECT_TRIGGER_MISSILE                    = 32,
    SPELL_EFFECT_OPEN_LOCK                          = 33,
    SPELL_EFFECT_SUMMON_CHANGE_ITEM                 = 34,
    SPELL_EFFECT_APPLY_AREA_AURA_PARTY              = 35,
    SPELL_EFFECT_LEARN_SPELL                        = 36,
    SPELL_EFFECT_SPELL_DEFENSE                      = 37,
    SPELL_EFFECT_DISPEL                             = 38,
    SPELL_EFFECT_LANGUAGE                           = 39,
    SPELL_EFFECT_DUAL_WIELD                         = 40,
    SPELL_EFFECT_JUMP                               = 41,
    SPELL_EFFECT_JUMP_DEST                          = 42,
    SPELL_EFFECT_TELEPORT_UNITS_FACE_CASTER         = 43,
    SPELL_EFFECT_SKILL_STEP                         = 44,
    SPELL_EFFECT_PLAY_MOVIE                         = 45,
    SPELL_EFFECT_SPAWN                              = 46,
    SPELL_EFFECT_TRADE_SKILL                        = 47,
    SPELL_EFFECT_STEALTH                            = 48,
    SPELL_EFFECT_DETECT                             = 49,
    SPELL_EFFECT_TRANS_DOOR                         = 50,
    SPELL_EFFECT_FORCE_CRITICAL_HIT                 = 51, // Unused (4.3.4)
    SPELL_EFFECT_GUARANTEE_HIT                      = 52, // Unused (4.3.4)
    SPELL_EFFECT_ENCHANT_ITEM                       = 53,
    SPELL_EFFECT_ENCHANT_ITEM_TEMPORARY             = 54,
    SPELL_EFFECT_TAMECREATURE                       = 55,
    SPELL_EFFECT_SUMMON_PET                         = 56,
    SPELL_EFFECT_LEARN_PET_SPELL                    = 57,
    SPELL_EFFECT_WEAPON_DAMAGE                      = 58,
    SPELL_EFFECT_CREATE_RANDOM_ITEM                 = 59,
    SPELL_EFFECT_PROFICIENCY                        = 60,
    SPELL_EFFECT_SEND_EVENT                         = 61,
    SPELL_EFFECT_POWER_BURN                         = 62,
    SPELL_EFFECT_THREAT                             = 63,
    SPELL_EFFECT_TRIGGER_SPELL                      = 64,
    SPELL_EFFECT_APPLY_AREA_AURA_RAID               = 65,
    SPELL_EFFECT_CREATE_MANA_GEM                    = 66,
    SPELL_EFFECT_HEAL_MAX_HEALTH                    = 67,
    SPELL_EFFECT_INTERRUPT_CAST                     = 68,
    SPELL_EFFECT_DISTRACT                           = 69,
    SPELL_EFFECT_PULL                               = 70,
    SPELL_EFFECT_PICKPOCKET                         = 71,
    SPELL_EFFECT_ADD_FARSIGHT                       = 72,
    SPELL_EFFECT_UNTRAIN_TALENTS                    = 73,
    SPELL_EFFECT_APPLY_GLYPH                        = 74,
    SPELL_EFFECT_HEAL_MECHANICAL                    = 75,
    SPELL_EFFECT_SUMMON_OBJECT_WILD                 = 76,
    SPELL_EFFECT_SCRIPT_EFFECT                      = 77,
    SPELL_EFFECT_ATTACK                             = 78,
    SPELL_EFFECT_SANCTUARY                          = 79,
    SPELL_EFFECT_ADD_COMBO_POINTS                   = 80,
    SPELL_EFFECT_CREATE_HOUSE                       = 81,
    SPELL_EFFECT_BIND_SIGHT                         = 82,
    SPELL_EFFECT_DUEL                               = 83,
    SPELL_EFFECT_STUCK                              = 84,
    SPELL_EFFECT_SUMMON_PLAYER                      = 85,
    SPELL_EFFECT_ACTIVATE_OBJECT                    = 86,
    SPELL_EFFECT_GAMEOBJECT_DAMAGE                  = 87,
    SPELL_EFFECT_GAMEOBJECT_REPAIR                  = 88,
    SPELL_EFFECT_GAMEOBJECT_SET_DESTRUCTION_STATE   = 89,
    SPELL_EFFECT_KILL_CREDIT                        = 90,
    SPELL_EFFECT_THREAT_ALL                         = 91,
    SPELL_EFFECT_ENCHANT_HELD_ITEM                  = 92,
    SPELL_EFFECT_FORCE_DESELECT                     = 93,
    SPELL_EFFECT_SELF_RESURRECT                     = 94,
    SPELL_EFFECT_SKINNING                           = 95,
    SPELL_EFFECT_CHARGE                             = 96,
    SPELL_EFFECT_CAST_BUTTON                        = 97,
    SPELL_EFFECT_KNOCK_BACK                         = 98,
    SPELL_EFFECT_DISENCHANT                         = 99,
    SPELL_EFFECT_INEBRIATE                          = 100,
    SPELL_EFFECT_FEED_PET                           = 101,
    SPELL_EFFECT_DISMISS_PET                        = 102,
    SPELL_EFFECT_REPUTATION                         = 103,
    SPELL_EFFECT_SUMMON_OBJECT_SLOT1                = 104,
    SPELL_EFFECT_SUMMON_OBJECT_SLOT2                = 105,
    SPELL_EFFECT_SUMMON_OBJECT_SLOT3                = 106,
    SPELL_EFFECT_SUMMON_OBJECT_SLOT4                = 107,
    SPELL_EFFECT_DISPEL_MECHANIC                    = 108,
    SPELL_EFFECT_RESURRECT_PET                      = 109,
    SPELL_EFFECT_DESTROY_ALL_TOTEMS                 = 110,
    SPELL_EFFECT_DURABILITY_DAMAGE                  = 111,
    SPELL_EFFECT_112                                = 112,
    SPELL_EFFECT_RESURRECT_NEW                      = 113,
    SPELL_EFFECT_ATTACK_ME                          = 114,
    SPELL_EFFECT_DURABILITY_DAMAGE_PCT              = 115,
    SPELL_EFFECT_SKIN_PLAYER_CORPSE                 = 116,
    SPELL_EFFECT_SPIRIT_HEAL                        = 117,
    SPELL_EFFECT_SKILL                              = 118,
    SPELL_EFFECT_APPLY_AREA_AURA_PET                = 119,
    SPELL_EFFECT_TELEPORT_GRAVEYARD                 = 120,
    SPELL_EFFECT_NORMALIZED_WEAPON_DMG              = 121,
    SPELL_EFFECT_122                                = 122, // Unused (4.3.4)
    SPELL_EFFECT_SEND_TAXI                          = 123,
    SPELL_EFFECT_PULL_TOWARDS                       = 124,
    SPELL_EFFECT_MODIFY_THREAT_PERCENT              = 125,
    SPELL_EFFECT_STEAL_BENEFICIAL_BUFF              = 126,
    SPELL_EFFECT_PROSPECTING                        = 127,
    SPELL_EFFECT_APPLY_AREA_AURA_FRIEND             = 128,
    SPELL_EFFECT_APPLY_AREA_AURA_ENEMY              = 129,
    SPELL_EFFECT_REDIRECT_THREAT                    = 130,
    SPELL_EFFECT_PLAY_SOUND                         = 131,
    SPELL_EFFECT_PLAY_MUSIC                         = 132,
    SPELL_EFFECT_UNLEARN_SPECIALIZATION             = 133,
    SPELL_EFFECT_KILL_CREDIT2                       = 134,
    SPELL_EFFECT_CALL_PET                           = 135,
    SPELL_EFFECT_HEAL_PCT                           = 136,
    SPELL_EFFECT_ENERGIZE_PCT                       = 137,
    SPELL_EFFECT_LEAP_BACK                          = 138,
    SPELL_EFFECT_CLEAR_QUEST                        = 139,
    SPELL_EFFECT_FORCE_CAST                         = 140,
    SPELL_EFFECT_FORCE_CAST_WITH_VALUE              = 141,
    SPELL_EFFECT_TRIGGER_SPELL_WITH_VALUE           = 142,
    SPELL_EFFECT_APPLY_AREA_AURA_OWNER              = 143,
    SPELL_EFFECT_KNOCK_BACK_DEST                    = 144,
    SPELL_EFFECT_PULL_TOWARDS_DEST                  = 145,
    SPELL_EFFECT_ACTIVATE_RUNE                      = 146,
    SPELL_EFFECT_QUEST_FAIL                         = 147,
    SPELL_EFFECT_TRIGGER_MISSILE_SPELL_WITH_VALUE   = 148,
    SPELL_EFFECT_CHARGE_DEST                        = 149,
    SPELL_EFFECT_QUEST_START                        = 150,
    SPELL_EFFECT_TRIGGER_SPELL_2                    = 151,
    SPELL_EFFECT_SUMMON_RAF_FRIEND                  = 152,
    SPELL_EFFECT_CREATE_TAMED_PET                   = 153,
    SPELL_EFFECT_DISCOVER_TAXI                      = 154,
    SPELL_EFFECT_TITAN_GRIP                         = 155,
    SPELL_EFFECT_ENCHANT_ITEM_PRISMATIC             = 156,
    SPELL_EFFECT_CREATE_ITEM_2                      = 157,
    SPELL_EFFECT_MILLING                            = 158,
    SPELL_EFFECT_ALLOW_RENAME_PET                   = 159,
    SPELL_EFFECT_FORCE_CAST_2                       = 160,
    SPELL_EFFECT_TALENT_SPEC_COUNT                  = 161,
    SPELL_EFFECT_TALENT_SPEC_SELECT                 = 162,
    SPELL_EFFECT_163                                = 163, // Unused (4.3.4)
    SPELL_EFFECT_REMOVE_AURA                        = 164,
    SPELL_EFFECT_DAMAGE_FROM_MAX_HEALTH_PCT         = 165,
    SPELL_EFFECT_GIVE_CURRENCY                      = 166,
    SPELL_EFFECT_UPDATE_PLAYER_PHASE                = 167,
    SPELL_EFFECT_ALLOW_CONTROL_PET                  = 168,
    SPELL_EFFECT_DESTROY_ITEM                       = 169,
    SPELL_EFFECT_UPDATE_ZONE_AURAS_AND_PHASES       = 170,
    SPELL_EFFECT_SUMMON_PERSONAL_GAMEOBJECT         = 171, // Summons gamebject
    SPELL_EFFECT_RESURRECT_WITH_AURA                = 172,
    SPELL_EFFECT_UNLOCK_GUILD_VAULT_TAB             = 173, // Guild tab unlocked (guild perk)
    SPELL_EFFECT_APPLY_AURA_2                       = 174,
    SPELL_EFFECT_175                                = 175, // Unused (4.3.4)
    SPELL_EFFECT_SANCTUARY_2                        = 176, // Some kind of sanctuary effect (Vanish)
    SPELL_EFFECT_177                                = 177,
    SPELL_EFFECT_178                                = 178, // Unused (4.3.4)
    SPELL_EFFECT_CREATE_AREATRIGGER                 = 179,
    SPELL_EFFECT_UPDATE_AREATRIGGER                 = 180, // Unused (4.3.4)
    SPELL_EFFECT_REMOVE_TALENT                      = 181, // Unused (4.3.4)
    SPELL_EFFECT_182                                = 182,
};

// Spell aura states
enum AuraStateType
{   // (C) used in caster aura state     (T) used in target aura state
    // (c) used in caster aura state-not (t) used in target aura state-not
    AURA_STATE_NONE                         = 0,            // C   |
    AURA_STATE_DEFENSE                      = 1,            // C   |
    AURA_STATE_HEALTHLESS_20_PERCENT        = 2,            // CcT |
    AURA_STATE_BERSERKING                   = 3,            // C T |
    AURA_STATE_FROZEN                       = 4,            //  c t| frozen target
    AURA_STATE_JUDGEMENT                    = 5,            // C   |
    AURA_STATE_UNKNOWN6                     = 6,            //     | not used
    AURA_STATE_HUNTER_PARRY                 = 7,            // C   |
    AURA_STATE_UNKNOWN8                     = 8,            //    t| test spells
    AURA_STATE_UNKNOWN9                     = 9,            //     |
    AURA_STATE_WARRIOR_VICTORY_RUSH         = 10,           // C   | warrior victory rush
    AURA_STATE_UNKNOWN11                    = 11,           // C  t| 60348 - Maelstrom Ready!, test spells
    AURA_STATE_FAERIE_FIRE                  = 12,           //  c t|
    AURA_STATE_HEALTHLESS_35_PERCENT        = 13,           // C T |
    AURA_STATE_CONFLAGRATE                  = 14,           //   T |
    AURA_STATE_SWIFTMEND                    = 15,           //   T |
    AURA_STATE_DEADLY_POISON                = 16,           //   T |
    AURA_STATE_ENRAGE                       = 17,           // C   |
    AURA_STATE_BLEEDING                     = 18,           //    T|
    AURA_STATE_UNKNOWN19                    = 19,           //     |
    AURA_STATE_UNKNOWN20                    = 20,           //  c  | only (45317 Suicide)
    AURA_STATE_UNKNOWN21                    = 21,           //     | not used
    AURA_STATE_UNKNOWN22                    = 22,           // C  t| varius spells (63884, 50240)
    AURA_STATE_HEALTH_ABOVE_75_PERCENT      = 23            // C   |
};

// Spell mechanics
enum Mechanics
{
    MECHANIC_NONE             = 0,
    MECHANIC_CHARM            = 1,
    MECHANIC_DISORIENTED      = 2,
    MECHANIC_DISARM           = 3,
    MECHANIC_DISTRACT         = 4,
    MECHANIC_FEAR             = 5,
    MECHANIC_GRIP             = 6,
    MECHANIC_ROOT             = 7,
    MECHANIC_SLOW_ATTACK      = 8,
    MECHANIC_SILENCE          = 9,
    MECHANIC_SLEEP            = 10,
    MECHANIC_SNARE            = 11,
    MECHANIC_STUN             = 12,
    MECHANIC_FREEZE           = 13,
    MECHANIC_KNOCKOUT         = 14,
    MECHANIC_BLEED            = 15,
    MECHANIC_BANDAGE          = 16,
    MECHANIC_POLYMORPH        = 17,
    MECHANIC_BANISH           = 18,
    MECHANIC_SHIELD           = 19,
    MECHANIC_SHACKLE          = 20,
    MECHANIC_MOUNT            = 21,
    MECHANIC_INFECTED         = 22,
    MECHANIC_TURN             = 23,
    MECHANIC_HORROR           = 24,
    MECHANIC_INVULNERABILITY  = 25,
    MECHANIC_INTERRUPT        = 26,
    MECHANIC_DAZE             = 27,
    MECHANIC_DISCOVERY        = 28,
    MECHANIC_IMMUNE_SHIELD    = 29,                         // Divine (Blessing) Shield/Protection and Ice Block
    MECHANIC_SAPPED           = 30,
    MECHANIC_ENRAGED          = 31,
    MECHANIC_WOUNDED          = 32,
};

// Spell dispel type
enum DispelType
{
    DISPEL_NONE         = 0,
    DISPEL_MAGIC        = 1,
    DISPEL_CURSE        = 2,
    DISPEL_DISEASE      = 3,
    DISPEL_POISON       = 4,
    DISPEL_STEALTH      = 5,
    DISPEL_INVISIBILITY = 6,
    DISPEL_ALL          = 7,
    DISPEL_SPE_NPC_ONLY = 8,
    DISPEL_ENRAGE       = 9,
    DISPEL_ZG_TICKET    = 10,
    DESPEL_OLD_UNUSED   = 11
};

enum Targets
{
    TARGET_NONE                                 = 0,
    TARGET_UNIT_CASTER                          = 1,
    TARGET_UNIT_NEARBY_ENEMY                    = 2,
    TARGET_UNIT_NEARBY_ALLY                     = 3,
    TARGET_UNIT_NEARBY_PARTY                    = 4,
    TARGET_UNIT_PET                             = 5,
    TARGET_UNIT_TARGET_ENEMY                    = 6,
    TARGET_UNIT_SRC_AREA_ENTRY                  = 7,
    TARGET_UNIT_DEST_AREA_ENTRY                 = 8,
    TARGET_DEST_HOME                            = 9,
    TARGET_UNK_10                               = 10,
    TARGET_UNIT_SRC_AREA_UNK_11                 = 11,
    TARGET_UNK_12                               = 12,
    TARGET_UNK_13                               = 13,
    TARGET_UNK_14                               = 14,
    TARGET_UNIT_SRC_AREA_ENEMY                  = 15,
    TARGET_UNIT_DEST_AREA_ENEMY                 = 16,
    TARGET_DEST_DB                              = 17,
    TARGET_DEST_CASTER                          = 18,
    TARGET_UNK_19                               = 19,
    TARGET_UNIT_CASTER_AREA_PARTY               = 20,
    TARGET_UNIT_TARGET_ALLY                     = 21,
    TARGET_SRC_CASTER                           = 22,
    TARGET_GAMEOBJECT_TARGET                    = 23,
    TARGET_UNIT_CONE_ENEMY_24                   = 24,
    TARGET_UNIT_TARGET_ANY                      = 25,
    TARGET_GAMEOBJECT_ITEM_TARGET               = 26,
    TARGET_UNIT_MASTER                          = 27,
    TARGET_DEST_DYNOBJ_ENEMY                    = 28,
    TARGET_DEST_DYNOBJ_ALLY                     = 29,
    TARGET_UNIT_SRC_AREA_ALLY                   = 30,
    TARGET_UNIT_DEST_AREA_ALLY                  = 31,
    TARGET_DEST_CASTER_SUMMON                   = 32, // front left, doesn't use radius
    TARGET_UNIT_SRC_AREA_PARTY                  = 33,
    TARGET_UNIT_DEST_AREA_PARTY                 = 34,
    TARGET_UNIT_TARGET_PARTY                    = 35,
    TARGET_DEST_CASTER_UNK_36                   = 36,
    TARGET_UNIT_LASTTARGET_AREA_PARTY           = 37,
    TARGET_UNIT_NEARBY_ENTRY                    = 38,
    TARGET_DEST_CASTER_FISHING                  = 39,
    TARGET_GAMEOBJECT_NEARBY_ENTRY              = 40,
    TARGET_DEST_CASTER_FRONT_RIGHT              = 41,
    TARGET_DEST_CASTER_BACK_RIGHT               = 42,
    TARGET_DEST_CASTER_BACK_LEFT                = 43,
    TARGET_DEST_CASTER_FRONT_LEFT               = 44,
    TARGET_UNIT_TARGET_CHAINHEAL_ALLY           = 45,
    TARGET_DEST_NEARBY_ENTRY                    = 46,
    TARGET_DEST_CASTER_FRONT                    = 47,
    TARGET_DEST_CASTER_BACK                     = 48,
    TARGET_DEST_CASTER_RIGHT                    = 49,
    TARGET_DEST_CASTER_LEFT                     = 50,
    TARGET_GAMEOBJECT_SRC_AREA                  = 51,
    TARGET_GAMEOBJECT_DEST_AREA                 = 52,
    TARGET_DEST_TARGET_ENEMY                    = 53,
    TARGET_UNIT_CONE_180_DEG_ENEMY              = 54, // Defaults to 180 if ConeDegrees is not set
    TARGET_DEST_CASTER_FRONT_LEAP               = 55, // for a leap spell
    TARGET_UNIT_CASTER_AREA_RAID                = 56,
    TARGET_UNIT_TARGET_RAID                     = 57,
    TARGET_UNIT_NEARBY_RAID                     = 58,
    TARGET_UNIT_CONE_ALLY                       = 59,
    TARGET_UNIT_CONE_ENTRY                      = 60,
    TARGET_UNIT_TARGET_AREA_RAID_CLASS          = 61,
    TARGET_DEST_CASTER_GROUND                   = 62,
    TARGET_DEST_TARGET_ANY                      = 63,
    TARGET_DEST_TARGET_FRONT                    = 64,
    TARGET_DEST_TARGET_BACK                     = 65,
    TARGET_DEST_TARGET_RIGHT                    = 66,
    TARGET_DEST_TARGET_LEFT                     = 67,
    TARGET_DEST_TARGET_FRONT_RIGHT              = 68,
    TARGET_DEST_TARGET_BACK_RIGHT               = 69,
    TARGET_DEST_TARGET_BACK_LEFT                = 70,
    TARGET_DEST_TARGET_FRONT_LEFT               = 71,
    TARGET_DEST_CASTER_RANDOM                   = 72,
    TARGET_DEST_CASTER_RADIUS                   = 73,
    TARGET_DEST_TARGET_RANDOM                   = 74,
    TARGET_DEST_TARGET_RADIUS                   = 75,
    TARGET_DEST_CHANNEL_TARGET                  = 76,
    TARGET_UNIT_CHANNEL_TARGET                  = 77,
    TARGET_DEST_DEST_FRONT                      = 78,
    TARGET_DEST_DEST_BACK                       = 79,
    TARGET_DEST_DEST_RIGHT                      = 80,
    TARGET_DEST_DEST_LEFT                       = 81,
    TARGET_DEST_DEST_FRONT_RIGHT                = 82,
    TARGET_DEST_DEST_BACK_RIGHT                 = 83,
    TARGET_DEST_DEST_BACK_LEFT                  = 84,
    TARGET_DEST_DEST_FRONT_LEFT                 = 85,
    TARGET_DEST_DEST_RANDOM                     = 86,
    TARGET_DEST_DEST                            = 87,
    TARGET_DEST_DYNOBJ_NONE                     = 88,
    TARGET_DEST_TRAJ                            = 89,
    TARGET_UNIT_TARGET_MINIPET                  = 90,
    TARGET_DEST_DEST_RADIUS                     = 91,
    TARGET_UNIT_SUMMONER                        = 92,
    TARGET_CORPSE_SRC_AREA_ENEMY                = 93, // NYI
    TARGET_UNIT_VEHICLE                         = 94,
    TARGET_UNIT_TARGET_PASSENGER                = 95,
    TARGET_UNIT_PASSENGER_0                     = 96,
    TARGET_UNIT_PASSENGER_1                     = 97,
    TARGET_UNIT_PASSENGER_2                     = 98,
    TARGET_UNIT_PASSENGER_3                     = 99,
    TARGET_UNIT_PASSENGER_4                     = 100,
    TARGET_UNIT_PASSENGER_5                     = 101,
    TARGET_UNIT_PASSENGER_6                     = 102,
    TARGET_UNIT_PASSENGER_7                     = 103,
    TARGET_UNIT_CONE_CASTER_TO_DEST_ENEMY       = 104,
    TARGET_UNIT_CASTER_AND_PASSENGERS           = 105,
    TARGET_DEST_CHANNEL_CASTER                  = 106,
    TARGET_DEST_NEARBY_ENTRY_2                  = 107,
    TARGET_GAMEOBJECT_CONE_CASTER_TO_DEST_ENEMY = 108,
    TARGET_GAMEOBJECT_CONE_CASTER_TO_DEST_ALLY  = 109,
    TARGET_UNIT_CONE_CASTER_TO_DEST_ENTRY       = 110, // 1 spell
    TARGET_UNK_111                              = 111,
    TARGET_DEST_TARGET_ANY_2                    = 112, // 1 Spell
    TARGET_UNK_113                              = 113,
    TARGET_UNK_114                              = 114,
    TARGET_UNK_115                              = 115,
    TARGET_UNK_116                              = 116,
    TARGET_UNK_117                              = 117,
    TARGET_UNIT_TARGET_ALLY_OR_RAID             = 118, // If target is in your party or raid, all party and raid members will be affected
    TARGET_CORPSE_SRC_AREA_RAID                 = 119,
    TARGET_UNIT_CASTER_AND_SUMMONS              = 120,
    TARGET_CORPSE_TARGET_ALLY                   = 121,
    TARGET_UNIT_AREA_THREAT_LIST                = 122,
    TARGET_UNIT_AREA_TAP_LIST                   = 123,
    TARGET_UNIT_TARGET_TAP_LIST                 = 124,
    TARGET_DEST_CASTER_GROUND_2                 = 125, // 1 spell in 4.3.4
    TARGET_UNIT_AREA_ENEMY                      = 126, // 1 spell in 4.3.4 (checked up until 8.3.0)
    TARGET_UNK_127                              = 127,
};

enum SpellDmgClass
{
    SPELL_DAMAGE_CLASS_NONE     = 0,
    SPELL_DAMAGE_CLASS_MAGIC    = 1,
    SPELL_DAMAGE_CLASS_MELEE    = 2,
    SPELL_DAMAGE_CLASS_RANGED   = 3,
};

enum SkillType
{
    SKILL_NONE                     = 0,

    SKILL_FROST                    = 6,
    SKILL_FIRE                     = 8,
    SKILL_ARMS                     = 26,
    SKILL_COMBAT                   = 38,
    SKILL_SUBTLETY                 = 39,
    SKILL_SWORDS                   = 43,
    SKILL_AXES                     = 44,
    SKILL_BOWS                     = 45,
    SKILL_GUNS                     = 46,
    SKILL_BEAST_MASTERY            = 50,
    SKILL_SURVIVAL                 = 51,
    SKILL_MACES                    = 54,
    SKILL_2H_SWORDS                = 55,
    SKILL_HOLY                     = 56,
    SKILL_SHADOW                   = 78,
    SKILL_DEFENSE                  = 95,
    SKILL_LANG_COMMON              = 98,
    SKILL_RACIAL_DWARVEN           = 101,
    SKILL_LANG_ORCISH              = 109,
    SKILL_LANG_DWARVEN             = 111,
    SKILL_LANG_DARNASSIAN          = 113,
    SKILL_LANG_TAURAHE             = 115,
    SKILL_DUAL_WIELD               = 118,
    SKILL_RACIAL_TAUREN            = 124,
    SKILL_ORC_RACIAL               = 125,
    SKILL_RACIAL_NIGHT_ELF         = 126,
    SKILL_FIRST_AID                = 129,
    SKILL_FERAL_COMBAT             = 134,
    SKILL_STAVES                   = 136,
    SKILL_LANG_THALASSIAN          = 137,
    SKILL_LANG_DRACONIC            = 138,
    SKILL_LANG_DEMON_TONGUE        = 139,
    SKILL_LANG_TITAN               = 140,
    SKILL_LANG_OLD_TONGUE          = 141,
    SKILL_SURVIVAL2                = 142,
    SKILL_RIDING_HORSE             = 148,
    SKILL_RIDING_WOLF              = 149,
    SKILL_RIDING_TIGER             = 150,
    SKILL_RIDING_RAM               = 152,
    SKILL_SWIMING                  = 155,
    SKILL_2H_MACES                 = 160,
    SKILL_UNARMED                  = 162,
    SKILL_MARKSMANSHIP             = 163,
    SKILL_BLACKSMITHING            = 164,
    SKILL_LEATHERWORKING           = 165,
    SKILL_ALCHEMY                  = 171,
    SKILL_2H_AXES                  = 172,
    SKILL_DAGGERS                  = 173,
    SKILL_THROWN                   = 176,
    SKILL_HERBALISM                = 182,
    SKILL_GENERIC_DND              = 183,
    SKILL_RETRIBUTION              = 184,
    SKILL_COOKING                  = 185,
    SKILL_MINING                   = 186,
    SKILL_PET_IMP                  = 188,
    SKILL_PET_FELHUNTER            = 189,
    SKILL_TAILORING                = 197,
    SKILL_ENGINEERING              = 202,
    SKILL_PET_SPIDER               = 203,
    SKILL_PET_VOIDWALKER           = 204,
    SKILL_PET_SUCCUBUS             = 205,
    SKILL_PET_INFERNAL             = 206,
    SKILL_PET_DOOMGUARD            = 207,
    SKILL_PET_WOLF                 = 208,
    SKILL_PET_CAT                  = 209,
    SKILL_PET_BEAR                 = 210,
    SKILL_PET_BOAR                 = 211,
    SKILL_PET_CROCILISK            = 212,
    SKILL_PET_CARRION_BIRD         = 213,
    SKILL_PET_CRAB                 = 214,
    SKILL_PET_GORILLA              = 215,
    SKILL_PET_RAPTOR               = 217,
    SKILL_PET_TALLSTRIDER          = 218,
    SKILL_RACIAL_UNDED             = 220,
    SKILL_CROSSBOWS                = 226,
    SKILL_WANDS                    = 228,
    SKILL_POLEARMS                 = 229,
    SKILL_PET_SCORPID              = 236,
    SKILL_ARCANE                   = 237,
    SKILL_PET_TURTLE               = 251,
    SKILL_ASSASSINATION            = 253,
    SKILL_FURY                     = 256,
    SKILL_PROTECTION               = 257,
    SKILL_PROTECTION2              = 267,
    SKILL_PET_TALENTS              = 270,
    SKILL_PLATE_MAIL               = 293,
    SKILL_LANG_GNOMISH             = 313,
    SKILL_LANG_TROLL               = 315,
    SKILL_ENCHANTING               = 333,
    SKILL_DEMONOLOGY               = 354,
    SKILL_AFFLICTION               = 355,
    SKILL_FISHING                  = 356,
    SKILL_ENHANCEMENT              = 373,
    SKILL_RESTORATION              = 374,
    SKILL_ELEMENTAL_COMBAT         = 375,
    SKILL_SKINNING                 = 393,
    SKILL_MAIL                     = 413,
    SKILL_LEATHER                  = 414,
    SKILL_CLOTH                    = 415,
    SKILL_SHIELD                   = 433,
    SKILL_FIST_WEAPONS             = 473,
    SKILL_RIDING_RAPTOR            = 533,
    SKILL_RIDING_MECHANOSTRIDER    = 553,
    SKILL_RIDING_UNDEAD_HORSE      = 554,
    SKILL_RESTORATION2             = 573,
    SKILL_BALANCE                  = 574,
    SKILL_DESTRUCTION              = 593,
    SKILL_HOLY2                    = 594,
    SKILL_DISCIPLINE               = 613,
    SKILL_LOCKPICKING              = 633,
    SKILL_PET_BAT                  = 653,
    SKILL_PET_HYENA                = 654,
    SKILL_PET_BIRD_OF_PREY         = 655,
    SKILL_PET_WIND_SERPENT         = 656,
    SKILL_LANG_GUTTERSPEAK         = 673,
    SKILL_RIDING_KODO              = 713,
    SKILL_RACIAL_TROLL             = 733,
    SKILL_RACIAL_GNOME             = 753,
    SKILL_RACIAL_HUMAN             = 754,
    SKILL_JEWELCRAFTING            = 755,
    SKILL_RACIAL_BLOODELF          = 756,
    SKILL_PET_EVENT_RC             = 758,   // SkillCategory = -1
    SKILL_LANG_DRAENEI             = 759,
    SKILL_RACIAL_DRAENEI           = 760,
    SKILL_PET_FELGUARD             = 761,
    SKILL_RIDING                   = 762,
    SKILL_PET_DRAGONHAWK           = 763,
    SKILL_PET_NETHER_RAY           = 764,
    SKILL_PET_SPOREBAT             = 765,
    SKILL_PET_WARP_STALKER         = 766,
    SKILL_PET_RAVAGER              = 767,
    SKILL_PET_SERPENT              = 768,
    SKILL_INTERNAL                 = 769,
    SKILL_DK_BLOOD                 = 770,
    SKILL_DK_FROST                 = 771,
    SKILL_DK_UNHOLY                = 772,
    SKILL_INSCRIPTION              = 773,
    SKILL_PET_MOTH                 = 775,
    SKILL_RUNEFORGING              = 776,
    SKILL_MOUNTS                   = 777,
    SKILL_COMPANIONS               = 778,
    SKILL_PET_EXOTIC_CHIMAERA      = 780,
    SKILL_PET_EXOTIC_DEVILSAUR     = 781,
    SKILL_PET_GHOUL                = 782,
    SKILL_PET_EXOTIC_SILITHID      = 783,
    SKILL_PET_EXOTIC_WORM          = 784,
    SKILL_PET_WASP                 = 785,
    SKILL_PET_EXOTIC_RHINO         = 786,
    SKILL_PET_EXOTIC_CORE_HOUND    = 787,
    SKILL_PET_EXOTIC_SPIRIT_BEAST  = 788,
    SKILL_RACIAL_WORGEN            = 789,
    SKILL_RACIAL_GOBLIN            = 790,
    SKILL_LANG_WORGEN              = 791,
    SKILL_LANG_GOBLIN              = 792,
    SKILL_ARCHAEOLOGY              = 794,
    SKILL_GENERAL_HUNTER           = 795,
    SKILL_GENERAL_DEATH_KNIGHT     = 796,
    SKILL_GENERAL_ROGUE            = 797,
    SKILL_GENERAL_DRUID            = 798,
    SKILL_GENERAL_MAGE             = 799,
    SKILL_GENERAL_PALADIN          = 800,
    SKILL_GENERAL_SHAMAN           = 801,
    SKILL_GENERAL_WARLOCK          = 802,
    SKILL_GENERAL_WARRIOR          = 803,
    SKILL_GENERAL_PRIEST           = 804,
    SKILL_PET_WATER_ELEMENTAL      = 805,
    SKILL_PET_FOX                  = 808,
    SKILL_ALL_GLYPHS               = 810,
    SKILL_PET_DOG                  = 811,
    SKILL_PET_MONKEY               = 815,
    SKILL_PET_SHALE_SPIDER         = 817,
    SKILL_PET_BEETLE               = 818,
    SKILL_ALL_GUILD_PERKS          = 821,
    SKILL_PET_HYDRA                = 824
};

enum SpellPreventionType
{
    SPELL_PREVENTION_TYPE_NONE      = 0,
    SPELL_PREVENTION_TYPE_SILENCE   = 1,
    SPELL_PREVENTION_TYPE_PACIFY    = 2,
    SPELL_PREVENTION_TYPE_UNK       = 3, // Only a few spells have this, but most of the should be interruptable.
    SPELL_PREVENTION_TYPE_NO_ACTIONS= 4
};

enum SpellCastTargetFlags
{
    TARGET_FLAG_NONE            = 0x00000000,               // 0
    TARGET_FLAG_UNUSED_1        = 0x00000001,               // 1 not used
    TARGET_FLAG_UNIT            = 0x00000002,               // 2 pguid
    TARGET_FLAG_UNIT_RAID       = 0x00000004,               // 3 not sent, used to validate target (if raid member)
    TARGET_FLAG_UNIT_PARTY      = 0x00000008,               // 4 not sent, used to validate target (if party member)
    TARGET_FLAG_ITEM            = 0x00000010,               // 5 pguid
    TARGET_FLAG_SOURCE_LOCATION = 0x00000020,               // 6 pguid, 3 float
    TARGET_FLAG_DEST_LOCATION   = 0x00000040,               // 7 pguid, 3 float
    TARGET_FLAG_UNIT_ENEMY      = 0x00000080,               // 8 not sent, used to validate target (if enemy)
    TARGET_FLAG_UNIT_ALLY       = 0x00000100,               // 9 not sent, used to validate target (if ally)
    TARGET_FLAG_CORPSE_ENEMY    = 0x00000200,               // 10 pguid
    TARGET_FLAG_UNIT_DEAD       = 0x00000400,               // 11 not sent, used to validate target (if dead creature)
    TARGET_FLAG_GAMEOBJECT      = 0x00000800,               // 12 pguid, used with TARGET_GAMEOBJECT_TARGET
    TARGET_FLAG_TRADE_ITEM      = 0x00001000,               // 13 pguid
    TARGET_FLAG_STRING          = 0x00002000,               // 14 string
    TARGET_FLAG_GAMEOBJECT_ITEM = 0x00004000,               // 15 not sent, used with TARGET_GAMEOBJECT_ITEM_TARGET
    TARGET_FLAG_CORPSE_ALLY     = 0x00008000,               // 16 pguid
    TARGET_FLAG_UNIT_MINIPET    = 0x00010000,               // 17 pguid, used to validate target (if non combat pet)
    TARGET_FLAG_GLYPH_SLOT      = 0x00020000,               // 18 used in glyph spells
    TARGET_FLAG_DEST_TARGET     = 0x00040000,               // 19 sometimes appears with DEST_TARGET spells (may appear or not for a given spell)
    TARGET_FLAG_EXTRA_TARGETS   = 0x00080000,               // 20 uint32 counter, loop { vec3 - screen position (?), guid }, not used so far
    TARGET_FLAG_UNIT_PASSENGER  = 0x00100000,               // 21 guessed, used to validate target (if vehicle passenger)
};

enum CreatureType
{
    CREATURE_TYPE_BEAST            = 1,
    CREATURE_TYPE_DRAGONKIN        = 2,
    CREATURE_TYPE_DEMON            = 3,
    CREATURE_TYPE_ELEMENTAL        = 4,
    CREATURE_TYPE_GIANT            = 5,
    CREATURE_TYPE_UNDEAD           = 6,
    CREATURE_TYPE_HUMANOID         = 7,
    CREATURE_TYPE_CRITTER          = 8,
    CREATURE_TYPE_MECHANICAL       = 9,
    CREATURE_TYPE_NOT_SPECIFIED    = 10,
    CREATURE_TYPE_TOTEM            = 11,
    CREATURE_TYPE_NON_COMBAT_PET   = 12,
    CREATURE_TYPE_GAS_CLOUD        = 13
};

enum ShapeshiftForm
{
    FORM_CAT                = 0x01,     // 1
    FORM_TREE               = 0x02,     // 2
    FORM_TRAVEL             = 0x03,     // 3
    FORM_AQUA               = 0x04,     // 4
    FORM_BEAR               = 0x05,     // 5
    FORM_AMBIENT            = 0x06,     // 6
    FORM_GHOUL              = 0x07,     // 7
    FORM_DIREBEAR           = 0x08,     // 8 Removed in 4.0.1
    FORM_STEVES_GHOUL       = 0x09,     // 9
    FORM_THARONJA_SKELETON  = 0x0A,     // 10
    FORM_TEST_OF_STRENGTH   = 0x0B,     // 11
    FORM_BLB_PLAYER         = 0x0C,     // 12
    FORM_SHADOW_DANCE       = 0x0D,     // 13
    FORM_CREATUREBEAR       = 0x0E,     // 14
    FORM_CREATURECAT        = 0x0F,     // 15
    FORM_GHOSTWOLF          = 0x10,     // 16
    FORM_BATTLESTANCE       = 0x11,     // 17
    FORM_DEFENSIVESTANCE    = 0x12,     // 18
    FORM_BERSERKERSTANCE    = 0x13,     // 19
    FORM_TEST               = 0x14,     // 20
    FORM_ZOMBIE             = 0x15,     // 21
    FORM_METAMORPHOSIS      = 0x16,     // 22
    FORM_UNK1               = 0x17,     // 23
    FORM_UNK2               = 0x18,     // 24
    FORM_UNDEAD             = 0x19,     // 25
    FORM_MASTER_ANGLER      = 0x1A,     // 26
    FORM_FLIGHT_EPIC        = 0x1B,     // 27
    FORM_SHADOW             = 0x1C,     // 28
    FORM_FLIGHT             = 0x1D,     // 29
    FORM_STEALTH            = 0x1E,     // 30
    FORM_MOONKIN            = 0x1F,     // 31
    FORM_SPIRITOFREDEMPTION = 0x20,     // 32
    FORM_GLADIATOR_STANCE   = 0x21      // 33
};

enum ItemClass
{
    ITEM_CLASS_CONSUMABLE                       = 0,
    ITEM_CLASS_CONTAINER                        = 1,
    ITEM_CLASS_WEAPON                           = 2,
    ITEM_CLASS_GEM                              = 3,
    ITEM_CLASS_ARMOR                            = 4,
    ITEM_CLASS_REAGENT                          = 5,
    ITEM_CLASS_PROJECTILE                       = 6,
    ITEM_CLASS_TRADE_GOODS                      = 7,
    ITEM_CLASS_GENERIC                          = 8,  // OBSOLETE
    ITEM_CLASS_RECIPE                           = 9,
    ITEM_CLASS_MONEY                            = 10, // OBSOLETE
    ITEM_CLASS_QUIVER                           = 11,
    ITEM_CLASS_QUEST                            = 12,
    ITEM_CLASS_KEY                              = 13,
    ITEM_CLASS_PERMANENT                        = 14, // OBSOLETE
    ITEM_CLASS_MISCELLANEOUS                    = 15,
    ITEM_CLASS_GLYPH                            = 16
};

enum ItemSubclassWeapon
{
    ITEM_SUBCLASS_WEAPON_AXE                    = 0,  // One-Handed Axes
    ITEM_SUBCLASS_WEAPON_AXE2                   = 1,  // Two-Handed Axes
    ITEM_SUBCLASS_WEAPON_BOW                    = 2,
    ITEM_SUBCLASS_WEAPON_GUN                    = 3,
    ITEM_SUBCLASS_WEAPON_MACE                   = 4,  // One-Handed Maces
    ITEM_SUBCLASS_WEAPON_MACE2                  = 5,  // Two-Handed Maces
    ITEM_SUBCLASS_WEAPON_POLEARM                = 6,
    ITEM_SUBCLASS_WEAPON_SWORD                  = 7,  // One-Handed Swords
    ITEM_SUBCLASS_WEAPON_SWORD2                 = 8,  // Two-Handed Swords
    ITEM_SUBCLASS_WEAPON_Obsolete               = 9,
    ITEM_SUBCLASS_WEAPON_STAFF                  = 10,
    ITEM_SUBCLASS_WEAPON_EXOTIC                 = 11, // One-Handed Exotics
    ITEM_SUBCLASS_WEAPON_EXOTIC2                = 12, // Two-Handed Exotics
    ITEM_SUBCLASS_WEAPON_FIST_WEAPON            = 13,
    ITEM_SUBCLASS_WEAPON_MISCELLANEOUS          = 14,
    ITEM_SUBCLASS_WEAPON_DAGGER                 = 15,
    ITEM_SUBCLASS_WEAPON_THROWN                 = 16,
    ITEM_SUBCLASS_WEAPON_SPEAR                  = 17,
    ITEM_SUBCLASS_WEAPON_CROSSBOW               = 18,
    ITEM_SUBCLASS_WEAPON_WAND                   = 19,
    ITEM_SUBCLASS_WEAPON_FISHING_POLE           = 20
};

enum ItemSubclassJunk
{
    ITEM_SUBCLASS_JUNK                          = 0,
    ITEM_SUBCLASS_JUNK_REAGENT                  = 1,
    ITEM_SUBCLASS_JUNK_PET                      = 2,
    ITEM_SUBCLASS_JUNK_HOLIDAY                  = 3,
    ITEM_SUBCLASS_JUNK_OTHER                    = 4,
    ITEM_SUBCLASS_JUNK_MOUNT                    = 5,
    ITEM_SUBCLASS_JUNK_UNK12                    = 12, // 1 item (37677)
};

enum InventoryType
{
    INVTYPE_NON_EQUIP                           = 0,
    INVTYPE_HEAD                                = 1,
    INVTYPE_NECK                                = 2,
    INVTYPE_SHOULDERS                           = 3,
    INVTYPE_BODY                                = 4,
    INVTYPE_CHEST                               = 5,
    INVTYPE_WAIST                               = 6,
    INVTYPE_LEGS                                = 7,
    INVTYPE_FEET                                = 8,
    INVTYPE_WRISTS                              = 9,
    INVTYPE_HANDS                               = 10,
    INVTYPE_FINGER                              = 11,
    INVTYPE_TRINKET                             = 12,
    INVTYPE_WEAPON                              = 13,
    INVTYPE_SHIELD                              = 14,
    INVTYPE_RANGED                              = 15,
    INVTYPE_CLOAK                               = 16,
    INVTYPE_2HWEAPON                            = 17,
    INVTYPE_BAG                                 = 18,
    INVTYPE_TABARD                              = 19,
    INVTYPE_ROBE                                = 20,
    INVTYPE_WEAPONMAINHAND                      = 21,
    INVTYPE_WEAPONOFFHAND                       = 22,
    INVTYPE_HOLDABLE                            = 23,
    INVTYPE_AMMO                                = 24,
    INVTYPE_THROWN                              = 25,
    INVTYPE_RANGEDRIGHT                         = 26,
    INVTYPE_QUIVER                              = 27,
    INVTYPE_RELIC                               = 28
};

enum Powers : int8_t
{
    POWER_MANA                          = 0,
    POWER_RAGE                          = 1,
    POWER_FOCUS                         = 2,
    POWER_ENERGY                        = 3,
    POWER_UNUSED                        = 4,
    POWER_RUNE                          = 5,
    POWER_RUNIC_POWER                   = 6,
    POWER_SOUL_SHARDS                   = 7,
    POWER_ECLIPSE                       = 8,
    POWER_HOLY_POWER                    = 9,
    POWER_ALTERNATE_POWER               = 10,           // Used in some quests
    MAX_POWERS                          = 11,
    POWER_ALL                           = 127,          // default for class?
    POWER_HEALTH                        = -2            // (-2 as signed value)
};

enum AuraType
{
    SPELL_AURA_NONE                                         = 0,
    SPELL_AURA_BIND_SIGHT                                   = 1,
    SPELL_AURA_MOD_POSSESS                                  = 2,
    SPELL_AURA_PERIODIC_DAMAGE                              = 3,
    SPELL_AURA_DUMMY                                        = 4,
    SPELL_AURA_MOD_CONFUSE                                  = 5,
    SPELL_AURA_MOD_CHARM                                    = 6,
    SPELL_AURA_MOD_FEAR                                     = 7,
    SPELL_AURA_PERIODIC_HEAL                                = 8,
    SPELL_AURA_MOD_ATTACKSPEED                              = 9,
    SPELL_AURA_MOD_THREAT                                   = 10,
    SPELL_AURA_MOD_TAUNT                                    = 11,
    SPELL_AURA_MOD_STUN                                     = 12,
    SPELL_AURA_MOD_DAMAGE_DONE                              = 13,
    SPELL_AURA_MOD_DAMAGE_TAKEN                             = 14,
    SPELL_AURA_DAMAGE_SHIELD                                = 15,
    SPELL_AURA_MOD_STEALTH                                  = 16,
    SPELL_AURA_MOD_STEALTH_DETECT                           = 17,
    SPELL_AURA_MOD_INVISIBILITY                             = 18,
    SPELL_AURA_MOD_INVISIBILITY_DETECT                      = 19,
    SPELL_AURA_OBS_MOD_HEALTH                               = 20,   // 20, 21 unofficial
    SPELL_AURA_OBS_MOD_POWER                                = 21,
    SPELL_AURA_MOD_RESISTANCE                               = 22,
    SPELL_AURA_PERIODIC_TRIGGER_SPELL                       = 23,
    SPELL_AURA_PERIODIC_ENERGIZE                            = 24,
    SPELL_AURA_MOD_PACIFY                                   = 25,
    SPELL_AURA_MOD_ROOT                                     = 26,
    SPELL_AURA_MOD_SILENCE                                  = 27,
    SPELL_AURA_REFLECT_SPELLS                               = 28,
    SPELL_AURA_MOD_STAT                                     = 29,
    SPELL_AURA_MOD_SKILL                                    = 30,
    SPELL_AURA_MOD_INCREASE_SPEED                           = 31,
    SPELL_AURA_MOD_INCREASE_MOUNTED_SPEED                   = 32,
    SPELL_AURA_MOD_DECREASE_SPEED                           = 33,
    SPELL_AURA_MOD_INCREASE_HEALTH                          = 34,
    SPELL_AURA_MOD_INCREASE_ENERGY                          = 35,
    SPELL_AURA_MOD_SHAPESHIFT                               = 36,
    SPELL_AURA_EFFECT_IMMUNITY                              = 37,
    SPELL_AURA_STATE_IMMUNITY                               = 38,
    SPELL_AURA_SCHOOL_IMMUNITY                              = 39,
    SPELL_AURA_DAMAGE_IMMUNITY                              = 40,
    SPELL_AURA_DISPEL_IMMUNITY                              = 41,
    SPELL_AURA_PROC_TRIGGER_SPELL                           = 42,
    SPELL_AURA_PROC_TRIGGER_DAMAGE                          = 43,
    SPELL_AURA_TRACK_CREATURES                              = 44,
    SPELL_AURA_TRACK_RESOURCES                              = 45,
    SPELL_AURA_46                                           = 46,   // Ignore all Gear test spells
    SPELL_AURA_MOD_PARRY_PERCENT                            = 47,
    SPELL_AURA_48                                           = 48,   // One periodic spell
    SPELL_AURA_MOD_DODGE_PERCENT                            = 49,
    SPELL_AURA_MOD_CRITICAL_HEALING_AMOUNT                  = 50,
    SPELL_AURA_MOD_BLOCK_PERCENT                            = 51,
    SPELL_AURA_MOD_WEAPON_CRIT_PERCENT                      = 52,
    SPELL_AURA_PERIODIC_LEECH                               = 53,
    SPELL_AURA_MOD_HIT_CHANCE                               = 54,
    SPELL_AURA_MOD_SPELL_HIT_CHANCE                         = 55,
    SPELL_AURA_TRANSFORM                                    = 56,
    SPELL_AURA_MOD_SPELL_CRIT_CHANCE                        = 57,
    SPELL_AURA_MOD_INCREASE_SWIM_SPEED                      = 58,
    SPELL_AURA_MOD_DAMAGE_DONE_CREATURE                     = 59,
    SPELL_AURA_MOD_PACIFY_SILENCE                           = 60,
    SPELL_AURA_MOD_SCALE                                    = 61,
    SPELL_AURA_PERIODIC_HEALTH_FUNNEL                       = 62,
    SPELL_AURA_63                                           = 63,   // old SPELL_AURA_PERIODIC_MANA_FUNNEL
    SPELL_AURA_PERIODIC_MANA_LEECH                          = 64,
    SPELL_AURA_MOD_CASTING_SPEED_NOT_STACK                  = 65,
    SPELL_AURA_FEIGN_DEATH                                  = 66,
    SPELL_AURA_MOD_DISARM                                   = 67,
    SPELL_AURA_MOD_STALKED                                  = 68,
    SPELL_AURA_SCHOOL_ABSORB                                = 69,
    SPELL_AURA_EXTRA_ATTACKS                                = 70,
    SPELL_AURA_MOD_SPELL_CRIT_CHANCE_SCHOOL                 = 71,
    SPELL_AURA_MOD_POWER_COST_SCHOOL_PCT                    = 72,
    SPELL_AURA_MOD_POWER_COST_SCHOOL                        = 73,
    SPELL_AURA_REFLECT_SPELLS_SCHOOL                        = 74,
    SPELL_AURA_MOD_LANGUAGE                                 = 75,
    SPELL_AURA_FAR_SIGHT                                    = 76,
    SPELL_AURA_MECHANIC_IMMUNITY                            = 77,
    SPELL_AURA_MOUNTED                                      = 78,
    SPELL_AURA_MOD_DAMAGE_PERCENT_DONE                      = 79,
    SPELL_AURA_MOD_PERCENT_STAT                             = 80,
    SPELL_AURA_SPLIT_DAMAGE_PCT                             = 81,
    SPELL_AURA_WATER_BREATHING                              = 82,
    SPELL_AURA_MOD_BASE_RESISTANCE                          = 83,
    SPELL_AURA_MOD_REGEN                                    = 84,
    SPELL_AURA_MOD_POWER_REGEN                              = 85,
    SPELL_AURA_CHANNEL_DEATH_ITEM                           = 86,
    SPELL_AURA_MOD_DAMAGE_PERCENT_TAKEN                     = 87,
    SPELL_AURA_MOD_HEALTH_REGEN_PERCENT                     = 88,
    SPELL_AURA_PERIODIC_DAMAGE_PERCENT                      = 89,
    SPELL_AURA_90                                           = 90,   // old SPELL_AURA_MOD_RESIST_CHANCE
    SPELL_AURA_MOD_DETECT_RANGE                             = 91,
    SPELL_AURA_PREVENTS_FLEEING                             = 92,
    SPELL_AURA_MOD_UNATTACKABLE                             = 93,
    SPELL_AURA_INTERRUPT_REGEN                              = 94,
    SPELL_AURA_GHOST                                        = 95,
    SPELL_AURA_SPELL_MAGNET                                 = 96,
    SPELL_AURA_MANA_SHIELD                                  = 97,
    SPELL_AURA_MOD_SKILL_TALENT                             = 98,
    SPELL_AURA_MOD_ATTACK_POWER                             = 99,
    SPELL_AURA_AURAS_VISIBLE                                = 100,
    SPELL_AURA_MOD_RESISTANCE_PCT                           = 101,
    SPELL_AURA_MOD_MELEE_ATTACK_POWER_VERSUS                = 102,
    SPELL_AURA_MOD_TOTAL_THREAT                             = 103,
    SPELL_AURA_WATER_WALK                                   = 104,
    SPELL_AURA_FEATHER_FALL                                 = 105,
    SPELL_AURA_HOVER                                        = 106,
    SPELL_AURA_ADD_FLAT_MODIFIER                            = 107,
    SPELL_AURA_ADD_PCT_MODIFIER                             = 108,
    SPELL_AURA_ADD_TARGET_TRIGGER                           = 109,
    SPELL_AURA_MOD_POWER_REGEN_PERCENT                      = 110,
    SPELL_AURA_ADD_CASTER_HIT_TRIGGER                       = 111,
    SPELL_AURA_OVERRIDE_CLASS_SCRIPTS                       = 112,
    SPELL_AURA_MOD_RANGED_DAMAGE_TAKEN                      = 113,
    SPELL_AURA_MOD_RANGED_DAMAGE_TAKEN_PCT                  = 114,
    SPELL_AURA_MOD_HEALING                                  = 115,
    SPELL_AURA_MOD_REGEN_DURING_COMBAT                      = 116,
    SPELL_AURA_MOD_MECHANIC_RESISTANCE                      = 117,
    SPELL_AURA_MOD_HEALING_PCT                              = 118,
    SPELL_AURA_119                                          = 119,  // old SPELL_AURA_SHARE_PET_TRACKING
    SPELL_AURA_UNTRACKABLE                                  = 120,
    SPELL_AURA_EMPATHY                                      = 121,
    SPELL_AURA_MOD_OFFHAND_DAMAGE_PCT                       = 122,
    SPELL_AURA_MOD_TARGET_RESISTANCE                        = 123,
    SPELL_AURA_MOD_RANGED_ATTACK_POWER                      = 124,
    SPELL_AURA_MOD_MELEE_DAMAGE_TAKEN                       = 125,
    SPELL_AURA_MOD_MELEE_DAMAGE_TAKEN_PCT                   = 126,
    SPELL_AURA_RANGED_ATTACK_POWER_ATTACKER_BONUS           = 127,
    SPELL_AURA_FIXATE                                       = 128,
    SPELL_AURA_MOD_SPEED_ALWAYS                             = 129,
    SPELL_AURA_MOD_MOUNTED_SPEED_ALWAYS                     = 130,
    SPELL_AURA_MOD_RANGED_ATTACK_POWER_VERSUS               = 131,
    SPELL_AURA_MOD_INCREASE_ENERGY_PERCENT                  = 132,
    SPELL_AURA_MOD_INCREASE_HEALTH_PERCENT                  = 133,
    SPELL_AURA_MOD_MANA_REGEN_INTERRUPT                     = 134,
    SPELL_AURA_MOD_HEALING_DONE                             = 135,
    SPELL_AURA_MOD_HEALING_DONE_PERCENT                     = 136,
    SPELL_AURA_MOD_TOTAL_STAT_PERCENTAGE                    = 137,
    SPELL_AURA_MOD_MELEE_HASTE                              = 138,
    SPELL_AURA_FORCE_REACTION                               = 139,
    SPELL_AURA_MOD_RANGED_HASTE                             = 140,
    SPELL_AURA_141                                          = 141,  // old SPELL_AURA_MOD_RANGED_AMMO_HASTE, unused now
    SPELL_AURA_MOD_BASE_RESISTANCE_PCT                      = 142,
    SPELL_AURA_MOD_RESISTANCE_EXCLUSIVE                     = 143,
    SPELL_AURA_SAFE_FALL                                    = 144,
    SPELL_AURA_MOD_PET_TALENT_POINTS                        = 145,
    SPELL_AURA_ALLOW_TAME_PET_TYPE                          = 146,
    SPELL_AURA_MECHANIC_IMMUNITY_MASK                       = 147,
    SPELL_AURA_RETAIN_COMBO_POINTS                          = 148,
    SPELL_AURA_REDUCE_PUSHBACK                              = 149,  //    Reduce Pushback
    SPELL_AURA_MOD_SHIELD_BLOCKVALUE_PCT                    = 150,
    SPELL_AURA_TRACK_STEALTHED                              = 151,  //    Track Stealthed
    SPELL_AURA_MOD_DETECTED_RANGE                           = 152,  //    Mod Detected Range
    SPELL_AURA_153                                          = 153,  // old SPELL_AURA_SPLIT_DAMAGE_FLAT. unused 4.3.4
    SPELL_AURA_MOD_STEALTH_LEVEL                            = 154,  //    Stealth Level Modifier
    SPELL_AURA_MOD_WATER_BREATHING                          = 155,  //    Mod Water Breathing
    SPELL_AURA_MOD_REPUTATION_GAIN                          = 156,  //    Mod Reputation Gain
    SPELL_AURA_PET_DAMAGE_MULTI                             = 157,  //    Mod Pet Damage
    SPELL_AURA_MOD_SHIELD_BLOCKVALUE                        = 158,
    SPELL_AURA_NO_PVP_CREDIT                                = 159,
    SPELL_AURA_160                                          = 160,  // old SPELL_AURA_MOD_AOE_AVOIDANCE. Unused 4.3.4
    SPELL_AURA_MOD_HEALTH_REGEN_IN_COMBAT                   = 161,
    SPELL_AURA_POWER_BURN                                   = 162,
    SPELL_AURA_MOD_CRIT_DAMAGE_BONUS                        = 163,
    SPELL_AURA_164                                          = 164,
    SPELL_AURA_MELEE_ATTACK_POWER_ATTACKER_BONUS            = 165,
    SPELL_AURA_MOD_ATTACK_POWER_PCT                         = 166,
    SPELL_AURA_MOD_RANGED_ATTACK_POWER_PCT                  = 167,
    SPELL_AURA_MOD_DAMAGE_DONE_VERSUS                       = 168,
    SPELL_AURA_169                                          = 169,  // old SPELL_AURA_MOD_CRIT_PERCENT_VERSUS. unused 4.3.4
    SPELL_AURA_DETECT_AMORE                                 = 170,
    SPELL_AURA_MOD_SPEED_NOT_STACK                          = 171,
    SPELL_AURA_MOD_MOUNTED_SPEED_NOT_STACK                  = 172,
    SPELL_AURA_173                                          = 173,  // old SPELL_AURA_ALLOW_CHAMPION_SPELLS
    SPELL_AURA_MOD_SPELL_DAMAGE_OF_STAT_PERCENT             = 174,  // by defeult intelect, dependent from SPELL_AURA_MOD_SPELL_HEALING_OF_STAT_PERCENT
    SPELL_AURA_MOD_SPELL_HEALING_OF_STAT_PERCENT            = 175,
    SPELL_AURA_SPIRIT_OF_REDEMPTION                         = 176,
    SPELL_AURA_AOE_CHARM                                    = 177,
    SPELL_AURA_178                                          = 178,  // old SPELL_AURA_MOD_DEBUFF_RESISTANCE, unused
    SPELL_AURA_MOD_ATTACKER_SPELL_CRIT_CHANCE               = 179,
    SPELL_AURA_MOD_FLAT_SPELL_DAMAGE_VERSUS                 = 180,
    SPELL_AURA_181                                          = 181,  // old SPELL_AURA_MOD_FLAT_SPELL_CRIT_DAMAGE_VERSUS - possible flat spell crit damage versus
    SPELL_AURA_MOD_RESISTANCE_OF_STAT_PERCENT               = 182,
    SPELL_AURA_MOD_CRITICAL_THREAT                          = 183,
    SPELL_AURA_MOD_ATTACKER_MELEE_HIT_CHANCE                = 184,
    SPELL_AURA_MOD_ATTACKER_RANGED_HIT_CHANCE               = 185,
    SPELL_AURA_MOD_ATTACKER_SPELL_HIT_CHANCE                = 186,
    SPELL_AURA_MOD_ATTACKER_MELEE_CRIT_CHANCE               = 187,
    SPELL_AURA_MOD_ATTACKER_RANGED_CRIT_CHANCE              = 188,
    SPELL_AURA_MOD_RATING                                   = 189,
    SPELL_AURA_MOD_FACTION_REPUTATION_GAIN                  = 190,
    SPELL_AURA_USE_NORMAL_MOVEMENT_SPEED                    = 191,
    SPELL_AURA_MOD_MELEE_RANGED_HASTE                       = 192,
    SPELL_AURA_MELEE_SLOW                                   = 193,
    SPELL_AURA_MOD_TARGET_ABSORB_SCHOOL                     = 194,
    SPELL_AURA_MOD_TARGET_ABILITY_ABSORB_SCHOOL             = 195,
    SPELL_AURA_MOD_COOLDOWN                                 = 196,  // only 24818 Noxious Breath
    SPELL_AURA_MOD_ATTACKER_SPELL_AND_WEAPON_CRIT_CHANCE    = 197,
    SPELL_AURA_198                                          = 198,  // old SPELL_AURA_MOD_ALL_WEAPON_SKILLS
    SPELL_AURA_199                                          = 199,  // old SPELL_AURA_MOD_INCREASES_SPELL_PCT_TO_HIT. unused 4.3.4
    SPELL_AURA_MOD_XP_PCT                                   = 200,
    SPELL_AURA_FLY                                          = 201,
    SPELL_AURA_IGNORE_COMBAT_RESULT                         = 202,
    SPELL_AURA_MOD_ATTACKER_MELEE_CRIT_DAMAGE               = 203,
    SPELL_AURA_MOD_ATTACKER_RANGED_CRIT_DAMAGE              = 204,
    SPELL_AURA_MOD_SCHOOL_CRIT_DMG_TAKEN                    = 205,
    SPELL_AURA_MOD_INCREASE_VEHICLE_FLIGHT_SPEED            = 206,
    SPELL_AURA_MOD_INCREASE_MOUNTED_FLIGHT_SPEED            = 207,
    SPELL_AURA_MOD_INCREASE_FLIGHT_SPEED                    = 208,
    SPELL_AURA_MOD_MOUNTED_FLIGHT_SPEED_ALWAYS              = 209,
    SPELL_AURA_MOD_VEHICLE_SPEED_ALWAYS                     = 210,
    SPELL_AURA_MOD_FLIGHT_SPEED_NOT_STACK                   = 211,
    SPELL_AURA_212                                          = 212,  // old SPELL_AURA_MOD_RANGED_ATTACK_POWER_OF_STAT_PERCENT. unused 4.3.4
    SPELL_AURA_MOD_RAGE_FROM_DAMAGE_DEALT                   = 213,
    SPELL_AURA_214                                          = 214,
    SPELL_AURA_ARENA_PREPARATION                            = 215,
    SPELL_AURA_HASTE_SPELLS                                 = 216,
    SPELL_AURA_MOD_MELEE_HASTE_2                            = 217,
    SPELL_AURA_HASTE_RANGED                                 = 218,
    SPELL_AURA_MOD_MANA_REGEN_FROM_STAT                     = 219,
    SPELL_AURA_MOD_RATING_FROM_STAT                         = 220,
    SPELL_AURA_MOD_DETAUNT                                  = 221,
    SPELL_AURA_222                                          = 222,
    SPELL_AURA_RAID_PROC_FROM_CHARGE                        = 223,
    SPELL_AURA_224                                          = 224,
    SPELL_AURA_RAID_PROC_FROM_CHARGE_WITH_VALUE             = 225,
    SPELL_AURA_PERIODIC_DUMMY                               = 226,
    SPELL_AURA_PERIODIC_TRIGGER_SPELL_WITH_VALUE            = 227,
    SPELL_AURA_DETECT_STEALTH                               = 228,
    SPELL_AURA_MOD_AOE_DAMAGE_AVOIDANCE                     = 229,
    SPELL_AURA_MOD_MAX_HEALTH                               = 230,
    SPELL_AURA_PROC_TRIGGER_SPELL_WITH_VALUE                = 231,
    SPELL_AURA_MECHANIC_DURATION_MOD                        = 232,
    SPELL_AURA_CHANGE_MODEL_FOR_ALL_HUMANOIDS               = 233,  // client-side only
    SPELL_AURA_MECHANIC_DURATION_MOD_NOT_STACK              = 234,
    SPELL_AURA_MOD_DISPEL_RESIST                            = 235,
    SPELL_AURA_CONTROL_VEHICLE                              = 236,
    SPELL_AURA_MOD_SPELL_DAMAGE_OF_ATTACK_POWER             = 237,
    SPELL_AURA_MOD_SPELL_HEALING_OF_ATTACK_POWER            = 238,
    SPELL_AURA_MOD_SCALE_2                                  = 239,
    SPELL_AURA_MOD_EXPERTISE                                = 240,
    SPELL_AURA_FORCE_MOVE_FORWARD                           = 241,
    SPELL_AURA_MOD_SPELL_DAMAGE_FROM_HEALING                = 242,
    SPELL_AURA_MOD_FACTION                                  = 243,
    SPELL_AURA_COMPREHEND_LANGUAGE                          = 244,
    SPELL_AURA_MOD_AURA_DURATION_BY_DISPEL                  = 245,
    SPELL_AURA_MOD_AURA_DURATION_BY_DISPEL_NOT_STACK        = 246,
    SPELL_AURA_CLONE_CASTER                                 = 247,
    SPELL_AURA_MOD_COMBAT_RESULT_CHANCE                     = 248,
    SPELL_AURA_CONVERT_RUNE                                 = 249,
    SPELL_AURA_MOD_INCREASE_HEALTH_2                        = 250,
    SPELL_AURA_MOD_ENEMY_DODGE                              = 251,
    SPELL_AURA_MOD_SPEED_SLOW_ALL                           = 252,
    SPELL_AURA_MOD_BLOCK_CRIT_CHANCE                        = 253,
    SPELL_AURA_MOD_DISARM_OFFHAND                           = 254,
    SPELL_AURA_MOD_MECHANIC_DAMAGE_TAKEN_PERCENT            = 255,
    SPELL_AURA_NO_REAGENT_USE                               = 256,
    SPELL_AURA_MOD_TARGET_RESIST_BY_SPELL_CLASS             = 257,
    SPELL_AURA_258                                          = 258,
    SPELL_AURA_259                                          = 259,  // old SPELL_AURA_MOD_HOT_PCT, unused 4.3.4
    SPELL_AURA_SCREEN_EFFECT                                = 260,
    SPELL_AURA_PHASE                                        = 261,
    SPELL_AURA_ABILITY_IGNORE_AURASTATE                     = 262,
    SPELL_AURA_DISABLE_CASTING_EXCEPT_ABILITIES             = 263,
    SPELL_AURA_DISABLE_ATTACKING_EXCEPT_ABILITIES           = 264,
    SPELL_AURA_265                                          = 265,
    SPELL_AURA_266                                          = 266,
    SPELL_AURA_MOD_IMMUNE_AURA_APPLY_SCHOOL                 = 267,
    SPELL_AURA_268                                          = 268,  // old SPELL_AURA_MOD_ATTACK_POWER_OF_STAT_PERCENT. unused 4.3.4
    SPELL_AURA_MOD_IGNORE_TARGET_RESIST                     = 269,
    SPELL_AURA_270                                          = 270,  // old SPELL_AURA_MOD_ABILITY_IGNORE_TARGET_RESIST, unused 4.3.4
    SPELL_AURA_MOD_DAMAGE_FROM_CASTER                       = 271,
    SPELL_AURA_IGNORE_MELEE_RESET                           = 272,
    SPELL_AURA_X_RAY                                        = 273,
    SPELL_AURA_274                                          = 274,  // old SPELL_AURA_ABILITY_CONSUME_NO_AMMO, unused 4.3.4
    SPELL_AURA_MOD_IGNORE_SHAPESHIFT                        = 275,
    SPELL_AURA_MOD_DAMAGE_DONE_FOR_MECHANIC                 = 276,
    SPELL_AURA_277                                          = 277,  // old SPELL_AURA_MOD_MAX_AFFECTED_TARGETS. unused 4.3.4
    SPELL_AURA_MOD_DISARM_RANGED                            = 278,
    SPELL_AURA_INITIALIZE_IMAGES                            = 279,
    SPELL_AURA_280                                          = 280,  // old SPELL_AURA_MOD_ARMOR_PENETRATION_PCT unused 4.3.4
    SPELL_AURA_MOD_HONOR_GAIN_PCT                           = 281,
    SPELL_AURA_MOD_BASE_HEALTH_PCT                          = 282,
    SPELL_AURA_MOD_HEALING_RECEIVED                         = 283,  // Possibly only for some spell family class spells
    SPELL_AURA_LINKED                                       = 284,
    SPELL_AURA_MOD_ATTACK_POWER_OF_ARMOR                    = 285,
    SPELL_AURA_ABILITY_PERIODIC_CRIT                        = 286,
    SPELL_AURA_DEFLECT_SPELLS                               = 287,
    SPELL_AURA_IGNORE_HIT_DIRECTION                         = 288,
    SPELL_AURA_PREVENT_DURABILITY_LOSS                      = 289,
    SPELL_AURA_MOD_CRIT_PCT                                 = 290,
    SPELL_AURA_MOD_XP_QUEST_PCT                             = 291,
    SPELL_AURA_OPEN_STABLE                                  = 292,
    SPELL_AURA_OVERRIDE_SPELLS                              = 293,
    SPELL_AURA_PREVENT_REGENERATE_POWER                     = 294,
    SPELL_AURA_295                                          = 295,
    SPELL_AURA_SET_VEHICLE_ID                               = 296,
    SPELL_AURA_BLOCK_SPELL_FAMILY                           = 297,
    SPELL_AURA_STRANGULATE                                  = 298,
    SPELL_AURA_299                                          = 299,
    SPELL_AURA_SHARE_DAMAGE_PCT                             = 300,
    SPELL_AURA_SCHOOL_HEAL_ABSORB                           = 301,
    SPELL_AURA_302                                          = 302,
    SPELL_AURA_MOD_DAMAGE_DONE_VERSUS_AURASTATE             = 303,
    SPELL_AURA_MOD_FAKE_INEBRIATE                           = 304,
    SPELL_AURA_MOD_MINIMUM_SPEED                            = 305,
    SPELL_AURA_306                                          = 306,
    SPELL_AURA_HEAL_ABSORB_TEST                             = 307,
    SPELL_AURA_MOD_CRIT_CHANCE_FOR_CASTER                   = 308,
    SPELL_AURA_309                                          = 309,  // Not used in 4.3.4
    SPELL_AURA_MOD_CREATURE_AOE_DAMAGE_AVOIDANCE            = 310,
    SPELL_AURA_311                                          = 311,
    SPELL_AURA_ANIM_REPLACEMENT_SET                         = 312,
    SPELL_AURA_313                                          = 313,  // Not used in 4.3.4 - related to mounts
    SPELL_AURA_PREVENT_RESURRECTION                         = 314,
    SPELL_AURA_UNDERWATER_WALKING                           = 315,
    SPELL_AURA_PERIODIC_HASTE                               = 316,  // Not used in 4.3.4 (name from 3.3.5a)
    SPELL_AURA_MOD_SPELL_POWER_PCT                          = 317,
    SPELL_AURA_MASTERY                                      = 318,
    SPELL_AURA_MOD_MELEE_HASTE_3                            = 319,
    SPELL_AURA_MOD_RANGED_HASTE_2                           = 320,
    SPELL_AURA_MOD_NO_ACTIONS                               = 321,
    SPELL_AURA_INTERFERE_TARGETTING                         = 322,  // NYI
    SPELL_AURA_323                                          = 323,  // Not used in 4.3.4
    SPELL_AURA_324                                          = 324,  // spell critical chance (probably by school mask)
    SPELL_AURA_325                                          = 325,  // Not used in 4.3.4
    SPELL_AURA_PHASE_GROUP                                  = 326,  // Puts the player in all the phases that are in the group with id = miscB
    SPELL_AURA_327                                          = 327,  // Not used in 4.3.4
    SPELL_AURA_PROC_ON_POWER_AMOUNT                         = 328,
    SPELL_AURA_MOD_RUNE_REGEN_SPEED                         = 329,  // NYI
    SPELL_AURA_CAST_WHILE_WALKING                           = 330,
    SPELL_AURA_FORCE_WEATHER                                = 331,
    SPELL_AURA_OVERRIDE_ACTIONBAR_SPELLS                    = 332,
    SPELL_AURA_OVERRIDE_ACTIONBAR_SPELLS_TRIGGERED          = 333,  // Spells cast with this override have no cast time or power cost
    SPELL_AURA_MOD_BLIND                                    = 334,  // NYI
    SPELL_AURA_335                                          = 335,
    SPELL_AURA_MOUNT_RESTRICTIONS                           = 336,
    SPELL_AURA_MOD_VENDOR_ITEMS_PRICES                      = 337,
    SPELL_AURA_MOD_DURABILITY_LOSS                          = 338,
    SPELL_AURA_INCREASE_SKILL_GAIN_CHANCE                   = 339,  // NYI
    SPELL_AURA_MOD_RESURRECTED_HEALTH_BY_GUILD_MEMBER       = 340,  // Increases health gained when resurrected by a guild member by X
    SPELL_AURA_MOD_SPELL_CATEGORY_COOLDOWN                  = 341,  // Modifies cooldown of all spells using affected category
    SPELL_AURA_MOD_MELEE_RANGED_HASTE_2                     = 342,
    SPELL_AURA_MOD_MELEE_DAMAGE_FROM_CASTER                 = 343,
    SPELL_AURA_MOD_AUTOATTACK_DAMAGE                        = 344,
    SPELL_AURA_BYPASS_ARMOR_FOR_CASTER                      = 345,
    SPELL_AURA_ENABLE_ALT_POWER                             = 346,  // NYI
    SPELL_AURA_MOD_SPELL_COOLDOWN_BY_HASTE                  = 347,
    SPELL_AURA_DEPOSIT_BONUS_MONEY_IN_GUILD_BANK_ON_LOOT    = 348,
    SPELL_AURA_MOD_CURRENCY_GAIN                            = 349,
    SPELL_AURA_MOD_GATHERING_ITEMS_GAINED_PERCENT           = 350,  // NYI
    SPELL_AURA_MOD_CURRENCY_CATEGORY_GAIN_PCT               = 351,
    SPELL_AURA_ENABLE_ALTERED_FORM                          = 352,
    SPELL_AURA_MOD_CAMOUFLAGE                               = 353,  // NYI
    SPELL_AURA_MOD_HEALING_DONE_PCT_VERSUS_TARGET_HEALTH    = 354,  // Restoration Shaman mastery - mod healing based on target's health (less = more healing)
    SPELL_AURA_355                                          = 355,
    SPELL_AURA_MOD_DAMAGE_FROM_MANA                         = 356,  // Arcane Mage mastery - mod damage based on current mana
    SPELL_AURA_ENABLE_BOSS1_UNIT_FRAME                      = 357,
    SPELL_AURA_WORGEN_ALTERED_FORM                          = 358,
    SPELL_AURA_359                                          = 359,
    SPELL_AURA_PROC_TRIGGER_SPELL_COPY                      = 360,  // Procs the same spell that caused this proc (Dragonwrath, Tarecgosa's Rest)
    SPELL_AURA_OVERRIDE_AUTOATTACK_WITH_MELEE_SPELL         = 361,
    SPELL_AURA_362                                          = 362,  // Not used in 4.3.4
    SPELL_AURA_MOD_NEXT_SPELL                               = 363,  // Used by 101601 Throw Totem - causes the client to initialize spell cast with specified spell
    SPELL_AURA_364                                          = 364,  // Not used in 4.3.4
    SPELL_AURA_MAX_FAR_CLIP_PLANE                           = 365,  // Overrides client's View Distance setting to max("Fair", current_setting) and turns off terrain display
    SPELL_AURA_OVERRIDE_SPELL_POWER_BY_AP_PCT               = 366,  // Sets spellpower equal to % of attack power, discarding all other bonuses (from gear and buffs)
    SPELL_AURA_OVERRIDE_AUTOATTACK_WITH_RANGED_SPELL        = 367,  // NYI
    SPELL_AURA_368                                          = 368,  // Not used in 4.3.4
    SPELL_AURA_ENABLE_POWER_BAR_TIMER                       = 369,
    SPELL_AURA_SET_FAIR_FAR_CLIP                            = 370,  // Overrides client's View Distance setting to max("Fair", current_setting)
};

enum UnitMods
{
    UNIT_MOD_STAT_STRENGTH,                                 // UNIT_MOD_STAT_STRENGTH..UNIT_MOD_STAT_SPIRIT must be in existed order, it's accessed by index values of Stats enum.
    UNIT_MOD_STAT_AGILITY,
    UNIT_MOD_STAT_STAMINA,
    UNIT_MOD_STAT_INTELLECT,
    UNIT_MOD_STAT_SPIRIT,
    UNIT_MOD_HEALTH,
    UNIT_MOD_MANA,                                          // UNIT_MOD_MANA..UNIT_MOD_RUNIC_POWER must be in existed order, it's accessed by index values of Powers enum.
    UNIT_MOD_RAGE,
    UNIT_MOD_FOCUS,
    UNIT_MOD_ENERGY,
    UNIT_MOD_UNUSED,                                        // Old UNIT_MOD_HAPPINESS
    UNIT_MOD_RUNE,
    UNIT_MOD_RUNIC_POWER,
    UNIT_MOD_SOUL_SHARDS,
    UNIT_MOD_ECLIPSE,
    UNIT_MOD_HOLY_POWER,
    UNIT_MOD_ALTERNATE_POWER,                               // Atramedes etc.
    UNIT_MOD_ARMOR,                                         // UNIT_MOD_ARMOR..UNIT_MOD_RESISTANCE_ARCANE must be in existed order, it's accessed by index values of SpellSchools enum.
    UNIT_MOD_RESISTANCE_HOLY,
    UNIT_MOD_RESISTANCE_FIRE,
    UNIT_MOD_RESISTANCE_NATURE,
    UNIT_MOD_RESISTANCE_FROST,
    UNIT_MOD_RESISTANCE_SHADOW,
    UNIT_MOD_RESISTANCE_ARCANE,
    UNIT_MOD_ATTACK_POWER,
    UNIT_MOD_ATTACK_POWER_POS,
    UNIT_MOD_ATTACK_POWER_NEG,
    UNIT_MOD_ATTACK_POWER_RANGED,
    UNIT_MOD_ATTACK_POWER_RANGED_POS,
    UNIT_MOD_ATTACK_POWER_RANGED_NEG,
    UNIT_MOD_DAMAGE_MAINHAND,
    UNIT_MOD_DAMAGE_OFFHAND,
    UNIT_MOD_DAMAGE_RANGED,
    UNIT_MOD_END,
};

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

enum SpellAttr0 : uint32_t
{
    SPELL_ATTR0_PROC_FAILURE_BURNS_CHARGE                           = 0x00000001, // TITLE Proc Failure Burns Charge
    SPELL_ATTR0_USES_RANGED_SLOT                                    = 0x00000002, // Uses Ranged Slot DESCRIPTION Use ammo, ranged attack range modifiers, ranged haste, etc.
    SPELL_ATTR0_ON_NEXT_SWING_NO_DAMAGE                             = 0x00000004, // On Next Swing (No Damage) DESCRIPTION Both "on next swing" attributes have identical handling in server & client
    SPELL_ATTR0_DO_NOT_LOG_IMMUNE_MISSES                            = 0x00000008, // Do Not Log Immune Misses (client only)
    SPELL_ATTR0_IS_ABILITY                                          = 0x00000010, // Is Ability DESCRIPTION Cannot be reflected, not affected by cast speed modifiers, etc.
    SPELL_ATTR0_IS_TRADESKILL                                       = 0x00000020, // Is Tradeskill DESCRIPTION Displayed in recipe list, not affected by cast speed modifiers
    SPELL_ATTR0_PASSIVE                                             = 0x00000040, // Passive DESCRIPTION Spell is automatically cast on self by core
    SPELL_ATTR0_DO_NOT_DISPLAY_SPELLBOOK_AURA_ICON_COMBAT_LOG       = 0x00000080, // Do Not Display (Spellbook, Aura Icon, Combat Log) (client only) DESCRIPTION Not visible in spellbook or aura bar
    SPELL_ATTR0_DO_NOT_LOG                                          = 0x00000100, // Do Not Log (client only) DESCRIPTION Spell will not appear in combat logs
    SPELL_ATTR0_HELD_ITEM_ONLY                                      = 0x00000200, // Held Item Only (client only) DESCRIPTION Client will automatically select main-hand item as cast target
    SPELL_ATTR0_ON_NEXT_SWING                                       = 0x00000400, // On Next Swing DESCRIPTION Both "on next swing" attributes have identical handling in server & client
    SPELL_ATTR0_WEARER_CASTS_PROC_TRIGGER                           = 0x00000800, // TITLE Wearer Casts Proc Trigger DESCRIPTION Just a marker attribute to show auras that trigger another spell (either directly or with a script)
    SPELL_ATTR0_SERVER_ONLY                                         = 0x00001000, // Server Only
    SPELL_ATTR0_ALLOW_ITEM_SPELL_IN_PVP                             = 0x00002000, // Allow Item Spell In PvP
    SPELL_ATTR0_ONLY_INDOORS                                        = 0x00004000, // Only Indoors
    SPELL_ATTR0_ONLY_OUTDOORS                                       = 0x00008000, // Only Outdoors
    SPELL_ATTR0_NOT_SHAPESHIFTED                                    = 0x00010000, // Not Shapeshifted
    SPELL_ATTR0_ONLY_STEALTHED                                      = 0x00020000, // Only Stealthed
    SPELL_ATTR0_DO_NOT_SHEATH                                       = 0x00040000, // Do Not Sheath (client only)
    SPELL_ATTR0_SCALES_WITH_CREATURE_LEVEL                          = 0x00080000, // Scales w/ Creature Level DESCRIPTION For non-player casts, scale impact and power cost with caster's level
    SPELL_ATTR0_CANCELS_AUTO_ATTACK_COMBAT                          = 0x00100000, // Cancels Auto Attack Combat DESCRIPTION After casting this, the current auto-attack will be interrupted
    SPELL_ATTR0_NO_ACTIVE_DEFENSE                                   = 0x00200000, // No Active Defense DESCRIPTION Spell cannot be dodged, parried or blocked
    SPELL_ATTR0_TRACK_TARGET_IN_CAST_PLAYER_ONLY                    = 0x00400000, // Track Target in Cast (Player Only) (client only)
    SPELL_ATTR0_ALLOW_CAST_WHILE_DEAD                               = 0x00800000, // Allow Cast While Dead DESCRIPTION Spells without this flag cannot be cast by dead units in non-triggered contexts
    SPELL_ATTR0_ALLOW_WHILE_MOUNTED                                 = 0x01000000, // Allow While Mounted
    SPELL_ATTR0_COOLDOWN_ON_EVENT                                   = 0x02000000, // Cooldown On Event DESCRIPTION Spell is unusable while already active, and cooldown does not begin until the effects have worn off
    SPELL_ATTR0_AURA_IS_DEBUFF                                      = 0x04000000, // Aura Is Debuff DESCRIPTION Forces the spell to be treated as a negative spell
    SPELL_ATTR0_ALLOW_WHILE_SITTING                                 = 0x08000000, // Allow While Sitting
    SPELL_ATTR0_NOT_IN_COMBAT_ONLY_PEACEFUL                         = 0x10000000, // Not In Combat (Only Peaceful)
    SPELL_ATTR0_NO_IMMUNITIES                                       = 0x20000000, // No Immunities DESCRIPTION Allows spell to pierce invulnerability, unless the invulnerability spell also has this attribute
    SPELL_ATTR0_HEARTBEAT_RESIST                                    = 0x40000000, // Heartbeat Resist DESCRIPTION Periodically re-rolls against resistance to potentially expire aura early
    SPELL_ATTR0_NO_AURA_CANCEL                                      = 0x80000000  // No Aura Cancel DESCRIPTION Prevents the player from voluntarily canceling a positive aura
};

enum SpellAttr1 : uint32_t
{
    SPELL_ATTR1_DISMISS_PET_FIRST                                   = 0x00000001, // Dismiss Pet First DESCRIPTION Without this attribute, summoning spells will fail if caster already has a pet
    SPELL_ATTR1_USE_ALL_MANA                                        = 0x00000002, // Use All Mana DESCRIPTION Ignores listed power cost and drains entire pool instead
    SPELL_ATTR1_IS_CHANNELLED                                       = 0x00000004, // Is Channelled DESCRIPTION Both "channeled" attributes have identical handling in server & client
    SPELL_ATTR1_NO_REDIRECTION                                      = 0x00000008, // No Redirection DESCRIPTION Spell will not be attracted by SPELL_MAGNET auras (Grounding Totem)
    SPELL_ATTR1_NO_SKILL_INCREASE                                   = 0x00000010, // No Skill Increase
    SPELL_ATTR1_ALLOW_WHILE_STEALTHED                               = 0x00000020, // Allow While Stealthed
    SPELL_ATTR1_IS_SELF_CHANNELLED                                  = 0x00000040, // Is Self Channelled DESCRIPTION Both "channeled" attributes have identical handling in server & client
    SPELL_ATTR1_NO_REFLECTION                                       = 0x00000080, // No Reflection DESCRIPTION Spell will pierce through Spell Reflection and similar
    SPELL_ATTR1_ONLY_PEACEFUL_TARGETS                               = 0x00000100, // Only Peaceful Targets DESCRIPTION Target cannot be in combat
    SPELL_ATTR1_INITIATES_COMBAT_ENABLES_AUTO_ATTACK                = 0x00000200, // Initiates Combat (Enables Auto-Attack) (client only) DESCRIPTION Caster will begin auto-attacking the target on cast
    SPELL_ATTR1_NO_THREAT                                           = 0x00000400, // No Threat DESCRIPTION Also does not cause target to engage
    SPELL_ATTR1_AURA_UNIQUE                                         = 0x00000800, // Aura Unique DESCRIPTION Aura will not refresh its duration when recast
    SPELL_ATTR1_FAILURE_BREAKS_STEALTH                              = 0x00001000, // Failure Breaks Stealth
    SPELL_ATTR1_TOGGLE_FAR_SIGHT                                    = 0x00002000, // Toggle Far Sight (client only)
    SPELL_ATTR1_TRACK_TARGET_IN_CHANNEL                             = 0x00004000, // Track Target in Channel DESCRIPTION While channeling, adjust facing to face target
    SPELL_ATTR1_IMMUNITY_PURGES_EFFECT                              = 0x00008000, // Immunity Purges Effect DESCRIPTION For immunity spells, cancel all auras that this spell would make you immune to when the spell is applied
    SPELL_ATTR1_IMMUNITY_TO_HOSTILE_AND_FRIENDLY_EFFECTS            = 0x00010000, /*WRONG IMPL*/ // Immunity to Hostile & Friendly Effects DESCRIPTION Will not pierce Divine Shield, Ice Block and other full invulnerabilities
    SPELL_ATTR1_NO_AUTOCAST_AI                                      = 0x00020000, // No AutoCast (AI)
    SPELL_ATTR1_PREVENTS_ANIM                                       = 0x00040000, /*NYI*/ // Prevents Anim DESCRIPTION Auras apply UNIT_FLAG_PREVENT_EMOTES_FROM_CHAT_TEXT
    SPELL_ATTR1_EXCLUDE_CASTER                                      = 0x00080000, // Exclude Caster
    SPELL_ATTR1_FINISHING_MOVE_DAMAGE                               = 0x00100000, // Finishing Move - Damage
    SPELL_ATTR1_THREAT_ONLY_ON_MISS                                 = 0x00200000, /*NYI*/ // Threat only on Miss
    SPELL_ATTR1_FINISHING_MOVE_DURATION                             = 0x00400000, // Finishing Move - Duration
    SPELL_ATTR1_IGNORE_OWNERS_DEATH                                 = 0x00800000, /*NYI*/ // Ignore Owner's Death
    SPELL_ATTR1_SPECIAL_SKILLUP                                     = 0x01000000, // Special Skillup
    SPELL_ATTR1_AURA_STAYS_AFTER_COMBAT                             = 0x02000000, // Aura Stays After Combat
    SPELL_ATTR1_REQUIRE_ALL_TARGETS                                 = 0x04000000, // TITLE Require All Targets
    SPELL_ATTR1_DISCOUNT_POWER_ON_MISS                              = 0x08000000, // Discount Power On Miss
    SPELL_ATTR1_NO_AURA_ICON                                        = 0x10000000, // No Aura Icon (client only)
    SPELL_ATTR1_NAME_IN_CHANNEL_BAR                                 = 0x20000000, // Name in Channel Bar (client only)
    SPELL_ATTR1_DISPEL_ALL_STACKS                                   = 0x40000000, // Dispel All Stacks
    SPELL_ATTR1_CAST_WHEN_LEARNED                                   = 0x80000000  // Cast When Learned
};

enum SpellAttr2 : uint32_t
{
    SPELL_ATTR2_ALLOW_DEAD_TARGET                                   = 0x00000001, // TITLE Allow Dead Target
    SPELL_ATTR2_NO_SHAPESHIFT_UI                                    = 0x00000002, // TITLE No shapeshift UI (client only) DESCRIPTION Does not replace action bar when shapeshifted
    SPELL_ATTR2_IGNORE_LINE_OF_SIGHT                                = 0x00000004, // TITLE Ignore Line of Sight
    SPELL_ATTR2_ALLOW_LOW_LEVEL_BUFF                                = 0x00000008, // TITLE Allow Low Level Buff
    SPELL_ATTR2_USE_SHAPESHIFT_BAR                                  = 0x00000010, // TITLE Use Shapeshift Bar (client only)
    SPELL_ATTR2_AUTO_REPEAT                                         = 0x00000020, // TITLE Auto Repeat
    SPELL_ATTR2_CANNOT_CAST_ON_TAPPED                               = 0x00000040, // TITLE Cannot cast on tapped DESCRIPTION Can only target untapped units, or those tapped by caster
    SPELL_ATTR2_DO_NOT_REPORT_SPELL_FAILURE                         = 0x00000080, // TITLE Do Not Report Spell Failure
    SPELL_ATTR2_INCLUDE_IN_ADVANCED_COMBAT_LOG                      = 0x00000100, // TITLE Include In Advanced Combat Log (client only) DESCRIPTION Determines whether to include this aura in list of auras in SMSG_ENCOUNTER_START
    SPELL_ATTR2_ALWAYS_CAST_AS_UNIT                                 = 0x00000200, /*NYI, UNK*/ // TITLE Always Cast As Unit
    SPELL_ATTR2_SPECIAL_TAMING_FLAG                                 = 0x00000400, // TITLE Special Taming Flag DESCRIPTION Related to taming?
    SPELL_ATTR2_NO_TARGET_PER_SECOND_COSTS                          = 0x00000800, // TITLE No Target Per-Second Costs
    SPELL_ATTR2_CHAIN_FROM_CASTER                                   = 0x00001000, // TITLE Chain From Caster
    SPELL_ATTR2_ENCHANT_OWN_ITEM_ONLY                               = 0x00002000, // TITLE Enchant own item only
    SPELL_ATTR2_ALLOW_WHILE_INVISIBLE                               = 0x00004000, // TITLE Allow While Invisible
    SPELL_ATTR2_DO_NOT_CONSUME_IF_GAINED_DURING_CAST                = 0x00008000, // TITLE Do Not Consume if Gained During Cast
    SPELL_ATTR2_NO_ACTIVE_PETS                                      = 0x00010000, // TITLE No Active Pets
    SPELL_ATTR2_DO_NOT_RESET_COMBAT_TIMERS                          = 0x00020000, // TITLE Do Not Reset Combat Timers DESCRIPTION Does not reset melee/ranged autoattack timer on cast
    SPELL_ATTR2_NO_JUMP_WHILE_CAST_PENDING                          = 0x00040000, // TITLE No Jump While Cast Pending (client only)
    SPELL_ATTR2_ALLOW_WHILE_NOT_SHAPESHIFTED_CASTER_FORM            = 0x00080000, // TITLE Allow While Not Shapeshifted (caster form) DESCRIPTION Even if Stances are nonzero, allow spell to be cast outside of shapeshift (though not in a different shapeshift)
    SPELL_ATTR2_INITIATE_COMBAT_POST_CAST_ENABLES_AUTO_ATTACK       = 0x00100000, // TITLE Initiate Combat Post-Cast (Enables Auto-Attack)
    SPELL_ATTR2_FAIL_ON_ALL_TARGETS_IMMUNE                          = 0x00200000, // TITLE Fail on all targets immune DESCRIPTION Causes BG flags to be dropped if combined with ATTR1_DISPEL_AURAS_ON_IMMUNITY
    SPELL_ATTR2_NO_INITIAL_THREAT                                   = 0x00400000, // TITLE No Initial Threat
    SPELL_ATTR2_PROC_COOLDOWN_ON_FAILURE                            = 0x00800000, // TITLE Proc Cooldown On Failure
    SPELL_ATTR2_ITEM_CAST_WITH_OWNER_SKILL                          = 0x01000000, // TITLE Item Cast With Owner Skill
    SPELL_ATTR2_DONT_BLOCK_MANA_REGEN                               = 0x02000000, // TITLE Don't Block Mana Regen
    SPELL_ATTR2_NO_SCHOOL_IMMUNITIES                                = 0x04000000, // TITLE No School Immunities DESCRIPTION Allow aura to be applied despite target being immune to new aura applications
    SPELL_ATTR2_IGNORE_WEAPONSKILL                                  = 0x08000000, // TITLE Ignore Weaponskill
    SPELL_ATTR2_NOT_AN_ACTION                                       = 0x10000000, // TITLE Not an Action
    SPELL_ATTR2_CANT_CRIT                                           = 0x20000000, // TITLE Can't Crit
    SPELL_ATTR2_ACTIVE_THREAT                                       = 0x40000000, // TITLE Active Threat
    SPELL_ATTR2_RETAIN_ITEM_CAST                                    = 0x80000000  // TITLE Retain Item Cast DESCRIPTION passes m_CastItem to triggered spells
};

enum SpellAttr3 : uint32_t
{
    SPELL_ATTR3_PVP_ENABLING                                        = 0x00000001, // TITLE PvP Enabling
    SPELL_ATTR3_NO_PROC_EQUIP_REQUIREMENT                           = 0x00000002, // TITLE No Proc Equip Requirement DESCRIPTION Ignores subclass mask check when checking proc
    SPELL_ATTR3_NO_CASTING_BAR_TEXT                                 = 0x00000004, // TITLE No Casting Bar Text
    SPELL_ATTR3_COMPLETELY_BLOCKED                                  = 0x00000008, // TITLE Completely Blocked
    SPELL_ATTR3_NO_RES_TIMER                                        = 0x00000010, // TITLE No Res Timer
    SPELL_ATTR3_NO_DURABILITY_LOSS                                  = 0x00000020, // TITLE No Durability Loss
    SPELL_ATTR3_NO_AVOIDANCE                                        = 0x00000040, // TITLE No Avoidance
    SPELL_ATTR3_DOT_STACKING_RULE                                   = 0x00000080, // TITLE DoT Stacking Rule DESCRIPTION Stack separately for each caster
    SPELL_ATTR3_ONLY_ON_PLAYER                                      = 0x00000100, // TITLE Only On Player
    SPELL_ATTR3_NOT_A_PROC                                          = 0x00000200, // TITLE Not a Proc DESCRIPTION Without this attribute, any triggered spell will be unable to trigger other auras' procs
    SPELL_ATTR3_REQUIRES_MAIN_HAND_WEAPON                           = 0x00000400, // TITLE Requires Main-Hand Weapon
    SPELL_ATTR3_ONLY_BATTLEGROUNDS                                  = 0x00000800, // TITLE Only Battlegrounds
    SPELL_ATTR3_ONLY_ON_GHOSTS                                      = 0x00001000, // TITLE Only On Ghosts
    SPELL_ATTR3_HIDE_CHANNEL_BAR                                    = 0x00002000, // TITLE Hide Channel Bar (client only)
    SPELL_ATTR3_HIDE_IN_RAID_FILTER                                 = 0x00004000, // TITLE Hide In Raid Filter (client only)
    SPELL_ATTR3_NORMAL_RANGED_ATTACK                                = 0x00008000, // TITLE Normal Ranged Attack DESCRIPTION Auto Shoot, Shoot, Throw - ranged normal attack attribute?
    SPELL_ATTR3_SUPPRESS_CASTER_PROCS                               = 0x00010000, // TITLE Suppress Caster Procs
    SPELL_ATTR3_SUPPRESS_TARGET_PROCS                               = 0x00020000, // TITLE Suppress Target Procs
    SPELL_ATTR3_ALWAYS_HIT                                          = 0x00040000, // TITLE Always Hit DESCRIPTION Spell cannot miss, or be dodged/parried/blocked
    SPELL_ATTR3_INSTANT_TARGET_PROCS                                = 0x00080000, // TITLE Instant Target Procs DESCRIPTION Proc events are triggered before spell batching processes the spell hit on target
    SPELL_ATTR3_ALLOW_AURA_WHILE_DEAD                               = 0x00100000, // TITLE Allow Aura While Dead
    SPELL_ATTR3_ONLY_PROC_OUTDOORS                                  = 0x00200000, // TITLE Only Proc Outdoors
    SPELL_ATTR3_DO_NOT_TRIGGER_TARGET_STAND                         = 0x00400000, // TITLE Do Not Trigger Target Stand
    SPELL_ATTR3_NO_DAMAGE_HISTORY                                   = 0x00800000, /*NYI, no damage history implementation*/ // TITLE No Damage History
    SPELL_ATTR3_REQUIRES_OFF_HAND_WEAPON                            = 0x01000000, // TITLE Requires Off-Hand Weapon
    SPELL_ATTR3_TREAT_AS_PERIODIC                                   = 0x02000000, // TITLE Treat As Periodic
    SPELL_ATTR3_CAN_PROC_FROM_PROCS                                 = 0x04000000, // TITLE Can Proc From Procs
    SPELL_ATTR3_ONLY_PROC_ON_CASTER                                 = 0x08000000, // TITLE Only Proc on Caster
    SPELL_ATTR3_IGNORE_CASTER_AND_TARGET_RESTRICTIONS               = 0x10000000, /*NYI*/ // TITLE Ignore Caster & Target Restrictions
    SPELL_ATTR3_IGNORE_CASTER_MODIFIERS                             = 0x20000000, // TITLE Ignore Caster Modifiers
    SPELL_ATTR3_DO_NOT_DISPLAY_RANGE                                = 0x40000000, // TITLE Do Not Display Range (client only)
    SPELL_ATTR3_NOT_ON_AOE_IMMUNE                                   = 0x80000000  /*NYI, no aoe immunity implementation*/ // TITLE Not On AOE Immune
};

enum SpellAttr4 : uint32_t
{
    SPELL_ATTR4_NO_CAST_LOG                                         = 0x00000001, // TITLE No Cast Log
    SPELL_ATTR4_CLASS_TRIGGER_ONLY_ON_TARGET                        = 0x00000002, // TITLE Class Trigger Only On Target
    SPELL_ATTR4_AURA_EXPIRES_OFFLINE                                = 0x00000004, // TITLE Aura Expires Offline DESCRIPTION Debuffs (except Resurrection Sickness) will automatically do this
    SPELL_ATTR4_NO_HELPFUL_THREAT                                   = 0x00000008, // TITLE No Helpful Threat
    SPELL_ATTR4_NO_HARMFUL_THREAT                                   = 0x00000010, // TITLE No Harmful Threat
    SPELL_ATTR4_ALLOW_CLIENT_TARGETING                              = 0x00000020, // TITLE Allow Client Targeting DESCRIPTION Allows client to send spell targets for this spell. Applies only to pet spells, without this attribute CMSG_PET_ACTION is sent instead of CMSG_PET_CAST_SPELL
    SPELL_ATTR4_CANNOT_BE_STOLEN                                    = 0x00000040, // TITLE Cannot Be Stolen
    SPELL_ATTR4_ALLOW_CAST_WHILE_CASTING                            = 0x00000080, // TITLE Allow Cast While Casting DESCRIPTION Ignores already in-progress cast and still casts
    SPELL_ATTR4_IGNORE_DAMAGE_TAKEN_MODIFIERS                       = 0x00000100, // TITLE Ignore Damage Taken Modifiers
    SPELL_ATTR4_COMBAT_FEEDBACK_WHEN_USABLE                         = 0x00000200, // TITLE Combat Feedback When Usable (client only)
    SPELL_ATTR4_WEAPON_SPEED_COST_SCALING                           = 0x00000400, // TITLE Weapon Speed Cost Scaling DESCRIPTION Adds 10 to power cost for each 1s of weapon speed
    SPELL_ATTR4_NO_PARTIAL_IMMUNITY                                 = 0x00000800, // TITLE No Partial Immunity
    SPELL_ATTR4_AURA_IS_BUFF                                        = 0x00001000, // TITLE Aura Is Buff
    SPELL_ATTR4_DO_NOT_LOG_CASTER                                   = 0x00002000, // TITLE Do Not Log Caster
    SPELL_ATTR4_REACTIVE_DAMAGE_PROC                                = 0x00004000, // TITLE Reactive Damage Proc DESCRIPTION Damage from spells with this attribute doesn't break auras that normally break on damage taken
    SPELL_ATTR4_NOT_IN_SPELLBOOK                                    = 0x00008000, // TITLE Not In Spellbook
    SPELL_ATTR4_NOT_IN_ARENA_OR_RATED_BATTLEGROUND                  = 0x00010000, // TITLE Not In Arena or Rated Battleground DESCRIPTION Makes spell unusable despite CD <= 10min
    SPELL_ATTR4_IGNORE_DEFAULT_ARENA_RESTRICTIONS                   = 0x00020000, // TITLE Ignore Default Arena Restrictions DESCRIPTION Makes spell usable despite CD > 10min
    SPELL_ATTR4_BOUNCY_CHAIN_MISSILES                               = 0x00040000, // TITLE Bouncy Chain Missiles DESCRIPTION Hits area targets over time instead of all at once
    SPELL_ATTR4_ALLOW_PROC_WHILE_SITTING                            = 0x00080000, // TITLE Allow Proc While Sitting
    SPELL_ATTR4_AURA_NEVER_BOUNCES                                  = 0x00100000, // TITLE Aura Never Bounces
    SPELL_ATTR4_ALLOW_ENTERING_ARENA                                = 0x00200000, // TITLE Allow Entering Arena
    SPELL_ATTR4_PROC_SUPPRESS_SWING_ANIM                            = 0x00400000, // TITLE Proc Suppress Swing Anim
    SPELL_ATTR4_SUPPRESS_WEAPON_PROCS                               = 0x00800000, // TITLE Suppress Weapon Procs
    SPELL_ATTR4_AUTO_RANGED_COMBAT                                  = 0x01000000, // TITLE Auto Ranged Combat
    SPELL_ATTR4_OWNER_POWER_SCALING                                 = 0x02000000, // TITLE Owner Power Scaling
    SPELL_ATTR4_ONLY_FLYING_AREAS                                   = 0x04000000, // TITLE Only Flying Areas
    SPELL_ATTR4_FORCE_DISPLAY_CASTBAR                               = 0x08000000, // TITLE Force Display Castbar
    SPELL_ATTR4_IGNORE_COMBAT_TIMER                                 = 0x10000000, // TITLE Ignore Combat Timer
    SPELL_ATTR4_AURA_BOUNCE_FAILS_SPELL                             = 0x20000000, // TITLE Aura Bounce Fails Spell
    SPELL_ATTR4_OBSOLETE                                            = 0x40000000, // TITLE Obsolete
    SPELL_ATTR4_USE_FACING_FROM_SPELL                               = 0x80000000  // TITLE Use Facing From Spell
};

enum SpellAttr5 : uint32_t
{
    SPELL_ATTR5_ALLOW_ACTIONS_DURING_CHANNEL                        = 0x00000001, // TITLE Allow Actions During Channel
    SPELL_ATTR5_NO_REAGENT_COST_WITH_AURA                           = 0x00000002, // TITLE No Reagent Cost With Aura
    SPELL_ATTR5_REMOVE_ENTERING_ARENA                               = 0x00000004, // TITLE Remove Entering Arena DESCRIPTION Force this aura to be removed on entering arena, regardless of other properties
    SPELL_ATTR5_ALLOW_WHILE_STUNNED                                 = 0x00000008, // TITLE Allow While Stunned
    SPELL_ATTR5_TRIGGERS_CHANNELING                                 = 0x00000010, // TITLE Triggers Channeling
    SPELL_ATTR5_LIMIT_N                                             = 0x00000020, // TITLE Limit N DESCRIPTION Remove previous application to another unit if applied
    SPELL_ATTR5_IGNORE_AREA_EFFECT_PVP_CHECK                        = 0x00000040, // TITLE Ignore Area Effect PvP Check
    SPELL_ATTR5_NOT_ON_PLAYER                                       = 0x00000080, // TITLE Not On Player
    SPELL_ATTR5_NOT_ON_PLAYER_CONTROLLED_NPC                        = 0x00000100, // TITLE Not On Player Controlled NPC
    SPELL_ATTR5_EXTRA_INITIAL_PERIOD                                = 0x00000200, // TITLE Extra Initial Period DESCRIPTION Immediately do periodic tick on apply
    SPELL_ATTR5_DO_NOT_DISPLAY_DURATION                             = 0x00000400, // TITLE Do Not Display Duration
    SPELL_ATTR5_IMPLIED_TARGETING                                   = 0x00000800, // TITLE Implied Targeting (client only)
    SPELL_ATTR5_MELEE_CHAIN_TARGETING                               = 0x00001000, // TITLE Melee Chain Targeting
    SPELL_ATTR5_SPELL_HASTE_AFFECTS_PERIODIC                        = 0x00002000, // TITLE Spell Haste Affects Periodic
    SPELL_ATTR5_NOT_AVAILABLE_WHILE_CHARMED                         = 0x00004000, // TITLE Not Available While Charmed
    SPELL_ATTR5_TREAT_AS_AREA_EFFECT                                = 0x00008000, // TITLE Treat as Area Effect
    SPELL_ATTR5_AURA_AFFECTS_NOT_JUST_REQ_EQUIPPED_ITEM             = 0x00010000, // TITLE Aura Affects Not Just Req. Equipped Item
    SPELL_ATTR5_ALLOW_WHILE_FLEEING                                 = 0x00020000, // TITLE Allow While Fleeing
    SPELL_ATTR5_ALLOW_WHILE_CONFUSED                                = 0x00040000, // TITLE Allow While Confused
    SPELL_ATTR5_AI_DOESNT_FACE_TARGET                               = 0x00080000, // TITLE AI Doesn't Face Target
    SPELL_ATTR5_DO_NOT_ATTEMPT_A_PET_RESUMMON_WHEN_DISMOUNTING      = 0x00100000, /*NYI*/ // TITLE Do Not Attempt a Pet Resummon When Dismounting
    SPELL_ATTR5_IGNORE_TARGET_REQUIREMENTS                          = 0x00200000, /*NYI*/ // TITLE Ignore Target Requirements
    SPELL_ATTR5_NOT_ON_TRIVIAL                                      = 0x00400000, /*NYI*/ // TITLE Not On Trivial
    SPELL_ATTR5_NO_PARTIAL_RESISTS                                  = 0x00800000, /*NYI*/ // TITLE No Partial Resists
    SPELL_ATTR5_IGNORE_CASTER_REQUIREMENTS                          = 0x01000000, /*NYI*/ // TITLE Ignore Caster Requirements
    SPELL_ATTR5_ALWAYS_LINE_OF_SIGHT                                = 0x02000000, // TITLE Always Line of Sight
    SPELL_ATTR5_ALWAYS_AOE_LINE_OF_SIGHT                            = 0x04000000, // TITLE Always AOE Line of Sight DESCRIPTION Requires line of sight between caster and target in addition to between dest and target
    SPELL_ATTR5_NO_CASTER_AURA_ICON                                 = 0x08000000, // TITLE No Caster Aura Icon (client only)
    SPELL_ATTR5_NO_TARGET_AURA_ICON                                 = 0x10000000, // TITLE No Target Aura Icon (client only)
    SPELL_ATTR5_AURA_UNIQUE_PER_CASTER                              = 0x20000000, // TITLE Aura Unique Per Caster
    SPELL_ATTR5_ALWAYS_SHOW_GROUND_TEXTURE                          = 0x40000000, // TITLE Always Show Ground Texture
    SPELL_ATTR5_ADD_MELEE_HIT_RATING                                = 0x80000000  /*NYI*/ // TITLE Add Melee Hit Rating
};

enum SpellAttr6 : uint32_t
{
    SPELL_ATTR6_NO_COOLDOWN_ON_TOOLTIP                              = 0x00000001, // TITLE No Cooldown On Tooltip (client only)
    SPELL_ATTR6_DO_NOT_RESET_COOLDOWN_IN_ARENA                      = 0x00000002, // TITLE Do Not Reset Cooldown In Arena
    SPELL_ATTR6_NOT_AN_ATTACK                                       = 0x00000004, /*NYI*/ // TITLE Not an Attack
    SPELL_ATTR6_CAN_ASSIST_IMMUNE_PC                                = 0x00000008, // TITLE Can Assist Immune PC
    SPELL_ATTR6_IGNORE_FOR_MOD_TIME_RATE                            = 0x00000010, /*NYI, time rate not implemented*/ // TITLE Ignore For Mod Time Rate
    SPELL_ATTR6_DO_NOT_CONSUME_RESOURCES                            = 0x00000020, // TITLE Do Not Consume Resources
    SPELL_ATTR6_FLOATING_COMBAT_TEXT_ON_CAST                        = 0x00000040, // TITLE Floating Combat Text On Cast (client only)
    SPELL_ATTR6_AURA_IS_WEAPON_PROC                                 = 0x00000080, // TITLE Aura Is Weapon Proc
    SPELL_ATTR6_DO_NOT_CHAIN_TO_CROWD_CONTROLLED_TARGETS            = 0x00000100, // TITLE Do Not Chain To Crowd-Controlled Targets DESCRIPTION Implicit targeting (chaining and area targeting) will not impact crowd controlled targets
    SPELL_ATTR6_ALLOW_ON_CHARMED_TARGETS                            = 0x00000200, /*NYI*/ // TITLE Allow On Charmed Targets
    SPELL_ATTR6_NO_AURA_LOG                                         = 0x00000400, // TITLE No Aura Log
    SPELL_ATTR6_NOT_IN_RAID_INSTANCES                               = 0x00000800, // TITLE Not In Raid Instances
    SPELL_ATTR6_ALLOW_WHILE_RIDING_VEHICLE                          = 0x00001000, // TITLE Allow While Riding Vehicle
    SPELL_ATTR6_IGNORE_PHASE_SHIFT                                  = 0x00002000, // TITLE Ignore Phase Shift
    SPELL_ATTR6_AI_PRIMARY_RANGED_ATTACK                            = 0x00004000, /*NYI*/ // TITLE AI Primary Ranged Attack
    SPELL_ATTR6_NO_PUSHBACK                                         = 0x00008000, // TITLE No Pushback
    SPELL_ATTR6_NO_JUMP_PATHING                                     = 0x00010000, /*NYI*/ // TITLE No Jump Pathing
    SPELL_ATTR6_ALLOW_EQUIP_WHILE_CASTING                           = 0x00020000, // TITLE Allow Equip While Casting
    SPELL_ATTR6_ORIGINATE_FROM_CONTROLLER                           = 0x00040000, // TITLE Originate From Controller DESCRIPTION Client will prevent casting if not possessed, charmer will be caster for all intents and purposes
    SPELL_ATTR6_DELAY_COMBAT_TIMER_DURING_CAST                      = 0x00080000, // TITLE Delay Combat Timer During Cast
    SPELL_ATTR6_AURA_ICON_ONLY_FOR_CASTER_LIMIT_10                  = 0x00100000, // TITLE Aura Icon Only For Caster (Limit 10) (client only)
    SPELL_ATTR6_SHOW_MECHANIC_AS_COMBAT_TEXT                        = 0x00200000, // TITLE Show Mechanic as Combat Text (client only)
    SPELL_ATTR6_ABSORB_CANNOT_BE_IGNORE                             = 0x00400000, // TITLE Absorb Cannot Be Ignore
    SPELL_ATTR6_TAPS_IMMEDIATELY                                    = 0x00800000, // TITLE Taps immediately
    SPELL_ATTR6_CAN_TARGET_UNTARGETABLE                             = 0x01000000, // TITLE Can Target Untargetable
    SPELL_ATTR6_DOESNT_RESET_SWING_TIMER_IF_INSTANT                 = 0x02000000, // TITLE Doesn't Reset Swing Timer if Instant
    SPELL_ATTR6_VEHICLE_IMMUNITY_CATEGORY                           = 0x04000000, /*NYI*/ // TITLE Vehicle Immunity Category
    SPELL_ATTR6_IGNORE_HEALING_MODIFIERS                            = 0x08000000, // TITLE Ignore Healing Modifiers DESCRIPTION This prevents certain healing modifiers from applying - see implementation if you really care about details
    SPELL_ATTR6_DO_NOT_AUTO_SELECT_TARGET_WITH_INITIATES_COMBAT     = 0x10000000, // TITLE Do Not Auto Select Target with Initiates Combat (client only)
    SPELL_ATTR6_IGNORE_CASTER_DAMAGE_MODIFIERS                      = 0x20000000, // TITLE Ignore Caster Damage Modifiers DESCRIPTION This prevents certain damage modifiers from applying - see implementation if you really care about details
    SPELL_ATTR6_DISABLE_TIED_EFFECT_POINTS                          = 0x40000000, /*NYI*/ // TITLE Disable Tied Effect Points
    SPELL_ATTR6_NO_CATEGORY_COOLDOWN_MODS                           = 0x80000000  // TITLE No Category Cooldown Mods
};

enum SpellAttr7 : uint32_t
{
    SPELL_ATTR7_ALLOW_SPELL_REFLECTION                              = 0x00000001, // TITLE Allow Spell Reflection
    SPELL_ATTR7_NO_TARGET_DURATION_MOD                              = 0x00000002, // TITLE No Target Duration Mod
    SPELL_ATTR7_DISABLE_AURA_WHILE_DEAD                             = 0x00000004, // TITLE Disable Aura While Dead
    SPELL_ATTR7_DEBUG_SPELL                                         = 0x00000008, // TITLE Debug Spell DESCRIPTION Cannot cast if caster doesn't have UnitFlag2 & UNIT_FLAG2_ALLOW_CHEAT_SPELLS
    SPELL_ATTR7_TREAT_AS_RAID_BUFF                                  = 0x00000010, /*NYI*/ // TITLE Treat as Raid Buff
    SPELL_ATTR7_CAN_BE_MULTI_CAST                                   = 0x00000020, // TITLE Can Be Multi Cast
    SPELL_ATTR7_DONT_CAUSE_SPELL_PUSHBACK                           = 0x00000040, // TITLE Don't Cause Spell Pushback DESCRIPTION Damage dealt by this does not cause spell pushback
    SPELL_ATTR7_PREPARE_FOR_VEHICLE_CONTROL_END                     = 0x00000080, /*NYI*/ // TITLE Prepare for Vehicle Control End
    SPELL_ATTR7_HORDE_SPECIFIC_SPELL                                = 0x00000100, /*NYI*/ // TITLE Horde Specific Spell
    SPELL_ATTR7_ALLIANCE_SPECIFIC_SPELL                             = 0x00000200, /*NYI*/ // TITLE Alliance Specific Spell
    SPELL_ATTR7_DISPEL_REMOVES_CHARGES                              = 0x00000400, // TITLE Dispel Removes Charges DESCRIPTION Dispel/Spellsteal remove individual charges
    SPELL_ATTR7_CAN_CAUSE_INTERRUPT                                 = 0x00000800, // TITLE Can Cause Interrupt DESCRIPTION Only interrupt non-player casting
    SPELL_ATTR7_CAN_CAUSE_SILENCE                                   = 0x00001000, /*NYI*/ // TITLE Can Cause Silence
    SPELL_ATTR7_NO_UI_NOT_INTERRUPTIBLE                             = 0x00002000, // TITLE No UI Not Interruptible DESCRIPTION Can always be interrupted, even if caster is immune
    SPELL_ATTR7_RECAST_ON_RESUMMON                                  = 0x00004000, /*NYI - deprecated attribute, there is no SPELL_GO sent anymore on pet resummon*/ // TITLE Recast On Resummon
    SPELL_ATTR7_RESET_SWING_TIMER_AT_SPELL_START                    = 0x00008000, // TITLE Reset Swing Timer at spell start
    SPELL_ATTR7_ONLY_IN_SPELLBOOK_UNTIL_LEARNED                     = 0x00010000, // TITLE Only In Spellbook Until Learned DESCRIPTION After learning these spells become hidden in spellbook (but are visible when not learned for low level characters)
    SPELL_ATTR7_DO_NOT_LOG_PVP_KILL                                 = 0x00020000, /*NYI, only used by 1 spell that is already filtered out in pvp credits because its self targeting*/ // TITLE Do Not Log PvP Kill
    SPELL_ATTR7_ATTACK_ON_CHARGE_TO_UNIT                            = 0x00040000, // TITLE Attack on Charge to Unit
    SPELL_ATTR7_REPORT_SPELL_FAILURE_TO_UNIT_TARGET                 = 0x00080000, // TITLE Report Spell failure to unit target
    SPELL_ATTR7_NO_CLIENT_FAIL_WHILE_STUNNED_FLEEING_CONFUSED       = 0x00100000, // TITLE No Client Fail While Stunned, Fleeing, Confused DESCRIPTION Clientside - skips stunned/fleeing/confused checks
    SPELL_ATTR7_RETAIN_COOLDOWN_THROUGH_LOAD                        = 0x00200000, /*NYI*/ // TITLE Retain Cooldown Through Load
    SPELL_ATTR7_IGNORES_COLD_WEATHER_FLYING_REQUIREMENT             = 0x00400000, /*NYI - deprecated attribute*/ // TITLE Ignores Cold Weather Flying Requirement
    SPELL_ATTR7_NO_ATTACK_DODGE                                     = 0x00800000, // TITLE No Attack Dodge
    SPELL_ATTR7_NO_ATTACK_PARRY                                     = 0x01000000, // TITLE No Attack Parry
    SPELL_ATTR7_NO_ATTACK_MISS                                      = 0x02000000, // TITLE No Attack Miss
    SPELL_ATTR7_TREAT_AS_NPC_AOE                                    = 0x04000000, // TITLE Treat as NPC AoE
    SPELL_ATTR7_BYPASS_NO_RESURRECT_AURA                            = 0x08000000, // TITLE Bypass No Resurrect Aura
    SPELL_ATTR7_DO_NOT_COUNT_FOR_PVP_SCOREBOARD                     = 0x10000000, // TITLE Do Not Count For PvP Scoreboard
    SPELL_ATTR7_REFLECTION_ONLY_DEFENDS                             = 0x20000000, // TITLE Reflection Only Defends
    SPELL_ATTR7_CAN_PROC_FROM_SUPPRESSED_TARGET_PROCS               = 0x40000000, // TITLE Can Proc From Suppressed Target Procs
    SPELL_ATTR7_ALWAYS_CAST_LOG                                     = 0x80000000  // TITLE Always Cast Log
};

enum SpellAttr8 : uint32_t
{
    SPELL_ATTR8_NO_ATTACK_BLOCK                                     = 0x00000001, // TITLE No Attack Block
    SPELL_ATTR8_IGNORE_DYNAMIC_OBJECT_CASTER                        = 0x00000002, /*NYI*/ // TITLE Ignore Dynamic Object Caster
    SPELL_ATTR8_REMOVE_OUTSIDE_DUNGEONS_AND_RAIDS                   = 0x00000004, // TITLE Remove Outside Dungeons and Raids
    SPELL_ATTR8_ONLY_TARGET_IF_SAME_CREATOR                         = 0x00000008, // TITLE Only Target If Same Creator
    SPELL_ATTR8_CAN_HIT_AOE_UNTARGETABLE                            = 0x00000010, /*NYI - no aoe immunity implementation*/ // TITLE Can Hit AOE Untargetable
    SPELL_ATTR8_ALLOW_WHILE_CHARMED                                 = 0x00000020, /*NYI - not implementable currently, charming replaces AI*/ // TITLE Allow While Charmed
    SPELL_ATTR8_AURA_REQUIRED_BY_CLIENT                             = 0x00000040, /*NYI - we send all auras to client*/ // TITLE Aura Required by Client
    SPELL_ATTR8_IGNORE_SANCTUARY                                    = 0x00000080, // TITLE Ignore Sanctuary
    SPELL_ATTR8_USE_TARGETS_LEVEL_FOR_SPELL_SCALING                 = 0x00000100, // TITLE Use Target's Level for Spell Scaling
    SPELL_ATTR8_PERIODIC_CAN_CRIT                                   = 0x00000200, // TITLE Periodic Can Crit
    SPELL_ATTR8_MIRROR_CREATURE_NAME                                = 0x00000400, // TITLE Mirror creature name DESCRIPTION Transform auras also override name (handled clientside)
    SPELL_ATTR8_ONLY_PLAYERS_CAN_CAST_THIS_SPELL                    = 0x00000800, // TITLE Only Players Can Cast This Spell
    SPELL_ATTR8_AURA_POINTS_ON_CLIENT                               = 0x00001000, // TITLE Aura Points On Client
    SPELL_ATTR8_NOT_IN_SPELLBOOK_UNTIL_LEARNED                      = 0x00002000, // TITLE Not In Spellbook Until Learned DESCRIPTION Hides autolearned spell from spellbook before learning (handled clientside)
    SPELL_ATTR8_TARGET_PROCS_ON_CASTER                              = 0x00004000, // TITLE Target Procs On Caster DESCRIPTION Target (taken) procs happen on caster (actor) instead of aura target (action target)
    SPELL_ATTR8_REQUIRES_LOCATION_TO_BE_ON_LIQUID_SURFACE           = 0x00008000, // TITLE Requires location to be on liquid surface
    SPELL_ATTR8_ONLY_TARGET_OWN_SUMMONS                             = 0x00010000, // TITLE Only Target Own Summons
    SPELL_ATTR8_HASTE_AFFECTS_DURATION                              = 0x00020000, // TITLE Haste Affects Duration
    SPELL_ATTR8_IGNORE_SPELLCAST_OVERRIDE_COST                      = 0x00040000, // TTILE Ignore Spellcast Override Cost
    SPELL_ATTR8_ALLOW_TARGETS_HIDDEN_BY_SPAWN_TRACKING              = 0x00080000, /*NYI - no spawn tracking implementation*/ // TITLE Allow Targets Hidden by Spawn Tracking
    SPELL_ATTR8_REQUIRES_EQUIPPED_INV_TYPES                         = 0x00100000, // TITLE Requires Equipped Inv Types
    SPELL_ATTR8_NO_SUMMON_DEST_FROM_CLIENT_TARGETING_PATHING_REQUIREMENT = 0x00200000, /*NYI - vald path to a spell dest is not required currently if the dest comes from client*/ // TITLE No 'Summon + Dest from Client' Targeting Pathing Requirement
    SPELL_ATTR8_MELEE_HASTE_AFFECTS_PERIODIC                        = 0x00400000, // TITLE Melee Haste Affects Periodic
    SPELL_ATTR8_ENFORCE_IN_COMBAT_RESSURECTION_LIMIT                = 0x00800000, // TITLE Enforce In Combat Ressurection Limit DESCRIPTION Used to limit the number of resurrections in boss encounters
    SPELL_ATTR8_HEAL_PREDICTION                                     = 0x01000000, // TITLE Heal Prediction
    SPELL_ATTR8_NO_LEVEL_UP_TOAST                                   = 0x02000000, // TITLE No Level Up Toast
    SPELL_ATTR8_SKIP_IS_KNOWN_CHECK                                 = 0x04000000, // TITLE Skip Is Known Check
    SPELL_ATTR8_AI_FACE_TARGET                                      = 0x08000000, /*NYI - unknown facing conditions, needs research*/ // TITLE AI Face Target
    SPELL_ATTR8_NOT_IN_BATTLEGROUND                                 = 0x10000000, // TITLE Not in Battleground
    SPELL_ATTR8_MASTERY_AFFECTS_POINTS                              = 0x20000000, // TITLE Mastery Affects Points
    SPELL_ATTR8_DISPLAY_LARGE_AURA_ICON_ON_UNIT_FRAMES_BOSS_AURA    = 0x40000000, // TITLE Display Large Aura Icon On Unit Frames (Boss Aura)
    SPELL_ATTR8_ATTACK_IGNORE_IMMUNE_TO_PC_FLAG                     = 0x80000000  // TITLE Can Attack ImmunePC DESCRIPTION Do not check UNIT_FLAG_IMMUNE_TO_PC in IsValidAttackTarget
};

enum SpellAttr9 : uint32_t
{
    SPELL_ATTR9_UNK0                             = 0x00000001, //  0
    SPELL_ATTR9_UNK1                             = 0x00000002, //  1
    SPELL_ATTR9_RESTRICTED_FLIGHT_AREA           = 0x00000004, //  2 Dalaran and Wintergrasp flight area auras have it
    SPELL_ATTR9_UNK3                             = 0x00000008, //  3
    SPELL_ATTR9_SPECIAL_DELAY_CALCULATION        = 0x00000010, //  4
    SPELL_ATTR9_SUMMON_PLAYER_TOTEM              = 0x00000020, //  5
    SPELL_ATTR9_UNK6                             = 0x00000040, //  6
    SPELL_ATTR9_UNK7                             = 0x00000080, //  7
    SPELL_ATTR9_AIMED_SHOT                       = 0x00000100, //  8
    SPELL_ATTR9_NOT_USABLE_IN_ARENA              = 0x00000200, //  9 Cannot be used in arenas
    SPELL_ATTR9_UNK10                            = 0x00000400, // 10
    SPELL_ATTR9_UNK11                            = 0x00000800, // 11
    SPELL_ATTR9_UNK12                            = 0x00001000, // 12
    SPELL_ATTR9_SLAM                             = 0x00002000, // 13
    SPELL_ATTR9_USABLE_IN_RATED_BATTLEGROUNDS    = 0x00004000, // 14 Can be used in Rated Battlegrounds
    SPELL_ATTR9_UNK15                            = 0x00008000, // 15
    SPELL_ATTR9_UNK16                            = 0x00010000, // 16
    SPELL_ATTR9_UNK17                            = 0x00020000, // 17
    SPELL_ATTR9_UNK18                            = 0x00040000, // 18
    SPELL_ATTR9_ALLOW_DARK_SIMULACRUM            = 0x00080000, // 19 Allow Dark Simulacrum
    SPELL_ATTR9_UNK20                            = 0x00100000, // 20
    SPELL_ATTR9_UNK21                            = 0x00200000, // 21
    SPELL_ATTR9_UNK22                            = 0x00400000, // 22
    SPELL_ATTR9_UNK23                            = 0x00800000, // 23
    SPELL_ATTR9_UNK24                            = 0x01000000, // 24
    SPELL_ATTR9_UNK25                            = 0x02000000, // 25
    SPELL_ATTR9_UNK26                            = 0x04000000, // 26
    SPELL_ATTR9_UNK27                            = 0x08000000, // 27
    SPELL_ATTR9_UNK28                            = 0x10000000, // 28
    SPELL_ATTR9_UNK29                            = 0x20000000, // 29
    SPELL_ATTR9_UNK30                            = 0x40000000, // 30
    SPELL_ATTR9_UNK31                            = 0x80000000  // 31
};

enum SpellAttr10 : uint32_t
{
    SPELL_ATTR10_BYPASS_VISIBILITY_CHECK          = 0x00000001, //  0 Bypass Visibility Check
    SPELL_ATTR10_IGNORE_POSITIVE_DAMAGE_TAKEN_MODS = 0x00000002, //  1 Ignore Positive Damage Taken Modifiers
    SPELL_ATTR10_USES_RANGED_SLOT                 = 0x00000004, //  2 Uses Ranged Slot (Cosmetic Only)
    SPELL_ATTR10_DONT_LOG_FULL_OVERHEAL           = 0x00000008, //  3 Do Not Log Full Overheal
    SPELL_ATTR10_WATER_SPOUT                      = 0x00000010, //  4 NPC Knockback - ignore doors
    SPELL_ATTR10_FORCE_NONBINARY_RESISTANCE       = 0x00000020, //  5 Force Non-Binary Resistance
    SPELL_ATTR10_NO_SUMMON_LOG                    = 0x00000040, //  6 No Summon Log
    SPELL_ATTR10_TELEPORT_PLAYER                  = 0x00000080, //  7 Ignore instance lock and farm limit on teleport
    SPELL_ATTR10_AREA_EFFECTS_USE_TARGET_RADIUS   = 0x00000100, //  8 Area Effects Use Target Radius
    SPELL_ATTR10_CHARGE_USE_ABSOLUTE_SPEED        = 0x00000200, //  9 Charge/JumpCharge - Use Absolute Speed
    SPELL_ATTR10_PROC_COOLDOWN_PER_TARGET         = 0x00000400, // 10 Proc cooldown on a per target basis
    SPELL_ATTR10_HERB_GATHERING_MINING            = 0x00000800, // 11 Lock chest at precast
    SPELL_ATTR10_USE_SPELL_BASE_LEVEL_FOR_SCALING = 0x00001000, // 12 Use Spell Base Level For Scaling
    SPELL_ATTR10_RESET_COOLDOWN_ON_ENCOUNTER_END  = 0x00002000, // 13 Reset cooldown upon ending an encounter
    SPELL_ATTR10_ROLLING_PERIODIC                 = 0x00004000, // 14 Rolling Periodic
    SPELL_ATTR10_SPELLBOOK_HIDDEN_UNTIL_OVERRIDEN = 0x00008000, // 15 Spellbook Hidden Until Overridden
    SPELL_ATTR10_DEFEND_AGAINST_FRIENDLY_CAST     = 0x00010000, // 16 Defend Against Friendly Cast
    SPELL_ATTR10_ALLOW_DEFENSE_WHILE_CASTING      = 0x00020000, // 17 Allow Defense While Casting
    SPELL_ATTR10_ALLOW_DEFENSE_WHILE_CHANNELING   = 0x00040000, // 18 Allow Defense While Channeling
    SPELL_ATTR10_ALLOW_FATAL_DUEL_DAMAGE          = 0x00080000, // 19 Allow Fatal Duel Damage
    SPELL_ATTR10_MULTI_CLICK_GROUND_TARGETING     = 0x00100000, // 20 Multi-Click Ground Targeting
    SPELL_ATTR10_AOE_CAN_HIT_SUMMONED_INVIS       = 0x00200000, // 21 AoE Can Hit Summoned Invis
    SPELL_ATTR10_ALLOW_WHILE_STUNNED_BY_HORROR    = 0x00400000, // 22 Allow While Stunned By Horror Mechanic
    SPELL_ATTR10_VISIBLE_ONLY_TO_CASTER           = 0x00800000, // 23 Visible only to caster (conversations only)
    SPELL_ATTR10_UPDATE_PASSIVES_ON_APPLY_REMOVE  = 0x01000000, // 24 Update Passives on Apply/Remove
    SPELL_ATTR10_NORMAL_MELEE_ATTACK              = 0x02000000, // 25 Normal Melee Attack
    SPELL_ATTR10_IGNORE_FEIGN_DEATH               = 0x04000000, // 26 Ignore Feign Death
    SPELL_ATTR10_CASTER_DEATH_CANCELS_PERSISTENT_AREA_AURAS = 0x08000000, // 27 Caster Death Cancels Persistent Area Auras
    SPELL_ATTR10_DO_NOT_LOG_ABSORB                = 0x10000000, // 28 Do Not Log Absorb
    SPELL_ATTR10_MOUNT_NOT_AT_ACCOUNT_LEVEL       = 0x20000000, // 29 This Mount is NOT at the account level
    SPELL_ATTR10_PREVENT_CLIENT_CAST_CANCEL       = 0x40000000, // 30 Prevent Client Cast Cancel
    SPELL_ATTR10_ENFORCE_FACTING_ON_PRIMARY_TARGET = 0x80000000  // 31 Enforce Facing on Primary Target Only
};

#endif // SPELLENUMS_H