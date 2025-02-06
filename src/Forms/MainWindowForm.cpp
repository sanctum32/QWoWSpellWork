#include "MainWindowForm.hpp"
#include "DataStorage.hpp"
#include "SearchFilterForm.hpp"
#include "ValueComparition.hpp"
#include <QCloseEvent>
#include <QDateTime>
#include <optional>

Q_LOGGING_CATEGORY(SPELLINFO_TAB, "spellwork.json");

// Base implementation
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    ui.setupUi(this);
    UpdateAdvFilterStatus(false);

    // resultList
    ClearResults(ui.resultList);

    // statusBar
    ui.statusBar->addPermanentWidget(&m_advFilterStatusLabel);
    ui.statusBar->addPermanentWidget(&m_connectionStatusLabel);

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

void MainWindow::UpdateSqlStatus(bool success)
{
    if (success)
    {
        m_connectionStatusLabel.setText("SQL: <span style=\"color:green\">connected</span>");
    }
    else
    {
        m_connectionStatusLabel.setText("SQL: <span style=\"color:red\">not connected</span>");
    }
}

void MainWindow::UpdateAdvFilterStatus(bool hasFilter)
{
    if (hasFilter)
    {
        m_advFilterStatusLabel.setText("Extra filters: <span style=\"color:green\">active</span>");
    }
    else
    {
        m_advFilterStatusLabel.setText("Extra filters: <span style=\"color:red\">inactive</span>");
    }
}

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

    const uint32_t spellId = spellRowItem->text().toUInt();
    if (spellId == 0)
    {
        return;
    }

    const auto* spell = sDataStorage->GetSpellEntry(spellId);
    const uint8_t selectedLevel = static_cast<uint8_t>(ui.levelScalingSlider->value());
    const uint8_t comboPoints = static_cast<uint8_t>(ui.comboPointsSlider->value());
    ui.spellInfoText->setText(spell->PrintBaseInfo(selectedLevel) + "<br>" + spell->PrintSpellEffectInfo(selectedLevel, comboPoints));
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

        UpdateAdvFilterStatus(hasBasicFilters || hasSpellFieldFilters || hasSpellEffectFilters);
    };

    filter->open();
}

void MainWindow::onClearResultsBtn()
{
    spellInfoTab.m_selectedSpellRowId = -1;
    ui.spellIdNameInput->clear();
    ui.resultCountLabel->setText("Found 0 results");
    ui.levelScalingSlider->setValue(1);
    ui.levelScalingText->setText("Selected Level 1, (max 85)");
    ui.comboPointsSlider->setValue(0);
    ui.comboScalingText->setText("Combo Points: 0");
    ui.spellInfoText->clear();
    ClearResults(ui.resultList);
}

// General functions
/*static*/ void MainWindow::PerformSpellSearch(QStringView spellNameOrId, bool searchById, bool searchByName, QTableWidget* resultList, const SpellWork::Filters::SpellSearchFilter& filter, QLabel* resultCounterLabel)
{
    assert(resultList != nullptr);
    const auto startMS = QDateTime::currentMSecsSinceEpoch();

    ClearResults(resultList);

    if (sDataStorage->GetSpellEntries().empty())
    {
        if (resultCounterLabel != nullptr)
        {
            resultCounterLabel->setText(QString("Found: 0 records in %1 milliseconds").arg(QDateTime::currentMSecsSinceEpoch() - startMS));
        }
        return;
    }

    uint32_t spellId = 0;
    if (!searchById && !searchByName)
    {
        resultCounterLabel->setText(QString("Found: 0 records in %1 milliseconds").arg(QDateTime::currentMSecsSinceEpoch() - startMS));
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

    if (const auto* spellFamily = filter.m_genericFilter.GetSpellFamily())
    {
        spellFamilyId = *spellFamily;
    }

    if (const auto* spellAuraType = filter.m_genericFilter.GetSpellAuraType())
    {
        auraTypeId = *spellAuraType;
    }

    if (const auto* spellEffect = filter.m_genericFilter.GetSpellEffect())
    {
        spellEffectId = *spellEffect;
    }

    if (const auto* spellTarget_A = filter.m_genericFilter.GetSpellTargetA())
    {
        spellTargetA = *spellTarget_A;
    }

    if (const auto* spelltarget_B = filter.m_genericFilter.GetSpellTargetB())
    {
        spellTargetB = *spelltarget_B;
    }

    std::array<DBCFieldDataCompare, 2> spellAttrFilter;
    std::array<DBCFieldDataCompare, 2> spellEffectAttrFilter;
    for (uint8_t i = 0; i < 2; ++i)
    {
        // Spell.dbc filter
        {
            const auto& spellDbcFilter = filter.m_spellEntryFieldsFilter.at(i);
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
            const auto& spellEffectsDbcFilter = filter.m_spellEffectFieldsFilter.at(i);
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

        if (canInsert)
        {
            int rowId = resultList->rowCount();
            resultList->insertRow(rowId);
            resultList->setItem(rowId, 0, new QTableWidgetItem(QString::number(_id)));
            resultList->setItem(rowId, 1, new QTableWidgetItem(_spellInfo.getSpellName()));
        }
    }

    resultCounterLabel->setText(QString("Found: %1 records in %2 milliseconds").arg(resultList->rowCount()).arg(QDateTime::currentMSecsSinceEpoch() - startMS));
}

/*static*/ void MainWindow::ClearResults(QTableWidget* resultList)
{
    for (int row = 0; row < resultList->rowCount(); ++row)
    {
        for (int col = 0; col < resultList->columnCount(); ++col)
        {
            QWidget *widget = resultList->cellWidget(row, col);
            if (widget) {
                delete widget;
            }
        }
    }

    resultList->clear();
    resultList->setColumnCount(2);
    resultList->setRowCount(0);
    resultList->verticalHeader()->setVisible(false);
    resultList->setHorizontalHeaderLabels(QStringList() << "ID" << "Name");
    resultList->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    resultList->horizontalHeader()->resizeSection(0, 55);
}
