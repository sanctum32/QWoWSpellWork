#include "JsonData.hpp"
#include <QJsonArray>
#include <QFile>
#include <QDebug>
#include <QJsonObject>

template<class T>
inline bool ReadBasicArray(const QString& fileName, T& container, const QString& keyName = "Id", const QString& nameValName = "Name")
{
    return QSpellWorkJson::OpenJson(fileName, [&](const QJsonDocument& json)
    {
        if (!json.isArray())
        {
            qCDebug(QSpellWorkJson::JSON) << "JSON: Json file \"" << fileName << "\" is not array type";
            return false;
        }

        const auto& jsonArray = json.array();
        for (const auto& jsonArrayItem : std::as_const(jsonArray))
        {
            const auto& arrayObj = jsonArrayItem.toObject();
            const uint32_t _keyId = static_cast<uint32_t>(arrayObj.value(keyName).toDouble());
            const QString _nameStr = arrayObj.value(nameValName).toString();

            if (container.contains(_keyId))
            {
                qCDebug(QSpellWorkJson::JSON) << "JSON: \"" << fileName << "\" has duplicate Id " << QString::number(_keyId) << ". Skipping";
                continue;
            }

            container[_keyId] = _nameStr;
        }

        if (container.empty())
        {
            qCDebug(QSpellWorkJson::JSON) << "JSON: Failed to load data from " << fileName << " data. Related container is empty!";
            return false;
        }

        return true;
    });
}

namespace QSpellWorkJson
{
    Q_LOGGING_CATEGORY(JSON, "spellwork.json")

    std::map<uint32_t /*id*/, QString /*name*/> SpellSchools;
    std::map<uint32_t /*hex*/, QString /*name*/> SpellSchoolMasks;
    std::map<uint32_t /*id*/, QString /*name*/> SpellModOps;
    std::map<uint32_t /*id*/, QString /*name*/> SpellInterruptFlags;
    std::map<uint32_t /*id*/, QString /*name*/> AuraInterruptFlags;
    std::map<uint16_t /*id*/, QString /*name*/> SpellAuraTypes;
    std::map<uint32_t /*flag*/, QString /*description*/> SpellProcInfo;
    std::map<uint32_t /*id*/, QString /*name*/> SpellFamilyInfo;
    std::array<std::map<uint32_t /*flag*/, QString /*name*/>, MAX_SPELL_ATTRIBUTES> SpellAttributes;
    std::map<uint32_t /*id*/, QString /*name*/> SpellEffectNames;
    std::map<uint32_t /*id*/, QString /*name*/> SpellTargetNames;
    std::map<uint32_t /*id*/, QString /*name*/> CombatRatingNames;
    std::map<uint32_t /*id*/, QString /*name*/> UnitModsNames;
    std::map<uint32_t /*id*/, QString /*name*/> SpellAuraStatesNames;

    // Reads json file
    // returns 1 on failure
    bool OpenJson(const QString& fileName, std::function<bool(const QJsonDocument& json)> handle)
    {
        QFile jsonFile(fileName);
        if (jsonFile.open(QIODevice::ReadOnly))
        {
            const auto jsonStrData = jsonFile.readAll();
            jsonFile.close();

            QJsonParseError jsonParseStatus;
            auto json = QJsonDocument::fromJson(jsonStrData, &jsonParseStatus);
            if (jsonParseStatus.error != QJsonParseError::NoError)
            {
                qCDebug(JSON) << "JSON: Failed to parse json, error: " << jsonParseStatus.errorString();
                return false;
            }

            if (handle(json))
            {
                qCDebug(JSON) << "JSON: Successfully loaded data from " << fileName << ".";
                return true;
            }
        }

        qCDebug(JSON) << "JSON: Failed to loaded data from " << fileName << ".";
        return false;
    }

