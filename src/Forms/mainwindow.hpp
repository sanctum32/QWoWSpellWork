#pragma once
#include "ui/ui_mainwindow.h"
#include <QMainWindow>
#include <QLabel>
#include <QLoggingCategory>

Q_DECLARE_LOGGING_CATEGORY(SPELLINFO_TAB)

// Forward declarations
class QTableWidgetItem;
class SearchFilter;

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
    void UpdateDBCStatus(bool success);
    void UpdateDB2Status(bool success);
    void UpdateJsonStatus(bool success);
    void UpdateFilterStatus(bool hasFilter);

private slots:
    void onSearchBtnClicked();
    void onSpellIdNameInputReturnPressed();
    void onResultListClick(QTableWidgetItem *item);
    void onScalingSliderUpdate();
    void onFiltersBtnClick();
    void onClearResultsBtn();

private:
    Ui::MainWindow ui;
    QLabel m_dbcStatus;
    QLabel m_db2Status;
    QLabel m_jsonStatus;
    QLabel m_sqlStatus;

    std::unique_ptr<SearchFilter> m_searchFilter;

// Generic functions
    void PerformSpellSearch();
    int32_t m_lastSpellSearchRowId{-1};    // Last select search list row id
};
