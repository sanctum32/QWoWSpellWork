#include "appSettings.hpp"
#include "JsonData/JsonData.hpp"
#include <QJsonDocument>
#include <QJsonObject>
#include <QSqlDatabase>
#include <QSqlError>

namespace QSpellWork
{
    AppSettings settings;

    void ReadSettings()
    {
        QSpellWorkJson::OpenJson("./json/appSettings.json", [&](const QJsonDocument& json)
        {
            if (!json.isObject())
            {
                return false;
            }

            const auto& document = json.object();

#ifdef _WIN32
            settings.darkMode = document.value("WindowsDarkMode").toBool();
#endif

            if (document.value("Sql").isObject())
            {
                const auto& sqlJson = document.value("Sql").toObject();
                settings.sql.enable = sqlJson.value("Enable").toBool();
                settings.sql.Hostname = sqlJson.value("Hostname").toString();
                settings.sql.Port = sqlJson.value("Port").toString();
                settings.sql.Username = sqlJson.value("Username").toString();
                settings.sql.Username = sqlJson.value("Password").toString();
                settings.sql.WorldDB = sqlJson.value("WorldDB").toString();

                QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
                db.setHostName(settings.sql.Hostname);
                db.setPort(settings.sql.Port.toInt());
                db.setUserName(settings.sql.Username);
                db.setPassword(settings.sql.Password);
                db.setDatabaseName(settings.sql.WorldDB);

                qDebug() << (db.open() ? "sql success" : "sql fail") << db.lastError().text();
                db.close();
            }

            return true;
        });
    }
}
