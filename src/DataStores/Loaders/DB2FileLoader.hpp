#pragma once

#include <cstddef>
#include <cstdint>
#include <string_view>

class DB2FileLoader
{
public:
    DB2FileLoader();
    DB2FileLoader(std::string_view filename, const char *fmt);
    ~DB2FileLoader();

    // Prevent copies
    DB2FileLoader(DB2FileLoader const& right) = delete;
    DB2FileLoader& operator=(DB2FileLoader const& right) = delete;

    bool Load(std::string_view filename, const char *fmt);

    class Record
    {
        Record(DB2FileLoader& file_, unsigned char* offset_): offset(offset_), file(file_) {}
        unsigned char *offset;
        DB2FileLoader& file;
        friend class DB2FileLoader;

    public:
        [[nodiscard]] float getFloat(size_t field) const;
        [[nodiscard]] uint32_t getUInt(size_t field) const;
        [[nodiscard]] int32_t getInt(size_t field) const;
        [[nodiscard]] uint8_t getUInt8(size_t field) const;
        [[nodiscard]] int8_t getInt8(size_t field) const;
        [[nodiscard]] uint64_t getUInt64(size_t field) const;
        [[nodiscard]] int64_t getInt64(size_t field) const;

        [[nodiscard]] const char *getString(size_t field) const;
    };

    // Get record by id
    Record getRecord(size_t id);
    /// Get begin iterator over records

    uint32_t GetNumRows() const { return db2Header.m_recordCount;}
    uint32_t GetCols() const { return db2Header.m_fieldCount; }
    uint32_t GetOffset(size_t id) const { return (m_fieldsOffset != nullptr && id < db2Header.m_fieldCount) ? m_fieldsOffset[id] : 0; }
    uint32_t GetHash() const { return db2Header.m_tableHash; }
    bool IsLoaded() const { return (m_data != nullptr); }
    char* AutoProduceData(char const* fmt, uint32_t& count, char**& indexTable);
    char* AutoProduceStringsArrayHolders(char const* fmt, char* dataTable);
    char* AutoProduceStrings(char const* format, char* dataTable, uint32_t locale);
    static uint32_t GetFormatRecordSize(char const* format, int32_t* index_pos = nullptr);
    static uint32_t GetFormatStringFieldCount(const char* format);
private:

    struct
    {
        uint32_t header{};
        uint32_t m_recordSize{};
        uint32_t m_recordCount{};
        uint32_t m_fieldCount{};
        uint32_t m_stringSize{};
        uint32_t m_tableHash{};
        uint32_t m_build{};

        int m_unk1{};          // WDB2
        int m_minIndex{};      // WDB2
        int m_maxIndex{};      // WDB2 (index table)
        int m_locale{};        // WDB2
        int m_unk5{};          // WDB2

        bool IsHeaderValid() const
        {
            // 'WDB2'
            return header == 0x32424457;
        }
    } db2Header;

    uint32_t *m_fieldsOffset{nullptr};
    unsigned char *m_data{nullptr};
    unsigned char *m_stringTable{nullptr};
};
