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
    std::map<uint32_t /*flag*/, QString /*name*/> AuraInterruptFlags;
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
    static bool OpenJson(const QString& fileName, std::function<bool(const QJsonDocument& json)> handle);

    // Data functions
    QStringView GetSpellSchoolName(uint32_t id);
    QStringView GetSpellSchoolMaskName(uint32_t flag);
    QStringView GetSpellModName(uint32_t id);
    QStringView GetSpellInterruptFlagName(uint32_t flag);
    QStringView GetAuraInterruptFlagName(uint32_t flag);
    QStringView GetSpellAuraTypeName(uint32_t id);
    QStringView GetSpellProcDescription(uint32_t id);
    QStringView GetSpellFamilyName(uint32_t id);
    QStringView GetSpellAttributeName(uint32_t attributeId, uint32_t attributeFlag);
    QStringView GetSpellEffectName(uint32_t id);
    QStringView GetSpellTargetName(uint32_t id);
    QStringView GetSpellTargetFlagName(uint32_t flag);
    QStringView GetCombatRatingName(uint32_t id);
    QStringView GetUnitModName(uint32_t id);
    QStringView GetSpellAuraStateName(uint32_t id);
    QStringView GetPowerTypeName(int32_t id);
    QStringView GetSpellMechanicName(uint32_t id);
    QStringView GetDispelName(uint32_t id);
    QStringView GetItemInventoryName(uint32_t id);
    QStringView GetItemSubclassWeaponName(uint32_t id);
    QStringView GetItemSubclassArmorName(uint32_t id);
    QStringView GetItemSubclassJunkName(uint32_t id);
    QStringView GetItemClassName(uint32_t id);
    QStringView GetShapeshiftFormName(uint32_t id);
    QStringView GetCreatureTypeName(uint32_t id);
    QStringView GetSpellDamageTypeName(uint32_t id);
    QStringView GetSpellPreventionTypeName(uint32_t id);
};

#define sSpellWorkJson SpellWorkJson::instance()
