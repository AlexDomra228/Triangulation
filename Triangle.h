#pragma once
#include "Headers.h"
#include "Points.h"
using namespace std;
bool IsEqual(TPoint2d a, TPoint2d b);
class Triangle{
public:
	//данные
	TPoint2d p1, p2, p3;
	int Ver[3];
	list<int>::iterator front_it;
	Triangle(void);
	Triangle(const Triangle &t);
	Triangle(TPoint2d P1, TPoint2d P2, TPoint2d P3);
	Triangle(TPoint2d P1, TPoint2d P2, TPoint2d P3,
             int i1, int i2, int i3);
    Triangle(TPoint2d P1, TPoint2d P2, TPoint2d P3,
             int i1, int i2, int i3,
             list<int>::iterator FrIt);

	//some math ) )
	const double area(void) const;
	const double quality(void) const;
	TPoint2d center(void);

	const bool operator <(const Triangle & t) const{
        return quality()>t.quality();
	}
	const bool operator >(const Triangle & t) const{
        return quality()<t.quality();
	}

	const bool operator ==(const TPoint2d & p) const{
        return IsEqual(p1,p)||IsEqual(p2,p)||IsEqual(p3,p);
	}
};

bool IsIntersect(TPoint2d a,TPoint2d b,TPoint2d c,TPoint2d d);
bool IsIntersect(Triangle T, TPoint2d p);
bool IsIntersect(Triangle T, TPoint2d p1, TPoint2d p2);
bool IsIntersectNotStrict(Triangle T, TPoint2d p);
//ещё кое что
double GetAngle(TPoint2d a, TPoint2d b, TPoint2d c);
double GetAngle2(TPoint2d a, TPoint2d b, TPoint2d c);
double Max(double a, double b);
double Max(double a, double b, double c);
double Min(double a, double b);
double Min(double a, double b, double c);
