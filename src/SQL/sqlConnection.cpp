#ifdef SPELLWORK_BUILD_SQL
#include "sqlConnection.hpp"
#include "appSettings.hpp"

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

bool SpellWorkSQL::Init()
{
    const auto& settings = sSpellWorkConfig->GetSQLConfig();
    if (!settings.enable)
    {
        qCDebug(SQL) << "Connection is disabled";
        return false;
    }

    if (initialized)
    {
        qCDebug(SQL) << "Attempted to initialize SQL connection twice";
        return m_connection != nullptr;
    }

    initialized = true;

    m_connection = mysql_init(nullptr);

    if (m_connection == nullptr)
    {
        qCDebug(SQL) << "Failed to initialize connection. Error: " << mysql_error(m_connection);
        return false;
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
        return false;
    }

    // Test world database
    std::stringstream query;
    query << "SELECT SCHEMA_NAME FROM INFORMATION_SCHEMA.SCHEMATA WHERE SCHEMA_NAME = '" << settings.worldDB.toStdString() << "'";
    if (mysql_query(m_connection, query.str().c_str()) != 0)
    {
        qCDebug(SQL) << "Failed to connect to world database. Error: " << mysql_error(m_connection);
        mysql_close(m_connection);
        m_connection = nullptr;
        return false;
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
        return false;
    }

    qCDebug(SQL) << "SQL connection was established successfully";
    return true;
}

#endif // SPELLWORK_BUILD_SQL
