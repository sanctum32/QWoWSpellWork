#include "appSettings.hpp"
#include "JsonData/JsonData.hpp"
#include <QJsonDocument>
#include <QJsonObject>

bool SpellWorkConfig::ReadSettings()
{
    return SpellWorkJson::OpenJson("./json/appSettings.json", [&](const QJsonDocument& json)
    {
        if (!json.isObject())
        {
            return false;
        }

        const auto& document = json.object();

#ifdef _WIN32
        m_appSettings.enableDarkMode = document.value("WindowsDarkMode").toBool();
#endif
        m_appSettings.loadDBCSpells = document.value("LoadDBCSpells").toBool();
        m_appSettings.loadSQLSpells = document.value("LoadSQLSpells").toBool();

        if (document.value("Sql").isObject())
        {
            const auto& sqlJson = document.value("Sql").toObject();
            m_sql.enable    = sqlJson.value("Enable").toBool();
            m_sql.hostname  = sqlJson.value("Hostname").toString();
            m_sql.port      = sqlJson.value("Port").toInt();
            m_sql.username  = sqlJson.value("Username").toString();
            m_sql.password  = sqlJson.value("Password").toString();
            m_sql.worldDB   = sqlJson.value("WorldDB").toString();
            m_sql.pingDelayInMS = sqlJson.value("PingDelayInMS").toInt();
            m_sql.canReconnect = sqlJson.value("CanReconnect").toBool();
        }

        return true;
    });
}
