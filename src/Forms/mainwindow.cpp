#include "mainwindow.hpp"
#include "DBCStructures.hpp"
#include "ui/ui_mainwindow.h"
#include "JsonData/JsonData.hpp"
#include <QCloseEvent>

Q_LOGGING_CATEGORY(SPELLINFO_TAB, "spellwork.json");
MainWindow* _mainWindow = nullptr;

// Base implementation
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    ui.setupUi(this);

    // resultList
    ui.resultList->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    ui.resultList->horizontalHeader()->resizeSection(0, 55);

    // statusBar
    ui.statusBar->addPermanentWidget(&m_dbcStatus);
    ui.statusBar->addPermanentWidget(&m_jsonStatus);
    ui.statusBar->addPermanentWidget(&m_sqlStatus);

    // Init advanced filter types
    for (auto const& itr : SpellEntryFields)
    {
        ui.advFilterTypes1->addItem(itr.second.first);
        ui.advFilterTypes2->addItem(itr.second.first);
    }

    constexpr std::array<const char*, 11> ConditionCompareTypeStr =
    {
        "x != y",           // 0
        "x == y",           // 1
        "x > y",            // 2
        "x >= y",           // 3
        "x < y",            // 4
        "x <= y",           // 5
        "(x & y) != 0",     // 6
        "(x & y) == 0",     // 7
        "x Starts With y",  // 8
        "x Ends With y",    // 9
        "x Contains y"      // 10
    };

    for (auto const* str : ConditionCompareTypeStr)
    {
        ui.advFilterCondition1->addItem(str);
        ui.advFilterCondition2->addItem(str);
    }

    // Signal connections
    QObject::connect(ui.searchBtn,        &QPushButton::clicked,     this, &MainWindow::onSearchBtnClicked);
    QObject::connect(ui.spellIdNameInput, &QLineEdit::returnPressed, this, &MainWindow::onSpellIdNameInputReturnPressed);
    QObject::connect(ui.resultList,       &QTableWidget::itemClicked,    this, &MainWindow::onResultListClick);
    QObject::connect(ui.levelScalingSlider, &QSlider::valueChanged, this, &MainWindow::onLevelScalingSliderValueChange);
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

void MainWindow::UpdateComboBoxItems()
{
    // SpellFamilyFilter
    for (const auto& spellFamily : sSpellWorkJson->SpellFamilyInfo)
    {
        ui.SpellFamilyFilter->addItem(spellFamily.second);
    }
    ui.SpellFamilyFilter->setEditable(true);
    ui.SpellFamilyFilter->setMaxVisibleItems(10);

    // SpellAuraTypeFilter
    for (const auto& spellAuraTypes : sSpellWorkJson->_spellAuraTypes)
    {
        ui.SpellAuraTypeFilter->addItem(spellAuraTypes.second.name);
    }
    ui.SpellAuraTypeFilter->setEditable(true);
    ui.SpellAuraTypeFilter->setMaxVisibleItems(10);

    // SpellEffectFilter
    for (const auto& spellEffect : sSpellWorkJson->_spellEffectInfo)
    {
        ui.SpellEffectFilter->addItem(spellEffect.second.name);
    }
    ui.SpellEffectFilter->setEditable(true);
    ui.SpellEffectFilter->setMaxVisibleItems(10);

    // SpellTargetFilterA
    for (const auto& targetName : sSpellWorkJson->SpellTargetNames)
    {
        ui.SpellTargetFilterA->addItem(targetName.second);
    }
    ui.SpellTargetFilterA->setEditable(true);
    ui.SpellTargetFilterA->setMaxVisibleItems(10);

    // SpellTargetFilterB
    for (const auto& targetName : sSpellWorkJson->SpellTargetNames)
    {
        ui.SpellTargetFilterB->addItem(targetName.second);
    }
    ui.SpellTargetFilterB->setEditable(true);
    ui.SpellTargetFilterB->setMaxVisibleItems(10);
}
