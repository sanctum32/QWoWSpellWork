#pragma once

#include <QString>
#include <QJsonDocument>
#include <QLoggingCategory>
#include "Enums/SpellEnums.hpp"
#include <array>
#include <map>

Q_DECLARE_LOGGING_CATEGORY(JSON)

class SpellWorkJson
{
public:
    struct SpellEffectInfo
    {
        // Effect name
        QString name;

        // If set, it will add extra formatted details
        QString effectDetail;
    };

    struct SpellAuraTypeInfo
    {
        // Aura effect name
        QString name;

        // If set, it will add extra formatted details
        QString effectDetail;
    };

    // Storage
    std::map<uint32_t /*id*/, QString /*name*/> SpellSchools;
    std::map<uint32_t /*hex*/, QString /*name*/> SpellSchoolMasks;
    std::map<uint32_t /*id*/, QString /*name*/> SpellModOps;
    std::map<uint32_t /*flag*/, QString /*name*/> SpellInterruptFlags;
    std::array<std::map<uint32_t /*flag*/, QString /*name*/>, 2> AuraInterruptFlags;
    std::map<uint16_t /*id*/, SpellAuraTypeInfo /*info*/> _spellAuraTypes;
    std::map<uint32_t /*flag*/, QString /*description*/> SpellProcInfo;
    std::map<uint32_t /*id*/, QString /*name*/> SpellFamilyInfo;
    std::array<std::map<uint32_t /*flag*/, QString /*name*/>, MAX_SPELL_ATTRIBUTES> SpellAttributes;
    std::map<uint32_t /*id*/, SpellEffectInfo /*info*/> _spellEffectInfo;
    std::map<uint32_t /*id*/, QString /*name*/> SpellTargetNames;
    std::map<uint32_t /*flag*/, QString /*name*/> SpellTargetFlags;
    std::map<uint32_t /*id*/, QString /*name*/> CombatRatingNames;
    std::map<uint32_t /*id*/, QString /*name*/> UnitModsNames;
    std::map<uint32_t /*id*/, QString /*name*/> SpellAuraStatesNames;
    std::map<int32_t /*id*/, QString /*name*/> PowerTypeNames;
    std::map<uint32_t /*id*/, QString /*name*/> SpellMechanicNames;
    std::map<uint32_t /*id*/, QString /*name*/> DispelNames;
    std::map<uint32_t /*id*/, QString /*name*/> ItemInventoryNames;
    std::map<uint32_t /*id*/, QString /*name*/> ItemSubclassWeapon;
    std::map<uint32_t /*id*/, QString /*name*/> ItemSubclassJunk;
    std::map<uint32_t /*id*/, QString /*name*/> ItemSubclassArmor;
    std::map<uint32_t /*id*/, QString /*name*/> ItemClassNames;
    std::map<uint32_t /*id*/, QString /*name*/> ShapeshiftForms;
    std::map<uint32_t /*id*/, QString /*name*/> CreatureTypeNames;
    std::map<uint32_t /*id*/, QString /*name*/> SpellDamageTypeNames;
    std::map<uint32_t /*id*/, QString /*name*/> SpellPreventionTypeNames;

    SpellWorkJson() = default;
    // Prevent copies
    SpellWorkJson(SpellWorkJson const&) = delete;
    SpellWorkJson(SpellWorkJson&&) = delete;
    SpellWorkJson& operator= (SpellWorkJson const&) = delete;
    SpellWorkJson& operator= (SpellWorkJson&&) = delete;

    static SpellWorkJson* instance()
    {
        static SpellWorkJson instance;
        return &instance;
    }

    // Data load - must be called once
    bool LoadJsonData();

    // Opens json
    static bool OpenJson(QString fileName, std::function<bool(const QJsonDocument& json)> handle);

    // Data functions
    const QString GetSpellSchoolName(uint32_t id);
    const QString GetSpellSchoolMaskName(uint32_t flag);
    const QString GetSpellModName(uint32_t id);
    const QString GetSpellInterruptFlagName(uint32_t flag);

    // flagsIds: 0 -> AuraInterruptFlags, 1 -> AuraInterruptFlags2
    const QString GetAuraInterruptFlagName(uint32_t flag, uint8_t flagsId);

    const QString GetSpellAuraTypeName(uint32_t id);
    const QString GetSpellProcDescription(uint32_t id);
    const QString GetSpellFamilyName(uint32_t id);
    const QString GetSpellAttributeName(uint32_t attributeId, uint32_t attributeFlag);
    const QString GetSpellEffectName(uint32_t id);
    const QString GetSpellTargetName(uint32_t id);
    const QString GetSpellTargetFlagName(uint32_t flag);
    const QString GetCombatRatingName(uint32_t id);
    const QString GetUnitModName(uint32_t id);
    const QString GetSpellAuraStateName(uint32_t id);
    const QString GetPowerTypeName(int32_t id);
    const QString GetSpellMechanicName(uint32_t id);
    const QString GetDispelName(uint32_t id);
    const QString GetItemInventoryName(uint32_t id);
    const QString GetItemSubclassWeaponName(uint32_t id);
    const QString GetItemSubclassArmorName(uint32_t id);
    const QString GetItemSubclassJunkName(uint32_t id);
    const QString GetItemClassName(uint32_t id);
    const QString GetShapeshiftFormName(uint32_t id);
    const QString GetCreatureTypeName(uint32_t id);
    const QString GetSpellDamageTypeName(uint32_t id);
    const QString GetSpellPreventionTypeName(uint32_t id);
};

#define sSpellWorkJson SpellWorkJson::instance()
