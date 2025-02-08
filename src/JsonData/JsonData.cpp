#include "JsonData.hpp"
#include "DataStorage.hpp"
#include <QJsonArray>
#include <QFile>
#include <QJsonObject>
#include <utility>

Q_LOGGING_CATEGORY(JSON, "spellwork.json");

template<class T>
void ReadBasicJsonArrayPairData(T& container, const QJsonArray& jsonArray, QString jsonFileName, QString arrayName, QString keyName, QString keyValueName)
{
    for (const auto& dataArray : jsonArray)
    {
        if (!dataArray.isObject())
        {
            continue;
        }

        const auto& dataArrayObj = dataArray.toObject();
        if (!dataArrayObj.contains(keyName) || !dataArrayObj.contains(keyName))
        {
            continue;
        }

        using keyType = typename T::key_type;
        const keyType _keyId = static_cast<keyType>(dataArrayObj.value(keyName).toDouble());

        if (container.contains(_keyId))
        {
            if (!arrayName.isEmpty())
            {
                qCDebug(JSON) << "Tried to load array \"" << arrayName << "\" (" << keyName << ": " << _keyId << ") data, but value data already exists! Skipped";
            }
            else
            {
                qCDebug(JSON) << "Tried to load array data for " << keyName << " '" << _keyId << "', but value data already exists! Skipped";
            }
        }
        else
        {
            container[_keyId] = dataArrayObj.value(keyValueName).toString();
        }
    }

    if (!arrayName.isEmpty())
    {
        qCDebug(JSON) << "Loaded " << container.size() << " \"" << arrayName << "\" array data from file \"" << jsonFileName << "\"!";
    }
    else
    {
        qCDebug(JSON) << "Loaded " << container.size() << " array data from file \"" << jsonFileName << "\"!";
    }
}

template<class T>
bool ReadBasicArrayPairFromFile(QString fileName, T& container, QString keyName = "Id", QString keyValueName = "Name")
{
    return SpellWorkJson::OpenJson(fileName, [&](const QJsonDocument& json)
    {
        if (!json.isArray())
        {
            qCDebug(JSON) << "Json file \"" << fileName << "\" is not array type";
            return false;
        }

        ReadBasicJsonArrayPairData(container, json.array(), fileName, {}, keyName, keyValueName);
        return true;
    });
}

/*static*/ bool SpellWorkJson::OpenJson(const QString& fileName, std::function<void(const QJsonDocument& json)> readJsonDataFn)
{
    qCDebug(JSON) << "Loading: " << fileName;

    QFile jsonFile(fileName);
    if (jsonFile.open(QIODevice::ReadOnly))
    {
        const auto jsonStrData = jsonFile.readAll();
        jsonFile.close();

        QJsonParseError jsonParseStatus;
        auto json = QJsonDocument::fromJson(jsonStrData, &jsonParseStatus);
        if (jsonParseStatus.error != QJsonParseError::NoError)
        {
            qCDebug(JSON) << "Failed to parse json, error: " << jsonParseStatus.errorString();
            return false;
        }

        readJsonDataFn(json);
        qCDebug(JSON) << "Successfully loaded data from " << fileName << ".";
        return true;
    }

    qCDebug(JSON) << "Failed to loaded data from " << fileName << ".";
    return false;
}

