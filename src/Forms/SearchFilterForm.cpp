#include <QMessageBox>
#include <QCloseEvent>

#include "SearchFilterForm.hpp"
#include "SpellSearchFilter.hpp"
#include "ValueComparition.hpp"
#include "DBCStructures.hpp"
#include "JsonData.hpp"

SearchFilterForm::SearchFilterForm(SpellWork::Filters::SpellSearchFilter *filterData, QWidget* parent /*= nullptr*/) : QDialog(parent), m_filterData(filterData)
{
    assert(m_filterData != nullptr);
    ui.setupUi(this);

    // SpellFamilyFilter
    for (const auto& [id, name] : sSpellWorkJson->GetSpellFamilyData())
    {
        ui.SpellFamilyFilter->addItem(QString("%1 - %2").arg(id).arg(name), id);
    }

    // SpellAuraTypeFilter
    for (const auto& [id, auraType] : sSpellWorkJson->GetSpellAuraEffectData())
    {
        ui.SpellAuraTypeFilter->addItem(QString("%1 - %2").arg(id).arg(auraType.name), id);
    }

    // SpellEffectFilter
    for (const auto& [id, effect] : sSpellWorkJson->GetSpellEffectData())
    {
        ui.SpellEffectFilter->addItem(QString("%1 - %2").arg(id).arg(effect.name), id);
    }

    // SpellTargetFilter
    for (const auto& [id, name] : sSpellWorkJson->GetSpellTargetData())
    {
        ui.SpellTargetFilterA->addItem(QString("%1 - %2").arg(id).arg(name), id);
        ui.SpellTargetFilterB->addItem(QString("%1 - %2").arg(id).arg(name), id);
    }

    // Init advanced filter types
    for (auto const& [fieldId, fieldData] : SpellEntryFields)
    {
        ui.spellAttrFieldName0->addItem(QString("%1 - %2").arg(fieldId).arg(fieldData.fieldName), fieldId);
        ui.spellAttrFieldName1->addItem(QString("%1 - %2").arg(fieldId).arg(fieldData.fieldName), fieldId);
    }

    for (auto const& [fieldId, fieldData] : SpellEffectEntryFields)
    {
        ui.effectFieldName0->addItem(QString("%1 - %2").arg(fieldId).arg(fieldData.fieldName), fieldId);
        ui.effectFieldName1->addItem(QString("%1 - %2").arg(fieldId).arg(fieldData.fieldName), fieldId);
    }

    uint8_t idVal = 0;
    for (auto const* str : ConditionCompareTypeStr)
    {
        ui.spellAttrCompareType0->addItem(str, idVal);
        ui.spellAttrCompareType1->addItem(str, idVal);
        ui.effectAttrCompareType0->addItem(str, idVal);
        ui.effectAttrCompareType1->addItem(str, idVal);
        ++idVal;
    }

    QObject::connect(ui.buttonBox, &QDialogButtonBox::clicked, this, &SearchFilterForm::onButtonClicked);
    QObject::connect(ui.spellFamilyResetBtn, &QPushButton::clicked, this, &SearchFilterForm::spellFamilyResetBtnClick);
    QObject::connect(ui.SpellAuraEffResetBtn, &QPushButton::clicked, this, &SearchFilterForm::spellAuraEffResetBtnClick);
    QObject::connect(ui.SpellEffResetBtn, &QPushButton::clicked, this, &SearchFilterForm::spellEffResetBtnClick);
    QObject::connect(ui.SpellTargetAResetBtn, &QPushButton::clicked, this, &SearchFilterForm::spellTargetAResetBtnClick);
    QObject::connect(ui.SpellTargetBResetBtn, &QPushButton::clicked, this, &SearchFilterForm::spellTargetBResetBtnClick);
    QObject::connect(ui.SpellAttrFilter0ResetBtn, &QPushButton::clicked, this, &SearchFilterForm::spellAttrFilter0ResetBtnClick);
    QObject::connect(ui.SpellAttrFilter1ResetBtn, &QPushButton::clicked, this, &SearchFilterForm::spellAttrFilter1ResetBtnClick);
    QObject::connect(ui.EffectAttrFilter0ResetBtn, &QPushButton::clicked, this, &SearchFilterForm::effectAttrFilter0ResetBtnClick);
    QObject::connect(ui.EffectAttrFilter1ResetBtn, &QPushButton::clicked, this, &SearchFilterForm::effectAttrFilter1ResetBtnClick);
}

