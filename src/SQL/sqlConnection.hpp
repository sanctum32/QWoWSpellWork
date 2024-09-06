#pragma once
#ifdef SPELLWORK_BUILD_SQL
#include <QLoggingCategory>
#include <mysql/mysql.h>
#include <thread>
#include <atomic>

extern std::atomic_bool isSQLShuttingDown;
Q_DECLARE_LOGGING_CATEGORY(SQL)

class SpellWorkSQL
{
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

    // Initializes and creates sql connection
    // Must be called only once
    bool Init();

    // Returns active sql connection
    auto* GetConnection() const { return m_connection; }
};

#define sSpellWorkSQL SpellWorkSQL::instance()
#endif //BUILD_SQL
