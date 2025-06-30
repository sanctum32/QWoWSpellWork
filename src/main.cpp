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

int main(int argc, char *argv[])
{
    sSpellWorkConfig->ReadSettings();
    const auto& appSettings = sSpellWorkConfig->GetAppConfig();

    sSpellWorkJson->LoadJsonData();
    sDataStorage->LoadDBC();
    sDataStorage->LoadDB2();
    sDataStorage->GenerateExtraDataInfo();

    QApplication app(argc, argv);

    if (appSettings.useQtFusionStyle)
    {
        app.setStyle(QStyleFactory::create("Fusion"));
    }

    if (!appSettings.themeName.isEmpty())
    {
        QFile file("./themes/" + appSettings.themeName + ".css");
        if (file.open(QFile::ReadOnly))
        {
            app.setStyleSheet(QLatin1String(file.readAll()));
        }
    }

    if (appSettings.loadLoggingRules)
    {
        QSettings settings("./qtlogging.ini", QSettings::IniFormat);

        settings.beginGroup("Rules");
        const QStringList keys = settings.allKeys();

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

    MainWindow mainWindow;
    mainWindow.show();
    return app.exec();
}
