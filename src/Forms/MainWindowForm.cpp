#include "MainWindowForm.hpp"
#include "DataStorage.hpp"
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
    ui.resultList->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    ui.resultList->horizontalHeader()->resizeSection(0, 55);

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

// General functions
/*static*/ void MainWindow::PerformSpellSearch(QStringView spellNameOrId, bool searchById, bool searchByName, QTableWidget* resultList, const SpellWork::Filters::SpellSearchFilter& filter, QLabel* resultCounterLabel)
{
    assert(resultList != nullptr);
    const auto startMS = QDateTime::currentMSecsSinceEpoch();

    for (int row = 0; row < resultList->rowCount(); ++row) {
        for (int col = 0; col < resultList->columnCount(); ++col) {
            QWidget *widget = resultList->cellWidget(row, col);
            if (widget) {
                delete widget;  // Free allocated memory
            }
        }
    }

    resultList->clear();
    resultList->setColumnCount(2);
    resultList->setRowCount(0);
    resultList->verticalHeader()->setVisible(false);
    resultList->setHorizontalHeaderLabels(QStringList() << "ID" << "Name");

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
