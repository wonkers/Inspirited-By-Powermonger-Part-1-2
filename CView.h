#pragma once
#include "support/gcc8_c_support.h"
#include <exec/types.h>
#include <proto/graphics.h>
#include <graphics/gfxbase.h>
#include <graphics/view.h>
#include <graphics/gfxmacros.h>
#include "newdelete.h"
#include "CViewPort.h"

class CView
{
    private:
    struct View m_View;
    struct View *OldView;
    
    //used for double buffering
    cprlist *LOF[2];
	cprlist *SHF[2];

    public:
    CView(UWORD depth, ULONG width, ULONG height, ULONG modes)
    {
        OldView = GfxBase->ActiView;

        InitView(&m_View);
        m_View.Modes = modes;
        m_View.ViewPort = new CViewPort(depth, width, height, modes);
        MakeVPort(&m_View, m_View.ViewPort);
        MrgCop(&m_View);

        LoadView(&m_View);
    }
    ~CView()
    {
        LoadView(OldView);
        delete m_View.ViewPort;       
    }

    CViewPort *ViewPort()
    {
        return (CViewPort *)m_View.ViewPort;
    }
};