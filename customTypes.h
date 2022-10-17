
#pragma once
#include <exec/types.h>
class Vector2d
{
	public:
		WORD x;
		WORD y;
        Vector2d(){}
        Vector2d(WORD _x, WORD _y)
        {
            x = _x;
            y = _y;
        }
        Vector2d& operator=(const Point& point)
        {
            this->x = point.x;
            this->y = point.y;
            return *this;
        }
};
class Vector3d : public Vector2d
{
	public:
		WORD z;
        Vector3d(){}
        Vector3d(WORD _x, WORD _y, WORD _z) :Vector2d(_x, _y) {
            z = _z;
        }
};
class CPoint : public Point
{
    public:
    CPoint(){}
    CPoint(WORD _x, WORD _y)
    {
        x = _x;
        y = _y;
    }
    CPoint& operator-(const CPoint& rhs)
    {
        this->x -= rhs.x;
        this->y -= rhs.y;
        return *this;
    }
};

struct Polygon
{
    public:
        Point p1;
        Point p2;
        Point p3;
        Polygon()
        {
            
        }

        Polygon(Point _p1,Point _p2, Point _p3)   
        : p1(_p1), p2(_p2), p3(_p3)        
        {

        }
};

class TexturedPolygon : public Polygon{
    public:
    UWORD *texture;
    WORD height;
    TexturedPolygon(){}
    TexturedPolygon(Point _p1, Point _p2, Point _p3) 
        : Polygon(_p1, _p2, _p3)
    {

    }
    TexturedPolygon(Point _p1, Point _p2, Point _p3, UWORD* tex, WORD ht)
    : Polygon(_p1, _p2, _p3)
    {
        texture = tex;
        height = ht;
    }

};