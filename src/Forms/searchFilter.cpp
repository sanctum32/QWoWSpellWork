#include <QMessageBox>
#include <QCloseEvent>

#include "searchFilter.hpp"
#include "SearchFiltersStore.hpp"
#include "ValueComparition.hpp"
#include "mainwindow.hpp"
#include "DBCStructures.hpp"
#include "JsonData.hpp"

SearchFilter::SearchFilter(QWidget *parent) : QDialog(parent)
{
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

    QObject::connect(ui.buttonBox, &QDialogButtonBox::clicked, this, &SearchFilter::onButtonClicked);
    QObject::connect(ui.spellFamilyResetBtn, &QPushButton::clicked, this, &SearchFilter::spellFamilyResetBtnClick);
    QObject::connect(ui.SpellAuraEffResetBtn, &QPushButton::clicked, this, &SearchFilter::spellAuraEffResetBtnClick);
    QObject::connect(ui.SpellEffResetBtn, &QPushButton::clicked, this, &SearchFilter::spellEffResetBtnClick);
    QObject::connect(ui.SpellTargetAResetBtn, &QPushButton::clicked, this, &SearchFilter::spellTargetAResetBtnClick);
    QObject::connect(ui.SpellTargetBResetBtn, &QPushButton::clicked, this, &SearchFilter::spellTargetBResetBtnClick);
    QObject::connect(ui.SpellAttrFilter0ResetBtn, &QPushButton::clicked, this, &SearchFilter::spellAttrFilter0ResetBtnClick);
    QObject::connect(ui.SpellAttrFilter1ResetBtn, &QPushButton::clicked, this, &SearchFilter::spellAttrFilter1ResetBtnClick);
    QObject::connect(ui.EffectAttrFilter0ResetBtn, &QPushButton::clicked, this, &SearchFilter::effectAttrFilter0ResetBtnClick);
    QObject::connect(ui.EffectAttrFilter1ResetBtn, &QPushButton::clicked, this, &SearchFilter::effectAttrFilter1ResetBtnClick);
}

