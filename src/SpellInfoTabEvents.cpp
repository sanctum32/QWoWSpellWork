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
        qDebug() << "spell id was 0";
        return;
    }

    if (const auto* spell = GetDBCEntry(spellId, sDBCStores->m_spellEntries))
    {
        ui.spellInfoText->setText(spell->PrintBaseInfo(ui.levelScalingSlider->value()));
        ui.spellEffectInfo->setText(spell->PrintSpellEffectInfo(ui.levelScalingSlider->value()));
    }
}

// General functions
void MainWindow::PerformSpellSearch()
{
    const auto startMS = QDateTime::currentMSecsSinceEpoch();

    auto* resultList = ui.resultList;
    resultList->setRowCount(0);

    if (sDBCStores->m_spellEntries.empty())
    {
        ui.ResultsGroup->setTitle(QString("Found: 0 records in %1 milliseconds").arg(QDateTime::currentMSecsSinceEpoch() - startMS));
        return;
    }

    const QString spellNameOrId = ui.spellIdNameInput->text().toUpper();

    uint32_t spellId = 0;

    const bool searchById = ui.searchByIdCheckBox->isChecked();
    const bool searchByName = ui.seearchByNameCheckBox->isChecked();
    const bool includeServerSide = ui.serverSideCheckBox->isChecked();

    if (!searchById && !searchByName)
    {
        ui.ResultsGroup->setTitle(QString("Found: 0 records in %1 milliseconds").arg(QDateTime::currentMSecsSinceEpoch() - startMS));
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
        const auto& spellFamilyItr = std::find_if(sSpellWorkJson->SpellFamilyInfo.begin(), sSpellWorkJson->SpellFamilyInfo.end(),
            [familyStr = ui.SpellFamilyFilter->currentText()](const auto& spellFamily)
        {
            return spellFamily.second == familyStr;
        });

        if (spellFamilyItr != sSpellWorkJson->SpellFamilyInfo.end())
        {
            spellFamilyId = spellFamilyItr->first;
        }
    }

    // Spell aura type filter
    if (ui.SpellAuraTypeFilter->currentIndex() != 0)
    {
        const auto& spellAuraTypeItr = std::find_if(sSpellWorkJson->_spellAuraTypes.begin(), sSpellWorkJson->_spellAuraTypes.end(),
            [auraTypeStr = ui.SpellAuraTypeFilter->currentText()](const auto& spellAuraType)
        {
            return spellAuraType.second.name == auraTypeStr;
        });

        if (spellAuraTypeItr != sSpellWorkJson->_spellAuraTypes.end())
        {
            auraTypeId = spellAuraTypeItr->first;
        }
    }

    // Spell effect filter
    if (ui.SpellEffectFilter->currentIndex() != 0)
    {
        const auto& effectNameItr = std::find_if(sSpellWorkJson->_spellEffectInfo.begin(), sSpellWorkJson->_spellEffectInfo.end(),
            [selectedEffect = ui.SpellEffectFilter->currentText()](const auto& data)
        {
            return data.second.name == selectedEffect;
        });

        if (effectNameItr != sSpellWorkJson->_spellEffectInfo.end())
        {
            spellEffectId = effectNameItr->first;
        }
    }

    // TargetA filter
    if (ui.SpellTargetFilterA->currentIndex() != 0)
    {
        const auto& targetNameItr = std::find_if(sSpellWorkJson->SpellTargetNames.begin(), sSpellWorkJson->SpellTargetNames.end(),
            [selectedTarget = ui.SpellTargetFilterA->currentText()](const auto& spellTarget)
        {
            return spellTarget.second == selectedTarget;
        });

        if (targetNameItr != sSpellWorkJson->SpellTargetNames.end())
        {
            spellTargetA = targetNameItr->first;
        }
    }

    // TargetB filter
    if (ui.SpellTargetFilterB->currentIndex() != 0)
    {
        const auto& targetNameItr = std::find_if(sSpellWorkJson->SpellTargetNames.begin(), sSpellWorkJson->SpellTargetNames.end(),
            [selectedTarget = ui.SpellTargetFilterA->currentText()](const auto& spellTarget)
        {
            return spellTarget.second == selectedTarget;
        });

        if (targetNameItr != sSpellWorkJson->SpellTargetNames.end())
        {
            spellTargetB = targetNameItr->first;
        }
    }

    std::map<uint32_t /*spell*/, QString /*name*/> foundEntries;
    for (const auto& [_id, _spellInfo] : sDBCStores->m_spellEntries)
    {
        if (_spellInfo.m_IsServerSide && !includeServerSide)
        {
            continue;
        }

        bool canInsert = spellNameOrId.isEmpty();
        if (!canInsert && searchById && spellId != 0 && _id == spellId)
        {
            canInsert = true;
        }

        // Find by name
        if (!canInsert && searchByName && _spellInfo.m_spellNameUpper.contains(spellNameOrId))
        {
            canInsert = true;
        }

        if (!canInsert)
        {
            continue;
        }

        if (spellFamilyId.has_value())
        {
            const auto* spellClassOptions = GetDBCEntry(_spellInfo.SpellClassOptionsId, sDBCStores->m_SpellClassOptions);
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

        foundEntries[_id] = _spellInfo.SpellName.c_str();
    }

    if (foundEntries.empty())
    {
        ui.ResultsGroup->setTitle(QString("Found: 0 records in %1 milliseconds").arg(QDateTime::currentMSecsSinceEpoch() - startMS));
        return;
    }

    ui.ResultsGroup->setTitle(QString("Found: %1 records in %2 milliseconds").arg(QString::number(foundEntries.size())).arg(QDateTime::currentMSecsSinceEpoch() - startMS));

    resultList->setRowCount(static_cast<int>(foundEntries.size()));
    int rowId = 0;
    for (const auto& [_spellId, _spellname] : foundEntries)
    {
        // Set id
        {
            auto* idWidget = new QTableWidgetItem();
            idWidget->setData(Qt::EditRole, _spellId);
            resultList->setItem(rowId, 0, idWidget);
        }
        // Set name
        {
            auto* spellNameWidget = new QTableWidgetItem();
            spellNameWidget->setData(Qt::EditRole, _spellname);
            resultList->setItem(rowId, 1, spellNameWidget);
        }

        ++rowId;
    }
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
        qDebug() << "spell id was 0";
        return;
    }

    if (const auto* spell = GetDBCEntry(spellId, sDBCStores->m_spellEntries))
    {
        ui.spellInfoText->setText(spell->PrintBaseInfo(ui.levelScalingSlider->value()));
        ui.spellEffectInfo->setText(spell->PrintSpellEffectInfo(ui.levelScalingSlider->value()));
    }
}
