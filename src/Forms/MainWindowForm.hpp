#pragma once
#include "SpellSearchFilter.hpp"
#include "ui/ui_mainwindow.h"
#include <QMainWindow>
#include <QLabel>
#include <QLoggingCategory>
#include <QTableWidget>

Q_DECLARE_LOGGING_CATEGORY(SPELLINFO_TAB)

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    friend class SearchFilter;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void UpdateSqlStatus(bool success);
    void UpdateAdvFilterStatus(bool hasFilter);

private slots:
    void onSearchBtnClicked();
    void onSpellIdNameInputReturnPressed();
    void onResultListClick(QTableWidgetItem *item);
    void onScalingSliderUpdate();
    void onFiltersBtnClick();
    void onClearResultsBtn();

private:
    Ui::MainWindow ui;
    QLabel m_connectionStatusLabel;
    QLabel m_advFilterStatusLabel;

    struct
    {
        SpellWork::Filters::SpellSearchFilter m_spellSearchFilter;

        // Stores selected spell result list row id
        int32_t m_selectedSpellRowId{-1};
    } spellInfoTab;

    // Generic functions
    static void PerformSpellSearch(QStringView spellNameOrId, bool searchById, bool searchByName, QTableWidget* resultList, const SpellWork::Filters::SpellSearchFilter& filter, QLabel* resultCounterLabel);
    static void ClearResults(QTableWidget* resultList);
};
