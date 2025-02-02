// Qt
#include <QDebug>
#include <QTableWidget>
#include <QDate>
// project
#include "MainWindowForm.hpp"
#include "SearchFilterForm.hpp"
#include "DataStorage.hpp"
#include <cassert>

void MainWindow::onSearchBtnClicked()
{
    PerformSpellSearch(ui.spellIdNameInput->text(), ui.searchByIdCheckBox->isChecked(), ui.searchByNameCheckBox->isChecked(), ui.resultList, spellInfoTab.m_spellSearchFilter, ui.resultCountLabel);
    spellInfoTab.m_selectedSpellRowId = -1;
}

void MainWindow::onSpellIdNameInputReturnPressed()
{
    PerformSpellSearch(ui.spellIdNameInput->text(), ui.searchByIdCheckBox->isChecked(), ui.searchByNameCheckBox->isChecked(), ui.resultList, spellInfoTab.m_spellSearchFilter, ui.resultCountLabel);
    spellInfoTab.m_selectedSpellRowId = -1;
}

void MainWindow::onResultListClick(QTableWidgetItem *item)
{
    if (spellInfoTab.m_selectedSpellRowId == item->row())
    {
        return;
    }

    spellInfoTab.m_selectedSpellRowId = item->row();

    // Select only number field
    const auto* spellRowItem = ui.resultList->item(spellInfoTab.m_selectedSpellRowId, 0);
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
    SearchFilterForm* filter = new SearchFilterForm(&spellInfoTab.m_spellSearchFilter, this);
    filter->setAttribute(Qt::WA_DeleteOnClose);

    filter->OnCloseOrApplyEventFn = [this]()
    {
        const bool hasBasicFilters = spellInfoTab.m_spellSearchFilter.m_genericFilter.HasData();
        const bool hasSpellFieldFilters = std::ranges::any_of(spellInfoTab.m_spellSearchFilter.m_spellEntryFieldsFilter, [](const auto& filter)
        {
            return filter.HasData();
        });
        const bool hasSpellEffectFilters = std::ranges::any_of(spellInfoTab.m_spellSearchFilter.m_spellEffectFieldsFilter, [](const auto& filter)
        {
            return filter.HasData();
        });

        UpdateFilterStatus(hasBasicFilters || hasSpellFieldFilters || hasSpellEffectFilters);
    };

    filter->open();
}

void MainWindow::onClearResultsBtn()
{
    spellInfoTab.m_selectedSpellRowId = -1;
    ui.spellInfoText->clear();
    ui.resultList->clearContents();
    ui.spellIdNameInput->clear();
    ui.resultCountLabel->setText("Found 0 results");
    ui.levelScalingSlider->setValue(1);
    ui.levelScalingText->setText("Selected Level 1, (max 85)");
    ui.comboPointsSlider->setValue(0);
    ui.comboScalingText->setText("Combo Points: 0");
}
