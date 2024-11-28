#include "DBCStructures.hpp"
#include "DataStorage.hpp"
#include "ItemDefines.hpp"
#include "JsonData/JsonData.hpp"
#include "SharedDefines.hpp"

constexpr char const* line = "==============================================<br>";

// Returns first found school mask's name
inline QString GetFirstSchoolMaskNameStr(uint32_t mask)
{
    QString result;
    for (uint8_t i = 0; i < MAX_UINT32_BITMASK_INDEX; ++i)
    {
        const uint32_t schoolMask = (1U << i);
        if ((mask & schoolMask) != 0)
        {
            result += sSpellWorkJson->GetSpellSchoolMaskName(schoolMask);
        }
    }

    return result;
}

inline QString GetStancesNames(uint32_t stancesNames)
{
    QString formNames;
    for (uint8_t i = 0; i <= MAX_UINT32_BITMASK_INDEX; ++i)
    {
        if (((1U << i) & stancesNames) == 0)
        {
            continue;
        }

        if (!formNames.isEmpty())
        {
            formNames += ", ";
        }

        formNames += sSpellWorkJson->GetShapeshiftFormName(i);
    }

    return formNames;
}

inline void PrintSpellClassOptions(QString& result, uint32_t classOptionsEntry)
{
    if (const auto* spellClassOptions = sDataStorage->GetSpellClassOptionsEntry(classOptionsEntry))
    {
        result += QString("Modal Next Spell: %1<br>").arg(spellClassOptions->modalNextSpell);
        result += QString("FamilyName %1 (%2), flat [0] 0x%3 [1] 0x%4 [2] 0x%5<br>")
                         .arg(spellClassOptions->SpellFamilyName)
                         .arg(sSpellWorkJson->GetSpellFamilyName(spellClassOptions->SpellFamilyName))
                         .arg(spellClassOptions->SpellFamilyFlags[0], 8, 16, QLatin1Char('0'))
                         .arg(spellClassOptions->SpellFamilyFlags[1], 8, 16, QLatin1Char('0'))
                         .arg(spellClassOptions->SpellFamilyFlags[2], 8, 16, QLatin1Char('0'));
    }
    else
    {
        result += QString("Modal Next Spell: 0<br>");
        result += QString("Family 0 %1, flag [0] 0x00000000 [1] 0x00000000 [2] 0x00000000<br>").arg(sSpellWorkJson->GetSpellFamilyName(SPELLFAMILY_GENERIC));
    }
}

inline void PrintSpellCategory(QString& result, uint32_t category_id)
{
    if (const auto* spellCategory = sDataStorage->GetSpellCategoriesEntry(category_id))
    {
        // Damage/defense type
        result += QString("DamageClass = %1 (%2)<br>")
                      .arg(spellCategory->DefenseType)
                      .arg(sSpellWorkJson->GetSpellDamageTypeName(spellCategory->DefenseType));

        // Prevention type
        result += QString("PreventionType = %1 (%2)<br>")
                      .arg(spellCategory->PreventionType)
                      .arg(sSpellWorkJson->GetSpellPreventionTypeName(spellCategory->PreventionType));

        // Category
        result += QString("Category id = %1").arg(category_id);
        if (const auto* spellCategoryInfo = sDataStorage->GetSpellCategoryEntry(spellCategory->Id))
        {
            result += QString(" (%1)").arg(spellCategoryInfo->GetName());
        }

        result += "<br>";

        // Dispel info
        result += QString("DispelType = %1 (%2)<br>")
                      .arg(spellCategory->DispelType)
                      .arg(sSpellWorkJson->GetDispelName(spellCategory->DispelType));

        // Mechanic
        result += QString("Mechanic = %1 (%2)<br>")
                      .arg(spellCategory->Mechanic)
                      .arg(sSpellWorkJson->GetSpellMechanicName(spellCategory->Mechanic));
    }
    else
    {
        result += QString("DamageClass = 0 (%1)<br>").arg(sSpellWorkJson->GetSpellDamageTypeName(SPELL_DAMAGE_CLASS_NONE));
        result += QString("PreventionType = 0 (%1)<br>").arg(sSpellWorkJson->GetSpellPreventionTypeName(SPELL_PREVENTION_TYPE_NONE));
        result += QString("Category id = %1<br>").arg(category_id);
        result += QString("DispelType = 0 (%1)<br>").arg(sSpellWorkJson->GetDispelName(DISPEL_NONE));
        result += QString("Mechanic = 0 (%1)<br>").arg(sSpellWorkJson->GetSpellMechanicName(MECHANIC_NONE));
    }
}

inline void PrintAttributes(QString& result, const std::vector<uint32_t>& attributes)
{
    if (attributes.empty() || !std::any_of(attributes.begin(), attributes.end(), [](uint32_t attr){ return attr != 0; }))
    {
        return;
    }

    result += line;
    for (uint8_t attribute = 0; attribute < MAX_SPELL_ATTRIBUTES; ++attribute)
    {
        const auto& attributeMask = attributes[attribute];
        if (attributeMask == 0)
        {
            continue;
        }

        QString attributeStr;
        for (uint8_t id = 0; id <= MAX_UINT32_BITMASK_INDEX; ++id)
        {
            const uint32_t mask = 1u << id;
            if ((mask & attributeMask) == 0)
            {
                continue;
            }

            if (!attributeStr.isEmpty())
            {
                attributeStr += ", ";
            }

            attributeStr += sSpellWorkJson->GetSpellAttributeName(attribute, mask);
        }

        result += QString("Attributes%1: %2<br><br>")
                      .arg(attribute)
                      .arg(attributeStr);
    }
}

