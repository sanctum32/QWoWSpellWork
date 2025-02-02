#pragma once
#include <QDialog>
#include "ui/ui_searchFilter.h"

QT_BEGIN_NAMESPACE
namespace Ui { class SearchFilter; }
QT_END_NAMESPACE

class QAbstractButton;

class SearchFilter : public QDialog
{
    Q_OBJECT

public:
    SearchFilter(QWidget* parent = nullptr);

private slots:
    void onButtonClicked(QAbstractButton* button);

    // Generic filter
    void spellFamilyResetBtnClick();
    void spellAuraEffResetBtnClick();
    void spellEffResetBtnClick();
    void spellTargetAResetBtnClick();
    void spellTargetBResetBtnClick();

    // Spell entry attributes
    void spellAttrFilter0ResetBtnClick();
    void spellAttrFilter1ResetBtnClick();

    // Spell effect entry attributes
    void effectAttrFilter0ResetBtnClick();
    void effectAttrFilter1ResetBtnClick();

private:
    void closeEvent(QCloseEvent* /*e*/) override;
    void showEvent(QShowEvent *event) override;
    Ui::SearchFilter ui;
};
