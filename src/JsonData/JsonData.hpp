#pragma once

#include <QString>
#include <QJsonDocument>
#include <QLoggingCategory>
#include "Enums/SpellEnums.hpp"
#include <array>
#include <map>

namespace QSpellWorkJson
{
    Q_DECLARE_LOGGING_CATEGORY(JSON)

// Data load - must be called once
    extern bool LoadJsonData();
    extern bool OpenJson(const QString& fileName, std::function<bool(const QJsonDocument& json)> handle);

// Storage
    extern std::map<uint32_t /*id*/, QString /*name*/> SpellSchools;
    extern std::map<uint32_t /*hex*/, QString /*name*/> SpellSchoolMasks;
    extern std::map<uint32_t /*id*/, QString /*name*/> SpellModOps;
    extern std::map<uint32_t /*flag*/, QString /*name*/> SpellInterruptFlags;
    extern std::map<uint32_t /*flag*/, QString /*name*/> AuraInterruptFlags;
    extern std::map<uint16_t /*id*/, QString /*name*/> SpellAuraTypes;
    extern std::map<uint32_t /*flag*/, QString /*description*/> SpellProcInfo;
    extern std::map<uint32_t /*id*/, QString /*name*/> SpellFamilyInfo;
    extern std::array<std::map<uint32_t /*flag*/, QString /*name*/>, MAX_SPELL_ATTRIBUTES> SpellAttributes;
    extern std::map<uint32_t /*id*/, QString /*name*/> SpellEffectNames;
    extern std::map<uint32_t /*id*/, QString /*name*/> SpellTargetNames;
    extern std::map<uint32_t /*id*/, QString /*name*/> CombatRatingNames;
    extern std::map<uint32_t /*id*/, QString /*name*/> UnitModsNames;
    extern std::map<uint32_t /*id*/, QString /*name*/> SpellAuraStatesNames;
    extern std::map<int32_t /*id*/, QString /*name*/> PowerTypeNames;
}
