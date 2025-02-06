// Qt
#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QStyleHints>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStatusBar>
#include <QJsonArray>
#include <QFile>
#include <QSettings>
#include <QStyleFactory>

// App
#include "MainWindowForm.hpp"
#include "DataStorage.hpp"
#include "JsonData/JsonData.hpp"
#include "Globals/appSettings.hpp"

#ifdef SPELLWORK_BUILD_SQL
#include "SQL/sqlConnection.hpp"
#endif // SPELLWORK_BUILD_SQL

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    sSpellWorkConfig->ReadSettings();
    const auto& appSettings = sSpellWorkConfig->GetAppConfig();

    // Load logging settings
    if (appSettings.loadLoggingRules)
    {
        QSettings settings("./qtlogging.ini", QSettings::IniFormat);

        settings.beginGroup("Rules");
        QStringList keys = settings.allKeys();

        for (const QString &key : keys) {
            QString rule = key + "=" + settings.value(key).toString();
            QLoggingCategory::setFilterRules(rule);
        }
    }

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "QSpellWork_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            app.installTranslator(&translator);
            break;
        }
    }

    if (appSettings.useQtFusionStyle)
    {
        app.setStyle(QStyleFactory::create("Fusion"));
    }

    MainWindow mainWindow;

#ifdef SPELLWORK_BUILD_SQL
    sSpellWorkSQL->Init(mainWindow);
#else
    mainWindow.UpdateSqlStatus(false);
#endif

    const bool dbcLoaded = sDataStorage->LoadDBCData();
    const bool db2Loaded = sDataStorage->LoadDB2Datas();
    const bool jsonLoaded = sSpellWorkJson->LoadJsonData();

    sDataStorage->GenerateExtraDataInfo();

    // Load the CSS file
    if (!sSpellWorkConfig->GetAppConfig().themeName.isEmpty())
    {
        QFile file("./themes/" + sSpellWorkConfig->GetAppConfig().themeName + ".css");
        if (file.open(QFile::ReadOnly))
        {
            app.setStyleSheet(QLatin1String(file.readAll()));
        }
    }

    mainWindow.UpdateDBCStatus(dbcLoaded);
    mainWindow.UpdateJsonStatus(jsonLoaded);
    mainWindow.UpdateFilterStatus(false);
    mainWindow.UpdateDB2Status(db2Loaded);

    mainWindow.show();
    return app.exec();
}
