#include "mainwindow.hpp"
#include "searchFilter.hpp"
#include "ui/ui_mainwindow.h"
#include <QCloseEvent>

Q_LOGGING_CATEGORY(SPELLINFO_TAB, "spellwork.json");

// Base implementation
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    ui.setupUi(this);

    m_searchFilter = std::make_unique<SearchFilter>(this);

    // resultList
    ui.resultList->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    ui.resultList->horizontalHeader()->resizeSection(0, 55);

    // statusBar
    ui.statusBar->addPermanentWidget(&m_dbcStatus);
    ui.statusBar->addPermanentWidget(&m_jsonStatus);
    ui.statusBar->addPermanentWidget(&m_sqlStatus);

    // Signal connections
    QObject::connect(ui.searchBtn,        &QPushButton::clicked,     this, &MainWindow::onSearchBtnClicked);
    QObject::connect(ui.spellIdNameInput, &QLineEdit::returnPressed, this, &MainWindow::onSpellIdNameInputReturnPressed);
    QObject::connect(ui.resultList,       &QTableWidget::itemClicked,    this, &MainWindow::onResultListClick);
    QObject::connect(ui.levelScalingSlider, &QSlider::valueChanged, this, &MainWindow::onLevelScalingSliderValueChange);
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