inline void PrintTargetRestrictions(QString& result, uint32_t SpellTargetRestrictionsId, uint32_t SpellLevelsId, bool isSingleTarget)
{
    const auto* spellRestrictionsEntry = sDataStorage->GetSpellTargetRestrictionsEntry(SpellTargetRestrictionsId);
    if (spellRestrictionsEntry != nullptr)
    {
        if (spellRestrictionsEntry->Targets != 0)
        {
            result += QString("Targets Mask = [0] 0x%1").arg(spellRestrictionsEntry->Targets, 8, 16, QLatin1Char('0')) + "(";

            QString targets;
            for (uint8_t i = 0; i <= MAX_UINT32_BITMASK_INDEX; ++i)
            {
                const uint32_t flag = 1U << i;
                if ((flag & spellRestrictionsEntry->Targets) != 0)
                {
                    if (!targets.isEmpty())
                    {
                        targets += ", ";
                    }

                    targets += sSpellWorkJson->GetSpellTargetFlagName(flag);
                }
            }
            result += targets + ")";
        }

        if (spellRestrictionsEntry->TargetCreatureType != 0)
        {
            result += QString("Creature Type Mask = 0x%1 (%2)")
                          .arg(spellRestrictionsEntry->TargetCreatureType, 8, 16, QLatin1Char('0'))
                          .arg(sSpellWorkJson->GetCreatureTypeName(spellRestrictionsEntry->TargetCreatureType));
        }

        uint32_t targetCount = spellRestrictionsEntry->MaxAffectedTargets;
        if (isSingleTarget)
        {
            targetCount = 1;
        }

        result += "<br>";
        result += QString("MaxAffectedTargets = %1<br>").arg(targetCount);
        if (spellRestrictionsEntry->ConeAngle > 0.0f)
        {
            result += QString("Effected cone angle: %1<br>").arg(spellRestrictionsEntry->ConeAngle);
        }
    }

    if (const auto* spellLevel = sDataStorage->GetSpellLevelsEntry(SpellLevelsId))
    {
        result += QString("Spell level = %1, base %2, max %3, maxTarget level %4<br>")
                      .arg(spellLevel->spellLevel)
                      .arg(spellLevel->baseLevel)
                      .arg(spellLevel->maxLevel)
                      .arg(spellRestrictionsEntry != nullptr ? spellRestrictionsEntry->MaxTargetLevel : 0);
    }
}

inline void PrintShapeShiftingInfo(QString& result, uint32_t SpellShapeshiftId)
{
    const auto* shapeshiftingEntry = sDataStorage->GetSpellShapeshiftEntry(SpellShapeshiftId);
    if (shapeshiftingEntry == nullptr)
    {
        return;
    }

    auto printList = [&](const std::list<uint32_t>& list, const QString& stancesTypeStr)
    {
        if (list.empty())
        {
            return;
        }

        QString stanceResult;
        for (auto const stanceId : list)
        {
            if (!stanceResult.isEmpty())
            {
                result += ", ";
            }

            stanceResult += QString::number(stanceId);
        }

        result += stancesTypeStr + stanceResult;
        result += "<br>";
    };

    std::list<uint32_t> stances = { shapeshiftingEntry->ShapeshiftMask.begin(), shapeshiftingEntry->ShapeshiftMask.end() };
    stances.remove(0);
    printList(stances, "Allowed stances: ");
    stances.clear();

    stances = { shapeshiftingEntry->ShapeshiftExclude.begin(), shapeshiftingEntry->ShapeshiftExclude.end() };
    stances.remove(0);
    printList(stances, "Excluded stances: ");
}

inline void PrintSkillLinks(QString& result, uint32_t spellId)
{
    SkillLineEntry const* skillLine = nullptr;
    SkillLineAbilityEntry const* skillLineAbility = nullptr;
    const auto& skillLineAbilities = sDataStorage->GetSkillLineAbilityEntries();
    for (const auto& itr : sDataStorage->GetSkillLineEntries())
    {
        const auto _skillId = itr.first;
        const auto& _skillLineData = itr.second;

        const auto& itr2 = std::find_if(skillLineAbilities.begin(), skillLineAbilities.end(), [_skillId, spellId](const auto _skillLineAbility)
        {
            auto const& abilityData = _skillLineAbility.second;
            return _skillId == abilityData.SkillLine && abilityData.Spell == spellId;
        });

        if (itr2 != skillLineAbilities.end())
        {
            skillLine = &_skillLineData;
            skillLineAbility = &itr2->second;
            break;
        }
    }

    if (skillLine != nullptr && skillLineAbility != nullptr)
    {
        result += QString("Skill (Id %1) \"%2\"<br>").arg(skillLineAbility->SkillLine).arg(skillLine->GetName());
        result += QString("    MinSkillLineRank %1<br>").arg(skillLineAbility->MinSkillLineRank);

        result += QString(", SupercedesSpell = %1, MinMaxValue (%2, %3)<br>")
                      .arg(skillLineAbility->MinSkillLineRank)
                      .arg(skillLineAbility->TrivialSkillLineRankLow)
                      .arg(skillLineAbility->TrivialSkillLineRankHigh);

        result += QString(", NumSkillups (%1)<br>")
                      .arg(skillLineAbility->NumSkillUps);

        result += line;
    }
}

inline void PrintReagents(QString& result, uint32_t SpellReagentsId)
{
    const auto* spellReagent = sDataStorage->GetSpellReagentsEntry(SpellReagentsId);
    if (spellReagent == nullptr || !std::any_of(spellReagent->Reagent.begin(), spellReagent->Reagent.end(), [](int32_t reagent){ return reagent != 0; }))
    {
        return;
    }

    result += "Reagents:<br>";
    for (uint8_t i = 0; i < MAX_SPELL_REAGENTS; ++i)
    {
        if (spellReagent->Reagent[i] != 0)
        {
            result += QString(" reagentId %1, amount %2<br>").arg(spellReagent->Reagent[i]).arg(spellReagent->ReagentCount[i]);
        }
    }

    result += line;
}

