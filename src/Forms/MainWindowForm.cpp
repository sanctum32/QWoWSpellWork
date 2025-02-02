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

    // resultList
    ui.resultList->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    ui.resultList->horizontalHeader()->resizeSection(0, 55);

    // statusBar
    ui.statusBar->addPermanentWidget(&m_dbcStatus);
    ui.statusBar->addPermanentWidget(&m_db2Status);
    ui.statusBar->addPermanentWidget(&m_jsonStatus);
    ui.statusBar->addPermanentWidget(&m_sqlStatus);

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
        m_sqlStatus.setText("SQL: <span style=\"color:green\">connected</span>");
    }
    else
    {
        m_sqlStatus.setText("SQL: <span style=\"color:red\">not connected</span>");
    }
}

void MainWindow::UpdateDBCStatus(bool success)
{
    if (success)
    {
        m_dbcStatus.setText("DBC: <span style=\"color:green\">loaded</span>");
    }
    else
    {
        m_dbcStatus.setText("DBC: <span style=\"color:red\">not loaded</span>");
    }
}

void MainWindow::UpdateDB2Status(bool success)
{
    if (success)
    {
        m_db2Status.setText("DB2: <span style=\"color:green\">loaded</span>");
    }
    else
    {
        m_db2Status.setText("DB2: <span style=\"color:red\">not loaded</span>");
    }
}

void MainWindow::UpdateJsonStatus(bool success)
{
    if (success)
    {
        m_jsonStatus.setText("JSON: <span style=\"color:green\">loaded</span>");
    }
    else
    {
        m_jsonStatus.setText("JSON: <span style=\"color:red\">not loaded</span>");
    }
}

void MainWindow::UpdateFilterStatus(bool hasFilter)
{
    if (hasFilter)
    {
        ui.filtersStatus->setText("Extra filters: <span style=\"color:green\">active</span>");
    }
    else
    {
        ui.filtersStatus->setText("Extra filters: <span style=\"color:red\">inactive</span>");
    }
}

// General functions
/*static*/ void MainWindow::PerformSpellSearch(QStringView spellNameOrId, bool searchById, bool searchByName, QTableWidget* resultList, const SpellWork::Filters::SpellSearchFilter& filter, QLabel* resultCounterLabel)
{
    assert(resultList != nullptr);
    const auto startMS = QDateTime::currentMSecsSinceEpoch();

    resultList->clearContents();

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
        if (resultCounterLabel != nullptr)
        {
            resultCounterLabel->setText(QString("Found: 0 records in %1 milliseconds").arg(QDateTime::currentMSecsSinceEpoch() - startMS));
        }
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

    if (resultCounterLabel != nullptr)
    {
        resultCounterLabel->setText(QString("Found: %1 records in %2 milliseconds").arg(QString::number(foundEntries.size())).arg(QDateTime::currentMSecsSinceEpoch() - startMS));
    }
}
