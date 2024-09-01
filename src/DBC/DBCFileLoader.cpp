#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <string>

#include "DBCFileLoader.hpp"

DBCFileLoader::DBCFileLoader(std::string_view filename, const char *fmt) :
    fieldsOffset(nullptr),
    data(nullptr),
    stringTable(nullptr)
{
    Load(filename, fmt);
}

DBCFileLoader::DBCFileLoader() :
    fieldsOffset(nullptr),
    data(nullptr),
    stringTable(nullptr)
{
}

bool DBCFileLoader::Load(std::string_view filename, const char* fmt)
{
    if (data)
    {
        delete [] data;
        data = nullptr;
    }

    FILE* f = fopen(filename.data(), "rb");
    if (f == nullptr)
        return false;

    // Number of records
    if (fread(&dbcHeader.header, 4, 1, f) != 1)
    {
        fclose(f);
        return false;
    }

    if (!dbcHeader.IsHeaderValid())
    {
        fclose(f);
        return false;
    }

    // Number of records
    if (fread(&dbcHeader.recordCount, 4, 1, f) != 1)
    {
        fclose(f);
        return false;
    }

    // Number of fields
    if (fread(&dbcHeader.fieldCount, 4, 1, f) != 1)
    {
        fclose(f);
        return false;
    }

    // Size of a record
    if (fread(&dbcHeader.recordSize, 4, 1, f) != 1)
    {
        fclose(f);
        return false;
    }

    // String size
    if (fread(&dbcHeader.stringSize, 4, 1, f) != 1)
    {
        fclose(f);
        return false;
    }

    fieldsOffset = new uint32_t[dbcHeader.fieldCount];
    fieldsOffset[0] = 0;
    for (uint32_t i = 1; i < dbcHeader.fieldCount; ++i)
    {
        fieldsOffset[i] = fieldsOffset[i - 1];
        // byte fields
        if (fmt[i - 1] == 'b' || fmt[i - 1] == 'X')
        {
            fieldsOffset[i] += sizeof(uint8_t);
        }
        else if (fmt[i - 1] == 'l')
        {
            fieldsOffset[i] += sizeof(uint64_t);
        }
        // 4 byte fields (int32/float/strings)
        else
        {
            fieldsOffset[i] += sizeof(uint32_t);
        }
    }

    data = new unsigned char[dbcHeader.recordSize * dbcHeader.recordCount + dbcHeader.stringSize];
    stringTable = data + dbcHeader.recordSize*dbcHeader.recordCount;

    if (fread(data, dbcHeader.recordSize * dbcHeader.recordCount + dbcHeader.stringSize, 1, f) != 1)
    {
        fclose(f);
        return false;
    }

    fclose(f);
    return true;
}

DBCFileLoader::~DBCFileLoader()
{
    if (data)
        delete [] data;

    if (fieldsOffset)
        delete [] fieldsOffset;
}

DBCFileLoader::Record DBCFileLoader::getRecord(size_t id)
{
    assert(data);
    return Record(*this, data + id * dbcHeader.recordSize);
}

uint32_t DBCFileLoader::GetFormatRecordSize(const char* format, int32_t* index_pos)
{
    uint32_t recordsize = 0;
    int32_t i = -1;
    for (uint32_t x = 0; format[x]; ++x)
    {
        switch (format[x])
        {
            case FT_FLOAT:
                recordsize += sizeof(float);
                break;
            case FT_INT:
                recordsize += sizeof(uint32_t);
                break;
            case FT_STRING:
                recordsize += sizeof(char*);
                break;
            case FT_SORT:
                i = x;
                break;
            case FT_IND:
                i = x;
                recordsize += sizeof(uint32_t);
                break;
            case FT_BYTE:
                recordsize += sizeof(uint8_t);
                break;
            case FT_LONG:
                recordsize += sizeof(uint64_t);
                break;
            case FT_NA:
            case FT_NA_BYTE:
                break;
            default:
                assert(false && "Unknown field format character");
                break;
        }
    }

    if (index_pos)
        *index_pos = i;

    return recordsize;
}

float DBCFileLoader::Record::getFloat(size_t field) const
{
    assert(field < file.dbcHeader.fieldCount);
    float val = *reinterpret_cast<float*>(offset+file.GetOffset(field));
    return val;
}

uint32_t DBCFileLoader::Record::getUInt(size_t field) const
{
    assert(field < file.dbcHeader.fieldCount);
    uint32_t val = *reinterpret_cast<uint32_t*>(offset+file.GetOffset(field));
    return val;
}

int32_t DBCFileLoader::Record::getInt(size_t field) const
{
    assert(field < file.dbcHeader.fieldCount);
    int32_t val = *reinterpret_cast<int32_t*>(offset+file.GetOffset(field));
    return val;
}

uint8_t DBCFileLoader::Record::getUInt8(size_t field) const
{
    assert(field < file.dbcHeader.fieldCount);
    return *reinterpret_cast<uint8_t*>(offset+file.GetOffset(field));
}

int8_t DBCFileLoader::Record::getInt8(size_t field) const
{
    assert(field < file.dbcHeader.fieldCount);
    return *reinterpret_cast<int8_t*>(offset+file.GetOffset(field));
}

uint64_t DBCFileLoader::Record::getUInt64(size_t field) const
{
    assert(field < file.dbcHeader.fieldCount);
    return *reinterpret_cast<uint64_t*>(offset + file.GetOffset(field));
}

int64_t DBCFileLoader::Record::getInt64(size_t field) const
{
    assert(field < file.dbcHeader.fieldCount);
    return *reinterpret_cast<int64_t*>(offset + file.GetOffset(field));
}

std::string DBCFileLoader::Record::getString(size_t field) const
{
    assert(field < file.dbcHeader.fieldCount);
    size_t stringOffset = getUInt(field);
    assert(stringOffset < file.dbcHeader.stringSize);
    return reinterpret_cast<char*>(file.stringTable + stringOffset);
}
