#pragma once

#include "ui/ui_mainwindow.h"
#include <QMainWindow>
#include <QLabel>

// Forward declarations
class QTableWidgetItem;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void UpdateSqlStatus(bool success);
    void UpdateDBCStatus(bool success);
    void UpdateJsonStatus(bool success);
    void UpdateComboBoxItems();

private slots:
    void onSearchBtnClicked();
    void onSpellIdNameInputReturnPressed();
    void onResultListClick(QTableWidgetItem *item);
    void onLevelScalingSliderValueChange();

private:
    Ui::MainWindow ui;
    QLabel m_dbcStatus;
    QLabel m_jsonStatus;
    QLabel m_sqlStatus;

// Generic functions
    void PerformSpellSearch();

protected:
};

extern MainWindow* _mainWindow;
