#pragma once
#include <QDialog>
#include "ui/ui_searchFilter.h"

namespace SpellWork::Filters
{
    struct SpellSearchFilter;
};

QT_BEGIN_NAMESPACE
namespace Ui { class SearchFilterForm; }
QT_END_NAMESPACE

class QAbstractButton;

class SearchFilterForm : public QDialog
{
    Q_OBJECT

public:
    SearchFilterForm(SpellWork::Filters::SpellSearchFilter* filterData, QWidget* parent = nullptr);

    // used to perform certain tasks on form closure or settings applying
    std::function<void()> OnCloseOrApplyEventFn;
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
    Ui::SearchFilterForm ui;
    SpellWork::Filters::SpellSearchFilter* m_filterData;
};
