#include "MainWindowForm.hpp"
#include "DataStorage.hpp"
#include "SearchFilterForm.hpp"
#include "ValueComparition.hpp"
#include <QCloseEvent>
#include <QDateTime>
#include <optional>
#include <qmessagebox.h>

Q_LOGGING_CATEGORY(SPELLINFO_TAB, "spellwork.json");

// Base implementation
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    ui.setupUi(this);

    // resultList
    ClearAndResetSearchResults();

    // Signal connections
    QObject::connect(ui.searchBtn,        &QPushButton::clicked,     this, &MainWindow::onSearchBtnClicked);
    QObject::connect(ui.spellIdNameInput, &QLineEdit::returnPressed, this, &MainWindow::onSpellIdNameInputReturnPressed);
    QObject::connect(ui.resultList,       &QTableWidget::itemClicked,    this, &MainWindow::onResultListClick);
    QObject::connect(ui.levelScalingSlider, &QSlider::valueChanged, this, &MainWindow::onScalingSliderUpdate);
    QObject::connect(ui.comboPointsSlider, &QSlider::valueChanged, this, &MainWindow::onScalingSliderUpdate);
    QObject::connect(ui.filtersBtn,       &QPushButton::clicked, this, &MainWindow::onFiltersBtnClick);
    QObject::connect(ui.clearResultsBtn,  &QPushButton::clicked, this, &MainWindow::onClearResultsBtn);
}

MainWindow::~MainWindow() = default;

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
    // Select only number field
    const auto* spellRowItem = ui.resultList->item(item->row(), 0);

    // Spell id in result list always non 0
    const uint32_t spellId = spellRowItem->text().toUInt();
    const auto* spell = sDataStorage->GetSpellEntry(spellId);
    const uint8_t selectedLevel = static_cast<uint8_t>(ui.levelScalingSlider->value());
    const uint8_t comboPoints = static_cast<uint8_t>(ui.comboPointsSlider->value());
    ui.spellInfoText->setText(spell->PrintBaseInfo(selectedLevel));
    ui.spellEffectText->setText(spell->PrintSpellEffectInfo(selectedLevel, comboPoints));
}

void MainWindow::onScalingSliderUpdate()
{
    const auto selectedLevel = ui.levelScalingSlider->value();
    const auto comboPoints = ui.comboPointsSlider->value();

    ui.levelScalingText->setText(QString("Selected Level %1, (max 85)").arg(selectedLevel));
    ui.comboScalingText->setText(QString("Combo Points: %1").arg(comboPoints));
    const auto* item = ui.resultList->currentItem();
    if (item == nullptr)
    {
        return;
    }

    const auto* spellRowItem = item->column() != 0 ? ui.resultList->item(ui.resultList->row(item), 0) : item;
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
        ui.spellInfoText->setText(spell->PrintBaseInfo(selectedLevel));
        ui.spellEffectText->setText(spell->PrintSpellEffectInfo(selectedLevel, comboPoints));
    }
}

void MainWindow::onFiltersBtnClick()
{
    auto* filter = new SearchFilterForm(&m_searchFilterData, this);
    filter->setAttribute(Qt::WA_DeleteOnClose);
    filter->open();
}

void MainWindow::onClearResultsBtn()
{
    ui.spellIdNameInput->clear();
    ui.resultCountLabel->setText("Found 0 results");
    ui.levelScalingSlider->setValue(1);
    ui.levelScalingText->setText("Selected Level 1, (max 85)");
    ui.comboPointsSlider->setValue(0);
    ui.comboScalingText->setText("Combo Points: 0");
    ui.spellInfoText->clear();
    ui.spellEffectText->clear();
    ClearAndResetSearchResults();
}

