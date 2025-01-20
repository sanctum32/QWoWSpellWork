#include "JsonData.hpp"
#include "DataStorage.hpp"
#include <QJsonArray>
#include <QFile>
#include <QJsonObject>
#include <utility>

Q_LOGGING_CATEGORY(JSON, "spellwork.json");

template<class T>
inline bool ReadBasicArrayFromFile(const QString fileName, T& container, const QString keyName = "Id", const QString nameValName = "Name")
{
    return SpellWorkJson::OpenJson(fileName, [&](const QJsonDocument& json)
    {
        if (!json.isArray())
        {
            qCDebug(JSON) << "Json file \"" << fileName << "\" is not array type";
            return false;
        }

        const auto& jsonArray = json.array();
        for (const auto& jsonArrayItem : std::as_const(jsonArray))
        {
            const auto& arrayObj = jsonArrayItem.toObject();

            using keyType = typename T::key_type;
            const keyType _keyId = static_cast<keyType>(arrayObj.value(keyName).toDouble());
            const QString _nameStr = arrayObj.value(nameValName).toString();

            if (container.contains(_keyId))
            {
                qCDebug(JSON) << fileName << "\" has duplicate Id " << QString::number(_keyId) << ". Skipping";
                continue;
            }

            container[_keyId] = _nameStr;
        }

        if (container.empty())
        {
            qCDebug(JSON) << "Failed to load data from " << fileName << " data. Related container is empty!";
            return false;
        }

        return true;
    });
}

// Reads json file
// returns 1 on failure
bool SpellWorkJson::OpenJson(const QString& fileName, std::function<bool(const QJsonDocument& json)> handle)
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

        if (handle(json))
        {
            qCDebug(JSON) << "Successfully loaded data from " << fileName << ".";
            return true;
        }
    }

    qCDebug(JSON) << "Failed to loaded data from " << fileName << ".";
    return false;
}

