#pragma once

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
