// Qt
#include <QDebug>
#include <QTableWidget>
#include <QDate>
// project
#include "ValueComparition.hpp"
#include "mainwindow.hpp"
#include "searchFilter.hpp"
#include "ui/ui_mainwindow.h"
#include "DBC/DBCStores.hpp"
#include <cassert>
#include <optional>

void MainWindow::onSearchBtnClicked()
{
    PerformSpellSearch();
}

void MainWindow::onSpellIdNameInputReturnPressed()
{
    PerformSpellSearch();
}

void MainWindow::onResultListClick(QTableWidgetItem *item)
{
    QTableWidgetItem const* spellRowItem = item->column() != 0 ? ui.resultList->item(ui.resultList->row(item), 0) : item;
    if (spellRowItem == nullptr)
    {
        return;
    }

    // Extract entry
    bool ok = false;
    uint32_t spellId = spellRowItem->text().toUInt(&ok);
    if (!ok || spellId == 0)
    {
        qCDebug(SPELLINFO_TAB) << "spell id was 0";
        return;
    }

    if (const auto* spell = sDBCStores->GetSpellEntry(spellId))
    {
        ui.spellInfoText->setText(spell->PrintBaseInfo(ui.levelScalingSlider->value()) + "<br>" + spell->PrintSpellEffectInfo(ui.levelScalingSlider->value()));
    }
}