void SpellWorkJson::LoadJsonData()
{
    OpenJson("./json/SpellSchools.json", [&](const QJsonDocument& json)
    {
        if (!json.isObject())
        {
            qCDebug(JSON) << "Json file \"SpellSchools.json\" is not object type";
            return;
        }

        const auto& jsonFileObject = json.object();

        if (jsonFileObject.contains("SpellSchool") && jsonFileObject.value("SpellSchool").isArray())
        {
            ReadBasicJsonArrayPairData(m_spellSchoolNames, jsonFileObject.value("SpellSchool").toArray(), "SpellSchools.json", "SpellSchool", "Id", "Name");
        }
        else
        {
            qCDebug(JSON) << "Array \"SpellSchool\" does not exists or is not array in file \"SpellSchools.json\"!";
        }

        if (jsonFileObject.contains("SpellSchoolMask") && jsonFileObject.value("SpellSchoolMask").isArray())
        {
            ReadBasicJsonArrayPairData(m_spellSchoolMaskNames, jsonFileObject.value("SpellSchool").toArray(), "SpellSchools.json", "SpellSchoolMask", "Id", "Name");
        }
        else
        {
            qCDebug(JSON) << "Array \"SpellSchoolMask\" does not exists or is not array in file \"SpellSchools.json\"!";
        }
    });

    OpenJson("./json/SpellInterrupt.json", [&](const QJsonDocument& json)
    {
        if (!json.isObject())
        {
            qCDebug(JSON) << "Json file \"SpellInterrupt.json\" is not Object type";
            return;
        }

        const auto& jsonFileObject = json.object();

        if (jsonFileObject.contains("SpellInterruptFlags") && jsonFileObject.value("SpellInterruptFlags").isArray())
        {
            ReadBasicJsonArrayPairData(m_spellInterruptFlagNames, jsonFileObject.value("SpellInterruptFlags").toArray(), "SpellInterrupt.json", "SpellInterruptFlags", "Id", "Name");
        }
        else
        {
            qCDebug(JSON) << "Array \"SpellInterruptFlags\" does not exists or is not array in file \"SpellInterrupt.json\"!";
        }

        if (jsonFileObject.contains("AuraInterruptFlags") && jsonFileObject.value("AuraInterruptFlags").isArray())
        {
            ReadBasicJsonArrayPairData(m_auraInterruptFlagNames[0], jsonFileObject.value("AuraInterruptFlags").toArray(), "SpellInterrupt.json", "AuraInterruptFlags", "Id", "Name");
        }
        else
        {
            qCDebug(JSON) << "Array \"AuraInterruptFlags\" does not exists or is not array in file \"SpellInterrupt.json\"!";
        }

        if (jsonFileObject.contains("AuraInterruptFlags2") && jsonFileObject.value("AuraInterruptFlags2").isArray())
        {
            ReadBasicJsonArrayPairData(m_auraInterruptFlagNames[1], jsonFileObject.value("AuraInterruptFlags2").toArray(), "SpellInterrupt.json", "AuraInterruptFlags2", "Id", "Name");
        }
        else
        {
            qCDebug(JSON) << "Array \"AuraInterruptFlags2\" does not exists or is not array in file \"SpellInterrupt.json\"!";
        }
    });

    OpenJson("./json/SpellAttributes.json", [&](const QJsonDocument& json)
    {
        if (!json.isObject())
        {
            qCDebug(JSON) << "Json file \"SpellAttributes.json\" is not Object type";
            return;
        }

        const auto& jsonFileObject = json.object();

        for (uint8_t i = 0; i < MAX_SPELL_ATTRIBUTES; ++i)
        {
            QString attributeName = QString("AttributesEx" + QString::number(i));

            if (jsonFileObject.contains(attributeName) && jsonFileObject.value(attributeName).isArray())
            {
                ReadBasicJsonArrayPairData(m_spellAttributeNames[i], jsonFileObject.value(attributeName).toArray(), "SpellAttributes.json", "AuraInterruptFlags2", "Flag", "Name");
            }
            else
            {
                qCDebug(JSON) << "Array \"" << attributeName << "\" does not exists or is not array in file \"SpellAttributes.json\"!";
            }
        }
    });

    OpenJson("./json/SpellTargets.json", [&](const QJsonDocument& json)
    {
        if (!json.isObject())
        {
            qCDebug(JSON) << "Json file \"Spelltargets.json\" is not Object type";
            return;
        }

        const auto& jsonFileObject = json.object();

        if (jsonFileObject.contains("SpellTargetNames") && jsonFileObject.value("SpellTargetNames").isArray())
        {
            ReadBasicJsonArrayPairData(m_spellTargetNames, jsonFileObject.value("SpellTargetNames").toArray(), "SpellTargets.json", "SpellTargetNames", "Id", "Name");
        }
        else
        {
            qCDebug(JSON) << "Array \"SpellTargetNames\" does not exists or is not array in file \"SpellTargets.json\"!";
        }

        if (jsonFileObject.contains("SpellCastTargetFlags") && jsonFileObject.value("SpellCastTargetFlags").isArray())
        {
            ReadBasicJsonArrayPairData(m_SpellTargetFlagNames, jsonFileObject.value("SpellCastTargetFlags").toArray(), "SpellTargets.json", "SpellCastTargetFlags", "Id", "Name");
        }
        else
        {
            qCDebug(JSON) << "Array \"SpellCastTargetFlags\" does not exists or is not array in file \"SpellTargets.json\"!";
        }
    });

    OpenJson("./json/ItemSubclass.json", [&](const QJsonDocument& json)
    {
        if (!json.isObject())
        {
            qCDebug(JSON) << "Json file \"ItemSubclass.json\" is not Object type";
            return false;
        }

        const auto& jsonFileObject = json.object();

        if (jsonFileObject.contains("ItemSubclassWeapon") && jsonFileObject.value("ItemSubclassWeapon").isArray())
        {
            ReadBasicJsonArrayPairData(m_itemSubClassWeaponNames, jsonFileObject.value("ItemSubclassWeapon").toArray(), "ItemSubclass.json", "ItemSubclassWeapon", "Id", "Name");
        }
        else
        {
            qCDebug(JSON) << "Array \"ItemSubclassWeapon\" does not exists or is not array in file \"ItemSubclass.json\"!";
        }

        if (jsonFileObject.contains("ItemSubclassArmor") && jsonFileObject.value("ItemSubclassArmor").isArray())
        {
            ReadBasicJsonArrayPairData(m_itemSubclassArmorNames, jsonFileObject.value("ItemSubclassArmor").toArray(), "ItemSubclass.json", "ItemSubclassArmor", "Id", "Name");
        }
        else
        {
            qCDebug(JSON) << "Array \"ItemSubclassArmor\" does not exists or is not array in file \"ItemSubclass.json\"!";
        }

        if (jsonFileObject.contains("ItemSubclassJunk") && jsonFileObject.value("ItemSubclassJunk").isArray())
        {
            ReadBasicJsonArrayPairData(m_itemSubclassJunkNames, jsonFileObject.value("ItemSubclassJunk").toArray(), "SpellTargets.json", "ItemSubclassJunk", "Id", "Name");
        }
        else
        {
            qCDebug(JSON) << "Array \"ItemSubclassArmor\" does not exists or is not array in file \"ItemSubclass.json\"!";
        }

        return true;
    });

    OpenJson("./json/SpellEffects.json", [&](const QJsonDocument& json)
    {
        if (!json.isArray())
        {
            qCDebug(JSON) << "Json file \"SpellEffects.json\" is not Array type";
            return;
        }

        const auto& jsonArray = json.array();
        for (const auto& attrData : std::as_const(jsonArray))
        {
            if (!attrData.isObject())
            {
                continue;
            }

            const auto& arrayData = attrData.toObject();
            if (!arrayData.contains("Id") || !arrayData.contains("Name"))
            {
                continue;
            }

            const uint32_t _keyId = arrayData.value("Id").toInt();
            if (m_spellEffectInfo.contains(_keyId))
            {
                qCDebug(JSON) << "\"./json/SpellEffects.json\" has duplicate entry " << QString::number(_keyId) << ". Skipping";
                continue;
            }

            auto& effectInfo = m_spellEffectInfo[_keyId];
            effectInfo.name = arrayData.value("Name").toString();

            if (!arrayData.value("EffectDetail").isNull())
            {
                effectInfo.extraDetailFormatStr         = arrayData.value("EffectDetail").toString();
            }
        }

        if (m_spellEffectInfo.empty())
        {
            qCDebug(JSON) << "Failed to load entries from SpellEffects.json";
        }
    });

    OpenJson("./json/SpellAuraTypes.json", [&](const QJsonDocument& json)
    {
        if (!json.isArray())
        {
            qCDebug(JSON) << "Json file \"SpellAuraTypes.json\" is not Array type";
            return;
        }

        const auto& jsonArray = json.array();
        for (const auto& attrData : jsonArray)
        {
            const auto& arrayData = attrData.toObject();
            if (!arrayData.contains("Id") || !arrayData.contains("Name"))
            {
                continue;
            }

            const uint32_t _keyId = arrayData.value("Id").toInt();

            if (m_spellAuraTypeNames.contains(_keyId))
            {
                qCDebug(JSON) << "\"./json/SpellAuraTypes.json\" has duplicate entry " << QString::number(_keyId) << ". Skipping";
                continue;
            }

            auto& effectInfo    = m_spellAuraTypeNames[_keyId];
            effectInfo.name     = arrayData.value("Name").toString();

            if (arrayData.contains("EffectDetail") && !arrayData.value("EffectDetail").isNull())
            {
                effectInfo.extraDetailFormatStr = arrayData.value("EffectDetail").toString();
            }
        }

        if (m_spellAuraTypeNames.empty())
        {
            qCDebug(JSON) << "Failed to load entries from SpellAuraTypes.json";
        }
    });

    OpenJson("./json/SummonProperties.json", [&](const QJsonDocument& json)
    {
        if (!json.isObject())
        {
            qCDebug(JSON) << "Json file \"SummonProperties.json\" is not Object type";
            return;
        }

        const auto& jsonFileObject = json.object();
        if (jsonFileObject.contains("SummonCategory") && jsonFileObject.value("SummonCategory").isArray())
        {
            ReadBasicJsonArrayPairData(m_SummonPropCategoryNames, jsonFileObject.value("SummonCategory").toArray(), "SummonProperties.json", "SummonCategory", "Id", "Name");
        }
        else
        {
            qCDebug(JSON) << "Array \"SummonCategory\" does not exists or is not array in file \"ItemSubclass.json\"!";
        }

        if (jsonFileObject.contains("SummonTypeName") && jsonFileObject.value("SummonTypeName").isArray())
        {
            ReadBasicJsonArrayPairData(m_SummonPropSummTypeNames, jsonFileObject.value("SummonTypeName").toArray(), "SummonProperties.json", "SummonTypeName", "Id", "Name");
        }
        else
        {
            qCDebug(JSON) << "Array \"SummonTypeName\" does not exists or is not array in file \"ItemSubclass.json\"!";
        }

        if (jsonFileObject.contains("SummonFlags") && jsonFileObject.value("SummonFlags").isArray())
        {
            ReadBasicJsonArrayPairData(m_SummonPropSummFlagNames, jsonFileObject.value("SummonFlags").toArray(), "SummonProperties.json", "SummonFlags", "Id", "Name");
        }
        else
        {
            qCDebug(JSON) << "Array \"SummonFlags\" does not exists or is not array in file \"ItemSubclass.json\"!";
        }

        if (jsonFileObject.contains("TypeNameIdOverwrite") && jsonFileObject.value("TypeNameIdOverwrite").isArray())
        {
            const auto& propExtraArray = jsonFileObject.value("TypeNameIdOverwrite").toArray();
            for (const auto& propExtra : std::as_const(propExtraArray))
            {
                if (!propExtra.isObject())
                {
                    continue;
                }

                const auto& propExtraObj = propExtra.toObject();
                if (!propExtraObj.contains("PropertyId") || !propExtraObj.contains("SummonTypeNameId"))
                {
                    continue;
                }

                const uint32_t propertyId = propExtraObj.value("PropertyId").toInt();
                auto* summonProperty = const_cast<SummonPropertiesEntry*>(sDataStorage->GetSummonPropertiesEntry(propertyId));
                if (summonProperty == nullptr)
                {
                    qCDebug(JSON) << "\"./json/SummonProperties.json\" has invalid duplicate TypeNameIdOverwrite entry " << QString::number(propertyId) << ". Skipping";
                    continue;
                }
                const uint32_t summonTypeNameId = propExtraObj.value("SummonTypeNameId").toInt();
                if (!m_SummonPropSummTypeNames.contains(summonTypeNameId))
                {
                    qCDebug(JSON) << "\"./json/SummonProperties.json\" has invalid SummonTitle entry " << QString::number(summonTypeNameId) << " for summon property entry "
                                  << QString::number(propertyId) << ". Skipping";

                    continue;
                }

                summonProperty->SummonTypeNameId = summonTypeNameId;
            }
        }
    });

    ReadBasicArrayPairFromFile("./json/SpellMod.json", m_spellModOpNames);
    ReadBasicArrayPairFromFile("./json/SpellProc.json", m_spellProcFlagNames, "Flag");
    ReadBasicArrayPairFromFile("./json/SpellFamily.json", m_spellFamilyNames);
    ReadBasicArrayPairFromFile("./json/CombatRating.json", m_combatRatingNames);
    ReadBasicArrayPairFromFile("./json/UnitMods.json", m_unitModsNames);
    ReadBasicArrayPairFromFile("./json/SpellAuraStates.json", m_spellAuraStatesNames);
    ReadBasicArrayPairFromFile("./json/PowerTypes.json", m_powerTypeNames);
    ReadBasicArrayPairFromFile("./json/SpellMechanics.json", m_spellMechanicNames);
    ReadBasicArrayPairFromFile("./json/SpellDispelTypes.json", m_dispelNames);
    ReadBasicArrayPairFromFile("./json/ItemInventoryTypes.json", m_itemInventoryNames);
    ReadBasicArrayPairFromFile("./json/ItemClass.json", m_itemClassNames);
    ReadBasicArrayPairFromFile("./json/ShapeShiftForms.json", m_shapeshiftFormNames);
    ReadBasicArrayPairFromFile("./json/CreatureTypes.json", m_creatureTypeNames);
    ReadBasicArrayPairFromFile("./json/SpellDamageTypes.json", m_spellDamageTypeNames);
    ReadBasicArrayPairFromFile("./json/SpellPreventionTypes.json", m_spellPreventionTypeNames);
}

