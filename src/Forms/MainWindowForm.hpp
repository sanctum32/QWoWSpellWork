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

private slots:
    void onSearchBtnClicked();
    void onSpellIdNameInputReturnPressed();
    void onResultListClick(QTableWidgetItem *item);
    void onScalingSliderUpdate();
    void onFiltersBtnClick();
    void onClearResultsBtn();

private:
    Ui::MainWindow ui;

    SpellWork::Filters::SpellSearchFilter m_searchFilterData;

    // Shared functions
    void PerformSpellSearch();
    void ClearAndResetSearchResults();
};