inline void PrintSpellEquipmentInfo(QString& result, uint32_t SpellEquippedItemsId)
{
    const auto* spellEquipedItems = sDataStorage->GetSpellEquippedItemsEntry(SpellEquippedItemsId);
    if (spellEquipedItems == nullptr)
    {
        return;
    }

    result += QString("EquippedItemClass = %1 (%2)<br>")
              .arg(spellEquipedItems->EquippedItemClass)
              .arg(sSpellWorkJson->GetItemClassName(spellEquipedItems->EquippedItemClass));

    if (spellEquipedItems->EquippedItemSubClassMask != 0)
    {
        switch (spellEquipedItems->EquippedItemClass)
        {
        case ITEM_CLASS_WEAPON:
        {
            QString subclassNames;
            for (uint8_t i = 0; i <= MAX_UINT32_BITMASK_INDEX; ++i)
            {
                if ((spellEquipedItems->EquippedItemClass & (1U << i)) == 0)
                {
                    continue;
                }

                if (!subclassNames.isEmpty())
                {
                    subclassNames += ", ";
                }

                subclassNames += sSpellWorkJson->GetItemSubclassWeaponName(i);
            }

            if (!subclassNames.isEmpty())
            {
                result += QString("SubClass mask 0x%1 (%2)<br>").arg(spellEquipedItems->EquippedItemSubClassMask, 8, 16, QLatin1Char('0')).arg(subclassNames);
            }
            break;
        }
        case ITEM_CLASS_ARMOR:
        {
            QString subclassNames;
            for (uint8_t i = 0; i <= MAX_UINT32_BITMASK_INDEX; ++i)
            {
                if ((spellEquipedItems->EquippedItemSubClassMask & (1U << i)) == 0)
                {
                    continue;
                }

                if (!subclassNames.isEmpty())
                {
                    subclassNames += ", ";
                }

                subclassNames += sSpellWorkJson->GetItemSubclassArmorName(i);
            }

            if (!subclassNames.isEmpty())
            {
                result += QString("    SubClass mask 0x%1 (%2)<br>").arg(spellEquipedItems->EquippedItemSubClassMask, 8, 16, QLatin1Char('0')).arg(subclassNames);
            }
            break;
        }
        case ITEM_CLASS_MISCELLANEOUS:
        {
            QString subclassNames;
            for (uint8_t i = 0; i <= MAX_UINT32_BITMASK_INDEX; ++i)
            {
                if ((spellEquipedItems->EquippedItemSubClassMask & (1U << i)) == 0)
                {
                    continue;
                }

                if (!subclassNames.isEmpty())
                {
                    subclassNames += ", ";
                }

                subclassNames += sSpellWorkJson->GetItemSubclassJunkName(i);
            }

            if (!subclassNames.isEmpty())
            {
                result += QString("    SubClass mask 0x%1 (%2)<br>").arg(spellEquipedItems->EquippedItemSubClassMask, 8, 16, QLatin1Char('0')).arg(subclassNames);
            }
            break;
        }
        }
    }

    if (spellEquipedItems->EquippedItemInventoryTypeMask != 0)
    {
        QString inventoryNames;
        for (uint8_t i = 0; i <= MAX_UINT32_BITMASK_INDEX; ++i)
        {
            if ((spellEquipedItems->EquippedItemInventoryTypeMask & (1U << i)) == 0)
            {
                continue;
            }

            if (!inventoryNames.isEmpty())
            {
                inventoryNames += ", ";
            }

            inventoryNames += sSpellWorkJson->GetItemInventoryName(i);
        }

        if (!inventoryNames.isEmpty())
        {
            result += QString("    InventoryType mask = 0x%1 (%2)<br>").arg(spellEquipedItems->EquippedItemInventoryTypeMask, 8, 16, QLatin1Char('0')).arg(inventoryNames);
        }
    }
}

inline void PrintSpellRangeInfo(QString& result, uint32_t rangeIndex)
{
    result += "<br>";
    if (const auto* spellRange = sDataStorage->GetSpellRangeEntry(rangeIndex))
    {
        result += QString("SpellRange: (Id %1) \"%2\"<br>").arg(spellRange->Id).arg(spellRange->GetName());
        result += QString("MinRangeNegative = %1, MinRangePositive %2<br>").arg(spellRange->minRangeHostile).arg(spellRange->minRangeFriend);
        result += QString("MaxRangeNegative = %1, MaxRangePositive = %2<br>").arg(spellRange->maxRangeHostile).arg(spellRange->maxRangeFriend);
    }
    else
    {
        result += "SpellRange: (Id 0) \"None\"<br>";
        result += "MinRangeNegative = 0, MinRangePositive = 0<br>";
        result += "MaxRangeNegative = 0, MaxRangePositive = 0<br>";
    }
}

inline void PrintSpellAuraOptions(QString& result, uint32_t SpellAuraOptionsId)
{
    const auto* spellAuraOptionEntry = sDataStorage->GetSpellAuraOptionsEntry(SpellAuraOptionsId);
    if (spellAuraOptionEntry == nullptr)
    {
        return;
    }

    result += QString("Stackable up to %1 times<br>").arg(spellAuraOptionEntry->StackAmount);

    if (spellAuraOptionEntry->procFlags != 0)
    {
        result += "<br>";
        result += QString("Proc flag 0x%1, chance = %2%, charges - %3<br>")
                         .arg(spellAuraOptionEntry->procFlags, 8, 16, QLatin1Char('0'))
                         .arg(spellAuraOptionEntry->procChance)
                         .arg(spellAuraOptionEntry->procCharges);

        QString procNames;

        for (uint8_t i = 0; i <= MAX_UINT32_BITMASK_INDEX; ++i)
        {
            const uint32_t mask = 1U << i;
            if ((spellAuraOptionEntry->procFlags & mask) != 0)
            {
                procNames += QString("<span style=\"color:orange\">Flags %1,</span> %2<br>")
                                 .arg(mask)
                                 .arg(sSpellWorkJson->GetSpellProcDescription(mask));
            }
        }

        if (!procNames.isEmpty())
        {
            result += line;
            result += procNames + "<br>";
        }
    }
}

inline void PrintSpellCastTimeInfo(QString& result, uint32_t CastingTimeIndex, float speed)
{
    result += QString("<br>Cast speed %1, ").arg(speed);
    if (const auto* castTimeEntry = sDataStorage->GetSpellCastTimesEntry(CastingTimeIndex))
    {
        result += QString("Cast time: %1 ms<br>").arg(castTimeEntry->CastTime);
    }
    else
    {
        result += "Cast time: 0 ms<br>";
    }
}

inline void PrintSpellCooldownInfo(QString& result, uint32_t SpellCooldownsId)
{
    const auto* spellCooldownEntry = sDataStorage->GetSpellCooldownsEntry(SpellCooldownsId);
    if (spellCooldownEntry != nullptr && (spellCooldownEntry->RecoveryTime != 0 || spellCooldownEntry->CategoryRecoveryTime != 0 || spellCooldownEntry->StartRecoveryTime != 0))
    {
        result += QString("RecoveryTime: %1 ms, CategoryRecoveryTime: %2 ms<br>").arg(spellCooldownEntry->RecoveryTime).arg(spellCooldownEntry->CategoryRecoveryTime);
        result += QString("StartRecoveryCategory = %1, StartRecoveryTime = %2 ms<br>").arg(spellCooldownEntry->CategoryRecoveryTime).arg(spellCooldownEntry->StartRecoveryTime);
    }
}

