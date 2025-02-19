#include "DB2FileLoader.hpp"
#include "SharedDefines.hpp"
#include "DataStoresDefines.hpp"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <format>

constexpr char const* nullStr = "";

DB2FileLoader::DB2FileLoader() = default;

DB2FileLoader::DB2FileLoader(std::string_view filename, const char *fmt)
{
    Load(filename, fmt);
}

bool DB2FileLoader::Load(std::string_view filename, char const* fmt)
{
    if (m_data)
    {
        delete [] m_data;
        m_data = nullptr;
    }

    FILE* f = fopen(filename.data(), "rbe");
    if (!f)
    {
        return false;
    }

    if (fread(&db2Header.header, 4, 1, f) != 1)                        // Signature
    {
        fclose(f);
        return false;
    }

    EndianConvert(db2Header.header);

    if (!db2Header.IsHeaderValid())
    {
        fclose(f);
        return false;                                       //'WDB2'
    }

    if (fread(&db2Header.m_recordCount, 4, 1, f) != 1)                 // Number of records
    {
        fclose(f);
        return false;
    }

    EndianConvert(db2Header.m_recordCount);

    if (fread(&db2Header.m_fieldCount, 4, 1, f) != 1)                 // Number of fields
    {
        fclose(f);
        return false;
    }

    EndianConvert(db2Header.m_fieldCount);

    if (fread(&db2Header.m_recordSize, 4, 1, f) != 1)                 // Size of a record
    {
        fclose(f);
        return false;
    }

    EndianConvert(db2Header.m_recordSize);

    if (fread(&db2Header.m_stringSize, 4, 1, f) != 1)                 // String size
    {
        fclose(f);
        return false;
    }

    EndianConvert(db2Header.m_stringSize);

    /* NEW WDB2 FIELDS*/
    if (fread(&db2Header.m_tableHash, 4, 1, f) != 1)                  // Table hash
    {
        fclose(f);
        return false;
    }

    EndianConvert(db2Header.m_tableHash);

    if (fread(&db2Header.m_build, 4, 1, f) != 1)                     // Build
    {
        fclose(f);
        return false;
    }

    EndianConvert(db2Header.m_build);

    if (fread(&db2Header.m_unk1, 4, 1, f) != 1)                     // Unknown WDB2
    {
        fclose(f);
        return false;
    }

    EndianConvert(db2Header.m_unk1);

    if (db2Header.m_build > 12880)
    {
        if (fread(&db2Header.m_minIndex, 4, 1, f) != 1)                           // MinIndex WDB2
        {
            fclose(f);
            return false;
        }
        EndianConvert(db2Header.m_minIndex);

        if (fread(&db2Header.m_maxIndex, 4, 1, f) != 1)                           // MaxIndex WDB2
        {
            fclose(f);
            return false;
        }
        EndianConvert(db2Header.m_maxIndex);

        if (fread(&db2Header.m_locale, 4, 1, f) != 1)                             // Locales
        {
            fclose(f);
            return false;
        }
        EndianConvert(db2Header.m_locale);

        if (fread(&db2Header.m_unk5, 4, 1, f) != 1)                               // Unknown WDB2
        {
            fclose(f);
            return false;
        }
        EndianConvert(db2Header.m_unk5);
    }

    if (db2Header.m_maxIndex != 0)
    {
        int32_t diff = db2Header.m_maxIndex - db2Header.m_minIndex + 1;
        fseek(f, diff * 4 + diff * 2, SEEK_CUR);    // diff * 4: an index for rows, diff * 2: a memory allocation bank
    }

    m_fieldsOffset = new uint32_t[db2Header.m_fieldCount];
    m_fieldsOffset[0] = 0;
    for (uint32_t i = 1; i < db2Header.m_fieldCount; i++)
    {
        m_fieldsOffset[i] = m_fieldsOffset[i - 1];
        if (fmt[i - 1] == 'b')
        {
            ++m_fieldsOffset[i];
        }
        else
        {
            m_fieldsOffset[i] += 4;
        }
    }

    m_data = new unsigned char[db2Header.m_recordSize * db2Header.m_recordCount + db2Header.m_stringSize];
    m_stringTable = m_data + db2Header.m_recordSize * db2Header.m_recordCount;

    if (fread(m_data, db2Header.m_recordSize * db2Header.m_recordCount + db2Header.m_stringSize, 1, f) != 1)
    {
        fclose(f);
        return false;
    }

    fclose(f);
    return true;
}

