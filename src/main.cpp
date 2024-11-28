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
#include "mainwindow.hpp"
#include "DataStorage.hpp"
#include "JsonData/JsonData.hpp"
#include "Globals/appSettings.hpp"

#ifdef SPELLWORK_BUILD_SQL
#include <thread>
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
#ifdef SPELLWORK_BUILD_SQL
    const bool sqlConnected = sSpellWorkSQL->Init();
#endif
    const bool dbcLoaded = sDataStorage->LoadDBCData();
    const bool db2Loaded = sDataStorage->LoadDB2Datas();

    sDataStorage->GenerateExtraDataInfo();

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
    mainWindow.UpdateDB2Status(db2Loaded);
    mainWindow.show();

#ifdef SPELLWORK_BUILD_SQL
    std::jthread sqlPingThread;
    if (sSpellWorkConfig->GetSQLConfig().enable && sSpellWorkConfig->GetSQLConfig().pingDelayInMS > 0)
    {
        sqlPingThread = std::jthread([&mainWindow, delayInMS = sSpellWorkConfig->GetSQLConfig().pingDelayInMS]
        {
            uint32_t timer = delayInMS; // first ping
            qCDebug(SQL) << "Ping thread initialized";
            int lastResult = -1;
            if (sSpellWorkSQL->GetConnection() == nullptr)
            {
                qCDebug(SQL) << "Ping thread stopped: sql connection was not initialized";
                return;
            }

            while (!isSQLShuttingDown)
            {
                if (timer >= delayInMS)
                {
                    int result = mysql_ping(sSpellWorkSQL->GetConnection());
                    if (result != lastResult)
                    {
                        lastResult = result;
                        mainWindow.UpdateSqlStatus(lastResult == 0);
                    }

                    qCDebug(SQL) << "Ping status: " << (lastResult == 0 ? "success" : "failed") << (" (") << lastResult << ")";
                    timer = 0;
                }

                if (isSQLShuttingDown)
                {
                    break;
                }
                const auto timeBefore = std::chrono::high_resolution_clock::now();
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
                if (isSQLShuttingDown)
                {
                    break;
                }
                const auto timerAfter = std::chrono::high_resolution_clock::now();

                timer += std::chrono::duration_cast<std::chrono::milliseconds>(timerAfter - timeBefore).count();
            }
            qCDebug(SQL) << "SQL ping thread finished was terminated";
        });
        sqlPingThread.detach();
    }
#endif // SPELLWORK_BUILD_SQL

    return a.exec();
}
