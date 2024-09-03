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

public:
    SpellWorkJson(SpellWorkJson const&) = delete;
    SpellWorkJson& operator= (SpellWorkJson const&) = delete;

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
    QStringView GetSpellSchoolName(uint32_t id) const;
    QStringView GetSpellSchoolMaskName(uint32_t flag) const;
    QStringView GetSpellModName(uint32_t id) const;
    QStringView GetSpellInterruptFlagName(uint32_t flag) const;

    // flagsIds: 0 -> AuraInterruptFlags, 1 -> AuraInterruptFlags2
    QStringView GetAuraInterruptFlagName(uint32_t flag, uint8_t flagsId) const;
    QStringView GetSpellAuraTypeName(uint32_t id) const;
    const SpellEffectInfo* GetSpellAuraEffectInfo(uint32_t id) const;
    const auto& GetSpellAuraEffectData() const { return m_spellAuraTypeNames; }
    QStringView GetSpellProcDescription(uint32_t id) const;
    const auto& GetSpellFamilyData() const { return m_spellFamilyNames; }
    QStringView GetSpellFamilyName(uint32_t id) const;

    QStringView GetSpellAttributeName(uint32_t attributeId, uint32_t attributeFlag) const;
    QStringView GetSpellEffectName(uint32_t id) const;
    const SpellEffectInfo* GetSpellEffectInfo(uint32_t id) const;
    auto const& GetSpellEffectData() const { return m_spellEffectInfo; }
    QStringView GetSpellTargetName(uint32_t id) const;
    auto const& GetSpellTargetData() const { return m_spellTargetNames; }
    QStringView GetSpellTargetFlagName(uint32_t flag) const;
    QStringView GetCombatRatingName(uint32_t id) const;
    QStringView GetUnitModName(uint32_t id) const;
    QStringView GetSpellAuraStateName(uint32_t id) const;
    QStringView GetPowerTypeName(int32_t id) const;
    QStringView GetSpellMechanicName(uint32_t id) const;
    QStringView GetDispelName(uint32_t id) const;
    QStringView GetItemInventoryName(uint32_t id) const;
    QStringView GetItemSubclassWeaponName(uint32_t id) const;
    QStringView GetItemSubclassArmorName(uint32_t id) const;
    QStringView GetItemSubclassJunkName(uint32_t id) const;
    QStringView GetItemClassName(uint32_t id) const;
    QStringView GetShapeshiftFormName(uint32_t id) const;
    QStringView GetCreatureTypeName(uint32_t id) const;
    QStringView GetSpellDamageTypeName(uint32_t id) const;
    QStringView GetSpellPreventionTypeName(uint32_t id) const;
};

#define sSpellWorkJson SpellWorkJson::instance()
