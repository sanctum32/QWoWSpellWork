#pragma once

#include <bit>
#include <cstddef>
#include <utility>

enum DBCFormat : char
{
    FT_NA           = 'x',                                        //not used or unknown, 4 byte size
    FT_NA_BYTE      = 'X',                                        //not used or unknown, byte
    FT_STRING       = 's',                                        //char*
    FT_FLOAT        = 'f',                                        //float
    FT_INT          = 'i',                                        //uint32_t
    FT_BYTE         = 'b',                                        //uint8
    FT_LONG         = 'l',                                        //uint64
    FT_SORT         = 'd',                                        //sorted by this field, field is not included
    FT_IND          = 'n',                                        //the same, but parsed to data
    FT_LOGIC        = 'l',                                        //Logical (boolean)
};

namespace ByteConverter
{
    template<size_t T>
    inline void convert(char *val)
    {
        std::swap(*val, *(val + T - 1));
        convert<T - 2>(val + 1);
    }

    template<> inline void convert<0>(char *) { }
    template<> inline void convert<1>(char *) { }           // ignore central byte

    template<typename T> inline void apply(T *val)
    {
        convert<sizeof(T)>((char *)(val));
    }
}

template<typename T>
inline void EndianConvert(T& val)
{
    if (std::endian::native == std::endian::big)
    {
        ByteConverter::apply<T>(&val);
    }
}

template<typename T> inline
void EndianConvertReverse(T& val)
{
    if (std::endian::native != std::endian::big)
    {
        ByteConverter::apply<T>(&val);
    }
}

template<typename T> inline
void EndianConvertPtr(void* val)
{
    if (std::endian::native == std::endian::big)
    {
        ByteConverter::apply<T>(val);
    }
}

template<typename T>
inline void EndianConvertPtrReverse(void* val)
{
    if (std::endian::native != std::endian::big)
    {
        ByteConverter::apply<T>(val);
    }
}
