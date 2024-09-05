#ifdef SPELLWORK_BUILD_SQL
#include "sqlConnection.hpp"
#include "appSettings.hpp"

Q_LOGGING_CATEGORY(SQL, "spellwork.sql");

SpellWorkSQL::~SpellWorkSQL()
{
    if (m_connection != nullptr)
    {
        mysql_close(m_connection);
        qCDebug(SQL) << "Disconnected";
    }
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

    if (m_connection == nullptr)
    {
        qCDebug(SQL) << "Failed to initialize connection. Error: " << mysql_error(m_connection);
    }

    mysql_options(m_connection, MYSQL_OPT_RECONNECT, &settings.canReconnect);

    if (mysql_real_connect(m_connection,
                           settings.hostname.toStdString().c_str(),
                           settings.username.toStdString().c_str(),
                           settings.password.toStdString().c_str(),
                           settings.worldDB.toStdString().c_str(),
                           settings.port,
                           nullptr, 0) == nullptr)
    {
        qCDebug(SQL) << "Failed to connect. Error: " << mysql_error(m_connection);
        return false;
    }

    qCDebug(SQL) << "connected";

    return true;
}

#endif