void MainWindow::PerformSpellSearch()
{
    ClearAndResetSearchResults();

    const auto startMS = QDateTime::currentMSecsSinceEpoch();
    if (sDataStorage->GetSpellEntries().empty())
    {
        ui.resultCountLabel->setText(QString("Found: 0 records in %1 milliseconds").arg(QDateTime::currentMSecsSinceEpoch() - startMS));

        QMessageBox msgBox;
        msgBox.setText("Spell storage is empty! Spell search cannot be processed!");
        msgBox.setIcon(QMessageBox::Information);
        msgBox.exec();
        return;
    }

    QStringView spellNameOrId = ui.spellIdNameInput->text();
    uint32_t spellId = 0;
    const bool searchById = ui.searchByIdCheckBox->isChecked();
    const bool searchByName = ui.searchByNameCheckBox->isChecked();
    if (!searchById && !searchByName)
    {
        ui.resultCountLabel->setText(QString("Found: 0 records in %1 milliseconds").arg(QDateTime::currentMSecsSinceEpoch() - startMS));

        QMessageBox msgBox;
        msgBox.setText("You must search for spell by least name or id!");
        msgBox.setIcon(QMessageBox::Information);
        msgBox.exec();
        return;
    }

    if (searchById)
    {
        spellId = ui.spellIdNameInput->text().toInt();
    }

    // Prepare spell effect filter entries
    std::optional<uint32_t> spellFamilyId;
    std::optional<uint32_t> auraTypeId;
    std::optional<uint32_t> spellEffectId;
    std::optional<uint32_t> spellTargetA;
    std::optional<uint32_t> spellTargetB;

    if (const auto* spellFamily = m_searchFilterData.m_genericFilter.GetSpellFamily())
    {
        spellFamilyId = *spellFamily;
    }

    if (const auto* spellAuraType = m_searchFilterData.m_genericFilter.GetSpellAuraType())
    {
        auraTypeId = *spellAuraType;
    }

    if (const auto* spellEffect = m_searchFilterData.m_genericFilter.GetSpellEffect())
    {
        spellEffectId = *spellEffect;
    }

    if (const auto* spellTarget_A = m_searchFilterData.m_genericFilter.GetSpellTargetA())
    {
        spellTargetA = *spellTarget_A;
    }

    if (const auto* spelltarget_B = m_searchFilterData.m_genericFilter.GetSpellTargetB())
    {
        spellTargetB = *spelltarget_B;
    }

    std::array<DBCFieldDataCompare, 2> spellAttrFilter;
    std::array<DBCFieldDataCompare, 2> spellEffectAttrFilter;
    for (uint8_t i = 0; i < 2; ++i)
    {
        // Spell.dbc filter
        {
            const auto& spellDbcFilter = m_searchFilterData.m_spellEntryFieldsFilter.at(i);
            const auto* fieldId = spellDbcFilter.GetFieldId();
            const auto* cmpType = spellDbcFilter.GetCompareType();
            const auto& cmpValue = spellDbcFilter.GetCompareValue();
            if (fieldId != nullptr && cmpType != nullptr && !cmpValue.isEmpty())
            {
                spellAttrFilter.at(i).SetValues(SpellEntryFields, *fieldId, ConditionCompareType(*cmpType), cmpValue);
            }
        }

        // SpellEffect.dbc filter
        {
            const auto& spellEffectsDbcFilter = m_searchFilterData.m_spellEffectFieldsFilter.at(i);
            const auto* fieldId = spellEffectsDbcFilter.GetFieldId();
            const auto* cmpType = spellEffectsDbcFilter.GetCompareType();
            const auto& cmpValue = spellEffectsDbcFilter.GetCompareValue();
            if (fieldId != nullptr && cmpType != nullptr && !cmpValue.isEmpty())
            {
                spellEffectAttrFilter.at(i).SetValues(SpellEffectEntryFields, *fieldId, ConditionCompareType(*cmpType), cmpValue);
            }
        }
    }

    for (const auto& itr : sDataStorage->GetSpellEntries())
    {
        const auto _id = itr.first;
        const auto& _spellInfo = itr.second;
        bool canInsert = false;
        if (spellId != 0 && _id == spellId)
        {
            canInsert = true;
        }

        // Find by name
        if (!canInsert && searchByName && _spellInfo.getSpellName().contains(spellNameOrId, Qt::CaseInsensitive))
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
        if (std::ranges::any_of(spellAttrFilter, [_spellInfo](const auto& compareParam) { return !compareParam.DoCheck(_spellInfo); }))
        {
            continue;
        }

        // SpellEffect.dbc filter
        // return spells which has least one effect having effect matching field value
        if (std::ranges::any_of(spellEffectAttrFilter, [](const auto& compareParam) { return compareParam.hasData; }))
        {
            canInsert = false;
            for (const auto& filter : spellEffectAttrFilter)
            {
                if (!filter.hasData)
                {
                    continue;
                }

                if (std::ranges::any_of(_spellInfo.m_spellEffects, [filter](const auto* effectInfo) { return effectInfo != nullptr && filter.DoCheck(*effectInfo); }))
                {
                    canInsert = true;
                    break;
                }
            }
        }

        if (canInsert)
        {
            int rowId = ui.resultList->rowCount();
            ui.resultList->insertRow(rowId);
            ui.resultList->setItem(rowId, 0, new QTableWidgetItem(QString::number(_id)));
            ui.resultList->setItem(rowId, 1, new QTableWidgetItem(_spellInfo.getSpellName()));
        }
    }

    ui.resultCountLabel->setText(QString("Found: %1 records in %2 milliseconds").arg(ui.resultList->rowCount()).arg(QDateTime::currentMSecsSinceEpoch() - startMS));
}

void MainWindow::ClearAndResetSearchResults()
{
    const int rowCount = ui.resultList->rowCount();
    const int colCount = ui.resultList->columnCount();
    for (int row = 0; row < rowCount; ++row)
    {
        for (int col = 0; col < colCount; ++col)
        {
            delete ui.resultList->takeItem(row, col);
        }
    }

    ui.resultList->clearContents();
    ui.resultList->setRowCount(0);
}
