#include "appSettings.hpp"
#include "JsonData/JsonData.hpp"
#include <QJsonDocument>
#include <QJsonObject>

void SpellWorkConfig::ReadSettings()
{
    SpellWorkJson::OpenJson("./json/appSettings.json", [&](const QJsonDocument& json)
    {
        if (!json.isObject())
        {
            return false;
        }

        const auto& document = json.object();

#ifdef _WIN32
        m_appSettings.enableDarkMode = document.value("WindowsDarkMode").toBool();
#endif

        if (document.value("Sql").isObject())
        {
            const auto& sqlJson = document.value("Sql").toObject();
            m_sql.enable    = sqlJson.value("Enable").toBool();
            m_sql.Hostname  = sqlJson.value("Hostname").toString();
            m_sql.Port      = sqlJson.value("Port").toInt();
            m_sql.Username  = sqlJson.value("Username").toString();
            m_sql.Username  = sqlJson.value("Password").toString();
            m_sql.WorldDB   = sqlJson.value("WorldDB").toString();
        }

        return true;
    });
}
