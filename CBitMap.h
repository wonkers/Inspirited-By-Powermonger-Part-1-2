#pragma once
#include "support/gcc8_c_support.h"
#include <exec/types.h>
#include <proto/graphics.h>
#include <graphics/gfxbase.h>
#include <graphics/view.h>
#include <graphics/gfxmacros.h>
#include "gels.h"
#include "newdelete.h"

class CBitMap : public BitMap
{
    public:
    CBitMap(USHORT depth, ULONG width, ULONG height)
    {
        InitBitMap(this, depth, width, height);
        for(UBYTE plane = 0; plane < depth; plane++)
        {
            Planes[plane] = AllocRaster(width, height);
            BltClear(Planes[plane], RASSIZE(width, height), 0);
        }
    }
    ~CBitMap()
    {
        for(UBYTE plane = 0; plane < Depth; plane++)
        {
            FreeRaster(Planes[plane], BytesPerRow<<3, Rows);
        }
    }

};