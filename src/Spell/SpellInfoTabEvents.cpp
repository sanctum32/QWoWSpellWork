// Qt
#include <QDebug>
#include <QTableWidget>
#include <QDate>
// project
#include "ValueComparition.hpp"
#include "MainWindowForm.hpp"
#include "SearchFilterForm.hpp"
#include "DataStorage.hpp"
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
    if (spellInfoTab.m_lastSpellSearchRowId == item->row())
    {
        return;
    }

    spellInfoTab.m_lastSpellSearchRowId = item->row();

    // Select only number field
    const auto* spellRowItem = ui.resultList->item(spellInfoTab.m_lastSpellSearchRowId, 0);
    if (spellRowItem == nullptr)
    {
        return;
    }

    // Extract entry
    bool ok = false;
    const uint32_t spellId = spellRowItem->text().toUInt(&ok);
    if (!ok)
    {
        return;
    }

    if (const auto* spell = sDataStorage->GetSpellEntry(spellId))
    {
        const uint8_t selectedLevel = static_cast<uint8_t>(ui.levelScalingSlider->value());
        const uint8_t comboPoints = static_cast<uint8_t>(ui.comboPointsSlider->value());
        ui.spellInfoText->setText(spell->PrintBaseInfo(selectedLevel) + "<br>" + spell->PrintSpellEffectInfo(selectedLevel, comboPoints));
    }
}

