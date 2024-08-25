#include "JsonData.hpp"
#include <QJsonArray>
#include <QFile>
#include <QDebug>
#include <QJsonObject>

Q_LOGGING_CATEGORY(JSON, "spellwork.json");

template<class T>
inline bool ReadBasicArrayFromFile(const QString& fileName, T& container, const QString& keyName = "Id", const QString& nameValName = "Name")
{
    return SpellWorkJson::OpenJson(fileName, [&](const QJsonDocument& json)
    {
        if (!json.isArray())
        {
            qCDebug(JSON) << "JSON: Json file \"" << fileName << "\" is not array type";
            return false;
        }

        const auto& jsonArray = json.array();
        for (const auto& jsonArrayItem : std::as_const(jsonArray))
        {
            const auto& arrayObj = jsonArrayItem.toObject();

            using keyType = T::key_type;
            const keyType _keyId = static_cast<keyType>(arrayObj.value(keyName).toDouble());
            const QString _nameStr = arrayObj.value(nameValName).toString();

            if (container.contains(_keyId))
            {
                qCDebug(JSON) << "JSON: \"" << fileName << "\" has duplicate Id " << QString::number(_keyId) << ". Skipping";
                continue;
            }

            container[_keyId] = _nameStr;
        }

        if (container.empty())
        {
            qCDebug(JSON) << "JSON: Failed to load data from " << fileName << " data. Related container is empty!";
            return false;
        }

        return true;
    });
}

// Reads json file
// returns 1 on failure
bool SpellWorkJson::OpenJson(const QString& fileName, std::function<bool(const QJsonDocument& json)> handle)
{
    qCDebug(JSON) << "JSON: Loading: " << fileName;

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

bool SpellWorkJson::LoadJsonData()
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
            qCDebug(JSON) << "JSON: Json file \"SpellAttributes.json\" is not Object type";
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

    if (!OpenJson("./json/SpellTargets.json", [&](const QJsonDocument& json)
    {
        if (!json.isObject())
        {
            qCDebug(JSON) << "JSON: Json file \"Spelltargets.json\" is not Object type";
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

                if (SpellTargetNames.contains(_keyId))
                {
                    qCDebug(JSON) << "JSON: \"./json/SpellTargets.json\" has duplicate SpellTargetNames entry " << QString::number(_keyId) << ". Skipping";
                    continue;
                }

                SpellTargetNames[_keyId] = attrObj.value("Name").toString();
            }

            if (SpellTargetNames.empty())
            {
                qCDebug(JSON) << "JSON: Failed to load SpellTargetNames from SpellTargets.json";
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

                if (SpellTargetFlags.contains(_keyId))
                {
                    qCDebug(JSON) << "JSON: \"./json/SpellTargets.json\" has duplicate SpellCastTargetFlags entry " << QString::number(_keyId) << ". Skipping";
                    continue;
                }

                SpellTargetFlags[_keyId] = attrObj.value("Name").toString();
            }

            if (SpellTargetFlags.empty())
            {
                qCDebug(JSON) << "JSON: Failed to load SpellTargetFlags from SpellTargets.json";
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
            qCDebug(JSON) << "JSON: Json file \"ItemSubclass.json\" is not Object type";
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

                if (ItemSubclassWeapon.contains(_keyId))
                {
                    qCDebug(JSON) << "JSON: \"./json/ItemSubclass.json\" has duplicate ItemSubclassWeapon entry " << QString::number(_keyId) << ". Skipping";
                    continue;
                }

                ItemSubclassWeapon[_keyId] = attrObj.value("Name").toString();
            }

            if (ItemSubclassWeapon.empty())
            {
                qCDebug(JSON) << "JSON: Failed to load ItemSubclassWeapon entries from Itemsubclass.json";
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

                if (ItemSubclassArmor.contains(_keyId))
                {
                    qCDebug(JSON) << "JSON: \"./json/ItemSubclass.json\" has duplicate ItemSubclassArmor entry " << QString::number(_keyId) << ". Skipping";
                    continue;
                }

                ItemSubclassArmor[_keyId] = attrObj.value("Name").toString();
            }

            if (ItemSubclassArmor.empty())
            {
                qCDebug(JSON) << "JSON: Failed to load ItemSubclassArmor entries from Itemsubclass.json";
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

                if (ItemSubclassJunk.contains(_keyId))
                {
                    qCDebug(JSON) << "JSON: \"./json/ItemSubclass.json\" has duplicate ItemSubclassJunk entry " << QString::number(_keyId) << ". Skipping";
                    continue;
                }

                ItemSubclassJunk[_keyId] = attrObj.value("Name").toString();
            }

            if (ItemSubclassJunk.empty())
            {
                qCDebug(JSON) << "JSON: Failed to load ItemSubclassJunk entries from Itemsubclass.json";
                return false;
            }
        }
        return true;
    }))
    {
        return false;
    }

    if (!ReadBasicArrayFromFile("./json/SpellMod.json", SpellModOps) ||
        !ReadBasicArrayFromFile("./json/SpellAuraTypes.json", SpellAuraTypes) ||
        !ReadBasicArrayFromFile("./json/SpellProc.json", SpellProcInfo, "Flag") ||
        !ReadBasicArrayFromFile("./json/SpellFamily.json", SpellFamilyInfo) ||
        !ReadBasicArrayFromFile("./json/SpellEffects.json", SpellEffectNames) ||
        !ReadBasicArrayFromFile("./json/CombatRating.json", CombatRatingNames) ||
        !ReadBasicArrayFromFile("./json/UnitMods.json", UnitModsNames) ||
        !ReadBasicArrayFromFile("./json/SpellAuraStates.json", SpellAuraStatesNames) ||
        !ReadBasicArrayFromFile("./json/PowerTypes.json", PowerTypeNames) ||
        !ReadBasicArrayFromFile("./json/SpellMechanics.json", SpellMechanicNames) ||
        !ReadBasicArrayFromFile("./json/SpellDispelTypes.json", DispelNames) ||
        !ReadBasicArrayFromFile("./json/ItemInventoryTypes.json", ItemInventoryNames) ||
        !ReadBasicArrayFromFile("./json/ItemClass.json", ItemClassNames) ||
        !ReadBasicArrayFromFile("./json/ShapeShiftForms.json", ShapeshiftForms) ||
        !ReadBasicArrayFromFile("./json/CreatureTypes.json", CreatureTypeNames) ||
        !ReadBasicArrayFromFile("./json/SpellDamageTypes.json", SpellDamageTypeNames) ||
        !ReadBasicArrayFromFile("./json/SpellPreventionTypes.json", SpellPreventionTypeNames)
    )
    {
        return false;
    }

    return true;
}