bool SpellWorkJson::LoadJsonData()
{
    QLoggingCategory::setFilterRules("spellwork.json.debug=true");

    if (!OpenJson("./json/SpellSchools.json", [&](const QJsonDocument& json)
    {
        if (!json.isObject())
        {
            qCDebug(JSON) << "Json file \"SpellSchools.json\" is not object type";
            return false;
        }

        const auto& document = json.object();
        const auto& schoolArrayObj = document.value("SpellSchool").toArray();
        for (const auto& objArray : std::as_const(schoolArrayObj))
        {
            const auto& schoolArray = objArray.toObject();
            const uint32_t _keyId = static_cast<uint32_t>(schoolArray.value("Id").toDouble());

            if (m_spellSchoolNames.contains(_keyId))
            {
                qCDebug(JSON) << "\"./json/SpellSchools.json\" has duplicate SpellSchool Id " << QString::number(_keyId) << ". Skipping";
                continue;
            }

            m_spellSchoolNames[_keyId] = schoolArray.value("Name").toString();
        }

        if (m_spellSchoolNames.empty())
        {
            qCDebug(JSON) << "Failed to load SpellSchools data!";
            return false;
        }

        const auto& schoolMaskArray = document.value("SpellSchoolMask").toArray();
        for (const auto& objArray : std::as_const(schoolMaskArray))
        {
            const auto& schoolArray = objArray.toObject();
            const uint32_t _keyId = static_cast<uint32_t>(schoolArray.value("Id").toDouble());

            if (m_spellSchoolMaskNames.contains(_keyId))
            {
                qCDebug(JSON) << "\"./json/SpellSchools.json\" has duplicate SpellSchoolMask Id " << QString::number(_keyId) << ". Skipping";
                continue;
            }

            m_spellSchoolMaskNames[_keyId] = schoolArray.value("Name").toString();
        }

        if (m_spellSchoolMaskNames.empty())
        {
            qCDebug(JSON) << "Failed to load SpellSchools mask data!";
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
            qCDebug(JSON) << "Json file \"SpellInterrupt.json\" is not Object type";
            return false;
        }

        const auto& document = json.object();
        {
            const auto& jsonArray = document.value("SpellInterruptFlags").toArray();
            for (const auto& spellInterruptFlag : std::as_const(jsonArray))
            {
                const auto& spellinterruptObj = spellInterruptFlag.toObject();
                const uint32_t _keyId = static_cast<uint32_t>(spellinterruptObj.value("Flag").toDouble());

                if (m_spellInterruptFlagNames.contains(_keyId))
                {
                    qCDebug(JSON) << "\"./json/SpellInterrupt.json\" has duplicate SpellInterruptFlags Id " << QString::number(_keyId) << ". Skipping";
                    continue;
                }

                m_spellInterruptFlagNames[_keyId] = spellinterruptObj.value("Name").toString();
            }

            if (m_spellInterruptFlagNames.empty())
            {
                qCDebug(JSON) << "Failed to load SpellInterruptFlags data!";
                return false;
            }
        }

        {
            auto& _AuraInterruptFlags = m_auraInterruptFlagNames[0];
            const auto& jsonArray = document.value("AuraInterruptFlags").toArray();
            for (const auto& auraInterruptFlag : std::as_const(jsonArray))
            {
                const auto& auraInterruptObj = auraInterruptFlag.toObject();
                const uint32_t _keyId = static_cast<uint32_t>(auraInterruptObj.value("Flag").toDouble());

                if (_AuraInterruptFlags.contains(_keyId))
                {
                    qCDebug(JSON) << "\"./json/SpellInterrupt.json\" has duplicate AuraInterruptFlags Id " << QString::number(_keyId) << ". Skipping";
                    continue;
                }

                _AuraInterruptFlags[_keyId] = auraInterruptObj.value("Name").toString();
            }

            if (_AuraInterruptFlags.empty())
            {
                qCDebug(JSON) << "Failed to load AuraInterruptFlags data!";
                return false;
            }
        }

        {
            auto& _AuraInterruptFlags = m_auraInterruptFlagNames[1];
            const auto& jsonArray = document.value("AuraInterruptFlags2").toArray();
            for (const auto& auraInterruptFlag : std::as_const(jsonArray))
            {
                const auto& auraInterruptObj = auraInterruptFlag.toObject();
                const uint32_t _keyId = static_cast<uint32_t>(auraInterruptObj.value("Flag").toDouble());

                if (_AuraInterruptFlags.contains(_keyId))
                {
                    qCDebug(JSON) << "\"./json/SpellInterrupt.json\" has duplicate AuraInterruptFlags2 Id " << QString::number(_keyId) << ". Skipping";
                    continue;
                }

                _AuraInterruptFlags[_keyId] = auraInterruptObj.value("Name").toString();
            }

            if (_AuraInterruptFlags.empty())
            {
                qCDebug(JSON) << "Failed to load AuraInterruptFlags2 data!";
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
            qCDebug(JSON) << "Json file \"SpellAttributes.json\" is not Object type";
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

                if (m_spellAttributeNames[i].contains(_keyId))
                {
                    qCDebug(JSON) << "\"./json/SpellAttributes.json\" has duplicate " << attributeName << " Flag " << QString::number(_keyId) << ". Skipping";
                    continue;
                }

                m_spellAttributeNames[i][attrObj.value("Flag").toInt()] = attrObj.value("Name").toString();
            }

            if (m_spellAttributeNames[i].empty())
            {
                qCDebug(JSON) << "Failed to load " << attributeName << " from SpellAttributes";
                return false;
            }
        }

        return true;
    }))
    {
        return false;
    }

    if (!OpenJson("./json/SpellTargets.json", [&](const QJsonDocument& json)
    {
        if (!json.isObject())
        {
            qCDebug(JSON) << "Json file \"Spelltargets.json\" is not Object type";
            return false;
        }

        const auto& jsonObj = json.object();
        // SpellTargetNames
        {
            const auto& attrArray = jsonObj.value("SpellTargetNames").toArray();
            for (const auto& attrData : std::as_const(attrArray))
            {
                const auto& attrObj = attrData.toObject();
                const uint32_t _keyId = attrObj.value("Id").toInt();

                if (m_spellTargetNames.contains(_keyId))
                {
                    qCDebug(JSON) << "\"./json/SpellTargets.json\" has duplicate SpellTargetNames entry " << QString::number(_keyId) << ". Skipping";
                    continue;
                }

                m_spellTargetNames[_keyId] = attrObj.value("Name").toString();
            }

            if (m_spellTargetNames.empty())
            {
                qCDebug(JSON) << "Failed to load SpellTargetNames from SpellTargets.json";
                return false;
            }
        }

        // SpellCastTargetFlags
        {
            const auto& attrArray = jsonObj.value("SpellCastTargetFlags").toArray();
            for (const auto& attrData : std::as_const(attrArray))
            {
                const auto& attrObj = attrData.toObject();
                const uint32_t _keyId = attrObj.value("Flag").toInt();

                if (m_SpellTargetFlagNames.contains(_keyId))
                {
                    qCDebug(JSON) << "\"./json/SpellTargets.json\" has duplicate SpellCastTargetFlags entry " << QString::number(_keyId) << ". Skipping";
                    continue;
                }

                m_SpellTargetFlagNames[_keyId] = attrObj.value("Name").toString();
            }

            if (m_SpellTargetFlagNames.empty())
            {
                qCDebug(JSON) << "Failed to load SpellTargetFlags from SpellTargets.json";
                return false;
            }
        }

        return true;
      }))
    {
        return false;
    }

    if (!OpenJson("./json/ItemSubclass.json", [&](const QJsonDocument& json)
    {
        if (!json.isObject())
        {
            qCDebug(JSON) << "Json file \"ItemSubclass.json\" is not Object type";
            return false;
        }

        const auto& jsonObj = json.object();
        // ItemSubclassWeapon
        {
            const auto& attrArray = jsonObj.value("ItemSubclassWeapon").toArray();
            for (const auto& attrData : std::as_const(attrArray))
            {
                const auto& attrObj = attrData.toObject();
                const uint32_t _keyId = attrObj.value("Id").toInt();

                if (m_itemSubClassWeaponNames.contains(_keyId))
                {
                    qCDebug(JSON) << "\"./json/ItemSubclass.json\" has duplicate ItemSubclassWeapon entry " << QString::number(_keyId) << ". Skipping";
                    continue;
                }

                m_itemSubClassWeaponNames[_keyId] = attrObj.value("Name").toString();
            }

            if (m_itemSubClassWeaponNames.empty())
            {
                qCDebug(JSON) << "Failed to load ItemSubclassWeapon entries from Itemsubclass.json";
                return false;
            }
        }

        // ItemSubclassArmor
        {
            const auto& attrArray = jsonObj.value("ItemSubclassArmor").toArray();
            for (const auto& attrData : std::as_const(attrArray))
            {
                const auto& attrObj = attrData.toObject();
                const uint32_t _keyId = attrObj.value("Id").toInt();

                if (m_itemSubclassArmorNames.contains(_keyId))
                {
                    qCDebug(JSON) << "\"./json/ItemSubclass.json\" has duplicate ItemSubclassArmor entry " << QString::number(_keyId) << ". Skipping";
                    continue;
                }

                m_itemSubclassArmorNames[_keyId] = attrObj.value("Name").toString();
            }

            if (m_itemSubclassArmorNames.empty())
            {
                qCDebug(JSON) << "Failed to load ItemSubclassArmor entries from Itemsubclass.json";
                return false;
            }
        }

        // ItemSubclassJunk
        {
            const auto& attrArray = jsonObj.value("ItemSubclassJunk").toArray();
            for (const auto& attrData : std::as_const(attrArray))
            {
                const auto& attrObj = attrData.toObject();
                const uint32_t _keyId = attrObj.value("Id").toInt();

                if (m_itemSubclassJunkNames.contains(_keyId))
                {
                    qCDebug(JSON) << "\"./json/ItemSubclass.json\" has duplicate ItemSubclassJunk entry " << QString::number(_keyId) << ". Skipping";
                    continue;
                }

                m_itemSubclassJunkNames[_keyId] = attrObj.value("Name").toString();
            }

            if (m_itemSubclassJunkNames.empty())
            {
                qCDebug(JSON) << "Failed to load ItemSubclassJunk entries from Itemsubclass.json";
                return false;
            }
        }
        return true;
    }))
    {
        return false;
    }

    if (!OpenJson("./json/SpellEffects.json", [&](const QJsonDocument& json)
    {
        if (!json.isArray())
        {
            qCDebug(JSON) << "Json file \"SpellEffects.json\" is not Array type";
            return false;
        }

        const auto& jsonArray = json.array();
        for (const auto& attrData : std::as_const(jsonArray))
        {
            const auto& arrayData = attrData.toObject();
            const uint32_t _keyId = arrayData.value("Id").toInt();

            if (m_spellEffectInfo.contains(_keyId))
            {
                qCDebug(JSON) << "\"./json/SpellEffects.json\" has duplicate entry " << QString::number(_keyId) << ". Skipping";
                continue;
            }

            auto& effectInfo = m_spellEffectInfo[_keyId];
            effectInfo.name                 = arrayData.value("Name").toString();
            if (!arrayData.value("EffectDetail").isNull())
            {
                effectInfo.extraDetailFormatStr         = arrayData.value("EffectDetail").toString();
            }
        }

        if (m_spellEffectInfo.empty())
        {
            qCDebug(JSON) << "Failed to load entries from SpellEffects.json";
            return false;
        }

        return true;
    }))
    {
        return false;
    }

    if (!OpenJson("./json/SpellAuraTypes.json", [&](const QJsonDocument& json)
    {
        if (!json.isArray())
        {
            qCDebug(JSON) << "Json file \"SpellAuraTypes.json\" is not Array type";
            return false;
        }

        const auto& jsonArray = json.array();
        for (const auto& attrData : std::as_const(jsonArray))
        {
            const auto& arrayData = attrData.toObject();
            const uint32_t _keyId = arrayData.value("Id").toInt();

            if (m_spellAuraTypeNames.contains(_keyId))
            {
                qCDebug(JSON) << "\"./json/SpellAuraTypes.json\" has duplicate entry " << QString::number(_keyId) << ". Skipping";
                continue;
            }

            auto& effectInfo    = m_spellAuraTypeNames[_keyId];
            effectInfo.name     = arrayData.value("Name").toString();
            if (!arrayData.value("EffectDetail").isNull())
            {
                effectInfo.extraDetailFormatStr         = arrayData.value("EffectDetail").toString();
            }
        }

        if (m_spellAuraTypeNames.empty())
        {
            qCDebug(JSON) << "Failed to load entries from SpellAuraTypes.json";
            return false;
        }

        return true;
    }))
    {
        return false;
    }

    if (!OpenJson("./json/SummonProperties.json", [&](const QJsonDocument& json)
    {
        if (!json.isObject())
        {
            qCDebug(JSON) << "Json file \"SummonProperties.json\" is not Object type";
            return false;
        }

        const auto& jsonObj = json.object();
        // SummonCategory
        {
            const auto& categoryArray = jsonObj.value("SummonCategory").toArray();
            for (const auto& category : std::as_const(categoryArray))
            {
                const auto& categoryObj = category.toObject();
                const uint32_t _keyId = categoryObj.value("Id").toInt();

                if (m_SummonPropCategoryNames.contains(_keyId))
                {
                    qCDebug(JSON) << "\"./json/SummonProperties.json\" has duplicate SummonCategory entry " << QString::number(_keyId) << ". Skipping";
                    continue;
                }

                m_SummonPropCategoryNames[_keyId] = categoryObj.value("Name").toString();
            }

            if (m_SummonPropCategoryNames.empty())
            {
                qCDebug(JSON) << "Failed to load SummonCategory entries from SummonProperties.json";
                return false;
            }
        }

        // SummonTypeName
        {
            const auto& summTitleArray = jsonObj.value("SummonTypeName").toArray();
            for (const auto& summTitle : std::as_const(summTitleArray))
            {
                const auto& summTitleObj = summTitle.toObject();
                const uint32_t _keyId = summTitleObj.value("Id").toInt();

                if (m_SummonPropSummTypeNames.contains(_keyId))
                {
                    qCDebug(JSON) << "\"./json/SummonProperties.json\" has duplicate SummonTypeName entry " << QString::number(_keyId) << ". Skipping";
                    continue;
                }

                m_SummonPropSummTypeNames[_keyId] = summTitleObj.value("Name").toString();
            }

            if (m_SummonPropSummTypeNames.empty())
            {
                qCDebug(JSON) << "Failed to load SummonTypeName entries from SummonProperties.json";
                return false;
            }
        }

        // SummonFlags
        {
            const auto& summFlagsArray = jsonObj.value("SummonFlags").toArray();
            for (const auto& summFlag : std::as_const(summFlagsArray))
            {
                const auto& summFlagObj = summFlag.toObject();
                const uint32_t _keyId = summFlagObj.value("Flag").toInt();

                if (m_SummonPropSummFlagNames.contains(_keyId))
                {
                    qCDebug(JSON) << "\"./json/SummonProperties.json\" has duplicate SummonFlags entry " << QString::number(_keyId) << ". Skipping";
                    continue;
                }

                m_SummonPropSummFlagNames[_keyId] = summFlagObj.value("Name").toString();
            }

            if (m_SummonPropSummFlagNames.empty())
            {
                qCDebug(JSON) << "Failed to load SummonFlags entries from SummonProperties.json";
                return false;
            }
        }

        // TypeNameIdOverwrite
        {
            const auto& propExtraArray = jsonObj.value("TypeNameIdOverwrite").toArray();
            for (const auto& propExtra : std::as_const(propExtraArray))
            {
                const auto& propExtraObj = propExtra.toObject();
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

        return true;
    }))
    {
        return false;
    }

    if (!ReadBasicArrayFromFile("./json/SpellMod.json", m_spellModOpNames) ||
        !ReadBasicArrayFromFile("./json/SpellProc.json", m_spellProcFlagNames, "Flag") ||
        !ReadBasicArrayFromFile("./json/SpellFamily.json", m_spellFamilyNames) ||
        !ReadBasicArrayFromFile("./json/CombatRating.json", m_combatRatingNames) ||
        !ReadBasicArrayFromFile("./json/UnitMods.json", m_unitModsNames) ||
        !ReadBasicArrayFromFile("./json/SpellAuraStates.json", m_spellAuraStatesNames) ||
        !ReadBasicArrayFromFile("./json/PowerTypes.json", m_powerTypeNames) ||
        !ReadBasicArrayFromFile("./json/SpellMechanics.json", m_spellMechanicNames) ||
        !ReadBasicArrayFromFile("./json/SpellDispelTypes.json", m_dispelNames) ||
        !ReadBasicArrayFromFile("./json/ItemInventoryTypes.json", m_itemInventoryNames) ||
        !ReadBasicArrayFromFile("./json/ItemClass.json", m_itemClassNames) ||
        !ReadBasicArrayFromFile("./json/ShapeShiftForms.json", m_shapeshiftFormNames) ||
        !ReadBasicArrayFromFile("./json/CreatureTypes.json", m_creatureTypeNames) ||
        !ReadBasicArrayFromFile("./json/SpellDamageTypes.json", m_spellDamageTypeNames) ||
        !ReadBasicArrayFromFile("./json/SpellPreventionTypes.json", m_spellPreventionTypeNames)
    )
    {
        return false;
    }

    return true;
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
