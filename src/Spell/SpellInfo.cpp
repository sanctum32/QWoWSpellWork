#include "DBCStructures.hpp"
#include "DataStorage.hpp"
#include "ItemDefines.hpp"
#include "JsonData/JsonData.hpp"
#include "SharedDefines.hpp"
#include "UnitDefines.hpp"
#include <cmath>
#include <random>

inline float frand(float min, float max)
{
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_real_distribution<float> distr(min, max);
    return distr(eng);
}

inline int irand(int min, int max)
{
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<int> distr(min, max);
    return distr(eng);
}

// Returns first found school mask's name
inline QString GetFirstSchoolMaskNameStr(uint32_t mask)
{
    for (uint8_t i = 0; i < MAX_UINT32_BITMASK_INDEX; ++i)
    {
        const uint32_t schoolMask = (1U << i);
        if ((mask & schoolMask) == 0)
        {
            continue;
        }

        auto result = sSpellWorkJson->GetSpellSchoolMaskName(schoolMask);
        if (!result.isEmpty())
        {
            return QString(result.data());
        }

        return QString("UNKNOWN SCHOOLMASK %1").arg(schoolMask);
    }

    return {};
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

inline void PrintSpellClassOptions(QString& result, const SpellClassOptionsEntry* spellClassOptionsEntry)
{
    if (spellClassOptionsEntry != nullptr)
    {
        result += QString("Modal Next Spell: %1<br>").arg(spellClassOptionsEntry->modalNextSpell);
        result += QString("FamilyName %1 (%2), flat [0] 0x%3 [1] 0x%4 [2] 0x%5<br>")
                         .arg(spellClassOptionsEntry->SpellFamilyName)
                         .arg(sSpellWorkJson->GetSpellFamilyName(spellClassOptionsEntry->SpellFamilyName))
                         .arg(spellClassOptionsEntry->SpellFamilyFlags[0], 8, 16, QLatin1Char('0'))
                         .arg(spellClassOptionsEntry->SpellFamilyFlags[1], 8, 16, QLatin1Char('0'))
                         .arg(spellClassOptionsEntry->SpellFamilyFlags[2], 8, 16, QLatin1Char('0'));
    }
    else
    {
        result += QString("Modal Next Spell: 0<br>");
        result += QString("Family 0 %1, flag [0] 0x00000000 [1] 0x00000000 [2] 0x00000000<br>").arg(sSpellWorkJson->GetSpellFamilyName(SPELLFAMILY_GENERIC));
    }
}

inline void PrintSpellCategory(QString& result, const SpellCategoriesEntry* spellCategoriesEntry)
{
    if (spellCategoriesEntry != nullptr)
    {
        // Damage/defense type
        result += QString("DamageClass = %1 (%2)<br>")
                      .arg(spellCategoriesEntry->DefenseType)
                      .arg(sSpellWorkJson->GetSpellDamageTypeName(spellCategoriesEntry->DefenseType));

        // Prevention type
        result += QString("PreventionType = %1 (%2)<br>")
                      .arg(spellCategoriesEntry->PreventionType)
                      .arg(sSpellWorkJson->GetSpellPreventionTypeName(spellCategoriesEntry->PreventionType));

        // Category
        result += QString("Category id = %1").arg(spellCategoriesEntry->Category);
        if (const auto* spellCategoryInfo = sDataStorage->GetSpellCategoryEntry(spellCategoriesEntry->Id))
        {
            result += QString(" (%1)").arg(spellCategoryInfo->GetName());
        }

        result += "<br>";

        // Dispel info
        result += QString("DispelType = %1 (%2)<br>")
                      .arg(spellCategoriesEntry->DispelType)
                      .arg(sSpellWorkJson->GetDispelName(spellCategoriesEntry->DispelType));

        // Mechanic
        result += QString("Mechanic = %1 (%2)<br>")
                      .arg(spellCategoriesEntry->Mechanic)
                      .arg(sSpellWorkJson->GetSpellMechanicName(spellCategoriesEntry->Mechanic));
    }
    else
    {
        result += QString("DamageClass = 0 (%1)<br>").arg(sSpellWorkJson->GetSpellDamageTypeName(SPELL_DAMAGE_CLASS_NONE));
        result += QString("PreventionType = 0 (%1)<br>").arg(sSpellWorkJson->GetSpellPreventionTypeName(SPELL_PREVENTION_TYPE_NONE));
        result += QString("Category id = 0 (SPELL_CATEGORY_NONE)<br>");
        result += QString("DispelType = 0 (%1)<br>").arg(sSpellWorkJson->GetDispelName(DISPEL_NONE));
        result += QString("Mechanic = 0 (%1)<br>").arg(sSpellWorkJson->GetSpellMechanicName(MECHANIC_NONE));
    }
}

inline void PrintTargetRestrictions(QString& result, const SpellTargetRestrictionsEntry* spellTargetRestrictionsentry, const SpellLevelsEntry* spellLevelsEntry, bool isSingleTarget)
{
    if (spellTargetRestrictionsentry != nullptr)
    {
        if (spellTargetRestrictionsentry->Targets != 0)
        {
            result += QString("Targets Mask = [0] 0x%1").arg(spellTargetRestrictionsentry->Targets, 8, 16, QLatin1Char('0')) + "(";

            QString targets;
            for (uint8_t i = 0; i <= MAX_UINT32_BITMASK_INDEX; ++i)
            {
                const uint32_t flag = 1U << i;
                if ((flag & spellTargetRestrictionsentry->Targets) != 0)
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

        if (spellTargetRestrictionsentry->TargetCreatureType != 0)
        {
            result += QString("Creature Type Mask = 0x%1 (%2)")
                          .arg(spellTargetRestrictionsentry->TargetCreatureType, 8, 16, QLatin1Char('0'))
                          .arg(sSpellWorkJson->GetCreatureTypeName(spellTargetRestrictionsentry->TargetCreatureType));
        }

        uint32_t targetCount = spellTargetRestrictionsentry->MaxAffectedTargets;
        if (isSingleTarget)
        {
            targetCount = 1;
        }

        result += "<br>";
        result += QString("MaxAffectedTargets = %1<br>").arg(targetCount);
        if (spellTargetRestrictionsentry->ConeAngle > 0.0f)
        {
            result += QString("Effected cone angle: %1<br>").arg(spellTargetRestrictionsentry->ConeAngle);
        }
    }

    if (spellLevelsEntry != nullptr)
    {
        result += QString("Spell level = %1, base %2, max %3, maxTarget level %4<br>")
                      .arg(spellLevelsEntry->spellLevel)
                      .arg(spellLevelsEntry->baseLevel)
                      .arg(spellLevelsEntry->maxLevel)
                      .arg(spellTargetRestrictionsentry != nullptr ? spellTargetRestrictionsentry->MaxTargetLevel : 0);
    }
}

inline void PrintShapeShiftingInfo(QString& result, const SpellShapeshiftEntry* shapeshiftingEntry)
{
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

        const auto& itr2 = std::ranges::find_if(skillLineAbilities, [_skillId, spellId](const auto _skillLineAbility)
        {
            const auto& abilityData = _skillLineAbility.second;
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
        result += printLine;
        result += QString("Skill (Id %1) \"%2\"<br>").arg(skillLineAbility->SkillLine).arg(skillLine->name);
        result += QString("MinSkillLineRank %1<br>").arg(skillLineAbility->MinSkillLineRank);

        result += QString("SupercedesSpell = %1, MinMaxValue (%2, %3)<br>")
                      .arg(skillLineAbility->MinSkillLineRank)
                      .arg(skillLineAbility->TrivialSkillLineRankLow)
                      .arg(skillLineAbility->TrivialSkillLineRankHigh);

        result += QString(", NumSkillups (%1)<br>")
                      .arg(skillLineAbility->NumSkillUps);
    }
}

inline void PrintReagents(QString& result, const SpellReagentsEntry* spellReagentsEntry)
{
    if (spellReagentsEntry == nullptr || !std::ranges::any_of(spellReagentsEntry->Reagents, [](int32_t reagent){ return reagent != 0; }))
    {
        return;
    }

    result += "<br><b>Required items (or reagents):</b><br>";
    for (uint8_t i = 0; i < MAX_SPELL_REAGENTS; ++i)
    {
        if (spellReagentsEntry->Reagents[i] == 0)
        {
            continue;
        }

        const auto* itemEntry = sDataStorage->GetItemEntry(spellReagentsEntry->Reagents[i]);
        result += QString("Item: %1 (\"%2\"), required amount %3<br>")
            .arg(spellReagentsEntry->Reagents[i])
            .arg(itemEntry != nullptr ? itemEntry->GetName() : "Unknown")
            .arg(spellReagentsEntry->ReagentCount[i]);
    }
}

inline void PrintSpellEquipmentInfo(QString& result, const SpellEquippedItemsEntry* spellEquipedItemsEntry)
{
    if (spellEquipedItemsEntry == nullptr)
    {
        return;
    }

    result += QString("EquippedItemClass = %1 (%2)<br>")
              .arg(spellEquipedItemsEntry->EquippedItemClass)
              .arg(sSpellWorkJson->GetItemClassName(spellEquipedItemsEntry->EquippedItemClass));

    if (spellEquipedItemsEntry->EquippedItemSubClassMask != 0)
    {
        switch (spellEquipedItemsEntry->EquippedItemClass)
        {
        case ITEM_CLASS_WEAPON:
        {
            QString subclassNames;
            for (uint8_t i = 0; i <= MAX_UINT32_BITMASK_INDEX; ++i)
            {
                if ((spellEquipedItemsEntry->EquippedItemClass & (1U << i)) == 0)
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
                result += QString("SubClass mask 0x%1 (%2)<br>").arg(spellEquipedItemsEntry->EquippedItemSubClassMask, 8, 16, QLatin1Char('0')).arg(subclassNames);
            }
            break;
        }
        case ITEM_CLASS_ARMOR:
        {
            QString subclassNames;
            for (uint8_t i = 0; i <= MAX_UINT32_BITMASK_INDEX; ++i)
            {
                if ((spellEquipedItemsEntry->EquippedItemSubClassMask & (1U << i)) == 0)
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
                result += QString("    SubClass mask 0x%1 (%2)<br>").arg(spellEquipedItemsEntry->EquippedItemSubClassMask, 8, 16, QLatin1Char('0')).arg(subclassNames);
            }
            break;
        }
        case ITEM_CLASS_MISCELLANEOUS:
        {
            QString subclassNames;
            for (uint8_t i = 0; i <= MAX_UINT32_BITMASK_INDEX; ++i)
            {
                if ((spellEquipedItemsEntry->EquippedItemSubClassMask & (1U << i)) == 0)
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
                result += QString("    SubClass mask 0x%1 (%2)<br>").arg(spellEquipedItemsEntry->EquippedItemSubClassMask, 8, 16, QLatin1Char('0')).arg(subclassNames);
            }
            break;
        }
        }
    }

    if (spellEquipedItemsEntry->EquippedItemInventoryTypeMask != 0)
    {
        QString inventoryNames;
        for (uint8_t i = 0; i <= MAX_UINT32_BITMASK_INDEX; ++i)
        {
            if ((spellEquipedItemsEntry->EquippedItemInventoryTypeMask & (1U << i)) == 0)
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
            result += QString("    InventoryType mask = 0x%1 (%2)<br>").arg(spellEquipedItemsEntry->EquippedItemInventoryTypeMask, 8, 16, QLatin1Char('0')).arg(inventoryNames);
        }
    }
}

inline void PrintSpellRangeInfo(QString& result, const SpellRangeEntry* rangeEntry)
{
    result += "<br>";
    if (rangeEntry != nullptr)
    {
        result += QString("SpellRange: (Id %1) \"%2\"<br>").arg(rangeEntry->Id).arg(rangeEntry->DisplayName);
        result += QString("MinRangeNegative = %1, MinRangePositive = %2<br>").arg(rangeEntry->RangeMin.at(0)).arg(rangeEntry->RangeMin.at(1));
        result += QString("MaxRangeNegative = %1, MaxRangePositive = %2<br>").arg(rangeEntry->RangeMax.at(0)).arg(rangeEntry->RangeMax.at(1));
    }
    else
    {
        result += "SpellRange: (Id 0) \"None\"<br>";
        result += "MinRangeNegative = 0, MinRangePositive = 0<br>";
        result += "MaxRangeNegative = 0, MaxRangePositive = 0<br>";
    }
}

inline void PrintSpellAuraOptions(QString& result, const SpellAuraOptionsEntry* spellAuraOptionsEntry)
{
    if (spellAuraOptionsEntry == nullptr)
    {
        return;
    }

    result += QString("Stackable up to %1 times<br>").arg(spellAuraOptionsEntry->CumulativeAura);

    if (spellAuraOptionsEntry->ProcTypeMask == 0)
    {
        return;
    }

    result += "<br>";
    result += QString("Proc flag 0x%1, chance = %2%, charges - %3<br>")
                     .arg(spellAuraOptionsEntry->ProcTypeMask, 8, 16, QLatin1Char('0'))
                     .arg(spellAuraOptionsEntry->ProcChance)
                     .arg(spellAuraOptionsEntry->ProcCharges);

    QString procNames;

    for (uint8_t i = 0; i <= MAX_UINT32_BITMASK_INDEX; ++i)
    {
        const uint32_t mask = 1U << i;
        if ((spellAuraOptionsEntry->ProcTypeMask & mask) != 0)
        {
            procNames += QString("<span style=\"color:orange\">Flags %1,</span> %2<br>")
                             .arg(mask)
                             .arg(sSpellWorkJson->GetSpellProcDescription(mask));
        }
    }

    if (!procNames.isEmpty())
    {
        result += printLine;
        result += procNames + "<br>";
    }
}

inline void PrintSpellCastTimeInfo(QString& result, const SpellCastTimesEntry* spellCastingTime)
{
    if (spellCastingTime != nullptr)
    {
        result += QString("Cast time: %1 ms<br>").arg(spellCastingTime->CastTime);
    }
    else
    {
        result += "Cast time: 0 ms<br>";
    }
}

inline void PrintSpellCooldownInfo(QString& result, const SpellCooldownsEntry* spellCooldownEntry)
{
    if (spellCooldownEntry != nullptr && (spellCooldownEntry->RecoveryTime != 0 || spellCooldownEntry->CategoryRecoveryTime != 0 || spellCooldownEntry->StartRecoveryTime != 0))
    {
        result += QString("RecoveryTime: %1 ms, CategoryRecoveryTime: %2 ms<br>").arg(spellCooldownEntry->RecoveryTime).arg(spellCooldownEntry->CategoryRecoveryTime);
        result += QString("StartRecoveryCategory = %1, StartRecoveryTime = %2 ms<br>").arg(spellCooldownEntry->CategoryRecoveryTime).arg(spellCooldownEntry->StartRecoveryTime);
    }
}

inline void PrintSpellDurationInfo(QString& result, const SpellDurationEntry* durationEntry)
{
    if (durationEntry != nullptr)
    {
        result += QString("Duration: ID (%1) %2 ms, %3 ms, %4 ms<br>")
                      .arg(durationEntry->Id)
                      .arg(durationEntry->Duration)
                      .arg(durationEntry->DurationPerLevel)
                      .arg(durationEntry->MaxDuration);
    }
}

inline void PrintSpellPowerInfo(QString& result, const SpellPowerEntry* spellPowerEntry, int8_t powerType)
{
    if (spellPowerEntry == nullptr || (spellPowerEntry->ManaCost == 0 &&
                                       spellPowerEntry->PowerCostPct == 0 &&
                                       spellPowerEntry->ManaCostPerLevel == 0 &&
                                       spellPowerEntry->ManaPerSecond == 0))
    {
        return;
    }

    result += QString("Power type: %1 (%2), Cost: ")
                  .arg(powerType)
                  .arg(sSpellWorkJson->GetPowerTypeName(powerType));

    if (spellPowerEntry->ManaCost == 0)
    {
        result += QString("%1 %").arg(spellPowerEntry->PowerCostPct);
    }
    else
    {
        uint32_t powerCost = spellPowerEntry->ManaCost;
        if (powerType == POWER_RAGE)
        {
            powerCost /= 10;
        }

        result += QString::number(powerCost);
    }

    result += "<br>";
}

// TODO: add secondary channel interrupt and aura interrupt flags output
inline void PrintInterruptInfo(QString& result, const SpellInterruptsEntry* m_spellInterruptsEntry)
{
    result += "<br>";
    uint32_t interruptFlags = 0;
    std::array<uint32_t, 2> auraInterruptFlags{};
    std::array<uint32_t, 2> channelInterruptFlags{};
    if (m_spellInterruptsEntry != nullptr)
    {
        interruptFlags = m_spellInterruptsEntry->InterruptFlags;
        auraInterruptFlags = m_spellInterruptsEntry->AuraInterruptFlags;
        channelInterruptFlags = m_spellInterruptsEntry->ChannelInterruptFlags;
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

static void PrintSpellRestrictionsInfo(QString& result, const SpellAuraRestrictionsEntry* restrictionsEntry)
{
    if (restrictionsEntry == nullptr)
    {
        return;
    }

    if (restrictionsEntry->CasterAuraState != 0)
    {
        result += QString("CasterAuraState = %1 (%2)<br>")
                      .arg(restrictionsEntry->CasterAuraState)
                      .arg(sSpellWorkJson->GetSpellAuraStateName(restrictionsEntry->CasterAuraState));
    }

    if (restrictionsEntry->CasterAuraStateNot != 0)
    {
        result += QString("CasterAuraStateNot = %1 (%2)<br>")
                      .arg(restrictionsEntry->CasterAuraStateNot)
                      .arg(sSpellWorkJson->GetSpellAuraStateName(restrictionsEntry->CasterAuraStateNot));
    }

    if (restrictionsEntry->TargetAuraState != 0)
    {
        result += QString("TargetAuraState = %1 (%2)<br>")
                      .arg(restrictionsEntry->TargetAuraState)
                      .arg(sSpellWorkJson->GetSpellAuraStateName(restrictionsEntry->TargetAuraState));
    }

    if (restrictionsEntry->TargetAuraStateNot != 0)
    {
        result += QString("TargetAuraStateNot = %1 (%2)<br>")
                      .arg(restrictionsEntry->TargetAuraStateNot)
                      .arg(sSpellWorkJson->GetSpellAuraStateName(restrictionsEntry->TargetAuraStateNot));
    }

    if (restrictionsEntry->casterAuraSpell != 0)
    {
        const auto* auraSpell = sDataStorage->GetSpellEntry(restrictionsEntry->casterAuraSpell);
        result += QString("  Caster Aura Spell (%1) %2<br>")
                      .arg(restrictionsEntry->casterAuraSpell)
                      .arg(auraSpell != nullptr ? auraSpell->getSpellName() : "unknown");
    }

    if (restrictionsEntry->targetAuraSpell != 0)
    {
        const auto* auraSpell = sDataStorage->GetSpellEntry(restrictionsEntry->targetAuraSpell);
        result += QString("  Target Aura Spell (%1) %2<br>")
                      .arg(restrictionsEntry->targetAuraSpell)
                      .arg(auraSpell != nullptr ? auraSpell->getSpellName() : "unknown");
    }

    if (restrictionsEntry->excludeCasterAuraSpell != 0)
    {
        const auto* auraSpell = sDataStorage->GetSpellEntry(restrictionsEntry->excludeCasterAuraSpell);
        result += QString("  Ex Caster Aura Spell (%1) %2<br>")
                      .arg(restrictionsEntry->excludeCasterAuraSpell)
                      .arg(auraSpell != nullptr ? auraSpell->getSpellName() : "unknown");
    }

    if (restrictionsEntry->excludeTargetAuraSpell != 0)
    {
        const auto* auraSpell = sDataStorage->GetSpellEntry(restrictionsEntry->excludeTargetAuraSpell);
        result += QString("  Ex Target Aura Spell (%1) %2<br>")
                      .arg(restrictionsEntry->excludeTargetAuraSpell)
                      .arg(auraSpell != nullptr ? auraSpell->getSpellName() : "unknown");
    }
}

inline void PrintSpellCastRequirements(QString& result, const SpellCastingRequirementsEntry* spellCastReqEntry)
{
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

inline void PrintEffectBaseValues(QString& result, const SpellEntry* spellEntry, uint8_t effIndex, uint8_t selectedLevel, uint8_t comboPoints)
{
    assert(spellEntry != nullptr);
    const auto* effectInfo = spellEntry->m_spellEffects.at(effIndex);
    assert(effectInfo != nullptr);

    result += QString("BasePoints = %1<br>").arg(effectInfo->getEffectBasePoints() + ((effectInfo->getEffectDieSides() == 0) ? 0 : 1));


    // Ported from SpellInfo::CalValue
    float basePointsPerLevel = effectInfo->getEffectRealPointsPerLevel();
    std::array<float, 2> basePoints = { static_cast<float>(effectInfo->getEffectBasePoints()), static_cast<float>(effectInfo->getEffectBasePoints())};
    float comboDamage = effectInfo->getEffectPointsPerResource();
    int32_t randomPoints = effectInfo->getEffectDieSides();

    // base amount modification based on spell lvl vs caster lvl
    if (spellEntry->m_scalingEntry != nullptr && spellEntry->m_scalingEntry->Coefficient.at(effectInfo->getEffectIndex()) != 0.0f)
    {
        float value = 0.0f;
        if (selectedLevel > 0 && spellEntry->m_scalingEntry->Class > 0)
        {
            if (GtSpellScalingEntry const* gtScaling = sDataStorage->GetGtSpellScalingEntry(((spellEntry->m_scalingEntry->Class > 0 ? spellEntry->m_scalingEntry->Class : ((MAX_CLASSES - 1 /*last class*/) - spellEntry->m_scalingEntry->Class)) - 1) * 100 + selectedLevel - 1))
                value = gtScaling->value;

            if (selectedLevel < spellEntry->m_scalingEntry->CastTimeMaxLevel && spellEntry->m_scalingEntry->CastTimeMax)
                value *= float(spellEntry->m_scalingEntry->CastTimeMin + (selectedLevel - 1) * (spellEntry->m_scalingEntry->CastTimeMax - spellEntry->m_scalingEntry->CastTimeMin) / (spellEntry->m_scalingEntry->CastTimeMaxLevel - 1)) / float(spellEntry->m_scalingEntry->CastTimeMax);

            if (selectedLevel < spellEntry->m_scalingEntry->NerfMaxLevel)
                value *= ((((1.0 - spellEntry->m_scalingEntry->NerfFactor) * (selectedLevel - 1)) / (spellEntry->m_scalingEntry->NerfMaxLevel - 1)) + spellEntry->m_scalingEntry->NerfFactor);
        }

        if (spellEntry->m_scalingEntry->ComboPointsCoefficient.at(effectInfo->getEffectIndex()) > 0.0f)
            comboDamage = spellEntry->m_scalingEntry->ComboPointsCoefficient.at(effectInfo->getEffectIndex()) * value;

        value *= spellEntry->m_scalingEntry->Coefficient.at(effectInfo->getEffectIndex());
        if (value >= 0.0f && value < 1.0f)
            value = 1.0f;

        basePoints.fill(value);
        if (spellEntry->m_scalingEntry->Variance.at(effectInfo->getEffectIndex()))
        {
            float delta = std::fabs(spellEntry->m_scalingEntry->Variance.at(effectInfo->getEffectIndex()) * value * 0.5f);
            //value += frand(-delta, delta);

            basePoints.at(0) += -delta;
            basePoints.at(1) += delta;
        }

        basePoints.at(0) = round(basePoints.at(0));
        basePoints.at(1) += round(basePoints.at(1));
        //basePoints = int32_t(round(value));
    }
    else
    {
        if (basePointsPerLevel != 0.0f)
        {
            uint8_t level = selectedLevel;
            if (spellEntry->m_spellLevelsEntry != nullptr)
            {
                if (level > uint8_t(spellEntry->m_spellLevelsEntry->maxLevel) && spellEntry->m_spellLevelsEntry->maxLevel > 0)
                    level = uint8_t(spellEntry->m_spellLevelsEntry->maxLevel);
                else if (level < uint8_t(spellEntry->m_spellLevelsEntry->baseLevel))
                    level = uint8_t(spellEntry->m_spellLevelsEntry->baseLevel);

                if (!spellEntry->HasAttribute(SPELL_ATTR0_PASSIVE))
                    level -= uint8_t(spellEntry->m_spellLevelsEntry->spellLevel);
            }

            basePoints.fill(level * basePointsPerLevel);
        }

        // roll in a range <1;EffectDieSides> as of patch 3.3.3
        switch (randomPoints)
        {
        case 0:
            break;
        case 1:
            ++basePoints.at(0);
            basePoints.at(1) = basePoints.at(0);
            break;                     // range 1..1
        default:
        {
            // range can have positive (1..rand) and negative (rand..1) values, so order its for irand
            /*int32_t randvalue = (randomPoints >= 1)
                                  ? irand(1, randomPoints)
                                  : irand(randomPoints, 1);*/

            // basePoints += randvalue;

            if (randomPoints >= 1)
            {
                basePoints.at(1) = basePoints.at(0) + randomPoints;
            }
            else
            {
                basePoints.at(0) = basePoints.at(0) + randomPoints;
            }

            break;
        }
        }
    }

    // random damage
    for (float& value : basePoints)
    {
        // bonus amount from combo points
        if (comboPoints > 0 && spellEntry->HasAttribute(SPELL_ATTR1_FINISHING_MOVE_DAMAGE) && comboDamage != 0.f)
            value += comboDamage * comboPoints;

        if (spellEntry->m_spellLevelsEntry != nullptr && spellEntry->m_spellLevelsEntry->spellLevel > 0 && spellEntry->m_spellLevelsEntry->spellLevel != selectedLevel &&
            !basePointsPerLevel && spellEntry->HasAttribute(SPELL_ATTR0_SCALES_WITH_CREATURE_LEVEL))
        {
            bool canEffectScale = false;
            switch (effectInfo->getEffect())
            {
            case SPELL_EFFECT_SCHOOL_DAMAGE:
            case SPELL_EFFECT_DUMMY:
            case SPELL_EFFECT_POWER_DRAIN:
            case SPELL_EFFECT_HEALTH_LEECH:
            case SPELL_EFFECT_HEAL:
            case SPELL_EFFECT_WEAPON_DAMAGE:
            case SPELL_EFFECT_POWER_BURN:
            case SPELL_EFFECT_SCRIPT_EFFECT:
            case SPELL_EFFECT_NORMALIZED_WEAPON_DMG:
            case SPELL_EFFECT_FORCE_CAST_WITH_VALUE:
            case SPELL_EFFECT_TRIGGER_SPELL_WITH_VALUE:
            case SPELL_EFFECT_TRIGGER_MISSILE_SPELL_WITH_VALUE:
                canEffectScale = true;
                break;
            default:
                break;
            }

            switch (effectInfo->getEffectAura())
            {
            case SPELL_AURA_PERIODIC_DAMAGE:
            case SPELL_AURA_DUMMY:
            case SPELL_AURA_PERIODIC_HEAL:
            case SPELL_AURA_DAMAGE_SHIELD:
            case SPELL_AURA_PROC_TRIGGER_DAMAGE:
            case SPELL_AURA_PERIODIC_LEECH:
            case SPELL_AURA_PERIODIC_MANA_LEECH:
            case SPELL_AURA_SCHOOL_ABSORB:
            case SPELL_AURA_PERIODIC_TRIGGER_SPELL_WITH_VALUE:
                canEffectScale = true;
                break;
            default:
                break;
            }

            if (canEffectScale)
            {
                const auto* spellScaler = sDataStorage->GetGtNPCManaCostScalerEntry(spellEntry->m_spellLevelsEntry->spellLevel - 1);
                const auto* casterScaler = sDataStorage->GetGtNPCManaCostScalerEntry(selectedLevel - 1);
                if (spellScaler && casterScaler)
                {
                    value *= casterScaler->ratio / spellScaler->ratio;
                    if (selectedLevel > 80)
                        value *= (selectedLevel - 80) * 4.4f; // Cataclysm creatures have a way higher jump in stats than previous expansions so we use this estimated value based on combat log packet research
                }
            }
        }

        value = floor(value + 0.5f);
    }

    int32_t basePointsMinINT = static_cast<int32_t>(std::min(basePoints.at(0), basePoints.at(1)));
    int32_t basePointsMaxINT = static_cast<int32_t>(std::max(basePoints.at(0), basePoints.at(1)));
    result += QString("Calculated BasePoints (before modifiers). Min = %1, max = %2, random points = %3, SpellScalingId = %4<br>").arg(basePointsMinINT).arg(basePointsMaxINT).arg(randomPoints).arg(spellEntry->getSpellLevelsId());
}

QString const SpellEntry::PrintSpellEffectInfo(uint8_t scalingLevel, uint8_t comboPoints) const
{
    QString result;
    for (uint8_t effIndex = 0; effIndex < MAX_SPELL_EFFECTS; ++effIndex)
    {
        result += printLine;

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

        if (HasAttribute(SPELL_ATTR10_USE_SPELL_BASE_LEVEL_FOR_SCALING))
        {
            if (m_spellLevelsEntry != nullptr)
            {
                scalingLevel = m_spellLevelsEntry->baseLevel;
            }
            else
            {
                scalingLevel = 1;
            }
        }

        PrintEffectBaseValues(result, this, effIndex, scalingLevel, comboPoints);

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

        result += printLine;

        if (effectInfo->getEffectAura() == 0)
        {
            result += QString("EffectMiscValueA = %1, EffectMiscValueB = %2, EffectAmplitude = %3, Mechanic = %4 (%5)<br>")
                    .arg(effectInfo->getEffectMiscValue())
                    .arg(effectInfo->getEffectMiscValueB())
                    .arg(effectInfo->getEffectAmplitude())
                    .arg(effectInfo->getEffectMechanic())
                    .arg(sSpellWorkJson->GetSpellMechanicName(effectInfo->getEffectMechanic()));

            if (effectInfo->HasExtraInfo())
            {
                result += effectInfo->GetExtraInfo();
                result += "<br>";
            }
        }
        else
        {
            result += QString("Aura Id %1 (%2), value = %3, misc = %4, miscB = %5, periodic = %6, mechanic = %7 (%8)<br>")
                    .arg(effectInfo->getEffectAura())
                    .arg(sSpellWorkJson->GetSpellAuraTypeName(effectInfo->getEffectAura()))
                    .arg(effectInfo->getEffectBasePoints())
                    .arg(effectInfo->getEffectMiscValue())
                    .arg(effectInfo->getEffectMiscValueB())
                    .arg(effectInfo->getEffectAuraPeriod())
                    .arg(effectInfo->getEffectMechanic())
                    .arg(sSpellWorkJson->GetSpellMechanicName(effectInfo->getEffectMechanic()));

            if (effectInfo->HasExtraInfo())
            {
                result += effectInfo->GetExtraInfo();
                result += "<br>";
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

                for (const auto&[entry, spellInfo] : sDataStorage->GetSpellEntries())
                {
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
                    const bool skillAbilityFound = std::ranges::any_of(skillLineAbilities, [entry](const auto& skillAbility)
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

        // append trigger spell
        if (effectInfo->getEffectTriggerSpell() != 0)
        {
            if (const auto* triggerSpell = sDataStorage->GetSpellEntry(effectInfo->getEffectTriggerSpell()))
            {
                result += "<span style=\"color:green; font-weight: bold\">";
                result += QString("   Trigger spell (%1) %2. Chance = %3<br>")
                              .arg(triggerSpell->getId())
                                 .arg(triggerSpell->GetSpellNameRank())
                                 .arg(m_spellAuraOptionsEntry != nullptr ? m_spellAuraOptionsEntry->ProcChance : 0.0f);

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
                    result += QString("Charges - %1<br>").arg(triggerAuraOptions->ProcCharges);
                    result += printLine;

                    for (uint8_t i = 0; i <= MAX_UINT32_BITMASK_INDEX; ++i)
                    {
                        const uint32_t mask = 1U << i;
                        if ((triggerAuraOptions->ProcTypeMask & mask) != 0)
                        {
                            result += sSpellWorkJson->GetSpellProcDescription(mask);
                            result += "<br>";
                        }
                    }

                    result += printLine;
                }
            }
            else
            {
                result += QString("Trigger spell (%1) Not found, Chance = %2<br>").arg(effectInfo->getEffectTriggerSpell()).arg(m_spellAuraOptionsEntry != nullptr ? m_spellAuraOptionsEntry->ProcChance : 0.0f);
            }
        }

        if (effectInfo->getEffectChainTargets() != 0)
        {
            result += QString("EffectChainTarget = %1<br>").arg(effectInfo->getEffectChainTargets());
        }

        result += "<br>";
    }

    return result;
}

QString const SpellEntry::PrintBaseInfo(uint8_t scalingLevel) const
{
    QString spellText;

    spellText += QString("<b>ID: %1 %2</b><br>")
                     .arg(getId())
                     .arg(GetSpellNameRank());

    if (m_spellDifficultyEntry != nullptr)
    {
        spellText += printLine;
        spellText += QString("<b><i>Difficulty entries:</i></b> %1 (normal/10man), %2 (heroic/25man), %3 (10man hc), %4 (25 man hc)<br>")
                         .arg(m_spellDifficultyEntry->DifficultySpellID.at(0))
                         .arg(m_spellDifficultyEntry->DifficultySpellID.at(1))
                         .arg(m_spellDifficultyEntry->DifficultySpellID.at(2))
                         .arg(m_spellDifficultyEntry->DifficultySpellID.at(3));
    }

    spellText += printLine;

    if (!getDescription().isEmpty())
    {
        spellText += getDescription();
        spellText += "<br>";
        spellText += printLine;
    }

    spellText += QString("ToolTip: %1<br>").arg(getToolTip());
    spellText += printLine;
    spellText += QString("Category = %1, SpellIconID = %2, activeIconID = %3, SpellVisual = (%4, %5)<br>")
                     .arg(getSpellCategoriesId())
                     .arg(getSpellIconID())
                     .arg(getActiveIconID())
                     .arg(getSpellVisual1())
                     .arg(getSpellVisual2());
    spellText += QString("SpellSchoolMask = %1 (%2)<br>")
                     .arg(getSchoolMask())
                     .arg(GetFirstSchoolMaskNameStr(getSchoolMask()));

    PrintSpellClassOptions(spellText, m_spellClassOptionsEntry);
    PrintSpellCategory(spellText, m_spellCategoriesEntry);
    spellText += m_AttributesStr;
    PrintTargetRestrictions(spellText, m_spellTargetRestrictionsEntry, m_spellLevelsEntry, HasAttribute(SPELL_ATTR5_LIMIT_N));
    PrintShapeShiftingInfo(spellText, m_spellShapeshiftEntry);
    PrintSkillLinks(spellText, getId());
    PrintReagents(spellText, m_spellReagentsEntry);
    PrintSpellEquipmentInfo(spellText, m_spellEquipedItemsEntry);

    spellText += printLine;

    PrintSpellRangeInfo(spellText, m_spellRangeEntry);
    PrintSpellAuraOptions(spellText, m_spellAuraOptionsEntry);

    spellText += QString("<br>Cast speed %1, ").arg(getSpeed());

    PrintSpellCastTimeInfo(spellText, m_spellCastingTimeEntry);
    PrintSpellCooldownInfo(spellText, m_spellCooldownEntry);
    PrintSpellDurationInfo(spellText, m_spellDurationEntry);
    PrintSpellPowerInfo(spellText, m_spellPowerEntry, getPowerType());
    PrintInterruptInfo(spellText, m_spellInterruptsEntry);
    PrintSpellRestrictionsInfo(spellText, m_spellRestrictionsEntry);
    PrintSpellCastRequirements(spellText, m_spellCastingReqEntry);
    return spellText;
}

void SpellEffectEntry::GenerateExtraInfo()
{
    if (getEffectAura() != SPELL_AURA_NONE)
    {
        const auto* auraEffJsonInfo = sSpellWorkJson->GetSpellAuraEffectInfo(getEffectAura());
        if (auraEffJsonInfo != nullptr && !auraEffJsonInfo->extraDetailFormatStr.isEmpty())
        {
            m_extraInformation = auraEffJsonInfo->extraDetailFormatStr;
        }
    }
    else if (getEffect() != SPELL_EFFECT_NONE)
    {
        const auto* effectJsonInfo = sSpellWorkJson->GetSpellEffectInfo(getEffect());
        if (effectJsonInfo != nullptr && !effectJsonInfo->extraDetailFormatStr.isEmpty())
        {
            m_extraInformation = effectJsonInfo->extraDetailFormatStr;
        }
    }

    if (m_extraInformation.isEmpty())
    {
        return;
    }

    using strRepFormatData = std::pair<QString /*strToRep*/, int32_t /*effectValue*/>;

    {
        const std::array<const strRepFormatData, 2> miscValues = {{ {":MiscValue:", getEffectMiscValue() }, { ":MiscValueB:", getEffectMiscValueB() } }};
        for (const auto& [strToRep, value] : miscValues)
        {
            if (!m_extraInformation.contains(strToRep, Qt::CaseInsensitive))
            {
                continue;
            }

            m_extraInformation.replace(strToRep, QString::number(value), Qt::CaseInsensitive);
        }
    }

    {
        const std::array<const strRepFormatData, 2> areaEntryNames = {{ {":AreaEntryNameMiscVal:", getEffectMiscValue() }, { ":AreaEntryNameMiscValB:", getEffectMiscValueB() } }};
        for (const auto& [strToRep, value] : areaEntryNames)
        {
            if (!m_extraInformation.contains(strToRep, Qt::CaseInsensitive))
            {
                continue;
            }

            const auto* areaInfo = sDataStorage->GetAreaTableEntry(value);
            m_extraInformation.replace(strToRep, areaInfo != nullptr ? areaInfo->GetName().toString() : "Unknown", Qt::CaseInsensitive);
        }
    }

    {
        const std::array<const strRepFormatData, 2> unitModStat = {{ {":UnitModNameMiscVal:", getEffectMiscValue() }, { ":UnitModNameMiscValB:", getEffectMiscValueB() } }};
        for (const auto& [strToRep, value] : unitModStat)
        {
            if (!m_extraInformation.contains(strToRep, Qt::CaseInsensitive))
            {
                continue;
            }

            const auto statName = sSpellWorkJson->GetUnitModName(value);
            m_extraInformation.replace(strToRep, QString(statName.data()), Qt::CaseInsensitive);
        }
    }

    {
        const std::array<const strRepFormatData, 2> spellMod = {{ {":SpellModNameMiscVal:", getEffectMiscValue() }, { ":SpellModNameMiscValB:", getEffectMiscValueB() } }};
        for (const auto& [strToRep, value] : spellMod)
        {
            if (!m_extraInformation.contains(strToRep, Qt::CaseInsensitive))
            {
                continue;
            }

            const auto statName = sSpellWorkJson->GetSpellModName(value);
            m_extraInformation.replace(strToRep, QString(statName.data()), Qt::CaseInsensitive);
        }
    }

    {
        const std::array<const strRepFormatData, 2> factionName = {{ {":FactionNameMiscVal:", getEffectMiscValue() }, { ":FactionNameMiscValB:", getEffectMiscValueB() } }};
        for (const auto& [strToRep, value] : factionName)
        {
            if (!m_extraInformation.contains(strToRep, Qt::CaseInsensitive))
            {
                continue;
            }

            if (const auto* factionEntry = sDataStorage->GetFactionEntry(value))
            {
                m_extraInformation.replace(strToRep, factionEntry->Name, Qt::CaseInsensitive);
            }
            else
            {
                m_extraInformation.replace(strToRep, QString("<b>Cannot find entry %1 in Faction.dbc</b><br>").arg(value), Qt::CaseInsensitive);
            }
        }
    }

    {
        const std::array<const strRepFormatData, 2> combatRating = {{ {":CBRatingListMiscVal:", getEffectMiscValue() }, { ":CBRatingListMiscValB:", getEffectMiscValueB() } }};
        for (const auto& [strToRep, value] : combatRating)
        {
            if (!m_extraInformation.contains(strToRep, Qt::CaseInsensitive))
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
            m_extraInformation.replace(strToRep, ratingsStr, Qt::CaseInsensitive);
        }
    }

    {
        const std::array<const strRepFormatData, 2> screenEffect = {{ {":ScreenEffectMiscVal:", getEffectMiscValue() }, { ":ScreenEffectMiscValB:", getEffectMiscValueB() } }};
        for (const auto& [strToRep, value] : screenEffect)
        {
            if (!m_extraInformation.contains(strToRep, Qt::CaseInsensitive))
            {
                continue;
            }

            const auto* _screenEffect = sDataStorage->GetScreenEffectEntry(value);
            m_extraInformation.replace(strToRep, _screenEffect != nullptr ? _screenEffect->GetName().toString() : "unknown", Qt::CaseInsensitive);
        }
    }

    {
        const std::array<const strRepFormatData, 2> overrideSpellList = {{ {":OverrideSpellListMiscVal:", getEffectMiscValue() }, { ":OverrideSpellListMiscValB:", getEffectMiscValueB() } }};
        for (const auto& [strToRep, value] : overrideSpellList)
        {
            if (!m_extraInformation.contains(strToRep, Qt::CaseInsensitive))
            {
                continue;
            }

            const auto* spellOverride = sDataStorage->GetOverrideSpellDataEntry(value);
            if (spellOverride == nullptr)
            {
                m_extraInformation.replace(strToRep, QString("entry %1 does not exist in OverrideSpellData.dbc").arg(value));
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

                m_extraInformation.replace(strToRep, result, Qt::CaseInsensitive);
            }
        }
    }

    {
        const std::array<const strRepFormatData, 2> mechanicImmunities = {{ {":MechanicImmunitiesMiscVal:", getEffectMiscValue() }, { ":MechanicImmunitiesMiscValB:", getEffectMiscValueB() } }};
        for (const auto& [strToRep, value] : mechanicImmunities)
        {
            if (!m_extraInformation.contains(strToRep, Qt::CaseInsensitive))
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

            m_extraInformation.replace(strToRep, result, Qt::CaseInsensitive);
        }
    }

    {
        const std::array<const strRepFormatData, 2> mechanicImmunities = {{ {":MechanicImmunityMiscVal:", getEffectMiscValue() }, { ":MechanicImmunityMiscValB:", getEffectMiscValueB() } }};
        for (const auto& [strToRep, value] : mechanicImmunities)
        {
            if (!m_extraInformation.contains(strToRep, Qt::CaseInsensitive))
            {
                continue;
            }

            m_extraInformation.replace(strToRep, sSpellWorkJson->GetSpellMechanicName(value).toString(), Qt::CaseInsensitive);
        }
    }

    if (m_extraInformation.contains(":EffectItemType:", Qt::CaseInsensitive))
    {
        m_extraInformation.replace(":EffectItemType:", QString::number(getEffectItemType()), Qt::CaseInsensitive);
    }

    if (m_extraInformation.contains(":EffectItemTypeName:", Qt::CaseInsensitive))
    {
        QString itemName;
        if (getEffectItemType() == 0)
        {
            itemName = "None";
        }
        else
        {
            const auto* itemEntry = sDataStorage->GetItemEntry(getEffectItemType());
            itemName = itemEntry != nullptr ? itemEntry->GetName() : "Unknown";
        }

        m_extraInformation.replace(":EffectItemTypeName:", itemName, Qt::CaseInsensitive);
    }

    if (getEffect() == SPELL_EFFECT_SUMMON || getEffect() == SPELL_EFFECT_SUMMON_PET)
    {
        auto GenSummonPropertyId = [&]
        {
            if (!m_extraInformation.contains(":SummonCategoryId:", Qt::CaseInsensitive))
            {
                return;
            }

            if (const auto* summonProp = sDataStorage->GetSummonPropertiesEntry(getEffectMiscValueB()))
            {
                m_extraInformation.replace(":SummonCategoryId:", QString::number(summonProp->Id), Qt::CaseInsensitive);
            }
            else
            {
                m_extraInformation.replace(":SummonCategoryId:", "0", Qt::CaseInsensitive);
            }

        };

        auto GenSummonPropertyName = [&]
        {
            if (!m_extraInformation.contains(":SummonCategoryName:", Qt::CaseInsensitive))
            {
                return;
            }

            if (const auto* summonProp = sDataStorage->GetSummonPropertiesEntry(getEffectMiscValueB()))
            {
                m_extraInformation.replace(":SummonCategoryName:", sSpellWorkJson->GetSummonCategoryName(summonProp->CategoryId).toString(), Qt::CaseInsensitive);
            }
            else
            {
                m_extraInformation.replace(":SummonCategoryName:", sSpellWorkJson->GetSummonCategoryName(0).toString(), Qt::CaseInsensitive);
            }
        };

        auto GenSummonTypeNameId = [&]
        {
            if (!m_extraInformation.contains(":SummonPropTitleId:", Qt::CaseInsensitive))
            {
                return;
            }

            if (const auto* summonProp = sDataStorage->GetSummonPropertiesEntry(getEffectMiscValueB()))
            {
                m_extraInformation.replace(":SummonPropTitleId:", QString::number(summonProp->SummonTypeNameId), Qt::CaseInsensitive);
            }
            else
            {
                m_extraInformation.replace(":SummonPropTitleId:", "0", Qt::CaseInsensitive);
            }
        };

        auto GenSummonTypeName = [&]
        {
            if (!m_extraInformation.contains(":SummonPropTitleName:", Qt::CaseInsensitive))
            {
                return;
            }

            if (const auto* summonProp = sDataStorage->GetSummonPropertiesEntry(getEffectMiscValueB()))
            {
                m_extraInformation.replace(":SummonPropTitleName:", sSpellWorkJson->GetSummonTypeName(summonProp->SummonTypeNameId).toString(), Qt::CaseInsensitive);
            }
            else
            {
                m_extraInformation.replace(":SummonPropTitleName:", sSpellWorkJson->GetSummonTypeName(0).toString(), Qt::CaseInsensitive);
            }
        };

        auto GenSummonFlags = [&]
        {
            if (!m_extraInformation.contains(":SummonPropFlags:", Qt::CaseInsensitive))
            {
                return;
            }

            if (const auto* summonProp = sDataStorage->GetSummonPropertiesEntry(getEffectMiscValueB()))
            {
                m_extraInformation.replace(":SummonPropFlags:", QString::number(summonProp->Flags), Qt::CaseInsensitive);
            }
            else
            {
                m_extraInformation.replace(":SummonPropFlags:", "0", Qt::CaseInsensitive);
            }
        };

        auto GenSummonFlagNames = [&]
        {
            if (!m_extraInformation.contains(":SummonPropFlagNames:", Qt::CaseInsensitive))
            {
                return;
            }

            const auto* summonProp = sDataStorage->GetSummonPropertiesEntry(getEffectMiscValueB());
            QString result;
            if (summonProp != nullptr && summonProp->Flags != 0)
            {
                for (uint8_t id = 1; id <= MAX_UINT32_BITMASK_INDEX; ++id)
                {
                    const uint32_t flag = 1U << (id - 1);
                    if ((summonProp->Flags & flag) == 0)
                    {
                        continue;
                    }

                    if (!result.isEmpty())
                    {
                        result += ", ";
                    }

                    result += sSpellWorkJson->GetSummonPropertyFlagName(flag);
                }
            }

            if (result.isEmpty())
            {
                result = "None";
            }
            m_extraInformation.replace(":SummonPropFlagNames:", result, Qt::CaseInsensitive);
        };

        GenSummonPropertyId();
        GenSummonPropertyName();
        GenSummonTypeNameId();
        GenSummonTypeName();
        GenSummonFlags();
        GenSummonFlagNames();
    }
}