QStringView SpellWorkJson::GetSpellSchoolName(uint32_t id) const
{
    const auto& itr = m_spellSchoolNames.find(id);
    return itr != m_spellSchoolNames.end() ? itr->second : QString("SPELL_SCHOOL_UNK_%1").arg(id);
}

QStringView SpellWorkJson::GetSpellSchoolMaskName(uint32_t flag) const
{
    const auto& itr = m_spellSchoolMaskNames.find(flag);
    return itr != m_spellSchoolMaskNames.end() ? itr->second : QString("SPELL_SCHOOL_MASK_UNK_%1").arg(flag);
}

QStringView SpellWorkJson::GetSpellModName(uint32_t id) const
{
    const auto& itr = m_spellModOpNames.find(id);
    return itr != m_spellModOpNames.end() ? itr->second : QString("SPELL_MOD_UNK_%1").arg(id);
}

QStringView SpellWorkJson::GetSpellInterruptFlagName(uint32_t flag) const
{
    const auto& itr = m_spellInterruptFlagNames.find(flag);
    return itr != m_spellInterruptFlagNames.end() ? itr->second : QString("SPELL_INTERRUPT_FLAG_UNK_0x%1").arg(flag, 8, 16, QLatin1Char('0'));
}

QStringView SpellWorkJson::GetAuraInterruptFlagName(uint32_t flag, uint8_t flagsId) const
{
    assert(flagsId < 2);
    const auto& itr = m_auraInterruptFlagNames[flagsId].find(flag);
    return itr != m_auraInterruptFlagNames[flagsId].end() ? itr->second : QString("AURA_INTERRUPT_FLAG%1_UNK_%2").arg(flagsId).arg(flag, 8, 16, QLatin1Char('0'));
}

