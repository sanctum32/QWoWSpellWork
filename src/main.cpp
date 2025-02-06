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

    MainWindow mainWindow;
    sSpellWorkConfig->ReadSettings();
    if (sSpellWorkConfig->GetAppConfig().useQtFusionStyle)
    {
        QApplication::setStyle("Fusion");
    }

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
            QString styleSheet = QLatin1String(file.readAll());
            a.setStyleSheet(styleSheet);
        }
    }

    mainWindow.UpdateDBCStatus(dbcLoaded);
    mainWindow.UpdateJsonStatus(jsonLoaded);
    mainWindow.UpdateFilterStatus(false);
    mainWindow.UpdateDB2Status(db2Loaded);

    mainWindow.show();
    return a.exec();
}