QStringView SpellWorkJson::GetSpellSchoolName(uint32_t id)
{
    const auto& itr = SpellSchools.find(id);
    return itr != SpellSchools.end() ? itr->second : QString("SPELL_SCHOOL_UNK_%1").arg(id);
}

QStringView SpellWorkJson::GetSpellSchoolMaskName(uint32_t flag)
{
    const auto& itr = SpellSchoolMasks.find(flag);
    return itr != SpellSchoolMasks.end() ? itr->second : QString("SPELL_SCHOOL_MASK_UNK_%1").arg(flag);
}

QStringView SpellWorkJson::GetSpellModName(uint32_t id)
{
    const auto& itr = SpellModOps.find(id);
    return itr != SpellModOps.end() ? itr->second : QString("SPELL_MOD_UNK_%1").arg(id);
}

QStringView SpellWorkJson::GetSpellInterruptFlagName(uint32_t flag)
{
    const auto& itr = SpellInterruptFlags.find(flag);
    return itr != SpellInterruptFlags.end() ? itr->second : QString("SPELL_INTERRUPT_FLAG_UNK_0x%1").arg(flag, 8, 16, QLatin1Char('0'));
}

QStringView SpellWorkJson::GetAuraInterruptFlagName(uint32_t flag)
{
    const auto& itr = AuraInterruptFlags.find(flag);
    return itr != AuraInterruptFlags.end() ? itr->second : QString("AURA_INTERRUPT_FLAG_UNK_%1").arg(flag, 8, 16, QLatin1Char('0'));
}

QStringView SpellWorkJson::GetSpellAuraTypeName(uint32_t id)
{
    const auto& itr = SpellAuraTypes.find(id);
    return itr != SpellAuraTypes.end() ? itr->second : QString("SPELL_AURA_UNK_%1").arg(id);
}

QStringView SpellWorkJson::GetSpellProcDescription(uint32_t id)
{
    const auto& itr = SpellProcInfo.find(id);
    return itr != SpellProcInfo.end() ? itr->second : "-- no description --";
}

QStringView SpellWorkJson::GetSpellFamilyName(uint32_t id)
{
    const auto& itr = SpellFamilyInfo.find(id);
    return itr != SpellFamilyInfo.end() ? itr->second : QString("SPELLFAMILY_UNK_%1").arg(id);
}

QStringView SpellWorkJson::GetSpellAttributeName(uint32_t attributeId, uint32_t attributeFlag)
{
    const auto nullResult = QString("SPELL_ATTR%1_UNK_%2").arg(attributeId).arg(attributeFlag);
    if (attributeId >= MAX_SPELL_ATTRIBUTES)
    {
        return nullResult;
    }

    const auto& itr = SpellAttributes[attributeId].find(attributeFlag);
    return itr != SpellFamilyInfo.end() ? itr->second : nullResult;
}