QStringView SpellWorkJson::GetSpellAuraTypeName(uint32_t id) const
{
    const auto& itr = m_spellAuraTypeNames.find(id);
    return itr != m_spellAuraTypeNames.end() ? itr->second.name : QString("SPELL_AURA_UNK_%1").arg(id);
}

const SpellEffectInfo* SpellWorkJson::GetSpellAuraEffectInfo(uint32_t id) const
{
    const auto& itr = m_spellAuraTypeNames.find(id);
    return itr != m_spellAuraTypeNames.end() ? &itr->second : nullptr;
}

QStringView SpellWorkJson::GetSpellProcDescription(uint32_t id) const
{
    const auto& itr = m_spellProcFlagNames.find(id);
    return itr != m_spellProcFlagNames.end() ? itr->second : "-- no description --";
}

QStringView SpellWorkJson::GetSpellFamilyName(uint32_t id) const
{
    const auto& itr = m_spellFamilyNames.find(id);
    return itr != m_spellFamilyNames.end() ? itr->second : QString("SPELLFAMILY_UNK_%1").arg(id);
}

QStringView SpellWorkJson::GetSpellAttributeName(uint32_t attributeId, uint32_t attributeFlag) const
{
    const auto nullResult = QString("SPELL_ATTR%1_UNK_%2").arg(attributeId).arg(attributeFlag);
    if (attributeId >= MAX_SPELL_ATTRIBUTES)
    {
        return QString("SPELL_ATTR%1_UNK_%2").arg(attributeId).arg(attributeFlag);
    }

    const auto& itr = m_spellAttributeNames[attributeId].find(attributeFlag);
    return itr != m_spellAttributeNames[attributeId].end() ? itr->second : nullResult;
}