DB2FileLoader::~DB2FileLoader()
{
    if (m_data)
        delete [] m_data;
    if (m_fieldsOffset)
        delete [] m_fieldsOffset;
}

DB2FileLoader::Record DB2FileLoader::getRecord(size_t id)
{
    assert(m_data);
    return Record(*this, m_data + id*db2Header.m_recordSize);
}

uint32_t DB2FileLoader::GetFormatRecordSize(char const* format, int32_t* index_pos)
{
    uint32_t recordsize = 0;
    int32_t i = -1;
    for (uint32_t x=0; format[x]; ++x)
    {
        switch (format[x])
        {
        case FT_FLOAT:
        case FT_INT:
            recordsize += 4;
            break;
        case FT_STRING:
            recordsize += sizeof(char*);
            break;
        case FT_SORT:
            i = x;
            break;
        case FT_IND:
            i = x;
            recordsize += 4;
            break;
        case FT_BYTE:
            recordsize += 1;
            break;
        }
    }

    if (index_pos)
        *index_pos = i;

    return recordsize;
}

uint32_t DB2FileLoader::GetFormatStringFieldCount(char const* format)
{
    uint32_t stringfields = 0;
    for (uint32_t x = 0; format[x]; ++x)
        if (format[x] == FT_STRING)
            ++stringfields;

    return stringfields;
}

char* DB2FileLoader::AutoProduceData(char const* format, uint32_t& records, char**& indexTable)
{
    typedef char * ptr;
    if (strlen(format) != db2Header.m_fieldCount)
        return nullptr;

    //get struct size and index pos
    int32_t indexField;
    uint32_t recordsize = GetFormatRecordSize(format, &indexField);

    if (indexField >= 0)
    {
        uint32_t maxi = 0;
        //find max index
        for (uint32_t y = 0; y < db2Header.m_recordCount; y++)
        {
            uint32_t ind = getRecord(y).getUInt(indexField);
            if (ind > maxi)
                maxi = ind;
        }

        ++maxi;
        records = maxi;
        indexTable = new ptr[maxi];
        memset(indexTable, 0, maxi * sizeof(ptr));
    }
    else
    {
        records = db2Header.m_recordCount;
        indexTable = new ptr[db2Header.m_recordCount];
    }

    char* dataTable = new char[db2Header.m_recordCount * recordsize];

    uint32_t offset = 0;

    for (uint32_t y = 0; y < db2Header.m_recordCount; y++)
    {
        if (indexField >= 0)
            indexTable[getRecord(y).getUInt(indexField)] = &dataTable[offset];
        else
            indexTable[y] = &dataTable[offset];

        for (uint32_t x = 0; x < db2Header.m_fieldCount; x++)
        {
            switch (format[x])
            {
            case FT_FLOAT:
                *((float*)(&dataTable[offset])) = getRecord(y).getFloat(x);
                offset += 4;
                break;
            case FT_IND:
            case FT_INT:
                *((uint32_t*)(&dataTable[offset])) = getRecord(y).getUInt(x);
                offset += 4;
                break;
            case FT_BYTE:
                *((uint8_t*)(&dataTable[offset])) = getRecord(y).getUInt8(x);
                offset += 1;
                break;
            case FT_STRING:
                *((char**)(&dataTable[offset])) = nullptr;   // will be replaces non-empty or "" strings in AutoProduceStrings
                offset += sizeof(char*);
                break;
            }
        }
    }

    return dataTable;
}

