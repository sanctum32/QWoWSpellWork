#pragma once
#include <QDialog>
#include "ui/ui_searchFilter.h"

QT_BEGIN_NAMESPACE
namespace Ui { class SearchFilter; }
QT_END_NAMESPACE

class MainWindow;
class QAbstractButton;

class SearchFilter : public QDialog
{
    Q_OBJECT
    friend class MainWindow;
public:
    SearchFilter(MainWindow* parent);

private slots:
    void onButtonClicked(QAbstractButton* button);

private:
    MainWindow* GetMainWindow();

    void closeEvent(QCloseEvent* /*e*/) override;
    void showEvent(QShowEvent *event) override;

    struct
    {
        int spellFamily{-1};
        int spellAuraType{-1};
        int spellEffect{-1};
        int spellTargetA{-1};
        int spellTargetB{-1};
    } genericFilter;

    struct
    {
        std::array<int, 2> conditionFieldName{-1, -1};
        std::array<int, 2> conditionCompareType{-1, -1};
        std::array<QString, 2> conditionValue;

        bool HasData(uint8_t id) const
        {
            return id < 2 && conditionFieldName[id] != -1 && conditionCompareType[id] != -1 && !conditionValue.empty();
        }
    } spellAttributesFilter;

    Ui::SearchFilter ui;
};