QStringView SpellWorkJson::GetSpellEffectName(uint32_t id) const
{
    const auto& itr = m_spellEffectInfo.find(id);
    return itr != m_spellEffectInfo.end() ? itr->second.name : QString("SPELL_EFFECT_UNK_%1").arg(id);
}

const SpellEffectInfo* SpellWorkJson::GetSpellEffectInfo(uint32_t id) const
{
    const auto& itr = m_spellEffectInfo.find(id);
    return itr != m_spellEffectInfo.end() ? &itr->second : nullptr;
}

QStringView SpellWorkJson::GetSpellTargetName(uint32_t id) const
{
    const auto& itr = m_spellTargetNames.find(id);
    return itr != m_spellTargetNames.end() ? itr->second : QString("TARGET_UNK_%1").arg(id);
}

QStringView SpellWorkJson::GetSpellTargetFlagName(uint32_t flag) const
{
    const auto& itr =  m_SpellTargetFlagNames.find(flag);
    return itr != m_SpellTargetFlagNames.end() ? itr->second : QString("TARGET_FLAG_UNK_%1").arg(flag);
}

QStringView SpellWorkJson::GetCombatRatingName(uint32_t id) const
{
    const auto& itr = m_combatRatingNames.find(id);
    return itr != m_combatRatingNames.end() ? itr->second : QString("CR_UNK_%1").arg(id);
}

