#pragma once
#include "support/gcc8_c_support.h"
#include <exec/types.h>
#include <proto/graphics.h>
#include <graphics/gfxbase.h>
#include <graphics/view.h>
#include <graphics/gfxmacros.h>
#include "gels.h"
#include "newdelete.h"
#include "CBitMap.h"
#define MAXVECTORS 80 //just used what was in the manual

class CRastPort : public RastPort
{
    private:
    struct TmpRas m_TmpRas;
    struct AreaInfo m_AreaInfo;
    PLANEPTR m_RasBuffer;
    WORD m_areaBuffer[MAXVECTORS * 5]; // 5 x maxVectors (80)
    ULONG m_width;
    ULONG m_height;

    public:
    CRastPort(ULONG width, ULONG height, CBitMap *bitmap)
    {
        m_width=width;
        m_height=height;

        InitRastPort(this);
        m_RasBuffer = AllocRaster(width, height);

        InitTmpRas(&m_TmpRas, m_RasBuffer, RASSIZE(width, height));
        InitArea(&m_AreaInfo, m_areaBuffer, MAXVECTORS);
        TmpRas = &m_TmpRas;
        AreaInfo = &m_AreaInfo;
        BitMap = bitmap;

    }
    ~CRastPort()
    {
        FreeRaster(m_RasBuffer, m_width, m_height);
    }
};