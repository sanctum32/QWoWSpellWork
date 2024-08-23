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
#include "mainwindow.hpp"
#include "DBC/DBCStores.hpp"
#include "JsonData/JsonData.hpp"
#include "Globals/appSettings.hpp"

constexpr std::string_view StatusBarSeparator = "  <span style=\"color: yellow\">|</span>  ";

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSpellWork::ReadSettings();

#ifdef _WIN32
    if (QSpellWork::settings.darkMode)
    {
        a.setStyle("fusion");
    }
#endif

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "QSpellWork_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    const bool dbcLoaded = sDBCStores->LoadDBCDatas();
    const bool jsonLoaded = QSpellWorkJson::LoadJsonData();
    MainWindow w;
    QLabel statusLabel;

    if (dbcLoaded)
    {
        statusLabel.setText(statusLabel.text() + "DBC: <span style=\"color:green\">loaded</span>");
    }
    else
    {
        statusLabel.setText(statusLabel.text() + "DBC: <span style=\"color:red\">not loaded</span>");
    }

    statusLabel.setText(statusLabel.text() + StatusBarSeparator.data());

    if (jsonLoaded)
    {
        statusLabel.setText(statusLabel.text() + "JSON: <span style=\"color:green\">loaded</span>");
    }
    else
    {
        statusLabel.setText(statusLabel.text() + "JSON: <span style=\"color:red\">not loaded</span>");
    }

    w.statusBar()->addPermanentWidget(&statusLabel);

    w.show();
    return a.exec();
}
