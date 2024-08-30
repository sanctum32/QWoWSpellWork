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

// App
#include "SQL/sqlConnection.hpp"
#include "mainwindow.hpp"
#include "DBC/DBCStores.hpp"
#include "JsonData/JsonData.hpp"
#include "Globals/appSettings.hpp"

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

    QLoggingCategory::setFilterRules("spellwork.json.debug=true");
    QLoggingCategory::setFilterRules("spellwork.sql.debug=true");
    QLoggingCategory::setFilterRules("spellwork.dbcstores.debug=true");

    // Read settings
#ifdef _WIN32
    if (sSpellWorkConfig->GetAppConfig().enableDarkMode)
    {
        a.setStyle("fusion");
    }
#endif

    sSpellWorkConfig->ReadSettings();

    MainWindow mainWindow;
    mainWindow.UpdateSqlStatus(sSpellWorkSQL->Init());
    mainWindow.UpdateDBCStatus(sDBCStores->LoadData());
    mainWindow.UpdateJsonStatus(sSpellWorkJson->LoadJsonData());

    _mainWindow = &mainWindow;
    mainWindow.show();

    return a.exec();
}
