#pragma once
#include "ui/ui_mainwindow.h"
#include <QMainWindow>
#include <QLabel>
#include <QLoggingCategory>

Q_DECLARE_LOGGING_CATEGORY(SPELLINFO_TAB)

// Forward declarations
class QTableWidgetItem;

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
    void UpdateJsonStatus(bool success);
    void UpdateFilterStatus(bool hasFilter);

private slots:
    void onSearchBtnClicked();
    void onSpellIdNameInputReturnPressed();
    void onResultListClick(QTableWidgetItem *item);
    void onLevelScalingSliderValueChange();
    void onFiltersBtnClick();

private:
    Ui::MainWindow ui;
    QLabel m_dbcStatus;
    QLabel m_jsonStatus;
    QLabel m_sqlStatus;

// Generic functions
    void PerformSpellSearch();
};
