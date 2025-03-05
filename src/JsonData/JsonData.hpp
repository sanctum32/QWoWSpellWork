#pragma once

#include <QString>
#include <QJsonDocument>
#include <QLoggingCategory>
#include "Enums/SpellEnums.hpp"
#include <array>
#include <map>

Q_DECLARE_LOGGING_CATEGORY(JSON)

struct SpellEffectInfo
{
    // Effect name
    QString name;

    // If set, it will add extra formatted details
    QString extraDetailFormatStr;
};

class SpellWorkJson
{
    SpellWorkJson() = default;

    // Storage
    std::map<uint32_t /*id*/, QString /*name*/> m_spellSchoolNames;
    std::map<uint32_t /*hex*/, QString /*name*/> m_spellSchoolMaskNames;
    std::map<uint32_t /*id*/, QString /*name*/> m_spellModOpNames;
    std::map<uint32_t /*flag*/, QString /*name*/> m_spellInterruptFlagNames;
    std::array<std::map<uint32_t /*flag*/, QString /*name*/>, 2> m_auraInterruptFlagNames;
    std::map<uint16_t /*id*/, SpellEffectInfo /*info*/> m_spellAuraTypeNames;
    std::map<uint32_t /*flag*/, QString /*description*/> m_spellProcFlagNames;
    std::map<uint32_t /*id*/, QString /*name*/> m_spellFamilyNames;
    std::array<std::map<uint32_t /*flag*/, QString /*name*/>, MAX_SPELL_ATTRIBUTES> m_spellAttributeNames;
    std::map<uint32_t /*id*/, SpellEffectInfo /*info*/> m_spellEffectInfo;
    std::map<uint32_t /*id*/, QString /*name*/> m_spellTargetNames;
    std::map<uint32_t /*flag*/, QString /*name*/> m_SpellTargetFlagNames;
    std::map<uint32_t /*id*/, QString /*name*/> m_combatRatingNames;
    std::map<uint32_t /*id*/, QString /*name*/> m_unitModsNames;
    std::map<uint32_t /*id*/, QString /*name*/> m_spellAuraStatesNames;
    std::map<int32_t /*id*/, QString /*name*/> m_powerTypeNames;
    std::map<uint32_t /*id*/, QString /*name*/> m_spellMechanicNames;
    std::map<uint32_t /*id*/, QString /*name*/> m_dispelNames;
    std::map<uint32_t /*id*/, QString /*name*/> m_itemInventoryNames;
    std::map<uint32_t /*id*/, QString /*name*/> m_itemSubClassWeaponNames;
    std::map<uint32_t /*id*/, QString /*name*/> m_itemSubclassJunkNames;
    std::map<uint32_t /*id*/, QString /*name*/> m_itemSubclassArmorNames;
    std::map<uint32_t /*id*/, QString /*name*/> m_itemClassNames;
    std::map<uint32_t /*id*/, QString /*name*/> m_shapeshiftFormNames;
    std::map<uint32_t /*id*/, QString /*name*/> m_creatureTypeNames;
    std::map<uint32_t /*id*/, QString /*name*/> m_spellDamageTypeNames;
    std::map<uint32_t /*id*/, QString /*name*/> m_spellPreventionTypeNames;
    std::map<uint32_t /*id*/, QString /*name*/> m_SummonPropCategoryNames;
    std::map<uint32_t /*id*/, QString /*name*/> m_SummonPropSummTypeNames;
    std::map<uint32_t /*id*/, QString /*name*/> m_SummonPropSummFlagNames;

public:
    SpellWorkJson(SpellWorkJson const&) = delete;
    SpellWorkJson& operator= (SpellWorkJson const&) = delete;

    static SpellWorkJson* instance()
    {
        static SpellWorkJson instance;
        return &instance;
    }

    // Data load - must be called once
    void LoadJsonData();

    // Opens json
    static bool OpenJson(const QString& fileName, std::function<void(const QJsonDocument& json)> handle);

    // Data functions
    const QString GetSpellSchoolName(uint32_t id) const;
    const QString GetSpellSchoolMaskName(uint32_t flag) const;
    const QString GetSpellModName(uint32_t id) const;
    const QString GetSpellInterruptFlagName(uint32_t flag) const;

    // flagsIds: 0 -> AuraInterruptFlags, 1 -> AuraInterruptFlags2
    const QString GetAuraInterruptFlagName(uint32_t flag, uint8_t flagsId) const;
    const QString GetSpellAuraTypeName(uint32_t id) const;
    const SpellEffectInfo* GetSpellAuraEffectInfo(uint32_t id) const;
    const auto& GetSpellAuraEffectData() const { return m_spellAuraTypeNames; }
    const QString GetSpellProcDescription(uint32_t id) const;
    const auto& GetSpellFamilyData() const { return m_spellFamilyNames; }
    const QString GetSpellFamilyName(uint32_t id) const;

    const QString GetSpellAttributeName(uint32_t attributeId, uint32_t attributeFlag) const;
    const QString GetSpellEffectName(uint32_t id) const;
    const SpellEffectInfo* GetSpellEffectInfo(uint32_t id) const;
    auto const& GetSpellEffectData() const { return m_spellEffectInfo; }
    const QString GetSpellTargetName(uint32_t id) const;
    auto const& GetSpellTargetData() const { return m_spellTargetNames; }
    const QString GetSpellTargetFlagName(uint32_t flag) const;
    const QString GetCombatRatingName(uint32_t id) const;
    const QString GetUnitModName(uint32_t id) const;
    const QString GetSpellAuraStateName(uint32_t id) const;
    const QString GetPowerTypeName(int32_t id) const;
    const QString GetSpellMechanicName(uint32_t id) const;
    const QString GetDispelName(uint32_t id) const;
    const QString GetItemInventoryName(uint32_t id) const;
    const QString GetItemSubclassWeaponName(uint32_t id) const;
    const QString GetItemSubclassArmorName(uint32_t id) const;
    const QString GetItemSubclassJunkName(uint32_t id) const;
    const QString GetItemClassName(uint32_t id) const;
    const QString GetShapeshiftFormName(uint32_t id) const;
    const QString GetCreatureTypeName(uint32_t id) const;
    const QString GetSpellDamageTypeName(uint32_t id) const;
    const QString GetSpellPreventionTypeName(uint32_t id) const;
    const QString GetSummonCategoryName(uint32_t id) const;
    const QString GetSummonTypeName(uint32_t id) const;
    const QString GetSummonPropertyFlagName(uint32_t id) const;
};

#define sSpellWorkJson SpellWorkJson::instance()