// General functions
void MainWindow::PerformSpellSearch()
{
    const auto startMS = QDateTime::currentMSecsSinceEpoch();

    auto* resultList = ui.resultList;
    resultList->clearContents();
    spellInfoTab.m_lastSpellSearchRowId = -1;

    if (sDataStorage->GetSpellEntries().empty())
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
    std::optional<uint32_t> auraTypeId;
    std::optional<uint32_t> spellEffectId;
    std::optional<uint32_t> spellTargetA;
    std::optional<uint32_t> spellTargetB;

    if (const auto* spellFamily = spellInfoTab.spellInfoTabFilter.m_genericFilter.GetSpellFamily())
    {
        spellFamilyId = *spellFamily;
    }

    if (const auto* spellAuraType = spellInfoTab.spellInfoTabFilter.m_genericFilter.GetSpellAuraType())
    {
        auraTypeId = *spellAuraType;
    }

    if (const auto* spellEffect = spellInfoTab.spellInfoTabFilter.m_genericFilter.GetSpellEffect())
    {
        spellEffectId = *spellEffect;
    }

    if (const auto* spellTarget_A = spellInfoTab.spellInfoTabFilter.m_genericFilter.GetSpellTargetA())
    {
        spellTargetA = *spellTarget_A;
    }

    if (const auto* spelltarget_B = spellInfoTab.spellInfoTabFilter.m_genericFilter.GetSpellTargetB())
    {
        spellTargetB = *spelltarget_B;
    }

    std::array<DBCFieldDataCompare, 2> spellAttrFilter;
    std::array<DBCFieldDataCompare, 2> spellEffectAttrFilter;
    for (uint8_t i = 0; i < 2; ++i)
    {
        // Spell.dbc filter
        {
            const auto* fieldId = spellInfoTab.spellInfoTabFilter.m_spellEntryFilter.at(i).GetFieldId();
            const auto* cmpType = spellInfoTab.spellInfoTabFilter.m_spellEntryFilter.at(i).GetCompareType();
            const auto& cmpValue = spellInfoTab.spellInfoTabFilter.m_spellEntryFilter.at(i).GetCompareValue();
            if (fieldId != nullptr && cmpType != nullptr && !cmpValue.isEmpty())
            {
                spellAttrFilter.at(i).SetValues(SpellEntryFields, *fieldId, ConditionCompareType(*cmpType), cmpValue);
            }
        }

        // SpellEffect.dbc filter
        {
            const auto* fieldId = spellInfoTab.spellInfoTabFilter.m_spellEffectFilter.at(i).GetFieldId();
            const auto* cmpType = spellInfoTab.spellInfoTabFilter.m_spellEffectFilter.at(i).GetCompareType();
            const auto& cmpValue = spellInfoTab.spellInfoTabFilter.m_spellEffectFilter.at(i).GetCompareValue();
            if (fieldId != nullptr && cmpType != nullptr && !cmpValue.isEmpty())
            {
                spellEffectAttrFilter.at(i).SetValues(SpellEffectEntryFields, *fieldId, ConditionCompareType(*cmpType), cmpValue);
            }
        }
    }

    std::vector<std::pair<QTableWidgetItem* /*id*/, QTableWidgetItem* /*name*/>> foundEntries;
    for (const auto& itr : sDataStorage->GetSpellEntries())
    {
        const auto _id = itr.first;
        const auto& _spellInfo = itr.second;
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
            const auto* spellClassOptions = sDataStorage->GetSpellClassOptionsEntry(_spellInfo.getSpellClassOptionsId());
            if (spellClassOptions == nullptr || spellClassOptions->SpellFamilyName != *spellFamilyId)
            {
                continue;
            }
        }

        // Direct-generic effect filters
        if (auraTypeId.has_value() || spellEffectId.has_value() || spellTargetA.has_value() || spellTargetB.has_value())
        {
            if (!std::ranges::any_of(_spellInfo.m_spellEffects, [&](const auto* effectInfo)
            {
                if (effectInfo == nullptr)
                {
                    return false;
                }

                if (auraTypeId.has_value() && effectInfo->getEffectAura() != *auraTypeId)
                {
                    return false;
                }

                if (spellEffectId.has_value() && effectInfo->getEffect() != *spellEffectId)
                {
                    return false;
                }

                if (spellTargetA.has_value() && effectInfo->getEffectImplicitTargetA() != *spellTargetA)
                {
                    return false;
                }

                if (spellTargetB.has_value() && effectInfo->getEffectImplicitTargetB() != *spellTargetB)
                {
                    return false;
                }

                return true;
            }))
            {
                continue;
            }
        }

        // Spell.dbc filter
        if (std::ranges::any_of(spellAttrFilter, [_spellInfo](const auto& compareParam)
        {
            return !compareParam.DoCheck(_spellInfo);
        }))
        {
            continue;
        }

        // SpellEffect.dbc filter
        // return spells which has least one effect having effect matching field value
        if (std::ranges::any_of(spellEffectAttrFilter, [](const auto& compareParam)
        {
            return compareParam.hasData;
        }))
        {
            canInsert = false;
            for (const auto& filter : spellEffectAttrFilter)
            {
                if (!filter.hasData)
                {
                    continue;
                }

                if (std::ranges::any_of(_spellInfo.m_spellEffects, [filter](const auto* effectInfo)
                {
                    return effectInfo != nullptr && filter.DoCheck(*effectInfo);
                }))
                {
                    canInsert = true;
                    break;
                }
            }
        }

        if (!canInsert)
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

void MainWindow::onScalingSliderUpdate()
{
    const uint8_t selectedLevel = static_cast<uint8_t>(ui.levelScalingSlider->value());
    const uint8_t comboPoints = static_cast<uint8_t>(ui.comboPointsSlider->value());

    ui.levelScalingText->setText(QString("Selected Level %1, (max 85)").arg(selectedLevel));
    ui.comboScalingText->setText(QString("Combo Points: %1").arg(comboPoints));
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

    if (const auto* spell = sDataStorage->GetSpellEntry(spellId))
    {
        ui.spellInfoText->setText(spell->PrintBaseInfo(selectedLevel) + "<br>" + spell->PrintSpellEffectInfo(selectedLevel, comboPoints));
    }
}

void MainWindow::onFiltersBtnClick()
{
    SearchFilterForm* filter = new SearchFilterForm(&spellInfoTab.spellInfoTabFilter, this);
    filter->setAttribute(Qt::WA_DeleteOnClose);

    filter->OnCloseOrApplyEventFn = [this]()
    {
        using namespace SpellWork::SearchFilters;
        const bool hasBasicFilters = spellInfoTab.spellInfoTabFilter.m_genericFilter.HasData();
        const bool hasSpellFieldFilters = std::ranges::any_of(spellInfoTab.spellInfoTabFilter.m_spellEntryFilter, [](const auto& filter)
        {
            return filter.HasData();
        });
        const bool hasSpellEffectFilters = std::ranges::any_of(spellInfoTab.spellInfoTabFilter.m_spellEffectFilter, [](const auto& filter)
        {
            return filter.HasData();
        });

        UpdateFilterStatus(hasBasicFilters || hasSpellFieldFilters || hasSpellEffectFilters);
    };

    filter->open();
}

void MainWindow::onClearResultsBtn()
{
    spellInfoTab.m_lastSpellSearchRowId = -1;
    ui.spellInfoText->clear();
    ui.resultList->clearContents();
    ui.spellIdNameInput->clear();
    ui.resultCountLabel->setText("Found 0 results");
    ui.levelScalingSlider->setValue(1);
    ui.levelScalingText->setText("Selected Level 1, (max 85)");
    ui.comboPointsSlider->setValue(0);
    ui.comboScalingText->setText("Combo Points: 0");
}
