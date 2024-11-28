#pragma once
#include <cstdint>
#include <string>

class DBCFileLoader
{
public:
    DBCFileLoader();
    DBCFileLoader(std::string_view filename, const char *fmt);
    ~DBCFileLoader();

    bool Load(std::string_view filename, const char *fmt);

    class Record
    {
    public:
        float getFloat(size_t field) const;
        uint32_t getUInt(size_t field) const;
        int32_t getInt(size_t field) const;
        uint8_t getUInt8(size_t field) const;
        int8_t getInt8(size_t field) const;
        uint64_t getUInt64(size_t field) const;
        int64_t getInt64(size_t field) const;

        std::string getString(size_t field) const;

    private:
        Record(DBCFileLoader &file_, unsigned char *offset_): offset(offset_), file(file_) { }
        unsigned char *offset;
        DBCFileLoader &file;

        friend class DBCFileLoader;
    };

    // Get record by id
    Record getRecord(size_t id);
    /// Get begin iterator over records

    uint32_t GetNumRows() const { return dbcHeader.recordCount; }
    uint32_t GetRowSize() const { return dbcHeader.recordSize; }
    uint32_t GetCols() const { return dbcHeader.fieldCount; }
    uint32_t GetOffset(size_t id) const { return (fieldsOffset != nullptr && id < dbcHeader.fieldCount) ? fieldsOffset[id] : 0; }
    bool IsLoaded() const { return data != nullptr; }
    static uint32_t GetFormatRecordSize(const char * format, int32_t * index_pos = nullptr);

private:
    struct DBCHeader
    {
        DBCHeader() :
            header(0),
            recordCount(0),
            fieldCount(0),
            recordSize(0),
            stringSize(0)
        {
        }

        uint32_t header;
        uint32_t recordCount;
        uint32_t fieldCount;
        uint32_t recordSize;
        uint32_t stringSize;

        bool IsHeaderValid() const
        {
            //'WDBC'
            return header == 0x43424457;
        }
    } dbcHeader;

    uint32_t *fieldsOffset{nullptr};
    unsigned char *data{nullptr};
    unsigned char *stringTable{nullptr};

    DBCFileLoader(DBCFileLoader const& right) = delete;
    DBCFileLoader& operator=(DBCFileLoader const& right) = delete;
};