inline void PrintSpellDurationInfo(QString& result, uint32_t DurationIndex)
{
    if (const auto* spellDurationEntry = sDataStorage->GetSpellDurationEntry(DurationIndex))
    {
        result += QString("Duration: ID (%1) %2 ms, %3 ms, %4 ms<br>")
                      .arg(spellDurationEntry->Id)
                      .arg(spellDurationEntry->Duration[0])
                      .arg(spellDurationEntry->Duration[1])
                      .arg(spellDurationEntry->Duration[2]);
    }
}

inline void PrintSpellPowerInfo(QString& result, uint32_t SpellPowerId, int8_t powerType)
{
    const auto* spellPowerEntry = sDataStorage->GetSpellPowerEntry(SpellPowerId);
    if (spellPowerEntry != nullptr && (spellPowerEntry->manaCost != 0 ||
                                       spellPowerEntry->ManaCostPercentage != 0 ||
                                       spellPowerEntry->manaCostPerlevel != 0 ||
                                       spellPowerEntry->manaPerSecondPerLevel != 0))
    {
        result += QString("Power type: %1 (%2), Cost: ")
                      .arg(powerType)
                      .arg(sSpellWorkJson->GetPowerTypeName(powerType));

        if (spellPowerEntry->manaCost == 0)
        {
            result += QString("%1 %").arg(spellPowerEntry->ManaCostPercentage);
        }
        else
        {
            uint32_t powerCost = spellPowerEntry->manaCost;
            if (powerType == POWER_RAGE)
            {
                powerCost /= 10;
            }

            result += QString::number(powerCost);
        }

        result += "<br>";
    }
}

// TODO: add secondary channel interrupt and aura interrupt flags output
inline void PrintInterruptInfo(QString& result, uint32_t SpellInterruptsId)
{
    result += "<br>";
    uint32_t interruptFlags = 0;
    std::array<uint32_t, 2> auraInterruptFlags{};
    std::array<uint32_t, 2> channelInterruptFlags{};
    if (const auto* spellInterruptEntry = sDataStorage->GetSpellInterruptsEntry(SpellInterruptsId))
    {
        interruptFlags = spellInterruptEntry->InterruptFlags;
        auraInterruptFlags = spellInterruptEntry->AuraInterruptFlags;
        channelInterruptFlags = spellInterruptEntry->ChannelInterruptFlags;
    }

    QString interruptFlagsStr;
    for (uint8_t i = 0; i <= MAX_UINT32_BITMASK_INDEX; ++i)
    {
        const uint32_t flag = 1U << i;
        if ((interruptFlags & flag) != 0)
        {
            if (!interruptFlagsStr.isEmpty())
            {
                interruptFlagsStr += ", ";
            }

            interruptFlagsStr += sSpellWorkJson->GetSpellInterruptFlagName(flag);
        }
    }

    if (interruptFlagsStr.isEmpty())
    {
        interruptFlagsStr += sSpellWorkJson->GetSpellInterruptFlagName(0);
    }

    std::array<QString, 2> auraFlagsStr;
    for (uint8_t flagId = 0; flagId < 2; ++flagId)
    {
        for (uint8_t i = 0; i <= MAX_UINT32_BITMASK_INDEX; ++i)
        {
            const uint32_t flag = 1U << i;
            if ((auraInterruptFlags[flagId] & flag) != 0)
            {
                if (!auraFlagsStr[flagId].isEmpty())
                {
                    auraFlagsStr[flagId] += ", ";
                }

                auraFlagsStr[flagId] += sSpellWorkJson->GetAuraInterruptFlagName(flag, flagId);
            }
        }
    }

    for (uint8_t i = 0; i < 2; ++i)
    {
        if (auraFlagsStr[i].isEmpty())
        {
            auraFlagsStr[i] += sSpellWorkJson->GetAuraInterruptFlagName(0, i);
        }
    }

    std::array<QString, 2> channelFlagsStr;
    for (uint8_t flagId = 0; flagId < 2; ++flagId)
    {
        for (uint8_t i = 0; i <= MAX_UINT32_BITMASK_INDEX; ++i)
        {
            const uint32_t flag = 1U << i;
            if ((channelInterruptFlags[flagId] & flag) != 0)
            {
                if (!channelFlagsStr[flagId].isEmpty())
                {
                    channelFlagsStr[flagId] += ", ";
                }

                channelFlagsStr[flagId] += sSpellWorkJson->GetAuraInterruptFlagName(flag, flagId);
            }
        }
    }

    for (uint8_t i = 0; i < 2; ++i)
    {
        if (channelFlagsStr[i].isEmpty())
        {
            channelFlagsStr[i] += sSpellWorkJson->GetAuraInterruptFlagName(0, i);
        }
    }

    result += QString("Spell interrupt flags: 0x%1 (%2)<br>").arg(interruptFlags, 8, 16, QLatin1Char('0')).arg(interruptFlagsStr);
    result += QString("Aura interrupt flags: 0x%1 (%2)<br>").arg(auraInterruptFlags[0], 8, 16, QLatin1Char('0')).arg(auraFlagsStr[0]);
    result += QString("Aura interrupt flags2: 0x%1 (%2)<br>").arg(auraInterruptFlags[1], 8, 16, QLatin1Char('0')).arg(auraFlagsStr[1]);
    result += QString("Channel interrupt flags: 0x%1 (%2)<br>").arg(channelInterruptFlags[0], 8, 16, QLatin1Char('0')).arg(channelFlagsStr[0]);
    result += QString("Channel interrupt flags2: 0x%1 (%2)<br>").arg(channelInterruptFlags[1], 8, 16, QLatin1Char('0')).arg(channelFlagsStr[1]);
}

