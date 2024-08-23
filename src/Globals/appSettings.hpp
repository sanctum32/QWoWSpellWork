#pragma once
#include <QLoggingCategory>
#include <QString>

namespace QSpellWork
{
    struct AppSettings
    {
        struct{
            QString Hostname;
            QString Port;
            QString Username;
            QString Password;
            QString WorldDB;
            bool enable;
        } sql;

#ifdef _WIN32
        bool darkMode{false};      // Only windows
#endif // _WIN32
    };

    extern AppSettings settings;
    void ReadSettings();
}
