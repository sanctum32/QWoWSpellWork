#pragma once

#include <QString>
#include <QJsonDocument>
#include "Enums/SpellEnums.hpp"
#include <array>
#include <unordered_map>

namespace QSpellWorkJson{

// Data load - must be called once
    extern bool LoadJsonData();
    extern bool OpenJson(const QString& fileName, std::function<bool(const QJsonDocument& json)> handle);

// Storage
    extern std::unordered_map<uint32_t /*id*/, QString /*name*/> SpellSchools;
    extern std::unordered_map<uint32_t /*hex*/, QString /*name*/> SpellSchoolMasks;
    extern std::unordered_map<uint32_t /*id*/, QString /*name*/> SpellModOps;
    extern std::unordered_map<uint32_t /*flag*/, QString /*name*/> SpellInterruptFlags;
    extern std::unordered_map<uint32_t /*flag*/, QString /*name*/> AuraInterruptFlags;
    extern std::unordered_map<uint16_t /*id*/, QString /*name*/> SpellAuraTypes;
    extern std::unordered_map<uint32_t /*flag*/, QString /*description*/> SpellProcInfo;
    extern std::unordered_map<uint32_t /*id*/, QString /*name*/> SpellFamilyInfo;
    extern std::array<std::unordered_map<uint32_t /*flag*/, QString /*name*/>, MAX_SPELL_ATTRIBUTES> SpellAttributes;
    extern std::unordered_map<uint32_t /*id*/, QString /*name*/> SpellEffectNames;
    extern std::unordered_map<uint32_t /*id*/, QString /*name*/> SpellTargetNames;
}
