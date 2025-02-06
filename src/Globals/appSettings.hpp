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
    bool enable{};
};

struct AppSettings
{
    QString dbcFilePath{"./dbc"};
    QString themeName;
    bool loadSQLSpells{false};
    bool useQtFusionStyle{true};
    bool loadLoggingRules{false};
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
