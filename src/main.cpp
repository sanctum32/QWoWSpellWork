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
#include <thread>

// App
#include "mainwindow.hpp"
#include "DBC/DBCStores.hpp"
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

    sSpellWorkConfig->ReadSettings();
    const bool jsonLoaded = sSpellWorkJson->LoadJsonData();
    const bool dbcLoaded = sDBCStores->LoadData();
#ifdef SPELLWORK_BUILD_SQL
    const bool sqlConnected = sSpellWorkSQL->Init();
#endif

    if (sSpellWorkConfig->GetAppConfig().useQtFusionStyle)
    {
        QApplication::setStyle("Fusion");
    }

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

    MainWindow mainWindow;
#ifdef SPELLWORK_BUILD_SQL
    mainWindow.UpdateSqlStatus(sqlConnected);
#else
    mainWindow.UpdateSqlStatus(false);
#endif // SPELLWORK_BUILD_SQL

    mainWindow.UpdateDBCStatus(dbcLoaded);
    mainWindow.UpdateJsonStatus(jsonLoaded);
    mainWindow.UpdateFilterStatus(false);
    mainWindow.show();

#ifdef SPELLWORK_BUILD_SQL
    if (sSpellWorkConfig->GetSQLConfig().enable)
    {
        std::jthread sqlPingThread([&mainWindow, sqlConn = sSpellWorkSQL->GetConnection(), delay = sSpellWorkConfig->GetSQLConfig().pingDelayInMS]
        {
            qCDebug(SQL) << "Ping thread initialized";
            int lastResult = -1;
            if (sqlConn == nullptr)
            {
                qCDebug(SQL) << "Ping thread stopped: sql connection was not initialized";
                return;
            }

            while(true)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(delay));
                int result = mysql_ping(sqlConn);
                if (result != lastResult)
                {
                    lastResult = result;
                    mainWindow.UpdateSqlStatus(lastResult == 0);
                }

                qCDebug(SQL) << "Ping status: " << (lastResult == 0 ? "success" : "failed") << (" (") << lastResult << ")";
            }
        });
    }
#endif // SPELLWORK_BUILD_SQL

    return a.exec();
}