QStringView SpellWorkJson::GetUnitModName(uint32_t id) const
{
    const auto& itr = m_unitModsNames.find(id);
    return itr != m_unitModsNames.end() ? itr->second : QString("UNIT_MOD_UNK_%1").arg(id);
}

QStringView SpellWorkJson::GetSpellAuraStateName(uint32_t id) const
{
    const auto& itr = m_spellAuraStatesNames.find(id);
    return itr != m_spellAuraStatesNames.end() ? itr->second : QString("AURA_STATE_UNK_%1").arg(id);
}

QStringView SpellWorkJson::GetPowerTypeName(int32_t id) const
{
    const auto& itr = m_powerTypeNames.find(id);
    return itr != m_powerTypeNames.end() ? itr->second : QString("POWER_UNK_%1").arg(id);
}

QStringView SpellWorkJson::GetSpellMechanicName(uint32_t id) const
{
    const auto& itr = m_spellMechanicNames.find(id);
    return itr != m_spellMechanicNames.end() ? itr->second : QString("MECHANIC_UNK_%1").arg(id);
}

QStringView SpellWorkJson::GetDispelName(uint32_t id) const
{
    const auto& itr = m_dispelNames.find(id);
    return itr != m_dispelNames.end() ? itr->second : QString("DISPEL_UNK_%1").arg(id);
}

