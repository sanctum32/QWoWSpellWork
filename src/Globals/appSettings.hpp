#pragma once

#include <QLoggingCategory>
#include <QString>

Q_DECLARE_LOGGING_CATEGORY(appConfig)

struct SQLSettings
{
    QString hostname;
    QString username;
    QString password;
    QString worldDB;
    QString hotfixDB;
    unsigned int port{};
    unsigned int pingDelayInMS{};
    bool enable{};
    bool canReconnect{};
};

struct AppSettings
{
    std::string dbcFilePath{"./dbc"};
    QString themeName;
    bool loadDBCSpells{true};
    bool loadSQLSpells{false};
    bool useQtFusionStyle{true};
};

class SpellWorkConfig
{
    SpellWorkConfig() = default;
    SQLSettings m_sql;
    AppSettings m_appSettings;

public:
    SpellWorkConfig(const SpellWorkConfig&) = delete;
    SpellWorkConfig& operator=(const SpellWorkConfig&) = delete;

    static SpellWorkConfig* instance()
    {
        static SpellWorkConfig _instance;
        return &_instance;
    }

    bool ReadSettings();

    const SQLSettings& GetSQLConfig() const { return m_sql; }
    const AppSettings& GetAppConfig() const { return m_appSettings; }
};

#define sSpellWorkConfig SpellWorkConfig::instance()
