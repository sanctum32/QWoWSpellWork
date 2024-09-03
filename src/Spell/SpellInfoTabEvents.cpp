// Qt
#include <QDebug>
#include <QTableWidget>

// project
#include "mainwindow.hpp"
#include "ui/ui_mainwindow.h"
#include "DBC/DBCStores.hpp"
#include "JsonData/JsonData.hpp"
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

    // Spell family filter
    if (ui.SpellFamilyFilter->currentIndex() != 0)
    {
        const auto& spellFamilyData = sSpellWorkJson->GetSpellFamilyData();
        const auto& spellFamilyItr = std::find_if(spellFamilyData.begin(), spellFamilyData.end(),
            [familyStr = ui.SpellFamilyFilter->currentText()](const auto& spellFamily)
        {
            return spellFamily.second == familyStr;
        });

        if (spellFamilyItr != spellFamilyData.end())
        {
            spellFamilyId = spellFamilyItr->first;
        }
    }

    // Spell aura type filter
    if (ui.SpellAuraTypeFilter->currentIndex() != 0)
    {
        const auto& spellAuraData = sSpellWorkJson->GetSpellAuraEffectData();
        const auto& spellAuraTypeItr = std::find_if(spellAuraData.begin(), spellAuraData.end(),
            [auraTypeStr = ui.SpellAuraTypeFilter->currentText()](const auto& spellAuraType)
        {
            return spellAuraType.second.name == auraTypeStr;
        });

        if (spellAuraTypeItr != spellAuraData.end())
        {
            auraTypeId = spellAuraTypeItr->first;
        }
    }

    // Spell effect filter
    if (ui.SpellEffectFilter->currentIndex() != 0)
    {
        const auto& spellEffectData = sSpellWorkJson->GetSpellEffectData();
        const auto& effectNameItr = std::find_if(spellEffectData.begin(), spellEffectData.end(),
            [selectedEffect = ui.SpellEffectFilter->currentText()](const auto& data)
        {
            return data.second.name == selectedEffect;
        });

        if (effectNameItr != spellEffectData.end())
        {
            spellEffectId = effectNameItr->first;
        }
    }

    {
        const auto& targetData = sSpellWorkJson->GetSpellTargetData();
        // TargetA filter
        if (ui.SpellTargetFilterA->currentIndex() != 0)
        {
            const auto& targetNameItr = std::find_if(targetData.begin(), targetData.end(),
                [selectedTarget = ui.SpellTargetFilterA->currentText()](const auto& spellTarget)
            {
                return spellTarget.second == selectedTarget;
            });

            if (targetNameItr != targetData.end())
            {
                spellTargetA = targetNameItr->first;
            }
        }

        // TargetB filter
        if (ui.SpellTargetFilterB->currentIndex() != 0)
        {
            const auto& targetNameItr = std::find_if(targetData.begin(), targetData.end(),
                [selectedTarget = ui.SpellTargetFilterA->currentText()](const auto& spellTarget)
            {
                return spellTarget.second == selectedTarget;
            });

            if (targetNameItr != targetData.end())
            {
                spellTargetB = targetNameItr->first;
            }
        }
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

        QTableWidgetItem* idItem = new QTableWidgetItem();
        idItem->setData(Qt::EditRole, _id);

        QTableWidgetItem* spell = new QTableWidgetItem();
        spell->setData(Qt::EditRole, QString(_spellInfo.getSpellName().toString()));

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