static void PrintSpellRestrictionsInfo(QString& result, uint32_t SpellAuraRestrictionsId)
{
    const auto* spellRestrictions = sDataStorage->GetSpellAuraRestrictionsEntry(SpellAuraRestrictionsId);
    if (spellRestrictions == nullptr)
    {
        return;
    }

    if (spellRestrictions->CasterAuraState != 0)
    {
        result += QString("CasterAuraState = %1 (%2)<br>")
                      .arg(spellRestrictions->CasterAuraState)
                      .arg(sSpellWorkJson->GetSpellAuraStateName(spellRestrictions->CasterAuraState));
    }

    if (spellRestrictions->CasterAuraStateNot != 0)
    {
        result += QString("CasterAuraStateNot = %1 (%2)<br>")
                      .arg(spellRestrictions->CasterAuraStateNot)
                      .arg(sSpellWorkJson->GetSpellAuraStateName(spellRestrictions->CasterAuraStateNot));
    }

    if (spellRestrictions->TargetAuraState != 0)
    {
        result += QString("TargetAuraState = %1 (%2)<br>")
                      .arg(spellRestrictions->TargetAuraState)
                      .arg(sSpellWorkJson->GetSpellAuraStateName(spellRestrictions->TargetAuraState));
    }

    if (spellRestrictions->TargetAuraStateNot != 0)
    {
        result += QString("TargetAuraStateNot = %1 (%2)<br>")
                      .arg(spellRestrictions->TargetAuraStateNot)
                      .arg(sSpellWorkJson->GetSpellAuraStateName(spellRestrictions->TargetAuraStateNot));
    }

    if (spellRestrictions->casterAuraSpell != 0)
    {
        const auto* auraSpell = sDataStorage->GetSpellEntry(spellRestrictions->casterAuraSpell);
        result += QString("  Caster Aura Spell (%1) %2<br>")
                      .arg(spellRestrictions->casterAuraSpell)
                      .arg(auraSpell != nullptr ? auraSpell->getSpellName() : "unknown");
    }

    if (spellRestrictions->targetAuraSpell != 0)
    {
        const auto* auraSpell = sDataStorage->GetSpellEntry(spellRestrictions->targetAuraSpell);
        result += QString("  Target Aura Spell (%1) %2<br>")
                      .arg(spellRestrictions->targetAuraSpell)
                      .arg(auraSpell != nullptr ? auraSpell->getSpellName() : "unknown");
    }

    if (spellRestrictions->excludeCasterAuraSpell != 0)
    {
        const auto* auraSpell = sDataStorage->GetSpellEntry(spellRestrictions->excludeCasterAuraSpell);
        result += QString("  Ex Caster Aura Spell (%1) %2<br>")
                      .arg(spellRestrictions->excludeCasterAuraSpell)
                      .arg(auraSpell != nullptr ? auraSpell->getSpellName() : "unknown");
    }

    if (spellRestrictions->excludeTargetAuraSpell != 0)
    {
        const auto* auraSpell = sDataStorage->GetSpellEntry(spellRestrictions->excludeTargetAuraSpell);
        result += QString("  Ex Target Aura Spell (%1) %2<br>")
                      .arg(spellRestrictions->excludeTargetAuraSpell)
                      .arg(auraSpell != nullptr ? auraSpell->getSpellName() : "unknown");
    }
}

inline void PrintSpellCastRequirements(QString& result, uint32_t SpellCastingRequirementsId)
{
    const auto* spellCastReqEntry = sDataStorage->GetSpellCastingRequirementsEntry(SpellCastingRequirementsId);
    if (spellCastReqEntry == nullptr)
    {
        return;
    }

    result += QString("Requires Spell Focus %1<br>").arg(spellCastReqEntry->RequiresSpellFocus);

    const auto* groupEntry = sDataStorage->GetAreaGroupEntry(spellCastReqEntry->RequiredAreasID);
    if (groupEntry == nullptr)
    {
        return;
    }
    result += "<br>";
    result += "<b>Allowed areas:</b><br>";

    uint32_t groupId = 0;
    do
    {
        for (uint32_t const areaId : groupEntry->AreaId)
        {
            if (const auto* areaEntry = sDataStorage->GetAreaTableEntry(areaId))
            {
                result += QString("%1 - %2(MapId: %3)<br>").arg(areaId).arg(areaEntry->GetName()).arg(areaEntry->ContinentID);
            }
        }

        groupId = groupEntry->nextGroup;
    }
    while ((groupEntry = sDataStorage->GetAreaGroupEntry(groupId)) != nullptr);

    result += "<br>";
}

inline void PrintEffectScalingInfo(QString& result, const SpellEffectEntry* effectInfo, const SpellScalingEntry* scalingInfo, uint32_t scalingLevel)
{
    assert(effectInfo != nullptr);

    const auto effIndex = effectInfo->getEffectIndex();
    if (scalingInfo != nullptr && scalingInfo->Coefficient[effIndex] != 0.0f &&  scalingInfo->Class != 0)
    {
        uint32_t const selectedLevel = scalingLevel;

        uint32_t gtEntryId = static_cast<uint32_t>((scalingInfo->Class != -1 ? scalingInfo->Class - 1 : 11) * 100) + selectedLevel - 1;
        const auto* gtEntry = sDataStorage->GetGtSpellScalingEntry(gtEntryId);
        float gtMultiplier = gtEntry != nullptr ? gtEntry->value : 0.0f;

        if (scalingInfo->CastTimeMax > 0 && static_cast<uint32_t>(scalingInfo->CastTimeMaxLevel) > selectedLevel)
        {
            gtMultiplier *= static_cast<float>(scalingInfo->CastTimeMin + (selectedLevel - 1) * (scalingInfo->CastTimeMax - scalingInfo->CastTimeMin) / (scalingInfo->CastTimeMaxLevel - 1)) / static_cast<float>(scalingInfo->CastTimeMax);
        }

        if (scalingInfo->NerfMaxLevel > static_cast<int32_t>(selectedLevel))
        {
            gtMultiplier *= (1.0f -  scalingInfo->NerfFactor) * (float)(selectedLevel - 1) / (float)(scalingInfo->NerfMaxLevel - 1) + scalingInfo->NerfFactor;
        }

        if (scalingInfo->Variance[effIndex] != 0.0f)
        {
            float avg = scalingInfo->Coefficient[effIndex] * gtMultiplier;
            float delta = scalingInfo->Variance[effIndex] * scalingInfo->Coefficient[effIndex] * gtMultiplier * 0.5;
            result += QString("BasePoints = %1 to %2").arg(avg - delta).arg(avg + delta);
        }
        else
        {
            result += QString("AveragePoints = %1<br>").arg(scalingInfo->Coefficient[effIndex] * gtMultiplier);
        }

        if (scalingInfo->ComboPointsCoefficient[effIndex] != 0.0f)
        {
            result += QString(" + combo *  %1").arg(scalingInfo->ComboPointsCoefficient[effIndex] * gtMultiplier);
        }
        else
        {
            result += QString(" + combo *  %1").arg(effectInfo->getEffectPointsPerResource());
        }
    }
    else
    {
        result += QString("BasePoints = %1").arg(effectInfo->getEffectBasePoints() + ((effectInfo->getEffectDieSides() == 0) ? 0 : 1));

        if (effectInfo->getEffectRealPointsPerLevel() != 0)
        {
            result += QString(" + Level * %1").arg(effectInfo->getEffectRealPointsPerLevel());
        }

        if (effectInfo->getEffectDieSides() > 1)
        {
            if (effectInfo->getEffectRealPointsPerLevel() != 0)
            {
                result += QString(" to %1 + lvl * %2").arg(effectInfo->getEffectBasePoints() + effectInfo->getEffectDieSides(), effectInfo->getEffectRealPointsPerLevel());
            }
            else
            {
                result += QString(" to %1").arg(effectInfo->getEffectBasePoints() + effectInfo->getEffectDieSides());
            }
        }

        if (effectInfo->getEffectPointsPerResource() > 0)
        {
            result += QString(" + combo * %1").arg(effectInfo->getEffectPointsPerResource());
        }
    }
}