QStringView SpellWorkJson::GetSpellEffectName(uint32_t id)
{
    const auto& itr = SpellEffectNames.find(id);
    return itr != SpellEffectNames.end() ? itr->second : QString("SPELL_EFFECT_UNK_%1").arg(id);
}

QStringView SpellWorkJson::GetSpellTargetName(uint32_t id)
{
    const auto& itr = SpellTargetNames.find(id);
    return itr != SpellTargetNames.end() ? itr->second : QString("TARGET_UNK_%1").arg(id);
}

QStringView SpellWorkJson::GetSpellTargetFlagName(uint32_t flag)
{
    const auto& itr =  SpellTargetFlags.find(flag);
    return itr != SpellTargetFlags.end() ? itr->second : QString("TARGET_FLAG_UNK_%1").arg(flag);
}

QStringView SpellWorkJson::GetCombatRatingName(uint32_t id)
{
    const auto& itr = CombatRatingNames.find(id);
    return itr != CombatRatingNames.end() ? itr->second : QString("CR_UNK_%1").arg(id);
}

QStringView SpellWorkJson::GetUnitModName(uint32_t id)
{
    const auto& itr = UnitModsNames.find(id);
    return itr != UnitModsNames.end() ? itr->second : QString("UNIT_MOD_UNK_%1").arg(id);
}

QStringView SpellWorkJson::GetSpellAuraStateName(uint32_t id)
{
    const auto& itr = SpellAuraStatesNames.find(id);
    return itr != SpellAuraStatesNames.end() ? itr->second : QString("AURA_STATE_UNK_%1").arg(id);
}

QStringView SpellWorkJson::GetPowerTypeName(int32_t id)
{
    const auto& itr = PowerTypeNames.find(id);
    return itr != PowerTypeNames.end() ? itr->second : QString("POWER_UNK_%1").arg(id);
}

QStringView SpellWorkJson::GetSpellMechanicName(uint32_t id)
{
    const auto& itr = SpellMechanicNames.find(id);
    return itr != SpellMechanicNames.end() ? itr->second : QString("MECHANIC_UNK_%1").arg(id);
}

QStringView SpellWorkJson::GetDispelName(uint32_t id)
{
    const auto& itr = DispelNames.find(id);
    return itr != DispelNames.end() ? itr->second : QString("DISPEL_UNK_%1").arg(id);
}

QStringView SpellWorkJson::GetItemInventoryName(uint32_t id)
{
    const auto& itr = ItemInventoryNames.find(id);
    return itr != ItemInventoryNames.end() ? itr->second : QString("INVTYPE_UNK_%1").arg(id);
}

QStringView SpellWorkJson::GetItemSubclassWeaponName(uint32_t id)
{
    const auto& itr = ItemSubclassWeapon.find(id);
    return itr != ItemSubclassWeapon.end() ? itr->second : QString("ITEM_SUBCLASS_WEAPON_UNK_%1").arg(id);
}

QStringView SpellWorkJson::GetItemSubclassArmorName(uint32_t id)
{
    const auto& itr = ItemSubclassArmor.find(id);
    return itr != ItemSubclassArmor.end() ? itr->second : QString("ITEM_SUBCLASS_ARMOR_UNK_%1").arg(id);
}

QStringView SpellWorkJson::GetItemSubclassJunkName(uint32_t id)
{
    const auto& itr = ItemSubclassJunk.find(id);
    return itr != ItemSubclassJunk.end() ? itr->second : QString("ITEM_SUBCLASS_JUNK_UNK_%1").arg(id);
}

QStringView SpellWorkJson::GetItemClassName(uint32_t id)
{
    const auto& itr = ItemClassNames.find(id);
    return itr != ItemClassNames.end() ? itr->second : QString("ITEM_CLASS_UNK_%1").arg(id);
}

QStringView SpellWorkJson::GetShapeshiftFormName(uint32_t id)
{
    const auto& itr = ShapeshiftForms.find(id);
    return itr != ShapeshiftForms.end() ? itr->second : QString("FORM_UNK_%1").arg(id);
}

QStringView SpellWorkJson::GetCreatureTypeName(uint32_t id)
{
    const auto& itr = CreatureTypeNames.find(id);
    return itr != CreatureTypeNames.end() ? itr->second : QString("CREATURE_TYPE_UNK_%1").arg(id);
}

QStringView SpellWorkJson::GetSpellDamageTypeName(uint32_t id)
{
    const auto& itr = SpellDamageTypeNames.find(id);
    return itr != SpellDamageTypeNames.end() ? itr->second : QString("SPELL_DAMAGE_CLASS_UNK_%1").arg(id);
}

QStringView SpellWorkJson::GetSpellPreventionTypeName(uint32_t id)
{
    const auto& itr = SpellPreventionTypeNames.find(id);
    return itr != SpellPreventionTypeNames.end() ? itr->second : QString("SPELL_PREVENTION_TYPE_UNK_%1").arg(id);
}
