#pragma once
#include <QDialog>
#include "ui/ui_searchFilter.h"

QT_BEGIN_NAMESPACE
namespace Ui { class SearchFilter; }
QT_END_NAMESPACE

class MainWindow;
class QAbstractButton;
class SearchFilter;

class SearchFilter : public QDialog
{
    Q_OBJECT

public:
    SearchFilter(QWidget* parent);

private slots:
    void onButtonClicked(QAbstractButton* button);

private:
    void closeEvent(QCloseEvent* /*e*/) override;
    void showEvent(QShowEvent *event) override;

    Ui::SearchFilter ui;
};