// General functions
void MainWindow::PerformSpellSearch()
{
    const auto startMS = QDateTime::currentMSecsSinceEpoch();

    auto* resultList = ui.resultList;
    resultList->clearContents();

    if (sDBCStores->GetSpellEntries().empty())
    {
        ui.resultCountLabel->setText(QString("Found: 0 records in %1 milliseconds").arg(QDateTime::currentMSecsSinceEpoch() - startMS));
        return;
    }

    QStringView spellNameOrId = ui.spellIdNameInput->text();
    uint32_t spellId = 0;

    const bool searchById = ui.searchByIdCheckBox->isChecked();
    const bool searchByName = ui.searchByNameCheckBox->isChecked();

    if (!searchById && !searchByName)
    {
        ui.resultCountLabel->setText(QString("Found: 0 records in %1 milliseconds").arg(QDateTime::currentMSecsSinceEpoch() - startMS));
        return;
    }

    if (searchById)
    {
        try
        {
            spellId = spellNameOrId.toInt();
        }
        catch(...)
        {
            spellId = 0;
        }
    }

    // Prepare spell effect filter entries
    std::optional<uint32_t> spellFamilyId;
    if (searchFilterForm->genericFilter.spellFamily != -1)
    {
        spellFamilyId = searchFilterForm->ui.SpellFamilyFilter->itemData(searchFilterForm->genericFilter.spellFamily).toUInt();
    }

    std::optional<uint32_t> auraTypeId;
    if (searchFilterForm->genericFilter.spellAuraType != -1)
    {
        auraTypeId = searchFilterForm->ui.SpellAuraTypeFilter->itemData(searchFilterForm->genericFilter.spellAuraType).toUInt();
    }

    std::optional<uint32_t> spellEffectId;
    if (searchFilterForm->genericFilter.spellEffect != -1)
    {
        spellEffectId = searchFilterForm->ui.SpellEffectFilter->itemData(searchFilterForm->genericFilter.spellEffect).toUInt();
    }

    std::optional<uint32_t> spellTargetA;
    if (searchFilterForm->genericFilter.spellTargetA != -1)
    {
        spellTargetA = searchFilterForm->ui.SpellTargetFilterA->itemData(searchFilterForm->genericFilter.spellTargetA).toUInt();
    }
    std::optional<uint32_t> spellTargetB;
    if (searchFilterForm->genericFilter.spellTargetB != -1)
    {
        spellTargetB = searchFilterForm->ui.SpellTargetFilterA->itemData(searchFilterForm->genericFilter.spellTargetB).toUInt();
    }

    // advanced filters
    struct AdvancedSearchParams
    {
        bool hasData = false;
        ConditionCompareType compareType;
        std::optional<int32_t> int32val;
        std::optional<uint32_t> uint32val;
        std::optional<float> floatVal;
        std::optional<QString> textVal;

        uint8_t spellFieldId;

        bool CheckSpellFields(const SpellEntry& spell) const
        {
            // Nothing to check
            if (!hasData)
            {
                return true;
            }

            switch (compareType)
            {
            case ConditionCompareType::NotEqual:
            case ConditionCompareType::Equal:
            case ConditionCompareType::GreaterThan:
            case ConditionCompareType::GreaterOrEqual:
            case ConditionCompareType::LowerThan:
            case ConditionCompareType::LowerOrEqual:
            {
                const auto& aVal = spell.GetField(spellFieldId);
                if (int32val.has_value())
                {
                    return CompareNumericValues(compareType, aVal.int32Val, *int32val);
                }
                else if (uint32val.has_value())
                {
                    return CompareNumericValues(compareType, aVal.uint32Val, *uint32val);
                }
                else if (floatVal.has_value())
                {
                    return CompareNumericValues(compareType, aVal.floatVal, *floatVal);
                }
                break;
            }
            case ConditionCompareType::BitValue:
            case ConditionCompareType::NoBitValue:
            {
                const auto& aVal = spell.GetField(spellFieldId);
                if (uint32val.has_value())
                {
                    return CompareBitMasks(compareType, aVal.uint32Val, *uint32val);
                }
                break;
            }
            case ConditionCompareType::StartsWith:
            case ConditionCompareType::EndsWith:
            case ConditionCompareType::Contains:
            {
                const auto& aVal = spell.GetField(spellFieldId);
                if (textVal.has_value())
                {
                    return CompareStringValues(compareType, aVal.textVal, *textVal);
                }
                break;
            }
            }

            return false;
        }
    };

    std::array<AdvancedSearchParams, 2> advancedSearchParams;

    for (uint8_t i = 0; i < 2; ++i)
    {
        if (!searchFilterForm->spellAttributesFilter.HasData(i))
        {
            continue;
        }

        const auto& inputValue = searchFilterForm->spellAttributesFilter.conditionValue[i];
        const auto fieldId = searchFilterForm->ui.spellAttrFieldName0->itemData(searchFilterForm->spellAttributesFilter.conditionFieldName[i]).toUInt();
        ConditionCompareType compareType = ConditionCompareType(searchFilterForm->ui.spellAttrCompareType0->itemData(searchFilterForm->spellAttributesFilter.conditionCompareType[i]).toUInt());

        auto const& itr = SpellEntryFields.find(fieldId);
        if (itr == SpellEntryFields.end())
        {
            continue;
        }

        auto& searchParam = advancedSearchParams[i];
        switch (itr->second.cmpType)
        {
        case CompareTypes::SignedNumber:
        {
            bool ok = false;
            const int32_t val = inputValue.toInt(&ok);
            if (ok)
            {
                searchParam.int32val = val;
            }

            break;
        }
        case CompareTypes::UnsignedNumber:
        {
            bool ok = false;
            const uint32_t val = inputValue.toUInt(&ok);
            if (ok)
            {
                searchParam.uint32val = val;
            }

            break;
        }
        case CompareTypes::Float:
        {
            bool ok = false;
            const float val = inputValue.toFloat(&ok);
            if (ok)
            {
                searchParam.floatVal = val;
            }

            break;

        }
        case CompareTypes::String:
            searchParam.textVal = inputValue;
            break;
        default:
            break;
        }

        searchParam.spellFieldId = itr->first;
        searchParam.compareType = compareType;
        searchParam.hasData = true;
    }

    std::vector<std::pair<QTableWidgetItem* /*id*/, QTableWidgetItem* /*name*/>> foundEntries;
    for (const auto& [_id, _spellInfo] : sDBCStores->GetSpellEntries())
    {
        bool canInsert = spellNameOrId.isEmpty();
        if (!canInsert && spellId != 0 && _id == spellId)
        {
            canInsert = true;
        }

        // Find by name
        if (!canInsert && searchByName && _spellInfo.getSpellName().contains(spellNameOrId.toString(), Qt::CaseInsensitive))
        {
            canInsert = true;
        }

        if (!canInsert)
        {
            continue;
        }

        if (spellFamilyId.has_value())
        {
            const auto* spellClassOptions = sDBCStores->GetSpellClassOptionsEntry(_spellInfo.getSpellClassOptionsId());
            if (spellClassOptions == nullptr || spellClassOptions->SpellFamilyName != *spellFamilyId)
            {
                continue;
            }
        }

        if (auraTypeId.has_value() || spellEffectId.has_value() || spellTargetA.has_value() || spellTargetB.has_value())
        {
            if (!std::any_of(_spellInfo.m_spellEffects.begin(), _spellInfo.m_spellEffects.end(), [&](const auto* effectInfo)
            {
                if (effectInfo == nullptr)
                {
                    return false;
                }

                if (auraTypeId.has_value() && effectInfo->EffectAura != *auraTypeId)
                {
                    return false;
                }

                if (spellEffectId.has_value() && effectInfo->Effect != *spellEffectId)
                {
                    return false;
                }

                if (spellTargetA.has_value() && effectInfo->EffectImplicitTargetA != *spellTargetA)
                {
                    return false;
                }

                if (spellTargetB.has_value() && effectInfo->EffectImplicitTargetB != *spellTargetB)
                {
                    return false;
                }

                return true;
            }))
            {
                continue;
            }
        }

        if (std::any_of(advancedSearchParams.begin(), advancedSearchParams.end(), [_spellInfo](auto const advancedSrchParam)
        {
            return !advancedSrchParam.CheckSpellFields(_spellInfo);
        }))
        {
            continue;
        }

        QTableWidgetItem* idItem = new QTableWidgetItem();
        idItem->setData(Qt::EditRole, _id);

        QTableWidgetItem* spell = new QTableWidgetItem();
        spell->setData(Qt::EditRole, _spellInfo.getSpellName());

        foundEntries.emplace_back(idItem, spell);
    }

    if (foundEntries.empty())
    {
        ui.resultCountLabel->setText(QString("Found: 0 records in %1 milliseconds").arg(QDateTime::currentMSecsSinceEpoch() - startMS));
        return;
    }

    resultList->setRowCount(static_cast<int>(foundEntries.size()));

    int rowId = 0;
    for (const auto& [_spellId, _spellname] : foundEntries)
    {
        resultList->setItem(rowId, 0, _spellId);
        resultList->setItem(rowId, 1, _spellname);
        ++rowId;
    }

    ui.resultCountLabel->setText(QString("Found: %1 records in %2 milliseconds").arg(QString::number(foundEntries.size())).arg(QDateTime::currentMSecsSinceEpoch() - startMS));
}

void MainWindow::onLevelScalingSliderValueChange()
{
    ui.levelScalingText->setText(QString("Selected Level %1").arg(ui.levelScalingSlider->value()));
    const auto* item = ui.resultList->currentItem();
    if (item == nullptr)
    {
        return;
    }

    QTableWidgetItem const* spellRowItem = item->column() != 0 ? ui.resultList->item(ui.resultList->row(item), 0) : item;
    if (spellRowItem == nullptr)
    {
        return;
    }

    // Extract entry
    bool ok = false;
    uint32_t spellId = spellRowItem->text().toUInt(&ok);
    if (!ok || spellId == 0)
    {
        qCDebug(SPELLINFO_TAB) << "spell id was 0";
        return;
    }

    if (const auto* spell = sDBCStores->GetSpellEntry(spellId))
    {
        ui.spellInfoText->setText(spell->PrintBaseInfo(ui.levelScalingSlider->value()) + "<br>" + spell->PrintSpellEffectInfo(ui.levelScalingSlider->value()));
    }
}

void MainWindow::onAdvancedSearchBtnClick()
{
    this->setEnabled(false);
    searchFilterForm->setEnabled(true);
    searchFilterForm->show();
}