QString const SpellEntry::PrintSpellEffectInfo(uint32_t scalingLevel) const
{
    QString result;
    for (uint8_t effIndex = 0; effIndex < MAX_SPELL_EFFECTS; ++effIndex)
    {
        result += line;

        const auto* effectInfo = m_spellEffects[effIndex];
        if (effectInfo == nullptr)
        {
            result += QString("<b>Effect %1: Id %2 (%3)</b><br>")
                          .arg(effIndex)
                          .arg(SPELL_EFFECT_NONE)
                          .arg(sSpellWorkJson->GetSpellEffectName(SPELL_EFFECT_NONE));

            continue;
        }

        result += QString("<b>Effect %1: Id %2 (%3)</b><br>")
                      .arg(effIndex)
                      .arg(effectInfo->getEffect())
                      .arg(sSpellWorkJson->GetSpellEffectName(effectInfo->getEffect()));

        PrintEffectScalingInfo(result, effectInfo, sDataStorage->GetSpellScalingEntry(getSpellScalingId()), scalingLevel);

        if (effectInfo->getEffectBonusCoefficient() > 1.0f)
        {
            result += QString(" x %1").arg(effectInfo->getEffectBonusCoefficient());
        }

        if (effectInfo->getEffectAmplitude() > 0.0f)
        {
            result += QString("  Multiple = %1").arg(effectInfo->getEffectAmplitude());
        }

        result += "<br>";

        result += QString("Targets: (%1, %2) (%3, %4)<br>")
                .arg(effectInfo->getEffectImplicitTargetA())
                .arg(effectInfo->getEffectImplicitTargetB())
                .arg(sSpellWorkJson->GetSpellTargetName(effectInfo->getEffectImplicitTargetA()))
                .arg(sSpellWorkJson->GetSpellTargetName(effectInfo->getEffectImplicitTargetB()));

        result += line;

        if (effectInfo->getEffectAura() == 0)
        {
            result += QString("EffectMiscValueA = %1, EffectMiscValueB = %2, EffectAmplitude = %3<br>")
                    .arg(effectInfo->getEffectMiscValue())
                    .arg(effectInfo->getEffectMiscValueB())
                    .arg(effectInfo->getEffectAmplitude());

            if (const auto* effectJsonInfo = sSpellWorkJson->GetSpellEffectInfo(effectInfo->getEffect()))
            {
                if (const auto genDetail = effectInfo->GenerateExtraDetails(effectJsonInfo->extraDetailFormatStr))
                {
                    result += *genDetail;
                    result += "<br>";
                }
            }
        }
        else
        {
            result += QString("Aura Id %1 (%2), value = %3, misc = %4")
                    .arg(effectInfo->getEffectAura())
                    .arg(sSpellWorkJson->GetSpellAuraTypeName(effectInfo->getEffectAura()))
                    .arg(effectInfo->getEffectBasePoints())
                    .arg(effectInfo->getEffectMiscValue());

            result += QString(", miscB = %1").arg(effectInfo->getEffectMiscValueB());
            result += QString(", periodic = %1<br>").arg(effectInfo->getEffectAuraPeriod());

            if (const auto* aurEffInfo = sSpellWorkJson->GetSpellAuraEffectInfo(effectInfo->getEffectAura()))
            {
                if (const auto genDetail = effectInfo->GenerateExtraDetails(aurEffInfo->extraDetailFormatStr))
                {
                    result += *genDetail;
                    result += "<br>";
                }
            }
        }

        if (effectInfo->HasSpellClassMask())
        {
            if (const auto* thisEffClassOptions = sDataStorage->GetSpellClassOptionsEntry(getSpellClassOptionsId()))
            {
                result += QString("SpellClassMask = 0x%1 0x%2 0x%3<br>")
                              .arg(effectInfo->getEffectSpellClassMaskA(), 8, 16, QLatin1Char('0'))
                              .arg(effectInfo->getEffectSpellClassMaskB(), 8, 16, QLatin1Char('0'))
                              .arg(effectInfo->getEffectSpellClassMaskC(), 8, 16, QLatin1Char('0'));

                for (const auto& itr : sDataStorage->GetSpellEntries())
                {
                    const auto entry = itr.first;
                    const auto& spellInfo = itr.second;

                    const auto* otherSpellClassOpts = sDataStorage->GetSpellClassOptionsEntry(spellInfo.getSpellClassOptionsId());
                    if (otherSpellClassOpts == nullptr || otherSpellClassOpts->SpellFamilyName != thisEffClassOptions->SpellFamilyName)
                    {
                        continue;
                    }

                    {
                        bool hasFamilyFlag = false;
                        for (uint8_t i = 0; i < 3; ++i)
                        {
                            if (thisEffClassOptions->SpellFamilyFlags[i] & otherSpellClassOpts->SpellFamilyFlags[i])
                            {
                                hasFamilyFlag = true;
                                break;
                            }
                        }

                        if (!hasFamilyFlag)
                        {
                            continue;
                        }
                    }

                    const auto& skillLineAbilities = sDataStorage->GetSkillLineAbilityEntries();
                    const bool skillAbilityFound = std::any_of(skillLineAbilities.begin(), skillLineAbilities.end(), [entry](const auto& skillAbility)
                    {
                        return skillAbility.second.Spell == entry;
                    });

                    result += (skillAbilityFound ? "<span style=\"color:green\">\t+" : "<span style=\"color:red\">\t-</span>") + QString("%1 - %2</span><br>").arg(entry).arg(spellInfo.getSpellName());
                }
            }
        }

        if (effectInfo->getEffectRadiusIndex() != 0)
        {
            if (const auto* spellRadius = sDataStorage->GetSpellRadiusEntry(effectInfo->getEffectRadiusIndex()))
            {
                result += QString("Min radius: %1, max radius: %2<br>").arg(spellRadius->RadiusMin).arg(spellRadius->RadiusMax);
            }
        }

        const auto* spellAuraOptionEntry = sDataStorage->GetSpellAuraOptionsEntry(getSpellAuraOptionsId());

        // append trigger spell
        if (effectInfo->getEffectTriggerSpell() != 0)
        {
            if (const auto* triggerSpell = sDataStorage->GetSpellEntry(effectInfo->getEffectTriggerSpell()))
            {
                result += "<span style=\"color:green; font-weight: bold\">";
                result += QString("   Trigger spell (%1) %2. Chance = %3<br>")
                              .arg(triggerSpell->getId())
                                 .arg(triggerSpell->GetSpellNameRank())
                                 .arg(spellAuraOptionEntry != nullptr ? spellAuraOptionEntry->procChance : 0.0f);

                if (!triggerSpell->getDescription().isEmpty())
                {
                    result += QString("   Description: %1<br>").arg(triggerSpell->getDescription());
                }

                if (!triggerSpell->getToolTip().isEmpty())
                {
                    result += QString("ToolTip: %1<br>").arg(triggerSpell->getToolTip());
                }

                result += "</span>";

                if (const auto* triggerAuraOptions = sDataStorage->GetSpellAuraOptionsEntry(triggerSpell->getSpellAuraOptionsId()))
                {
                    result += QString("Charges - %1<br>").arg(triggerAuraOptions->procCharges);
                    result += line;

                    for (uint8_t i = 0; i <= MAX_UINT32_BITMASK_INDEX; ++i)
                    {
                        const uint32_t mask = 1U << i;
                        if ((triggerAuraOptions->procFlags & mask) != 0)
                        {
                            result += sSpellWorkJson->GetSpellProcDescription(mask);
                            result += "<br>";
                        }
                    }

                    result += line;
                }
            }
            else
            {
                result += QString("Trigger spell (%1) Not found, Chance = %2<br>").arg(effectInfo->getEffectTriggerSpell()).arg(spellAuraOptionEntry != nullptr ? spellAuraOptionEntry->procChance : 0.0f);
            }
        }

        if (effectInfo->getEffectChainTargets() != 0)
        {
            result += QString("EffectChainTarget = %1<br>").arg(effectInfo->getEffectChainTargets());
        }

        if (effectInfo->getEffectItemType() != 0)
        {
            result += QString("EffectItemType = %1<br>").arg(effectInfo->getEffectItemType());
        }

        if (effectInfo->getEffectMechanic() != MECHANIC_NONE)
        {
            result += QString("Effect Mechanic = %1 (%2)<br>")
                    .arg(effectInfo->getEffectMechanic())
                    .arg(sSpellWorkJson->GetSpellMechanicName(effectInfo->getEffectMechanic()));
        }

        result += "<br>";
    }

    return result;
}