QStringView SpellWorkJson::GetItemInventoryName(uint32_t id) const
{
    const auto& itr = m_itemInventoryNames.find(id);
    return itr != m_itemInventoryNames.end() ? itr->second : QString("INVTYPE_UNK_%1").arg(id);
}

QStringView SpellWorkJson::GetItemSubclassWeaponName(uint32_t id) const
{
    const auto& itr = m_itemSubClassWeaponNames.find(id);
    return itr != m_itemSubClassWeaponNames.end() ? itr->second : QString("ITEM_SUBCLASS_WEAPON_UNK_%1").arg(id);
}

QStringView SpellWorkJson::GetItemSubclassArmorName(uint32_t id) const
{
    const auto& itr = m_itemSubclassArmorNames.find(id);
    return itr != m_itemSubclassArmorNames.end() ? itr->second : QString("ITEM_SUBCLASS_ARMOR_UNK_%1").arg(id);
}

QStringView SpellWorkJson::GetItemSubclassJunkName(uint32_t id) const
{
    const auto& itr = m_itemSubclassJunkNames.find(id);
    return itr != m_itemSubclassJunkNames.end() ? itr->second : QString("ITEM_SUBCLASS_JUNK_UNK_%1").arg(id);
}

QStringView SpellWorkJson::GetItemClassName(uint32_t id) const
{
    const auto& itr = m_itemClassNames.find(id);
    return itr != m_itemClassNames.end() ? itr->second : QString("ITEM_CLASS_UNK_%1").arg(id);
}

QStringView SpellWorkJson::GetShapeshiftFormName(uint32_t id) const
{
    const auto& itr = m_shapeshiftFormNames.find(id);
    return itr != m_shapeshiftFormNames.end() ? itr->second : QString("FORM_UNK_%1").arg(id);
}

QStringView SpellWorkJson::GetCreatureTypeName(uint32_t id) const
{
    const auto& itr = m_creatureTypeNames.find(id);
    return itr != m_creatureTypeNames.end() ? itr->second : QString("CREATURE_TYPE_UNK_%1").arg(id);
}

QStringView SpellWorkJson::GetSpellDamageTypeName(uint32_t id) const
{
    const auto& itr = m_spellDamageTypeNames.find(id);
    return itr != m_spellDamageTypeNames.end() ? itr->second : QString("SPELL_DAMAGE_CLASS_UNK_%1").arg(id);
}

QStringView SpellWorkJson::GetSpellPreventionTypeName(uint32_t id) const
{
    const auto& itr = m_spellPreventionTypeNames.find(id);
    return itr != m_spellPreventionTypeNames.end() ? itr->second : QString("SPELL_PREVENTION_TYPE_UNK_%1").arg(id);
}

QStringView SpellWorkJson::GetSummonCategoryName(uint32_t id) const
{
    const auto& itr = m_SummonPropCategoryNames.find(id);
    return itr != m_SummonPropCategoryNames.end() ? itr->second : QString("UNKNOWN_SUMMON_CATEGORY_%1").arg(id);
}

QStringView SpellWorkJson::GetSummonTypeName(uint32_t id) const
{
    const auto& itr = m_SummonPropSummTypeNames.find(id);
    return itr != m_SummonPropSummTypeNames.end() ? itr->second : QString("UNKNOWN_SUMMON_CONTROL_TITLE_%1").arg(id);
}

QStringView SpellWorkJson::GetSummonPropertyFlagName(uint32_t id) const
{
    const auto& itr = m_SummonPropSummFlagNames.find(id);
    return itr != m_SummonPropSummFlagNames.end() ? itr->second : QString("SUMMON_PROP_FLAG_UNKNOWN_%1").arg(id);
}
