#pragma once

#include <QLoggingCategory>
#include <QString>

struct SQLSettings
{
    QString Hostname;
    unsigned int Port;
    QString Username;
    QString Password;
    QString WorldDB;
    bool enable;
};

#ifdef _WIN32
struct AppSettings
{
    bool enableDarkMode;
};
#endif // _WIN32

class SpellWorkConfig
{
    SpellWorkConfig() = default;
    SQLSettings m_sql;

#ifdef _WIN32
    AppSettings m_appSettings;
#endif // _WIN32

public:
    SpellWorkConfig(const SpellWorkConfig&) = delete;
    SpellWorkConfig& operator=(const SpellWorkConfig&) = delete;

    static SpellWorkConfig* instance()
    {
        static SpellWorkConfig _instance;
        return &_instance;
    }

    void ReadSettings();

    const SQLSettings& GetSQLConfig() const { return m_sql; }
#ifdef _WIN32
    const AppSettings& GetAppConfig() const { return m_appSettings; }
#endif // _WIN32
};

#define sSpellWorkConfig SpellWorkConfig::instance()