QString const SpellEntry::PrintBaseInfo(uint32_t scalingLevel) const
{
    QString spellText;

    spellText += QString("<b>ID: %1 %2</b><br>")
                     .arg(getId())
                     .arg(GetSpellNameRank());

    spellText += line;

    if (!getDescription().isEmpty())
    {
        spellText += getDescription();
        spellText += "<br>";
        spellText += line;
    }

    spellText += QString("ToolTip: %1<br>").arg(getToolTip());
    spellText += line;
    spellText += QString("Category = %1, SpellIconID = %2, activeIconID = %3, SpellVisual = (%4, %5)<br>")
                     .arg(getSpellCategoriesId())
                     .arg(getSpellIconID())
                     .arg(getActiveIconID())
                     .arg(getSpellVisual1())
                     .arg(getSpellVisual2());
    spellText += QString("SpellSchoolMask = %1 (%2)<br>")
                     .arg(getSchoolMask())
                     .arg(GetFirstSchoolMaskNameStr(getSchoolMask()));

    PrintSpellClassOptions(spellText, getSpellClassOptionsId());
    PrintSpellCategory(spellText, getSpellCategoriesId());
    PrintAttributes(spellText, {getAttribute0(), getAttribute1(), getAttribute2(),
                                getAttribute3(), getAttribute4(), getAttribute5(),
                                getAttribute6(), getAttribute7(), getAttribute8(),
                                getAttribute9(), getAttribute10()});
    PrintTargetRestrictions(spellText, getSpellTargetRestrictionsId(), getSpellLevelsId(), (getAttribute5() & SPELL_ATTR5_LIMIT_N) != 0);
    PrintShapeShiftingInfo(spellText, getSpellShapeshiftId());
    PrintSkillLinks(spellText, getId());
    PrintReagents(spellText, getSpellReagentsId());
    PrintSpellEquipmentInfo(spellText, getSpellEquippedItemsId());

    spellText += line;

    PrintSpellRangeInfo(spellText, getRangeIndex());
    PrintSpellAuraOptions(spellText, getSpellAuraOptionsId());
    PrintSpellCastTimeInfo(spellText, getCastingTimeIndex(), getSpeed());
    PrintSpellCooldownInfo(spellText, getSpellCooldownsId());
    PrintSpellDurationInfo(spellText, getDurationIndex());
    PrintSpellPowerInfo(spellText, getSpellPowerId(), getPowerType());
    PrintInterruptInfo(spellText, getSpellInterruptsId());
    PrintSpellRestrictionsInfo(spellText, getSpellAuraRestrictionsId());
    PrintSpellCastRequirements(spellText, getSpellCastingRequirementsId());
    return spellText;
}

