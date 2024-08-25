#include "DBC/DBCStructures.hpp"
#include "DBCStores.hpp"
#include "JsonData/JsonData.hpp"
#include <QDebug>

constexpr char const* line = "==============================================<br>";

// Returns first found school mask's name
inline QString GetFirstSchoolMaskNameStr(uint32_t mask)
{
    QString result;
    for (uint8_t i = 0; i < MAX_SPELL_SCHOOL; ++i)
    {
        const uint32_t schoolMask = (1 << i);
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
    for (uint8_t i = 0; i < MAX_UINT32_BITMASK_INDEX; ++i)
    {
        if (((1 << i) & stancesNames) != 0)
        {
            if (!formNames.isEmpty())
            {
                formNames += ", ";
            }

            formNames += sSpellWorkJson->GetShapeshiftFormName(i);
        }
    }

    return formNames;
}

inline void PrintSpellClassOptions(QString& result, uint32_t classOptionsEntry)
{
    if (const auto* spellClassOptions = GetDBCEntry(classOptionsEntry, sDBCStores->m_SpellClassOptions))
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
    if (const auto* spellCategory = GetDBCEntry(category_id, sDBCStores->m_SpellCategories))
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
        if (const auto* spellCategoryInfo = GetDBCEntry(spellCategory->Id, sDBCStores->m_SpellCategoryEntries))
        {
            result += QString(" (%1)").arg(spellCategoryInfo->Name.c_str());
        }

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

inline void PrintAttributes(QString& result, const SpellEntry* spell)
{
    if (spell != nullptr && std::any_of(spell->Attributes.begin(), spell->Attributes.end(), [](uint32_t attr){ return attr != 0; }))
    {
        result += line;
        for (uint8_t attribute = 0; attribute < MAX_SPELL_ATTRIBUTES; ++attribute)
        {
            const auto& attributeMask = spell->Attributes[attribute];
            if (spell->Attributes[attribute] != 0)
            {
                QString attributeStr;
                for (uint8_t id = 0; id <= MAX_UINT32_BITMASK_INDEX; ++id)
                {
                    const uint32_t mask = 1 << id;
                    if ((mask & attributeMask) != 0)
                    {
                        if (!attributeStr.isEmpty())
                        {
                            attributeStr += ", ";
                        }

                        attributeStr += sSpellWorkJson->GetSpellAttributeName(attribute, mask);
                    }
                }
                result += QString("Attributes%1: %2<br><br>")
                              .arg(attribute)
                              .arg(attributeStr);
            }

        }
    }
}

inline void PrintTargetRestrictions(QString& result, uint32_t SpellTargetRestrictionsId, uint32_t SpellLevelsId, bool isSingleTarget)
{
    const auto* spellRestrictionsEntry = GetDBCEntry(SpellTargetRestrictionsId, sDBCStores->m_SpellTargetRestrictions);
    if (spellRestrictionsEntry != nullptr)
    {
        if (spellRestrictionsEntry->Targets != 0)
        {
            result += QString("Targets Mask = [0] 0x%1").arg(spellRestrictionsEntry->Targets, 8, 16, QLatin1Char('0')) + "(";

            QString targets;
            for (uint8_t i = 0; i < MAX_UINT32_BITMASK_INDEX; ++i)
            {
                const uint32_t flag = 1 << i;
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
    }

    if (const auto* spellLevel = GetDBCEntry(SpellLevelsId, sDBCStores->m_SpellLevelsEntries))
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
    if (const auto* shapeshiftingEntry = GetDBCEntry(SpellShapeshiftId, sDBCStores->m_SpellShapeshiftEntries))
    {
        if (shapeshiftingEntry->Stances != 0)
        {
            result += QString("Stances: %1<br>").arg(GetStancesNames(shapeshiftingEntry->Stances));
        }

        if (shapeshiftingEntry->StancesNot != 0)
        {
            result += QString("Stances Not: %1<br>").arg(GetStancesNames(shapeshiftingEntry->StancesNot));
        }
    }
}

inline void PrintSkillLinks(QString& result, uint32_t spellId)
{
    SkillLineEntry const* skillLine = nullptr;
    SkillLineAbilityEntry const* skillLineAbility = nullptr;

    for (const auto& itr : sDBCStores->m_SkillLineEntries)
    {
        bool stop = false;
        for (const auto& itr2 : sDBCStores->m_SkillLineAbilityEntries)
        {
            if (itr.first == itr2.second.skillId && itr2.second.spellId == spellId)
            {
                skillLine = (&itr.second);
                skillLineAbility = (&itr2.second);
                stop = true;
                break;
            }
        }

        if (stop)
        {
            break;
        }
    }

    if (skillLine != nullptr && skillLineAbility != nullptr)
    {
        result += QString("Skill (Id %1) \"%2\"<br>").arg(skillLineAbility->skillId).arg(skillLine->name.c_str());
        result += QString("    ReqSkillValue %1<br>").arg(skillLineAbility->req_skill_value);
        result += QString(", Forward Spell = %1, MinMaxValue (%2, %3)<br>")
                      .arg(skillLineAbility->forward_spellid)
                      .arg(skillLineAbility->min_value)
                      .arg(skillLineAbility->max_value);

        result += QString(", CharacterPoints (%1, %2)<br>")
                      .arg(skillLineAbility->character_points[0])
                      .arg(skillLineAbility->character_points[1]);

        result += line;
    }
}

inline void PrintReagents(QString& result, uint32_t SpellReagentsId)
{
    if (const auto* spellReagent = GetDBCEntry(SpellReagentsId, sDBCStores->m_SpellReagentsEntries))
    {
        if (std::any_of(spellReagent->Reagent.begin(), spellReagent->Reagent.end(), [](int32_t reagent){ return reagent != 0; }))
        {
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
    }
}

inline void PrintSpellEquipmentInfo(QString& result, uint32_t SpellEquippedItemsId)
{
    if (const auto* spellEquipedItems = GetDBCEntry(SpellEquippedItemsId, sDBCStores->m_SpellEquippedItemsEntries))
    {
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
                for (uint8_t i = 0; i < MAX_UINT32_BITMASK_INDEX; ++i)
                {
                    if ((spellEquipedItems->EquippedItemClass & (1 << i)) != 0)
                    {
                        if (!subclassNames.isEmpty())
                        {
                            subclassNames += ", ";
                        }

                        subclassNames += sSpellWorkJson->GetItemSubclassWeaponName(i);
                    }
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
                for (uint8_t i = 0; i < MAX_UINT32_BITMASK_INDEX; ++i)
                {
                    if ((spellEquipedItems->EquippedItemSubClassMask & (1 << i)) != 0)
                    {
                        if (!subclassNames.isEmpty())
                        {
                            subclassNames += ", ";
                        }

                        subclassNames += sSpellWorkJson->GetItemSubclassArmorName(i);
                    }
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
                for (uint8_t i = 0; i < MAX_UINT32_BITMASK_INDEX; ++i)
                {
                    if ((spellEquipedItems->EquippedItemSubClassMask & (1 << i)) != 0)
                    {
                        if (!subclassNames.isEmpty())
                        {
                            subclassNames += ", ";
                        }

                        subclassNames += sSpellWorkJson->GetItemSubclassJunkName(i);
                    }
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
            for (uint8_t i = 0; i < MAX_UINT32_BITMASK_INDEX; ++i)
            {
                if ((spellEquipedItems->EquippedItemInventoryTypeMask & (1 << i)) != 0)
                {
                    if (!inventoryNames.isEmpty())
                    {
                        inventoryNames += ", ";
                    }

                    inventoryNames += sSpellWorkJson->GetItemInventoryName(i);
                }
            }

            if (!inventoryNames.isEmpty())
            {
                result += QString("    InventoryType mask = 0x%1 (%2)<br>").arg(spellEquipedItems->EquippedItemInventoryTypeMask, 8, 16, QLatin1Char('0')).arg(inventoryNames);
            }
        }
    }
}

inline void PrintSpellRangeInfo(QString& result, uint32_t rangeIndex)
{
    result += "<br>";
    if (const auto* spellRange = GetDBCEntry(rangeIndex, sDBCStores->m_SpellRangeEntries))
    {
        result += QString("SpellRange: (Id %1) \"%2\"<br>").arg(spellRange->ID).arg(spellRange->Name.c_str());
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
    const auto* spellAuraOptionEntry = GetDBCEntry(SpellAuraOptionsId, sDBCStores->m_SpellAuraOptionsEntries);
    if (spellAuraOptionEntry != nullptr)
    {
        result += QString("Stackable up to %1 times<br>").arg(spellAuraOptionEntry->StackAmount);

        if (spellAuraOptionEntry->procFlags != 0)
        {
            result += "<br>";
            result += QString("Proc flag 0x%1, chance = %2, charges - %3<br>")
                             .arg(spellAuraOptionEntry->procFlags, 8, 16, QLatin1Char('0'))
                             .arg(spellAuraOptionEntry->procChance)
                             .arg(spellAuraOptionEntry->procCharges);

            QString procNames;

            for (uint8_t i = 0; i < MAX_UINT32_BITMASK_INDEX; ++i)
            {
                const uint32_t mask = 1 << i;
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
}

inline void PrintSpellCastTimeInfo(QString& result, uint32_t CastingTimeIndex, float speed)
{
    result += QString("<br>Cast speed %1, ").arg(speed);
    if (const auto* castTimeEntry = GetDBCEntry(CastingTimeIndex, sDBCStores->m_SpellCastTimesEntries))
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
    if (const auto* spellCooldownEntry = GetDBCEntry(SpellCooldownsId, sDBCStores->m_SpellCooldownsEntries))
    {
        if (spellCooldownEntry->RecoveryTime != 0 || spellCooldownEntry->CategoryRecoveryTime != 0 || spellCooldownEntry->StartRecoveryTime != 0)
        {
            result += QString("RecoveryTime: %1 ms, CategoryRecoveryTime: %2 ms<br>").arg(spellCooldownEntry->RecoveryTime).arg(spellCooldownEntry->CategoryRecoveryTime);
            result += QString("StartRecoveryCategory = %1, StartRecoveryTime = %2 ms<br>").arg(spellCooldownEntry->CategoryRecoveryTime).arg(spellCooldownEntry->StartRecoveryTime);
        }
    }
}

inline void PrintSpellDurationInfo(QString& result, uint32_t DurationIndex)
{
    if (const auto* spellDurationEntry = GetDBCEntry(DurationIndex, sDBCStores->m_SpellDurationEntries))
    {
        result += QString("Duration: ID (%1) %2 ms, %3 ms, %4 ms<br>")
                      .arg(spellDurationEntry->ID)
                      .arg(spellDurationEntry->Duration[0])
                      .arg(spellDurationEntry->Duration[1])
                      .arg(spellDurationEntry->Duration[2]);
    }
}

inline void PrintSpellPowerInfo(QString& result, uint32_t SpellPowerId, int8_t powerType)
{
    const auto* spellPowerEntry = GetDBCEntry(SpellPowerId, sDBCStores->m_SpellPowerEntries);
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

inline void PrintInterruptInfo(QString& result, uint32_t SpellInterruptsId)
{
    result += "<br>";
    uint32_t interruptFlags = 0;
    uint32_t auraInterruptFlags = 0;
    uint32_t channelInterruptFlags = 0;
    if (const auto* spellInterruptEntry = GetDBCEntry(SpellInterruptsId, sDBCStores->m_SpellInterruptsEntries))
    {
        interruptFlags = spellInterruptEntry->InterruptFlags;
        auraInterruptFlags = spellInterruptEntry->AuraInterruptFlags;
        channelInterruptFlags = spellInterruptEntry->ChannelInterruptFlags;
    }

    QString interruptFlagsStr;
    for (uint8_t i = 0; i < MAX_UINT32_BITMASK_INDEX; ++i)
    {
        const uint32_t flag = 1 << i;
        if ((interruptFlags & flag) != 0)
        {
            if (!interruptFlagsStr.isEmpty())
            {
                interruptFlagsStr += ", ";
            }

            interruptFlagsStr += sSpellWorkJson->GetSpellInterruptFlagName(flag);
        }
    }

    QString auraFlagsStr;
    for (uint8_t i = 0; i < MAX_UINT32_BITMASK_INDEX; ++i)
    {
        const uint32_t flag = 1 << i;
        if ((auraInterruptFlags & flag) != 0)
        {
            if (!auraFlagsStr.isEmpty())
            {
                auraFlagsStr += ", ";
            }

            auraFlagsStr += sSpellWorkJson->GetAuraInterruptFlagName(flag);
        }
    }

    QString channelFlagsStr;
    for (uint8_t i = 0; i < MAX_UINT32_BITMASK_INDEX; ++i)
    {
        const uint32_t flag = 1 << i;
        if ((channelInterruptFlags & flag) != 0)
        {
            if (!channelFlagsStr.isEmpty())
            {
                channelFlagsStr += ", ";
            }

            channelFlagsStr += sSpellWorkJson->GetAuraInterruptFlagName(flag);
        }
    }

    result += QString("Spell interrupt flags: 0x%1 (%2)<br>").arg(interruptFlags, 8, 16, QLatin1Char('0')).arg(interruptFlagsStr);
    result += QString("Aura interrupt flags: 0x%1 (%2)<br>").arg(auraInterruptFlags, 8, 16, QLatin1Char('0')).arg(auraFlagsStr);
    result += QString("Channel interrupt flags 0x%1 (%2)<br>").arg(channelInterruptFlags, 8, 16, QLatin1Char('0')).arg(channelFlagsStr);
}

inline void PrintSpellRestrictionsInfo(QString& result, uint32_t SpellAuraRestrictionsId)
{
    const auto* spellRestrictions = GetDBCEntry(SpellAuraRestrictionsId, sDBCStores->m_SpellAuraRestrictionsEntries);
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
        const auto* auraSpell = GetDBCEntry(spellRestrictions->casterAuraSpell, sDBCStores->m_spellEntries);
        result += QString("  Caster Aura Spell (%1) %2<br>")
                      .arg(spellRestrictions->casterAuraSpell)
                      .arg(auraSpell != nullptr ? auraSpell->SpellName.c_str() : "unknown");
    }

    if (spellRestrictions->targetAuraSpell != 0)
    {
        const auto* auraSpell = GetDBCEntry(spellRestrictions->targetAuraSpell, sDBCStores->m_spellEntries);
        result += QString("  Target Aura Spell (%1) %2<br>")
                      .arg(spellRestrictions->targetAuraSpell)
                      .arg(auraSpell != nullptr ? auraSpell->SpellName.c_str() : "unknown");
    }

    if (spellRestrictions->excludeCasterAuraSpell != 0)
    {
        const auto* auraSpell = GetDBCEntry(spellRestrictions->excludeCasterAuraSpell, sDBCStores->m_spellEntries);
        result += QString("  Ex Caster Aura Spell (%1) %2<br>")
                      .arg(spellRestrictions->excludeCasterAuraSpell)
                      .arg(auraSpell != nullptr ? auraSpell->SpellName.c_str() : "unknown");
    }

    if (spellRestrictions->excludeTargetAuraSpell != 0)
    {
        const auto* auraSpell = GetDBCEntry(spellRestrictions->excludeTargetAuraSpell, sDBCStores->m_spellEntries);
        result += QString("  Ex Target Aura Spell (%1) %2<br>")
                      .arg(spellRestrictions->excludeTargetAuraSpell)
                      .arg(auraSpell != nullptr ? auraSpell->SpellName.c_str() : "unknown");
    }
}

inline void PrintSpellCastRequirements(QString& result, uint32_t SpellCastingRequirementsId)
{
    if (const auto* spellCastReqEntry = GetDBCEntry(SpellCastingRequirementsId, sDBCStores->m_SpellCastingRequirementsEntries))
    {
        if (const auto* groupEntry = GetDBCEntry(spellCastReqEntry->AreaGroupId, sDBCStores->m_AreaGroupEntries))
        {
            result += "<br>";
            result += "<b>Allowed areas:</b><br>";

            uint32_t groupId = 0;
            do
            {
                for (uint32_t const areaId : groupEntry->AreaId)
                {
                    if (const auto* areaEntry = GetDBCEntry(areaId, sDBCStores->m_AreaTableEntries))
                    {
                        result += QString("%1 - %2(MapId: %3)<br>").arg(areaId).arg(areaEntry->area_name.c_str()).arg(areaEntry->mapid);
                    }
                }

                groupId = groupEntry->nextGroup;
            }
            while ((groupEntry = GetDBCEntry(groupId, sDBCStores->m_AreaGroupEntries)) != nullptr);

            result += "<br>";
        }

        result += QString("Requires Spell Focus %1<br>").arg(spellCastReqEntry->RequiresSpellFocus);
    }
}

QString const SpellEntry::PrintSpellEffectInfo(uint32_t scalingLevel) const
{
    QString result;
    for (uint32_t effIndex = 0; effIndex < MAX_SPELL_EFFECTS; ++effIndex)
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
                      .arg(effectInfo->Effect)
                      .arg(sSpellWorkJson->GetSpellEffectName(effectInfo->Effect));

        const auto* scalingInfo = GetDBCEntry(SpellScalingId, sDBCStores->m_SpellScalingEntries);
        if (scalingInfo != nullptr && scalingInfo->Coefficient[effIndex] != 0.0f &&  scalingInfo->ScalingClass != 0)
        {
            uint32_t const selectedLevel = scalingLevel;

            uint32_t gtEntryId = static_cast<uint32_t>((scalingInfo->ScalingClass != -1 ? scalingInfo->ScalingClass - 1 : 11) * 100) + selectedLevel - 1;
            const auto* gtEntry = GetDBCEntry(gtEntryId, sDBCStores->m_GtSpellScalingEntries);
            float gtMultiplier = gtEntry != nullptr ? gtEntry->value : 0.0f;

            if (scalingInfo->CastTimeMax > 0 && scalingInfo->CastTimeMaxLevel > selectedLevel)
            {
                gtMultiplier *= static_cast<float>(scalingInfo->CastTimeMin + (selectedLevel - 1) * (scalingInfo->CastTimeMax - scalingInfo->CastTimeMin) / (scalingInfo->CastTimeMaxLevel - 1)) / static_cast<float>(scalingInfo->CastTimeMax);
            }

            if (scalingInfo->CoefLevelBase > selectedLevel)
                gtMultiplier *= (1.0f -  scalingInfo->CoefBase) * (float)(selectedLevel - 1) / (float)(scalingInfo->CoefLevelBase - 1) + scalingInfo->CoefBase;

            if (scalingInfo->RandomMultiplier[effIndex] != 0.0f)
            {
                float avg = scalingInfo->Coefficient[effIndex] * gtMultiplier;
                float delta = scalingInfo->RandomMultiplier[effIndex] * scalingInfo->Coefficient[effIndex] * gtMultiplier * 0.5;
                result += QString("BasePoints = %1 to %2").arg(avg - delta).arg(avg + delta);
            }
            else
            {
                result += QString("AveragePoints = %1<br>").arg(scalingInfo->Coefficient[effIndex] * gtMultiplier);
            }

            if (scalingInfo->OtherMultiplier[effIndex] != 0.0f)
            {
                result += QString(" + combo *  %1").arg(scalingInfo->OtherMultiplier[effIndex] * gtMultiplier);
            }
            else
            {
                result += QString(" + combo *  %1").arg(effectInfo->EffectPointsPerResource);
            }
        }
        else
        {
            result += QString("BasePoints = %1").arg(effectInfo->EffectBasePoints + ((effectInfo->EffectDieSides == 0) ? 0 : 1));

            if (effectInfo->EffectRealPointsPerLevel != 0)
            {
                result += QString(" + Level * %1").arg(effectInfo->EffectRealPointsPerLevel);
            }

            if (effectInfo->EffectDieSides > 1)
            {
                if (effectInfo->EffectRealPointsPerLevel != 0)
                {
                    result += QString(" to %1 + lvl * %2").arg(effectInfo->EffectBasePoints + effectInfo->EffectDieSides, effectInfo->EffectRealPointsPerLevel);
                }
                else
                {
                    result += QString(" to %1").arg(effectInfo->EffectBasePoints + effectInfo->EffectDieSides);
                }
            }

            if (effectInfo->EffectPointsPerResource > 0)
            {
                result += QString(" + combo * %1").arg(effectInfo->EffectPointsPerResource);
            }
        }

        if (effectInfo->EffectBonusCoefficient != 1.0f)
        {
            result += QString(" x %1").arg(effectInfo->EffectBonusCoefficient);
        }

        if (effectInfo->EffectAmplitude > 0.0f)
        {
            result += QString("  Multiple = %1").arg(effectInfo->EffectAmplitude);
        }

        result += "<br>";

        result += QString("Targets: (%1, %2) (%3, %4)<br>")
                      .arg(effectInfo->EffectImplicitTargetA)
                      .arg(effectInfo->EffectImplicitTargetB)
                      .arg(sSpellWorkJson->GetSpellTargetName(effectInfo->EffectImplicitTargetA))
                      .arg(sSpellWorkJson->GetSpellTargetName(effectInfo->EffectImplicitTargetB));

        result += line;

        if (effectInfo->EffectAura == 0)
        {
            result += QString("EffectMiscValueA = %1, EffectMiscValueB = %2, EffectAmplitude = %3<br>")
                          .arg(effectInfo->EffectMiscValue)
                          .arg(effectInfo->EffectMiscValueB)
                          .arg(effectInfo->EffectAmplitude);

            switch(effectInfo->Effect)
            {
            case SPELL_EFFECT_SUMMON:
            {
                break;
            }
            case SPELL_EFFECT_BIND:
            {
                const auto* areaInfo = GetDBCEntry(static_cast<uint32_t>(effectInfo->EffectMiscValue), sDBCStores->m_AreaTableEntries);
                result += QString("<span style=\"color:green\">Bind zone: %1</span><br>").arg(areaInfo != nullptr ? areaInfo->area_name.c_str() : "unknown");
                break;
            }
            default:
                break;
            }
        }
        else
        {
            result += QString("Aura Id %1 (%2), value = %3, misc = %4")
                          .arg(effectInfo->EffectAura)
                          .arg(sSpellWorkJson->GetSpellAuraTypeName(effectInfo->EffectAura))
                          .arg(effectInfo->EffectBasePoints)
                          .arg(effectInfo->EffectMiscValue);

            switch (effectInfo->EffectAura)
            {
            case SPELL_AURA_MOD_STAT:
            {
                result += QString(" (%1)").arg(sSpellWorkJson->GetUnitModName(effectInfo->EffectMiscValue));
                break;
            }
            case SPELL_AURA_ADD_FLAT_MODIFIER:
            case SPELL_AURA_ADD_PCT_MODIFIER:
            {
                result += QString(" (%1)").arg(sSpellWorkJson->GetSpellModName(effectInfo->EffectMiscValue));
                break;
            }
            // todo: more cases
            default:
                break;
            }

            result += QString(", miscB = %1").arg(effectInfo->EffectMiscValueB);
            result += QString(", periodic = %1<br>").arg(effectInfo->EffectAuraPeriod);

            switch (effectInfo->EffectAura)
            {
            case SPELL_AURA_OVERRIDE_SPELLS:
            {
                OverrideSpellDataEntry const* spellOverride = GetDBCEntry(effectInfo->EffectMiscValue, sDBCStores->m_OverrideSpellDataEntries);
                if (spellOverride == nullptr)
                {
                    result += QString("<b>Cannot find entry %1 in OverrideSpellData.dbc</b><br>").arg(effectInfo->EffectMiscValue);
                }
                else
                {
                    result += "<br>";
                    result += "<span style=\"color:red\"><b>Overriding Spells";
                    if (!spellOverride->SpellBarName.empty())
                    {
                        result += " ";
                        result += spellOverride->SpellBarName.c_str();
                    }
                    result += ":</b></span><br>";

                    for (uint8_t i = 0; i < MAX_OVERRIDE_SPELL; ++i)
                    {
                        if (spellOverride->spellId[i] != 0)
                        {
                            result += "<span style=\"color: blue\">\t - ";
                            result += QString::number(spellOverride->spellId[i]);

                            const SpellEntry* overrideSpell = GetDBCEntry(spellOverride->spellId[i], sDBCStores->m_spellEntries);
                            result += overrideSpell != nullptr ? overrideSpell->SpellName.c_str() : "unknown";
                            result += "</span><br>";
                        }
                    }
                    result += "<br>";
                }
                break;
            }
            case SPELL_AURA_SCREEN_EFFECT:
            {
                result += "<span style=\"color:green\"> ScreenEffect: ";
                const ScreenEffectEntry* screenEffect = GetDBCEntry(effectInfo->EffectMiscValue, sDBCStores->m_ScreenEffectEntries);
                result += screenEffect != nullptr ? screenEffect->Name.c_str() : "unknown";
                result += "</span><br>";
                break;
            }
            case SPELL_AURA_MOD_RATING:
            case SPELL_AURA_MOD_RATING_FROM_STAT:
            {
                QString ratingsStr;
                for (uint8_t ratingId = 0; ratingId < MAX_UINT32_BITMASK_INDEX; ++ratingId)
                {
                    const uint32_t mask = 1 << ratingId;
                    if ((effectInfo->EffectMiscValue & mask) != 0)
                    {
                        if (!ratingsStr.isEmpty())
                        {
                            ratingsStr += ", ";
                        }

                        ratingsStr += sSpellWorkJson->GetCombatRatingName(ratingId);
                    }
                }

                if (!ratingsStr.isEmpty())
                {
                    result += "Effected combat ratings: <span style=\"color:orange\">" + ratingsStr + "</span><br>";
                }
                break;
            }
            case SPELL_AURA_MOD_FACTION:
            {
                result += "Effected faction: " + QString::number(effectInfo->EffectMiscValue);
                if (const auto* factionEntry = GetDBCEntry(effectInfo->EffectMiscValue, sDBCStores->m_FactionEntries))
                {
                    result += QString("\"%1\"").arg(factionEntry->Name.c_str());
                }
                result += "<br>";
                break;
            }
            default:
                break;
            }
        }

        if (const auto* spellClassOptions = GetDBCEntry(SpellClassOptionsId, sDBCStores->m_SpellClassOptions))
        {
            if (spellClassOptions != nullptr && (effectInfo->EffectSpellClassMask[0] != 0 || effectInfo->EffectSpellClassMask[1] != 0 || effectInfo->EffectSpellClassMask[2] != 0))
            {
                result += QString("SpellClassMask = 0x%1 0x%2 0x%3<br>")
                              .arg(effectInfo->EffectSpellClassMask[0], 8, 16, QLatin1Char('0'))
                              .arg(effectInfo->EffectSpellClassMask[1], 8, 16, QLatin1Char('0'))
                              .arg(effectInfo->EffectSpellClassMask[2], 8, 16, QLatin1Char('0'));

                for (const auto&[entry, spellInfo] : sDBCStores->m_spellEntries)
                {
                    const SpellClassOptionsEntry* pSpellClassOptions = GetDBCEntry(spellInfo.SpellClassOptionsId, sDBCStores->m_SpellClassOptions);
                    if (pSpellClassOptions == nullptr || pSpellClassOptions->SpellFamilyName != spellClassOptions->SpellFamilyName)
                    {
                        continue;
                    }

                    {
                        bool hasFamilyFlag = false;
                        for (uint8_t i = 0; i < 3; ++i)
                        {
                            if (spellClassOptions->SpellFamilyFlags[i] & pSpellClassOptions->SpellFamilyFlags[i])
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

                    uint32_t skillId = 0;
                    for (const auto& skillItr : sDBCStores->m_SkillLineAbilityEntries)
                    {
                        if (skillItr.second.spellId == entry)
                        {
                            skillId = skillItr.second.skillId;
                            break;
                        }
                    }

                    result += (skillId > 0 ? "<span style=\"color:green\">\t+" : "<span style=\"color:red\">\t-") + QString("%1 - %2</span><br>").arg(entry).arg(spellInfo.SpellName.c_str());
                    result += "</span>";
                }
            }
        }

        if (effectInfo->EffectRadiusIndex != 0)
        {
            if (const auto* spellRadius = GetDBCEntry(effectInfo->EffectRadiusIndex, sDBCStores->m_SpellRadiusEntries))
            {
                result += QString("Min radius: %1, max radius: %2<br>").arg(spellRadius->RadiusMin).arg(spellRadius->RadiusMax);
            }
        }

        const auto* spellAuraOptionEntry = GetDBCEntry(SpellAuraOptionsId, sDBCStores->m_SpellAuraOptionsEntries);

        // append trigger spell
        if (effectInfo->EffectTriggerSpell != 0)
        {
            if (const auto* triggerSpell = GetDBCEntry(effectInfo->EffectTriggerSpell, sDBCStores->m_spellEntries))
            {
                result += "<span style=\"color:green; font-weight: bold\">";
                result += QString("   Trigger spell (%1) %2. Chance = %3<br>")
                                 .arg(triggerSpell->Id)
                                 .arg(triggerSpell->GetSpellNameRank().c_str())
                                 .arg(spellAuraOptionEntry != nullptr ? spellAuraOptionEntry->procChance : 0.0f);

                if (!triggerSpell->Description.empty())
                {
                    result += QString("   Description: %1<br>").arg(triggerSpell->Description.c_str());
                }

                if (!triggerSpell->ToolTip.empty())
                {
                    result += QString("ToolTip: %1<br>").arg(triggerSpell->ToolTip.c_str());
                }

                result += "</span>";

                if (const auto* triggerAuraOptions = GetDBCEntry(triggerSpell->SpellAuraOptionsId, sDBCStores->m_SpellAuraOptionsEntries))
                {
                    result += QString("Charges - %1<br>").arg(triggerAuraOptions->procCharges);
                    result += line;

                    for (uint8_t i = 0; i < MAX_UINT32_BITMASK_INDEX; ++i)
                    {
                        const uint32_t mask = 1 << i;
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
                result += QString("Trigger spell (%1) Not found, Chance = %2<br>").arg(effectInfo->EffectTriggerSpell).arg(spellAuraOptionEntry != nullptr ? spellAuraOptionEntry->procChance : 0.0f);
            }
        }

        if (effectInfo->EffectChainTargets != 0)
        {
            result += QString("EffectChainTarget = %1<br>").arg(effectInfo->EffectChainTargets);
        }

        if (effectInfo->EffectItemType != 0)
        {
            result += QString("EffectItemType = %1<br>").arg(effectInfo->EffectItemType);
        }

        if (effectInfo->EffectMechanic != MECHANIC_NONE)
        {
            result += QString("Effect Mechanic = %1 (%2)<br>")
                          .arg(effectInfo->EffectMechanic)
                          .arg(sSpellWorkJson->GetSpellMechanicName(effectInfo->EffectMechanic));
        }

        result += "<br>";
    }

    return result;
}

QString const SpellEntry::PrintBaseInfo(uint32_t scalingLevel) const
{
    QString spellText;
    spellText += QString("<b>ID: %1 %2</b><br>").arg(Id).arg(GetSpellNameRank().c_str());
    spellText += line;

    if (!Description.empty())
    {
        spellText += Description.c_str();
        spellText += "<br>";
        spellText += line;
    }

    spellText += QString("ToolTip: %1<br>").arg(ToolTip.c_str());
    spellText += line;
    spellText += QString("Category = %1, SpellIconID = %2, activeIconID = %3, SpellVisual = (%4, %5)<br>")
                     .arg(SpellCategoriesId)
                     .arg(SpellIconID)
                     .arg(activeIconID)
                     .arg(SpellVisual1)
                     .arg(SpellVisual2);
    spellText += QString("SpellSchoolMask = %1 (%2)<br>")
                     .arg(SchoolMask)
                     .arg(GetFirstSchoolMaskNameStr(SchoolMask));

    PrintSpellClassOptions(spellText, SpellClassOptionsId);
    PrintSpellCategory(spellText, SpellCategoriesId);
    PrintAttributes(spellText, this);
    PrintTargetRestrictions(spellText, SpellTargetRestrictionsId, SpellLevelsId, (Attributes[5] & SPELL_ATTR5_LIMIT_N) != 0);
    PrintShapeShiftingInfo(spellText, SpellShapeshiftId);
    PrintSkillLinks(spellText, Id);
    PrintReagents(spellText, SpellReagentsId);
    PrintSpellEquipmentInfo(spellText, SpellEquippedItemsId);

    spellText += line;

    PrintSpellRangeInfo(spellText, rangeIndex);
    PrintSpellAuraOptions(spellText, SpellAuraOptionsId);
    PrintSpellCastTimeInfo(spellText, CastingTimeIndex, speed);
    PrintSpellCooldownInfo(spellText, SpellCooldownsId);
    PrintSpellDurationInfo(spellText, DurationIndex);
    PrintSpellPowerInfo(spellText, SpellPowerId, powerType);
    PrintInterruptInfo(spellText, SpellInterruptsId);
    PrintSpellRestrictionsInfo(spellText, SpellAuraRestrictionsId);
    PrintSpellCastRequirements(spellText, SpellCastingRequirementsId);
    return spellText;
}