void SearchFilterForm::onButtonClicked(QAbstractButton* button)
{
    const auto* buttonBox = qobject_cast<QDialogButtonBox*>(sender());
    if (buttonBox == nullptr)
    {
        return;
    }

    switch (buttonBox->standardButton(button))
    {
    case QDialogButtonBox::Apply:
    {
        // Generic filter
        {
            auto& genericFilter = m_filterData->m_genericFilter;
            // SpellFamily
            {
                auto& [id, value] = genericFilter.m_spellFamily;
                id = ui.SpellFamilyFilter->currentIndex();
                value = ui.SpellFamilyFilter->itemData(id).toUInt();
            }
            // SpellAuraType
            {
                auto& [id, value] = genericFilter.m_spellAuraType;
                id = ui.SpellAuraTypeFilter->currentIndex();
                value = ui.SpellAuraTypeFilter->itemData(id).toUInt();
            }
            // SpellEffect
            {
                auto& [id, value] = genericFilter.m_spellEffect;
                id = ui.SpellEffectFilter->currentIndex();
                value = ui.SpellEffectFilter->itemData(id).toUInt();
            }
            // SpellTargetA
            {
                auto& [id, value] = genericFilter.m_spellTargetA;
                id = ui.SpellTargetFilterA->currentIndex();
                value = ui.SpellTargetFilterA->itemData(id).toUInt();
            }
            // SpellTargetB
            {
                auto& [id, value] = genericFilter.m_spellTargetB;
                id = ui.SpellTargetFilterB->currentIndex();
                value = ui.SpellTargetFilterB->itemData(id).toUInt();
            }
        }

        // Spell entry filter
        {
            // Filter 0
            {
                auto& filter = m_filterData->m_spellEntryFieldsFilter.at(0);
                // Field id
                {
                    auto& [id, value] = filter.m_entryField;
                    id = ui.spellAttrFieldName0->currentIndex();
                    value = ui.spellAttrFieldName0->itemData(id).toUInt();
                }
                // Compare type
                {
                    auto& [id, value] = filter.m_compareType;
                    id = ui.spellAttrCompareType0->currentIndex();
                    value = ui.spellAttrCompareType0->itemData(id).toUInt();
                }
                filter.m_compareValue = ui.spellAttrInput0->text();
            }
            // Filter 1
            {
                auto& filter = m_filterData->m_spellEntryFieldsFilter.at(1);
                // Field id
                {
                    auto& [id, value] = filter.m_entryField;
                    id = ui.spellAttrFieldName1->currentIndex();
                    value = ui.spellAttrFieldName1->itemData(id).toUInt();
                }
                // Compare type
                {
                    auto& [id, value] = filter.m_compareType;
                    id = ui.spellAttrCompareType1->currentIndex();
                    value = ui.spellAttrCompareType1->itemData(id).toUInt();
                }

                filter.m_compareValue = ui.spellAttrInput1->text();
            }
        }
        // Spell effect filter
        {
            auto& genericFilter = m_filterData->m_genericFilter;
            // Filter 0
            {
                auto& filter = m_filterData->m_spellEffectFieldsFilter.at(0);
                // Field id
                {
                    auto& [id, value] = filter.m_entryField;
                    id = ui.effectFieldName0->currentIndex();
                    value = ui.effectFieldName0->itemData(id).toUInt();
                }
                // Compare type
                {
                    auto& [id, value] = filter.m_compareType;
                    id = ui.effectAttrCompareType0->currentIndex();
                    value = ui.effectAttrCompareType0->itemData(id).toUInt();
                }
                filter.m_compareValue = ui.effectAttrInput0->text();
            }
            // Filter 1
            {
                auto& filter = m_filterData->m_spellEffectFieldsFilter.at(1);
                // Field id
                {
                    auto& [id, value] = filter.m_entryField;
                    id = ui.effectFieldName1->currentIndex();
                    value = ui.effectFieldName1->itemData(id).toUInt();
                }
                // Compare type
                {
                    auto& [id, value] = filter.m_compareType;
                    id = ui.effectAttrCompareType1->currentIndex();
                    value = ui.effectAttrCompareType1->itemData(id).toUInt();
                }
                filter.m_compareValue = ui.effectAttrInput1->text();
            }
        }

        OnCloseOrApplyEventFn();

        QMessageBox msgBox;
        msgBox.setText("Filter settings were applied!");
        msgBox.setIcon(QMessageBox::Information);
        msgBox.exec();
    }break;
    case QDialogButtonBox::Cancel:
    case QDialogButtonBox::Close:
    {
        OnCloseOrApplyEventFn();
    }
    case QDialogButtonBox::Reset:
    {
        ui.SpellFamilyFilter->setCurrentIndex(-1);
        ui.SpellAuraTypeFilter->setCurrentIndex(-1);
        ui.SpellEffectFilter->setCurrentIndex(-1);
        ui.SpellTargetFilterA->setCurrentIndex(-1);
        ui.SpellTargetFilterB->setCurrentIndex(-1);

        // spell attributes filter
        ui.spellAttrCompareType0->setCurrentIndex(-1);
        ui.spellAttrCompareType1->setCurrentIndex(-1);
        ui.spellAttrFieldName0->setCurrentIndex(-1);
        ui.spellAttrFieldName1->setCurrentIndex(-1);
        ui.spellAttrInput0->clear();
        ui.spellAttrInput1->clear();

        // spell effect attributes filter
        ui.effectFieldName0->setCurrentIndex(-1);
        ui.effectAttrCompareType0->setCurrentIndex(-1);
        ui.effectAttrInput0->clear();
        ui.effectFieldName1->setCurrentIndex(-1);
        ui.effectAttrCompareType1->setCurrentIndex(-1);
        ui.effectAttrInput1->clear();
        break;
    }
    default:
        break;
    }
}

