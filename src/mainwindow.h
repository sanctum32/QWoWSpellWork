#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>
#include <QMainWindow>
#include <QLabel>
#include <QTableWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onSearchBtnClicked();
    void onSpellIdNameInputReturnPressed();
    void onResultListClick(QTableWidgetItem *item);
    void onLevelScalingSliderValueChange();

private:
    std::unique_ptr<Ui::MainWindow> ui;

    // Generic functions
    void PerformSpellSearch();
};
#endif // MAINWINDOW_H