char* DB2FileLoader::AutoProduceStringsArrayHolders(char const* format, char* dataTable)
{
    if (strlen(format) != db2Header.m_fieldCount)
        return nullptr;

    // we store flat holders pool as single memory block
    std::size_t localizedStringFields = GetFormatStringFieldCount(format);
    if (!localizedStringFields)
        return nullptr;

    // each string field at load have array of string for each locale
    std::size_t stringHolderSize = sizeof(char*) * TOTAL_LOCALES;
    std::size_t stringHoldersRecordPoolSize = localizedStringFields * stringHolderSize;
    std::size_t stringHoldersPoolSize = stringHoldersRecordPoolSize * db2Header.m_recordCount;

    char* stringHoldersPool = new char[stringHoldersPoolSize];

    // DB2 strings expected to have at least empty string
    for (std::size_t i = 0; i < stringHoldersPoolSize / sizeof(char*); ++i)
        ((char const**)stringHoldersPool)[i] = nullStr;

    uint32_t offset = 0;

    // assign string holders to string field slots
    for (uint32_t y = 0; y < db2Header.m_recordCount; y++)
    {
        uint32_t stringFieldOffset = 0;

        for (uint32_t x = 0; x < db2Header.m_fieldCount; x++)
        {
            switch (format[x])
            {
                case FT_FLOAT:
                case FT_IND:
                case FT_INT:
                    offset += 4;
                    break;
                case FT_BYTE:
                    offset += 1;
                    break;
                case FT_STRING:
                {
                    // init db2 string field slots by pointers to string holders
                    char const*** slot = (char const***)(&dataTable[offset]);
                    *slot = (char const**)(&stringHoldersPool[stringHoldersRecordPoolSize * y + stringFieldOffset]);
                    stringFieldOffset += stringHolderSize;
                    offset += sizeof(char*);
                    break;
                }
                default:
                {
                    assert(false && std::format("unknown format character {}", format[x]).c_str());
                }
            }
        }
    }

    //send as char* for store in char* pool list for free at unload
    return stringHoldersPool;
}

char* DB2FileLoader::AutoProduceStrings(char const* format, char* dataTable, uint32_t locale)
{
    if (strlen(format) != db2Header.m_fieldCount)
        return nullptr;

    char* stringPool = new char[db2Header.m_stringSize];
    memcpy(stringPool, m_stringTable, db2Header.m_stringSize);

    uint32_t offset = 0;

    for (uint32_t y = 0; y < db2Header.m_recordCount; y++)
    {
        for (uint32_t x = 0; x < db2Header.m_fieldCount; x++)
        {
            switch (format[x])
            {
            case FT_FLOAT:
            case FT_IND:
            case FT_INT:
                offset += 4;
                break;
            case FT_BYTE:
                offset += 1;
                break;
            case FT_STRING:
            {
                // fill only not filled entries
                LocalizedString* db2str = *(LocalizedString**)(&dataTable[offset]);
                if (db2str->Str[locale] == nullStr)
                {
                    const char* st = getRecord(y).getString(x);
                    db2str->Str[locale] = stringPool + (st - (const char*)m_stringTable);
                }

                offset += sizeof(char*);
                break;
            }
            }
        }
    }

    return stringPool;
}

float DB2FileLoader::Record::getFloat(size_t field) const
{
    assert(field < file.db2Header.m_fieldCount);
    float val = *reinterpret_cast<float*>(offset+file.GetOffset(field));
    //EndianConvert(val);
    return val;
}

uint32_t DB2FileLoader::Record::getUInt(size_t field) const
{
    assert(field < file.db2Header.m_fieldCount);
    uint32_t val = *reinterpret_cast<uint32_t*>(offset+file.GetOffset(field));
    //EndianConvert(val);
    return val;
}

int32_t DB2FileLoader::Record::getInt(size_t field) const
{
    assert(field < file.db2Header.m_fieldCount);
    int32_t val = *reinterpret_cast<int32_t*>(offset+file.GetOffset(field));
    //EndianConvert(val);
    return val;
}

uint8_t DB2FileLoader::Record::getUInt8(size_t field) const
{
    assert(field < file.db2Header.m_fieldCount);
    return *reinterpret_cast<uint8_t*>(offset+file.GetOffset(field));
}

int8_t DB2FileLoader::Record::getInt8(size_t field) const
{
    assert(field < file.db2Header.m_fieldCount);
    return *reinterpret_cast<int8_t*>(offset+file.GetOffset(field));
}

uint64_t DB2FileLoader::Record::getUInt64(size_t field) const
{
    assert(field < file.db2Header.m_fieldCount);
    return *reinterpret_cast<uint64_t*>(offset+file.GetOffset(field));
}

int64_t DB2FileLoader::Record::getInt64(size_t field) const
{
    assert(field < file.db2Header.m_fieldCount);
    return *reinterpret_cast<int64_t*>(offset+file.GetOffset(field));
}

const char *DB2FileLoader::Record::getString(size_t field) const
{
    assert(field < file.db2Header.m_fieldCount);
    size_t stringOffset = getUInt(field);
    assert(stringOffset < file.db2Header.m_stringSize);
    return reinterpret_cast<char*>(file.m_stringTable + stringOffset);
}