    bool LoadJsonData()
    {
        QLoggingCategory::setFilterRules("spellwork.json.debug=true");

        if (!OpenJson("./json/SpellSchools.json", [&](const QJsonDocument& json)
        {
            if (!json.isObject())
            {
                qCDebug(JSON) << "JSON: Json file \"SpellSchools.json\" is not object type";
                return false;
            }

            const auto& document = json.object();
            const auto& schoolArray = document.value("SpellSchool").toArray();
            for (const auto& objArray : std::as_const(schoolArray))
            {
                const auto& schoolArray = objArray.toObject();
                const uint32_t _keyId = static_cast<uint32_t>(schoolArray.value("Id").toDouble());

                if (SpellSchools.contains(_keyId))
                {
                    qCDebug(JSON) << "JSON: \"./json/SpellSchools.json\" has duplicate SpellSchool Id " << QString::number(_keyId) << ". Skipping";
                    continue;
                }

                SpellSchools[_keyId] = schoolArray.value("Name").toString();
            }

            if (SpellSchools.empty())
            {
                qCDebug(JSON) << "JSON: Failed to load SpellSchools data!";
                return false;
            }

            const auto& schoolMaskArray = document.value("SpellSchoolMask").toArray();
            for (const auto& objArray : std::as_const(schoolMaskArray))
            {
                const auto& schoolArray = objArray.toObject();
                const uint32_t _keyId = static_cast<uint32_t>(schoolArray.value("Id").toDouble());

                if (SpellSchoolMasks.contains(_keyId))
                {
                    qCDebug(JSON) << "JSON: \"./json/SpellSchools.json\" has duplicate SpellSchoolMask Id " << QString::number(_keyId) << ". Skipping";
                    continue;
                }

                SpellSchoolMasks[_keyId] = schoolArray.value("Name").toString();
            }

            if (SpellSchoolMasks.empty())
            {
                qCDebug(JSON) << "JSON: Failed to load SpellSchools mask data!";
                return false;
            }

            return true;
        }))
        {
            return false;
        }

        if (!OpenJson("./json/SpellInterrupt.json", [&](const QJsonDocument& json)
        {
            if (!json.isObject())
            {
                qCDebug(JSON) << "JSON: Json file \"SpellInterrupt.json\" is not Object type";
                return false;
            }

            const auto& document = json.object();
            {
                const auto& jsonArray = document.value("SpellInterruptFlags").toArray();
                for (const auto& spellInterruptFlag : std::as_const(jsonArray))
                {
                    const auto& spellinterruptObj = spellInterruptFlag.toObject();
                    const uint32_t _keyId = static_cast<uint32_t>(spellinterruptObj.value("Flag").toDouble());

                    if (SpellInterruptFlags.contains(_keyId))
                    {
                        qCDebug(JSON) << "JSON: \"./json/SpellInterrupt.json\" has duplicate SpellInterruptFlags Id " << QString::number(_keyId) << ". Skipping";
                        continue;
                    }

                    SpellInterruptFlags[_keyId] = spellinterruptObj.value("Name").toString();
                }

                if (SpellInterruptFlags.empty())
                {
                    qCDebug(JSON) << "JSON: Failed to load SpellInterruptFlags data!";
                    return false;
                }
            }

            {
                const auto& jsonArray = document.value("AuraInterruptFlags").toArray();
                for (const auto& auraInterruptFlag : std::as_const(jsonArray))
                {
                    const auto& auraInterruptObj = auraInterruptFlag.toObject();
                    const uint32_t _keyId = static_cast<uint32_t>(auraInterruptObj.value("Flag").toDouble());

                    if (AuraInterruptFlags.contains(_keyId))
                    {
                        qCDebug(JSON) << "JSON: \"./json/SpellInterrupt.json\" has duplicate AuraInterruptFlags Id " << QString::number(_keyId) << ". Skipping";
                        continue;
                    }

                    AuraInterruptFlags[_keyId] = auraInterruptObj.value("Name").toString();
                }

                if (AuraInterruptFlags.empty())
                {
                    qCDebug(JSON) << "JSON: Failed to load AuraInterruptFlags data!";
                    return false;
                }
            }

            return true;
            }))
        {
            return false;
        }

        if (!OpenJson("./json/SpellAttributes.json", [&](const QJsonDocument& json)
        {
            if (!json.isObject())
            {
                qCDebug(JSON) << "JSON: Json file \"SpellAttributes.json\" is not Array type";
                return false;
            }

            const auto& jsonObj = json.object();
            for (uint8_t i = 0; i < MAX_SPELL_ATTRIBUTES; ++i)
            {
                QString attributeName("AttributesEx" + QString::number(i));
                const auto& attrArray = jsonObj.value(attributeName).toArray();
                for (const auto& attrData : std::as_const(attrArray))
                {
                    const auto& attrObj = attrData.toObject();
                    const uint32_t _keyId = attrObj.value("Flag").toInt();

                    if (SpellAttributes[i].contains(_keyId))
                    {
                        qCDebug(JSON) << "JSON: \"./json/SpellAttributes.json\" has duplicate " << attributeName << " Flag " << QString::number(_keyId) << ". Skipping";
                        continue;
                    }

                    SpellAttributes[i][attrObj.value("Flag").toInt()] = attrObj.value("Name").toString();
                }

                if (SpellAttributes[i].empty())
                {
                    qCDebug(JSON) << "JSON: Failed to load " << attributeName << " from SpellAttributes";
                    return false;
                }
            }

            return true;
        }))
        {
            return false;
        }

        if (!ReadBasicArray("./json/SpellMod.json", SpellModOps) ||
            !ReadBasicArray("./json/SpellAuraTypes.json", SpellAuraTypes) ||
            !ReadBasicArray("./json/SpellProc.json", SpellProcInfo, "Flag") ||
            !ReadBasicArray("./json/SpellFamily.json", SpellFamilyInfo) ||
            !ReadBasicArray("./json/SpellEffects.json", SpellEffectNames) ||
            !ReadBasicArray("./json/SpellTargets.json", SpellTargetNames) ||
            !ReadBasicArray("./json/CombatRating.json", CombatRatingNames) ||
            !ReadBasicArray("./json/UnitMods.json", UnitModsNames) ||
            !ReadBasicArray("./json/SpellAuraStates.json", SpellAuraStatesNames)

        )
        {
            return false;
        }

        return true;
    }
}
