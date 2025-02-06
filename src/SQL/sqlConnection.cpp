#include "MainWindowForm.hpp"
#ifdef SPELLWORK_BUILD_SQL
#include "sqlConnection.hpp"
#include "appSettings.hpp"
#include <thread>

std::atomic_bool isSQLShuttingDown = false;
Q_LOGGING_CATEGORY(SQL, "spellwork.sql");

SpellWorkSQL::~SpellWorkSQL()
{
    if (m_connection != nullptr)
    {
        mysql_close(m_connection);

        qCDebug(SQL) << "Disconnected";
    }

    isSQLShuttingDown = true;
}

void SpellWorkSQL::Init(MainWindow& mainWindow)
{
    assert(!initialized);

    const auto& settings = sSpellWorkConfig->GetSQLConfig();
    auto attemptFirstConnection = [&]
    {
        if (!settings.enable)
        {
            qCDebug(SQL) << "Connection is disabled";
            mainWindow.UpdateSqlStatus(false);
            return;
        }

        initialized = true;

        m_connection = mysql_init(nullptr);

        if (m_connection == nullptr)
        {
            qCDebug(SQL) << "Failed to initialize connection. Error: " << mysql_error(m_connection);
            mainWindow.UpdateSqlStatus(false);
            return;
        }

        mysql_options(m_connection, MYSQL_OPT_RECONNECT, &settings.canReconnect);

        if (mysql_real_connect(m_connection,
                               settings.hostname.toStdString().c_str(),
                               settings.username.toStdString().c_str(),
                               settings.password.toStdString().c_str(),
                               nullptr,
                               settings.port,
                               nullptr, 0) == nullptr)
        {
            qCDebug(SQL) << "Failed to connect. Error: " << mysql_error(m_connection);
            mainWindow.UpdateSqlStatus(false);
            return;
        }

        // Test world database
        std::stringstream query;
        query << "SELECT SCHEMA_NAME FROM INFORMATION_SCHEMA.SCHEMATA WHERE SCHEMA_NAME = '" << settings.worldDB.toStdString() << "'";
        if (mysql_query(m_connection, query.str().c_str()) != 0)
        {
            qCDebug(SQL) << "Failed to connect to world database. Error: " << mysql_error(m_connection);
            mysql_close(m_connection);
            m_connection = nullptr;
            mainWindow.UpdateSqlStatus(false);
            return;
        }

        // Test hotfix database
        query.clear();
        query.str("");
        query << "SELECT SCHEMA_NAME FROM INFORMATION_SCHEMA.SCHEMATA WHERE SCHEMA_NAME = '" << settings.hotfixDB.toStdString() << "'";
        if (mysql_query(m_connection, query.str().c_str()) != 0)
        {
            qCDebug(SQL) << "Failed to connect to hotfix database. Error: " << mysql_error(m_connection);
            mysql_close(m_connection);
            m_connection = nullptr;
            mainWindow.UpdateSqlStatus(false);
            return;
        }

        qCDebug(SQL) << "SQL connection was established successfully";
        mainWindow.UpdateSqlStatus(true);
    };

    attemptFirstConnection();

    if (m_connection != nullptr && sSpellWorkConfig->GetSQLConfig().pingDelayInMS > 0)
    {
        sqlPingThread = std::jthread([this, &mainWindow, delayInMS = settings.pingDelayInMS]
        {
            int lastStatus = 0;
            int currentStatus = 0;
            while (!isSQLShuttingDown)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(delayInMS));
                currentStatus = mysql_ping(m_connection);
                if (lastStatus != currentStatus)
                {
                    lastStatus = currentStatus;
                    mainWindow.UpdateSqlStatus(lastStatus == 0);
                    qCDebug(SQL) << "SQL ping was " << (lastStatus == 0 ? "successful" : "unsuccessful");
                }
            }
        });

        sqlPingThread.detach();
    }
}

#endif // SPELLWORK_BUILD_SQL
