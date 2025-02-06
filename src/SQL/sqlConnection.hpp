#pragma once
#ifdef SPELLWORK_BUILD_SQL
#include <QLoggingCategory>
#include <mysql/mysql.h>
#include <atomic>
#include <thread>

extern std::atomic_bool isSQLShuttingDown;
Q_DECLARE_LOGGING_CATEGORY(SQL)

class MainWindow;

class SpellWorkSQL
{
    std::jthread sqlPingThread;
    MYSQL* m_connection{nullptr};
    bool initialized{false};

    SpellWorkSQL() = default;
    ~SpellWorkSQL();

public:
    SpellWorkSQL(const SpellWorkSQL&) = delete;
    SpellWorkSQL operator=(const SpellWorkSQL&) = delete;

    static SpellWorkSQL* instance()
    {
        static SpellWorkSQL sql;
        return &sql;
    }

    // Initializes sql connection and tests world and hotfix databases
    // Must be called only once!
    void Init(MainWindow& mainWindow);

    // Returns active sql connection
    auto* GetConnection() const { return m_connection; }
};

#define sSpellWorkSQL SpellWorkSQL::instance()
#endif //BUILD_SQL