void SearchFilterForm::spellFamilyResetBtnClick()
{
    ui.SpellFamilyFilter->setCurrentIndex(-1);
}

void SearchFilterForm::spellAuraEffResetBtnClick()
{
    ui.SpellAuraTypeFilter->setCurrentIndex(-1);
}

void SearchFilterForm::spellEffResetBtnClick()
{
    ui.SpellEffectFilter->setCurrentIndex(-1);
}

void SearchFilterForm::spellTargetAResetBtnClick()
{
    ui.SpellTargetFilterA->setCurrentIndex(-1);
}

void SearchFilterForm::spellTargetBResetBtnClick()
{
    ui.SpellTargetFilterB->setCurrentIndex(-1);
}

void SearchFilterForm::spellAttrFilter0ResetBtnClick()
{
    ui.spellAttrFieldName0->setCurrentIndex(-1);
    ui.spellAttrCompareType0->setCurrentIndex(-1);
    ui.spellAttrInput0->clear();
}

void SearchFilterForm::spellAttrFilter1ResetBtnClick()
{
    ui.spellAttrFieldName1->setCurrentIndex(-1);
    ui.spellAttrCompareType1->setCurrentIndex(-1);
    ui.spellAttrInput1->clear();
}

void SearchFilterForm::effectAttrFilter0ResetBtnClick()
{
    ui.effectFieldName0->setCurrentIndex(-1);
    ui.effectAttrCompareType0->setCurrentIndex(-1);
    ui.effectAttrInput0->clear();
}

void SearchFilterForm::effectAttrFilter1ResetBtnClick()
{
    ui.effectFieldName1->setCurrentIndex(-1);
    ui.effectAttrCompareType1->setCurrentIndex(-1);
    ui.effectAttrInput1->clear();
}

void SearchFilterForm::closeEvent(QCloseEvent* e)
{
    hide();
    e->ignore();

    OnCloseOrApplyEventFn();
}

void SearchFilterForm::showEvent(QShowEvent* /*event*/)
{
    // Generic filter
    const auto& genericFilter = m_filterData->m_genericFilter;
    ui.SpellFamilyFilter->setCurrentIndex(genericFilter.m_spellFamily.first);
    ui.SpellAuraTypeFilter->setCurrentIndex(genericFilter.m_spellAuraType.first);
    ui.SpellEffectFilter->setCurrentIndex(genericFilter.m_spellEffect.first);
    ui.SpellTargetFilterA->setCurrentIndex(genericFilter.m_spellTargetA.first);
    ui.SpellTargetFilterB->setCurrentIndex(genericFilter.m_spellTargetB.first);

    // Spell.dbc filter
    const auto& spellEntryFilter = m_filterData->m_spellEntryFieldsFilter;
    ui.spellAttrCompareType0->setCurrentIndex(spellEntryFilter.at(0).m_compareType.first);
    ui.spellAttrCompareType1->setCurrentIndex(spellEntryFilter.at(1).m_compareType.first);
    ui.spellAttrFieldName0->setCurrentIndex(spellEntryFilter.at(0).m_entryField.first);
    ui.spellAttrFieldName1->setCurrentIndex(spellEntryFilter.at(1).m_entryField.first);
    ui.spellAttrInput0->setText(spellEntryFilter.at(0).m_compareValue);
    ui.spellAttrInput1->setText(spellEntryFilter.at(1).m_compareValue);

    // SpellEffect.dbc filter
    const auto& spellEffectFilter = m_filterData->m_spellEffectFieldsFilter;
    ui.effectFieldName0->setCurrentIndex(spellEffectFilter.at(0).m_entryField.first);
    ui.effectFieldName1->setCurrentIndex(spellEffectFilter.at(1).m_entryField.first);
    ui.effectAttrCompareType0->setCurrentIndex(spellEffectFilter.at(0).m_compareType.first);
    ui.effectAttrCompareType1->setCurrentIndex(spellEffectFilter.at(1).m_compareType.first);
    ui.effectAttrInput0->setText(spellEffectFilter.at(0).m_compareValue);
    ui.effectAttrInput1->setText(spellEffectFilter.at(1).m_compareValue);
}
