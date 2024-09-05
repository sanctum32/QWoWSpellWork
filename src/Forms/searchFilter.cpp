#include "mainwindow.hpp"
#include "DBCStructures.hpp"
#include "JsonData.hpp"

SearchFilter::SearchFilter(MainWindow *parent) : QDialog(parent)
{
    ui.setupUi(this);

    // SpellFamilyFilter
    for (const auto& [id, name] : sSpellWorkJson->GetSpellFamilyData())
    {
        ui.SpellFamilyFilter->addItem(name, id);
    }

    // SpellAuraTypeFilter
    for (const auto& [id, auraType] : sSpellWorkJson->GetSpellAuraEffectData())
    {
        ui.SpellAuraTypeFilter->addItem(auraType.name, id);
    }

    // SpellEffectFilter
    for (const auto& [id, effect] : sSpellWorkJson->GetSpellEffectData())
    {
        ui.SpellEffectFilter->addItem(effect.name, id);
    }

    // SpellTargetFilter
    for (const auto& [id, name] : sSpellWorkJson->GetSpellTargetData())
    {
        ui.SpellTargetFilterA->addItem(name, id);
        ui.SpellTargetFilterB->addItem(name, id);
    }

    // Init advanced filter types
    for (auto const& [fieldId, fieldInfo] : SpellEntryFields)
    {
        ui.spellAttrFieldName0->addItem(fieldInfo.fieldName, fieldId);
        ui.spellAttrFieldName1->addItem(fieldInfo.fieldName, fieldId);
    }

    for (auto const& [fieldId, fieldInfo] : SpellEffectEntryFields)
    {
        ui.effectFieldName0->addItem(fieldInfo.fieldName, fieldId);
        ui.effectFieldName1->addItem(fieldInfo.fieldName, fieldId);
    }

    constexpr std::array<const char*, 11> ConditionCompareTypeStr =
    {
        "x != y",           // 0
        "x == y",           // 1
        "x > y",            // 2
        "x >= y",           // 3
        "x < y",            // 4
        "x <= y",           // 5
        "(x & y) != 0",     // 6
        "(x & y) == 0",     // 7
        "x Starts With y",  // 8
        "x Ends With y",    // 9
        "x Contains y"      // 10
    };

    uint8_t idVal = 0;
    for (auto const* str : ConditionCompareTypeStr)
    {
        ui.spellAttrCompareType0->addItem(str, idVal);
        ui.spellAttrCompareType1->addItem(str, idVal);
        ui.effectAttrCompareType0->addItem(str, idVal);
        ui.effectAttrCompareType1->addItem(str, idVal);
        ++idVal;
    }

    QObject::connect(ui.buttonBox, &QDialogButtonBox::clicked, this, &SearchFilter::onButtonClicked);
}

void SearchFilter::onButtonClicked(QAbstractButton* button)
{
    const auto* buttonBox = qobject_cast<QDialogButtonBox*>(sender());
    if (buttonBox == nullptr)
    {
        return;
    }

    switch (buttonBox->standardButton(button))
    {
    case QDialogButtonBox::Ok:
    {
        genericFilter.spellFamily = ui.SpellFamilyFilter->currentIndex();
        genericFilter.spellAuraType = ui.SpellAuraTypeFilter->currentIndex();
        genericFilter.spellEffect = ui.SpellEffectFilter->currentIndex();
        genericFilter.spellTargetA = ui.SpellTargetFilterA->currentIndex();
        genericFilter.spellTargetB = ui.SpellTargetFilterB->currentIndex();

        spellAttributesFilter.conditionCompareType[0] = ui.spellAttrCompareType0->currentIndex();
        spellAttributesFilter.conditionCompareType[1] = ui.spellAttrCompareType1->currentIndex();
        spellAttributesFilter.conditionFieldName[0] = ui.spellAttrFieldName0->currentIndex();
        spellAttributesFilter.conditionFieldName[1] = ui.spellAttrFieldName1->currentIndex();
        spellAttributesFilter.conditionValue[0] = ui.spellAttrInput0->text();
        spellAttributesFilter.conditionValue[1] = ui.spellAttrInput1->text();
    }
    [[fallthrough]];
    case QDialogButtonBox::Cancel:
    {
        if (auto* mainWindow = GetMainWindow())
        {
            mainWindow->setEnabled(true);
            if (genericFilter.HasData() || spellAttributesFilter.HasData())
            {
                mainWindow->ui.filtersStatus->setText("Extra filters: <span style=\"color:green\">active</span>");
            }
            else
            {
                mainWindow->ui.filtersStatus->setText("Extra filters: <span style=\"color:red\">inactive</span>");
            }
        }
    }
    case QDialogButtonBox::Reset:
    {
        ui.SpellFamilyFilter->setCurrentIndex(-1);
        ui.SpellAuraTypeFilter->setCurrentIndex(-1);
        ui.SpellEffectFilter->setCurrentIndex(-1);
        ui.SpellTargetFilterA->setCurrentIndex(-1);
        ui.SpellTargetFilterB->setCurrentIndex(-1);

        //spellAttributesFilter
        ui.spellAttrCompareType0->setCurrentIndex(-1);
        ui.spellAttrCompareType1->setCurrentIndex(-1);
        ui.spellAttrFieldName0->setCurrentIndex(-1);
        ui.spellAttrFieldName1->setCurrentIndex(-1);
        ui.spellAttrInput0->clear();
        ui.spellAttrInput1->clear();
        break;
    }
    default:
        break;
    }
}

MainWindow* SearchFilter::GetMainWindow()
{
    return qobject_cast<MainWindow*>(this->parent());
}

void SearchFilter::closeEvent(QCloseEvent* /*e*/)
{
    if (MainWindow* mainWindow = GetMainWindow())
    {
        mainWindow->setEnabled(true);
        if (genericFilter.HasData() || spellAttributesFilter.HasData())
        {
            mainWindow->ui.filtersStatus->setText("Extra filters: <span style=\"color:green\">active</span>");
        }
        else
        {
            mainWindow->ui.filtersStatus->setText("Extra filters: <span style=\"color:red\">inactive</span>");
        }
    }
}

void SearchFilter::showEvent(QShowEvent* /*event*/)
{
    ui.SpellFamilyFilter->setCurrentIndex(genericFilter.spellFamily);
    ui.SpellAuraTypeFilter->setCurrentIndex(genericFilter.spellAuraType);
    ui.SpellEffectFilter->setCurrentIndex(genericFilter.spellEffect);
    ui.SpellTargetFilterA->setCurrentIndex(genericFilter.spellTargetA);
    ui.SpellTargetFilterB->setCurrentIndex(genericFilter.spellTargetB);

    ui.spellAttrCompareType0->setCurrentIndex(spellAttributesFilter.conditionCompareType[0]);
    ui.spellAttrCompareType1->setCurrentIndex(spellAttributesFilter.conditionCompareType[1]);
    ui.spellAttrFieldName0->setCurrentIndex(spellAttributesFilter.conditionFieldName[0]);
    ui.spellAttrFieldName1->setCurrentIndex(spellAttributesFilter.conditionFieldName[1]);
    ui.spellAttrInput0->setText(spellAttributesFilter.conditionValue[0]);
    ui.spellAttrInput1->setText(spellAttributesFilter.conditionValue[1]);
}
