#include "SearchFilters.hpp"
#include "mainwindow.hpp"
#include "DBCStructures.hpp"
#include "JsonData.hpp"

SearchFilter::SearchFilter(QWidget *parent) : QDialog(parent)
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

inline void UpdateMainWindowState(MainWindow* mainWindow)
{
    if (mainWindow == nullptr)
    {
        return;
    }

    using namespace SpellWork::SearchFilters;
    mainWindow->setEnabled(true);
    const bool hasFilters = m_genericFilter.HasData() || std::any_of(m_spellEntryFilter.begin(), m_spellEntryFilter.end(), [](const auto& filter)
    {
        return filter.HasData();
    });

    mainWindow->UpdateFilterStatus(hasFilters);
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
            // Filter 1
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
            // Filter 2
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
                filter.m_compareValue = ui.spellAttrInput0->text();
            }
        }
    }
    [[fallthrough]];
    case QDialogButtonBox::Cancel:
    {
        UpdateMainWindowState(dynamic_cast<MainWindow*>(parentWidget()));
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

void SearchFilter::closeEvent(QCloseEvent* /*e*/)
{
    UpdateMainWindowState(dynamic_cast<MainWindow*>(parentWidget()));
}

void SearchFilter::showEvent(QShowEvent* /*event*/)
{
    using namespace SpellWork::SearchFilters;
    ui.SpellFamilyFilter->setCurrentIndex(m_genericFilter.m_spellFamily.first);
    ui.SpellAuraTypeFilter->setCurrentIndex(m_genericFilter.m_spellAuraType.first);
    ui.SpellEffectFilter->setCurrentIndex(m_genericFilter.m_spellEffect.first);
    ui.SpellTargetFilterA->setCurrentIndex(m_genericFilter.m_spellTargetA.first);
    ui.SpellTargetFilterB->setCurrentIndex(m_genericFilter.m_spellTargetB.first);

    ui.spellAttrCompareType0->setCurrentIndex(m_spellEntryFilter.at(0).m_compareType.first);
    ui.spellAttrCompareType1->setCurrentIndex(m_spellEntryFilter.at(1).m_compareType.first);
    ui.spellAttrFieldName0->setCurrentIndex(m_spellEntryFilter.at(0).m_entryField.first);
    ui.spellAttrFieldName1->setCurrentIndex(m_spellEntryFilter.at(1).m_entryField.first);
    ui.spellAttrInput0->setText(m_spellEntryFilter.at(0).m_compareValue);
    ui.spellAttrInput1->setText(m_spellEntryFilter.at(1).m_compareValue);
}