inline void UpdateMainWindowState(MainWindow* mainWindow)
{
    if (mainWindow == nullptr)
    {
        return;
    }

    using namespace SpellWork::SearchFilters;
    const bool hasBasicFilters = m_genericFilter.HasData();
    const bool hasSpellFieldFilters = std::ranges::any_of(m_spellEntryFilter, [](const auto& filter)
    {
        return filter.HasData();
    });
    const bool hasSpellEffectFilters = std::ranges::any_of(m_spellEffectFilter, [](const auto& filter)
    {
        return filter.HasData();
    });

    mainWindow->UpdateFilterStatus(hasBasicFilters || hasSpellFieldFilters || hasSpellEffectFilters);
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
    case QDialogButtonBox::Apply:
    {
        using namespace SpellWork::SearchFilters;
        // Generic filter
        {
            auto& genericFilter = m_genericFilter;
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
                auto& filter = m_spellEntryFilter.at(0);
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
                auto& filter = m_spellEntryFilter.at(1);
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
            auto& genericFilter = m_genericFilter;
            // Filter 0
            {
                auto& filter = m_spellEffectFilter.at(0);
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
                auto& filter = m_spellEffectFilter.at(1);
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

        UpdateMainWindowState(dynamic_cast<MainWindow*>(parentWidget()));

        QMessageBox msgBox;
        msgBox.setText("Filter settings were applied!");
        msgBox.setIcon(QMessageBox::Information);
        msgBox.exec();
    }break;
    case QDialogButtonBox::Cancel:
    case QDialogButtonBox::Close:
    {
        if (MainWindow* mainWindow = dynamic_cast<MainWindow*>(parentWidget()))
        {
            UpdateMainWindowState(mainWindow);
        }
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

void SearchFilter::spellFamilyResetBtnClick()
{
    ui.SpellFamilyFilter->setCurrentIndex(-1);
}

void SearchFilter::spellAuraEffResetBtnClick()
{
    ui.SpellAuraTypeFilter->setCurrentIndex(-1);
}

void SearchFilter::spellEffResetBtnClick()
{
    ui.SpellEffectFilter->setCurrentIndex(-1);
}

void SearchFilter::spellTargetAResetBtnClick()
{
    ui.SpellTargetFilterA->setCurrentIndex(-1);
}

void SearchFilter::spellTargetBResetBtnClick()
{
    ui.SpellTargetFilterB->setCurrentIndex(-1);
}

void SearchFilter::spellAttrFilter0ResetBtnClick()
{
    ui.spellAttrFieldName0->setCurrentIndex(-1);
    ui.spellAttrCompareType0->setCurrentIndex(-1);
    ui.spellAttrInput0->clear();
}

void SearchFilter::spellAttrFilter1ResetBtnClick()
{
    ui.spellAttrFieldName1->setCurrentIndex(-1);
    ui.spellAttrCompareType1->setCurrentIndex(-1);
    ui.spellAttrInput1->clear();
}

void SearchFilter::effectAttrFilter0ResetBtnClick()
{
    ui.effectFieldName0->setCurrentIndex(-1);
    ui.effectAttrCompareType0->setCurrentIndex(-1);
    ui.effectAttrInput0->clear();
}

void SearchFilter::effectAttrFilter1ResetBtnClick()
{
    ui.effectFieldName1->setCurrentIndex(-1);
    ui.effectAttrCompareType1->setCurrentIndex(-1);
    ui.effectAttrInput1->clear();
}

void SearchFilter::closeEvent(QCloseEvent* e)
{
    hide();
    e->ignore();

    UpdateMainWindowState(dynamic_cast<MainWindow*>(parentWidget()));
}

void SearchFilter::showEvent(QShowEvent* /*event*/)
{
    using namespace SpellWork::SearchFilters;
    // Generic filter
    ui.SpellFamilyFilter->setCurrentIndex(m_genericFilter.m_spellFamily.first);
    ui.SpellAuraTypeFilter->setCurrentIndex(m_genericFilter.m_spellAuraType.first);
    ui.SpellEffectFilter->setCurrentIndex(m_genericFilter.m_spellEffect.first);
    ui.SpellTargetFilterA->setCurrentIndex(m_genericFilter.m_spellTargetA.first);
    ui.SpellTargetFilterB->setCurrentIndex(m_genericFilter.m_spellTargetB.first);

    // Spell.dbc filter
    ui.spellAttrCompareType0->setCurrentIndex(m_spellEntryFilter.at(0).m_compareType.first);
    ui.spellAttrCompareType1->setCurrentIndex(m_spellEntryFilter.at(1).m_compareType.first);
    ui.spellAttrFieldName0->setCurrentIndex(m_spellEntryFilter.at(0).m_entryField.first);
    ui.spellAttrFieldName1->setCurrentIndex(m_spellEntryFilter.at(1).m_entryField.first);
    ui.spellAttrInput0->setText(m_spellEntryFilter.at(0).m_compareValue);
    ui.spellAttrInput1->setText(m_spellEntryFilter.at(1).m_compareValue);

    // SpellEffect.dbc filter
    ui.effectFieldName0->setCurrentIndex(m_spellEffectFilter.at(0).m_entryField.first);
    ui.effectFieldName1->setCurrentIndex(m_spellEffectFilter.at(1).m_entryField.first);
    ui.effectAttrCompareType0->setCurrentIndex(m_spellEffectFilter.at(0).m_compareType.first);
    ui.effectAttrCompareType1->setCurrentIndex(m_spellEffectFilter.at(1).m_compareType.first);
    ui.effectAttrInput0->setText(m_spellEffectFilter.at(0).m_compareValue);
    ui.effectAttrInput1->setText(m_spellEffectFilter.at(1).m_compareValue);
}
