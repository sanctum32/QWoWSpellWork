#pragma once

#include <QLoggingCategory>
#include <QString>

struct SQLSettings
{
    QString hostname;
    unsigned int port;
    QString username;
    QString password;
    QString worldDB;
    unsigned int pingDelayInMS;
    bool enable;
    bool canReconnect;
};


struct AppSettings
{
#ifdef _WIN32
    bool enableDarkMode;
#endif // _WIN32
    bool loadDBCSpells;
    bool loadSQLSpells;
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
