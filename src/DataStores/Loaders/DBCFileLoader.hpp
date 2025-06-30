#pragma once
#include <cstdint>
#include <string>

class DBCFileLoader
{
public:
    DBCFileLoader();
    DBCFileLoader(std::string_view filename, const char *fmt);
    ~DBCFileLoader();

    // Prevent copies
    DBCFileLoader(DBCFileLoader const& right) = delete;
    DBCFileLoader& operator=(DBCFileLoader const& right) = delete;

    bool Load(std::string_view filename, const char *fmt);

    class Record
    {
    public:
        [[nodiscard]] float getFloat(size_t field) const;
        [[nodiscard]] uint32_t getUInt(size_t field) const;
        [[nodiscard]] int32_t getInt(size_t field) const;
        [[nodiscard]] uint8_t getUInt8(size_t field) const;
        [[nodiscard]] int8_t getInt8(size_t field) const;
        [[nodiscard]] uint64_t getUInt64(size_t field) const;
        [[nodiscard]] int64_t getInt64(size_t field) const;

        [[nodiscard]] std::string getString(size_t field) const;

    private:
        Record(DBCFileLoader &file_, unsigned char *offset_): offset(offset_), file(file_) { }
        unsigned char *offset;
        DBCFileLoader &file;

        friend class DBCFileLoader;
    };

    // Get record by id
    Record getRecord(size_t id);
    /// Get begin iterator over records

    [[nodiscard]] uint32_t GetNumRows() const { return dbcHeader.recordCount; }
    [[nodiscard]] uint32_t GetRowSize() const { return dbcHeader.recordSize; }
    [[nodiscard]] uint32_t GetCols() const { return dbcHeader.fieldCount; }
    [[nodiscard]] uint32_t GetOffset(size_t id) const { return (fieldsOffset != nullptr && id < dbcHeader.fieldCount) ? fieldsOffset[id] : 0; }
    [[nodiscard]] bool IsLoaded() const { return data != nullptr; }
    static uint32_t GetFormatRecordSize(const char * format, int32_t * index_pos = nullptr);

private:
    struct DBCHeader
    {
        DBCHeader() = default;

        uint32_t header{0};
        uint32_t recordCount{0};
        uint32_t fieldCount{0};
        uint32_t recordSize{0};
        uint32_t stringSize{0};

        [[nodiscard]] bool IsHeaderValid() const
        {
            //'WDBC'
            return header == 0x43424457;
        }
    } dbcHeader;

    uint32_t *fieldsOffset{nullptr};
    unsigned char *data{nullptr};
    unsigned char *stringTable{nullptr};
};
