#include "appSettings.hpp"
#include "JsonData/JsonData.hpp"
#include <QJsonDocument>
#include <QJsonObject>

Q_LOGGING_CATEGORY(appConfig, "spellwork.appConfig");

bool SpellWorkConfig::ReadSettings()
{
    if (SpellWorkJson::OpenJson("./json/appSettings.json", [&](const QJsonDocument& json)
    {
        if (!json.isObject())
        {
            qCDebug(appConfig) << "Failed to load appSettings.json. JSON config is not object";
            return false;
        }

        const auto& document = json.object();

        m_appSettings.dbcFilePath = document.value("dbcPath").toString().toStdString();
        if (m_appSettings.dbcFilePath.empty())
        {
            qCDebug(appConfig) << "dbc path is empty, setted to \"./dbc\"";
            m_appSettings.dbcFilePath = "./dbc";
        }

        m_appSettings.themeName = document.value("ThemeName").toString();
        m_appSettings.loadDBCSpells = document.value("LoadDBCSpells").toBool(true);
        m_appSettings.loadSQLSpells = document.value("LoadSQLSpells").toBool(true);
        m_appSettings.useQtFusionStyle = document.value("UseQtFusionStyle").toBool(false);

        if (document.value("Sql").isObject())
        {
            const auto& sqlJson = document.value("Sql").toObject();
            m_sql.enable    = sqlJson.value("Enable").toBool(false);
            if (m_sql.enable)
            {
                m_sql.hostname  = sqlJson.value("Hostname").toString();
                m_sql.port      = sqlJson.value("Port").toInt(3306);
                m_sql.username  = sqlJson.value("Username").toString();
                m_sql.password  = sqlJson.value("Password").toString();
                m_sql.worldDB   = sqlJson.value("WorldDB").toString();
                m_sql.hotfixDB  = sqlJson.value("HotfixDB").toString();
                m_sql.pingDelayInMS = sqlJson.value("PingDelayInMS").toInt(10000);
                m_sql.canReconnect = sqlJson.value("CanReconnect").toBool(true);

                qCDebug(appConfig) << "SQL connection settings were successfully loaded";
            }
            else
            {
                qCDebug(appConfig) << "SQL connection is disabled";
            }
        }
        else
        {
            qCDebug(appConfig) << "Failed to load sql settings. SQL directive is not object or does not exist!";
        }

        return true;
    }))
    {
        qCDebug(appConfig) << "Settings were uccessfully loaded";
        return true;
    }

    qCDebug(appConfig) << "Failed to load settings from json/appSettings.json";
    return false;
}
