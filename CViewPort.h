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
#include "CRastPort.h"

class CViewPort : public ViewPort
{
    private:
    struct RasInfo *m_RasInfos[2];
    CRastPort *m_RastPorts[2];
    CBitMap *BitMaps[4];

    public:
    CViewPort(UWORD depth, ULONG width, ULONG height, UWORD modes)
    {
        //initialize ViewPort
        InitVPort(this);
        Modes = modes;
        DHeight = height;
        DWidth = width;

        //I always just set maximum (32) (could use (2^depth)&0x20)
        ColorMap = GetColorMap(32);  

        //create viewport bitmap
        BitMaps[0] = new CBitMap(depth, width, height);
        
        //create rasinfo and assign bitmap
        m_RasInfos[0] = new struct RasInfo();
        RasInfo = m_RasInfos[0];
        RasInfo->BitMap = BitMaps[0];

        //create rastport
        m_RastPorts[0] = new CRastPort(width, height, BitMaps[0]);        
       
    }
    ~CViewPort()
    {
        delete m_RastPorts[0];
        delete m_RasInfos[0];
        delete BitMaps[0];
    }

    void Clear(int colour)
    {
        SetRast(m_RastPorts[0], colour);
    }

    void SetForeColour(int colour)
    {
        SetAPen(m_RastPorts[0], colour);
    }

    void SetColour(WORD i, UWORD colour)
    {
        SetRGB4(this, i, colour>>8, (colour&0xf0)>>4, colour&0x0f);
    }

    void WriteText(LONG x, LONG y, STRPTR text)
    {
        Move(m_RastPorts[0], x, y);
        Text(m_RastPorts[0], text, strlen(text));
    }

    void SetWireFrame(int colour)
    {
        SetOPen(m_RastPorts[0], colour);
    }

    void DrawFilledPolygon(Polygon *poly)
    {
        AreaMove(m_RastPorts[0], poly->p1.x, poly->p1.y);
        AreaDraw(m_RastPorts[0], poly->p2.x, poly->p2.y);
        AreaDraw(m_RastPorts[0], poly->p3.x, poly->p3.y);
        AreaEnd(m_RastPorts[0]);
    }
};