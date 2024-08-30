#include "sqlConnection.hpp"
#include "appSettings.hpp"
#include "mainwindow.hpp"

Q_LOGGING_CATEGORY(SQL, "spellwork.sql");

void PingSQL(MYSQL* connection, unsigned int delay)
{
    int lastResult = -1;
    if (connection == nullptr || _mainWindow == nullptr)
    {
        return;
    }

    while(true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
        int result = mysql_ping(connection);
        if (result != lastResult)
        {
            lastResult = result;
            _mainWindow->UpdateSqlStatus(lastResult == 0);
        }
    }
}

SpellWorkSQL::~SpellWorkSQL()
{
    if (m_connection != nullptr)
    {
        mysql_close(m_connection);
    }

    ShutdownThreads();
}

bool SpellWorkSQL::Init()
{
    if (initialized)
    {
        return m_connection != nullptr;
    }

    initialized = true;
    const auto& settings = sSpellWorkConfig->GetSQLConfig();
    m_connection = mysql_init(nullptr);

    mysql_options(m_connection, MYSQL_OPT_RECONNECT, &settings.canReconnect);

    if (mysql_real_connect(m_connection,
                           settings.hostname.toStdString().c_str(),
                           settings.username.toStdString().c_str(),
                           settings.password.toStdString().c_str(),
                           settings.worldDB.toStdString().c_str(),
                           settings.port,
                           nullptr, 0) == nullptr)
    {
        qCDebug(SQL) << "SQL: Failed to connect. Error: " << mysql_error(m_connection);
        return false;
    }

    qCDebug(SQL) << "SQL: connected";

    if (settings.pingDelayInMS != 0)
    {
        m_pingThread = std::thread(PingSQL, m_connection, settings.pingDelayInMS);
    }
    return true;
}

void SpellWorkSQL::ShutdownThreads()
{
    if (m_pingThread.joinable())
        m_pingThread.join();
}
