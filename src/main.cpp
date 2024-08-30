// Qt
#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QStyleHints>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStatusBar>
#include <QJsonArray>
#include <QDebug>
#include <QFile>

// App

#include "mainwindow.hpp"
#include "DBC/DBCStores.hpp"
#include "JsonData/JsonData.hpp"
#include "Globals/appSettings.hpp"
#ifdef SPELLWORK_BUILD_SQL
#include "SQL/sqlConnection.hpp"
#endif // SPELLWORK_BUILD_SQL

constexpr std::string_view StatusBarSeparator = "  <span style=\"color: yellow\">|</span>  ";

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "QSpellWork_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    sSpellWorkConfig->ReadSettings();
    QApplication::setStyle("Fusion");

    // Load the CSS file
    QFile file("./" + sSpellWorkConfig->GetAppConfig().themeName + ".css");
    if (file.open(QFile::ReadOnly))
    {
        QString styleSheet = QLatin1String(file.readAll());
        a.setStyleSheet(styleSheet);
    }
    else
    {
        QPalette minimalisticDarkPalette;
        minimalisticDarkPalette.setColor(QPalette::Window, QColor(20, 20, 20)); // Very dark gray background
        minimalisticDarkPalette.setColor(QPalette::WindowText, QColor(240, 240, 240)); // High contrast light gray text
        minimalisticDarkPalette.setColor(QPalette::Base, QColor(30, 30, 30)); // Slightly lighter gray for surfaces
        minimalisticDarkPalette.setColor(QPalette::AlternateBase, QColor(40, 40, 40)); // Darker gray for alternate surfaces
        minimalisticDarkPalette.setColor(QPalette::ToolTipBase, QColor(255, 255, 255)); // White tooltip background
        minimalisticDarkPalette.setColor(QPalette::ToolTipText, QColor(0, 0, 0)); // Black tooltip text
        minimalisticDarkPalette.setColor(QPalette::Text, QColor(240, 240, 240)); // High contrast light gray text
        minimalisticDarkPalette.setColor(QPalette::Button, QColor(40, 40, 40)); // Dark gray button background
        minimalisticDarkPalette.setColor(QPalette::ButtonText, QColor(240, 240, 240)); // Light gray button text
        minimalisticDarkPalette.setColor(QPalette::BrightText, QColor(255, 0, 0)); // Bright red text for emphasis or errors
        minimalisticDarkPalette.setColor(QPalette::Link, QColor(0, 150, 136)); // Teal accent color for links (minimal accent)
        minimalisticDarkPalette.setColor(QPalette::Highlight, QColor(0, 150, 136)); // Teal color for selection highlight
        minimalisticDarkPalette.setColor(QPalette::HighlightedText, QColor(255, 255, 255)); // White highlighted text
        a.setPalette(minimalisticDarkPalette);
    }

    MainWindow mainWindow;
#ifdef SPELLWORK_BUILD_SQL
    mainWindow.UpdateSqlStatus(sSpellWorkSQL->Init());
#else
    mainWindow.UpdateSqlStatus(false);
#endif // SPELLWORK_BUILD_SQL

    mainWindow.UpdateDBCStatus(sDBCStores->LoadData());
    mainWindow.UpdateJsonStatus(sSpellWorkJson->LoadJsonData());
    mainWindow.UpdateComboBoxItems();

    _mainWindow = &mainWindow;
    mainWindow.show();

    return a.exec();
}
