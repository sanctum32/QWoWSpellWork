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
#include "SearchFilters.hpp"
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
    std::optional<uint32_t> auraTypeId;
    std::optional<uint32_t> spellEffectId;
    std::optional<uint32_t> spellTargetA;
    std::optional<uint32_t> spellTargetB;

    if (const auto* spellFamily = SpellWork::SearchFilters::m_genericFilter.GetSpellFamily())
    {
        spellFamilyId = *spellFamily;
    }

    if (const auto* spellAuraType = SpellWork::SearchFilters::m_genericFilter.GetSpellAuraType())
    {
        auraTypeId = *spellAuraType;
    }

    if (const auto* spellEffect = SpellWork::SearchFilters::m_genericFilter.GetSpellEffect())
    {
        spellEffectId = *spellEffect;
    }

    if (const auto* spellTarget_A = SpellWork::SearchFilters::m_genericFilter.GetSpellTargetA())
    {
        spellTargetA = *spellTarget_A;
    }

    if (const auto* spelltarget_B = SpellWork::SearchFilters::m_genericFilter.GetSpellTargetB())
    {
        spellTargetB = *spelltarget_B;
    }

    std::array<AdvancedSearchParams<SpellEntry>, 2> spellAttrFilter;
    for (uint8_t i = 0; i < 2; ++i)
    {
        if (!SpellWork::SearchFilters::m_spellEntryFilter.at(i).HasData())
        {
            continue;
        }

        const auto& inputValue = SpellWork::SearchFilters::m_spellEntryFilter.at(i).GetCompareVale();
        const auto fieldId = *SpellWork::SearchFilters::m_spellEntryFilter.at(i).GetFieldId();
        ConditionCompareType compareType = ConditionCompareType(*SpellWork::SearchFilters::m_spellEntryFilter.at(i).GetCompareType());

        auto const& itr = SpellEntryFields.find(fieldId);
        if (itr == SpellEntryFields.end())
        {
            continue;
        }

        auto& searchParam = spellAttrFilter[i];
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
    for (const auto& itr : sDBCStores->GetSpellEntries())
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

        if (std::any_of(spellAttrFilter.begin(), spellAttrFilter.end(), [_spellInfo](auto const advancedSrchParam)
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

void MainWindow::onFiltersBtnClick()
{
    setEnabled(false);
    searchFilterForm->setEnabled(true);
    searchFilterForm->show();
}
