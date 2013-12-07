#ifndef FRMR_ENCODE_H
#define FRMR_ENCODE_H

#include <stdlib.h>
#include <string>

using std::string;

namespace frmr
{
    string      EncodeINT16( const int16_t num );
    int16_t     DecodeINT16( const string encodedNum );
    string      EncodeUINT16( const uint16_t num );
    uint16_t    DecodeUINT16( const string encodedNum );
    string      EncodeINT32( const int32_t num );
    int32_t     DecodeINT32( const string encodedNum );
    string      EncodeFloat( const float num );
    float       DecodeFloat( const string encodedNum );
}

#endif // FRMR_ENCODE_H