std::shared_ptr<QString> SpellEffectEntry::GenerateExtraDetails(const QString& format) const
{
    if (format.isEmpty())
    {
        return nullptr;
    }

    auto formattedStr = std::make_shared<QString>(format);

    using strRepFormatData = std::pair<QString /*strToRep*/, int32_t /*val*/>;

    const std::array<const strRepFormatData, 2> miscValues = {{ {":MiscValue:", getEffectMiscValue() }, { ":MiscValueB:", getEffectMiscValueB() } }};
    for (const auto& [strToRep, value] : miscValues)
    {
        if (!formattedStr->contains(strToRep))
        {
            continue;
        }

        formattedStr->replace(strToRep, QString::number(value));
    }

    const std::array<const strRepFormatData, 2> areaEntryNames = {{ {":AreaEntryNameMiscVal:", getEffectMiscValue() }, { ":AreaEntryNameMiscValB:", getEffectMiscValueB() } }};
    for (auto const& [strToRep, value] : areaEntryNames)
    {
        if (!formattedStr->contains(strToRep))
        {
            continue;
        }

        const auto* areaInfo = sDataStorage->GetAreaTableEntry(value);
        formattedStr->replace(strToRep, areaInfo != nullptr ? areaInfo->GetName().toString() : "Unknown");
    }

    const std::array<const strRepFormatData, 2> unitModStat = {{ {":UnitModNameMiscVal:", getEffectMiscValue() }, { ":UnitModNameMiscValB:", getEffectMiscValueB() } }};
    for (auto const& [strToRep, value] : unitModStat)
    {
        if (!formattedStr->contains(strToRep))
        {
            continue;
        }

        const auto statName = sSpellWorkJson->GetUnitModName(value);
        formattedStr->replace(strToRep, QString(statName.data()));
    }

    const std::array<const strRepFormatData, 2> spellMod = {{ {":SpellModNameMiscVal:", getEffectMiscValue() }, { ":SpellModNameMiscValB:", getEffectMiscValueB() } }};
    for (auto const& [strToRep, value] : spellMod)
    {
        if (!formattedStr->contains(strToRep))
        {
            continue;
        }

        const auto statName = sSpellWorkJson->GetSpellModName(value);
        formattedStr->replace(strToRep, QString(statName.data()));
    }

    const std::array<const strRepFormatData, 2> factionName = {{ {":FactionNameMiscVal:", getEffectMiscValue() }, { ":FactionNameMiscValB:", getEffectMiscValueB() } }};
    for (auto const& [strToRep, value] : factionName)
    {
        if (!formattedStr->contains(strToRep))
        {
            continue;
        }

        if (const auto* factionEntry = sDataStorage->GetFactionEntry(value))
        {
            formattedStr->replace(strToRep, factionEntry->Name);
        }
        else
        {
            formattedStr->replace(strToRep, QString("<b>Cannot find entry %1 in Faction.dbc</b><br>").arg(value));
        }
    }

    const std::array<const strRepFormatData, 2> combatRating = {{ {":CBRatingListMiscVal:", getEffectMiscValue() }, { ":CBRatingListMiscValB:", getEffectMiscValueB() } }};
    for (auto const& [strToRep, value] : combatRating)
    {
        if (!formattedStr->contains(strToRep))
        {
            continue;
        }

        QString ratingsStr;
        for (uint8_t ratingId = 0; ratingId <= MAX_UINT32_BITMASK_INDEX; ++ratingId)
        {
            const uint32_t mask = 1U << ratingId;
            if ((value & mask) != 0)
            {
                if (!ratingsStr.isEmpty())
                {
                    ratingsStr += ", ";
                }

                ratingsStr += sSpellWorkJson->GetCombatRatingName(ratingId);
            }
        }

        if (ratingsStr.isEmpty())
        {
            ratingsStr = "Unknown";
        }
        formattedStr->replace(strToRep, ratingsStr);
    }

    const std::array<const strRepFormatData, 2> screenEffect = {{ {":ScreenEffectMiscVal:", getEffectMiscValue() }, { ":ScreenEffectMiscValB:", getEffectMiscValueB() } }};
    for (auto const& [strToRep, value] : screenEffect)
    {
        if (!formattedStr->contains(strToRep))
        {
            continue;
        }

        const auto* _screenEffect = sDataStorage->GetScreenEffectEntry(value);
        formattedStr->replace(strToRep, _screenEffect != nullptr ? _screenEffect->GetName().toString() : "unknown");
    }

    const std::array<const strRepFormatData, 2> overrideSpellList = {{ {":OverrideSpellListMiscVal:", getEffectMiscValue() }, { ":OverrideSpellListMiscValB:", getEffectMiscValueB() } }};
    for (auto const& [strToRep, value] : overrideSpellList)
    {
        if (!formattedStr->contains(strToRep))
        {
            continue;
        }

        const auto* spellOverride = sDataStorage->GetOverrideSpellDataEntry(value);
        if (spellOverride == nullptr)
        {
            formattedStr->replace(strToRep, QString("entry %1 does not exist in OverrideSpellData.dbc").arg(value));
        }
        else
        {
            bool first = false;
            QString result;
            for (auto pSpellId : spellOverride->Spells)
            {
                if (pSpellId == 0)
                {
                    continue;
                }

                if (!first)
                {
                    first = true;
                    result = "<b>Overriding Spells:</b><br>";
                }
                const auto* spell = sDataStorage->GetSpellEntry(pSpellId);
                result += QString("<span style=\"color: orange\">- %1</span> %2<br>").arg(pSpellId).arg(spell != nullptr ? spell->getSpellName() : "unknown");
            }

            formattedStr->replace(strToRep, result);
        }
    }

    const std::array<const strRepFormatData, 2> mechanicImmunities = {{ {":MechanicImmunitiesMiscVal:", getEffectMiscValue() }, { ":MechanicImmunitiesMiscValB:", getEffectMiscValueB() } }};
    for (auto const& [strToRep, value] : mechanicImmunities)
    {
        if (!formattedStr->contains(strToRep))
        {
            continue;
        }

        QString result;
        for (uint8_t id = 1; id <= MAX_UINT32_BITMASK_INDEX; ++id)
        {
            const uint32_t flag = 1U << (id - 1);
            if ((value & flag) == 0)
            {
                continue;
            }

            if (!result.isEmpty())
            {
                result += ", ";
            }

            result += sSpellWorkJson->GetSpellMechanicName(id);
        }

        if (result.isEmpty())
        {
            result += sSpellWorkJson->GetSpellMechanicName(MECHANIC_NONE);
        }

        formattedStr->replace(strToRep, result);
    }

    if (formattedStr->contains(":EffectItemType:"))
    {
        formattedStr->replace(":EffectItemType:", QString(getEffectItemType()), Qt::CaseInsensitive);
    }

    if (formattedStr->contains(":EffectItemTypeName:"))
    {
        const auto* itemEntry = sDataStorage->GetItemEntry(getEffectItemType());
        formattedStr->replace(":EffectItemName:", itemEntry != nullptr ? itemEntry->GetName() : "<unknown>", Qt::CaseInsensitive);
    }

    return formattedStr;
}
