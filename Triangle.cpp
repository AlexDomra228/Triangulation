#include "Triangle.h"
using namespace std;
//Triangle
//конструкторы
Triangle::Triangle(void):
	p1(TPoint2d()), p2(TPoint2d()), p3(TPoint2d())
{
    Ver[0]=Ver[1]=Ver[2]=-1;
}

Triangle::Triangle(const Triangle &t) :
	p1(t.p1), p2(t.p2), p3(t.p3),
	front_it(t.front_it)
{
    Ver[0]=t.Ver[0],Ver[1]=t.Ver[1],Ver[2]=t.Ver[2];
}

Triangle::Triangle(TPoint2d P1, TPoint2d P2, TPoint2d P3) :
	p1(P1), p2(P2), p3(P3)
{
    Ver[0]=Ver[1]=Ver[2]=-1;
//    if(Cross(p2-p1,p3-p2)>0)
//    {p1 = P2, p2 = P1;}
}

Triangle::Triangle(TPoint2d P1, TPoint2d P2, TPoint2d P3,
                   int i1, int i2,int i3):
	p1(P1), p2(P2), p3(P3)
{
    Ver[0]=i1;Ver[1]=i2;Ver[2]=i3;
//    if(Cross(p2-p1,p3-p2)>0)
//    {p1 = P2, p2 = P1;}
}

Triangle::Triangle(TPoint2d P1, TPoint2d P2, TPoint2d P3,
                   int i1, int i2,int i3,
                   list<int>::iterator FrIt):
	p1(P1), p2(P2), p3(P3)
{
    Ver[0]=i1;Ver[1]=i2;Ver[2]=i3;
    front_it = FrIt;
//    if(Cross(p2-p1,p3-p2)>0)
//    {p1 = P2, p2 = P1;}
}


//операторы

//math
const double Triangle::area(void) const{
    double result = 0.5 * fabs(Cross(p3-p2,p1-p2));
	return result;

}
const double Triangle::quality(void) const {
    if(area()<1e-10) return 2.0;
	double a[] = {FindDist(p1,  p2),
                  FindDist(p2, p3),
                  FindDist(p3, p1)
                  };
	double result = a[0]*a[1]*a[2]/Min(a[0],a[1],a[2]);
	return 4 * area() / result / sqrt(3);
}
TPoint2d Triangle::center(void){
    TPoint2d result = 1/0.3*(p1+p2+p3);
    return result;
}
//func


double GetAngle(TPoint2d a, TPoint2d b, TPoint2d c) {
	double LengthProduct = FindDist(a,b)* FindDist(c,b);
	if (LengthProduct < 1e-10) return 361.0;
	double cos = (c-b)*(a-b) / LengthProduct;
	double result = acos(cos) * 180 / M_PI;
	if (Cross(c-b, a-b) < 0)//>0 if Right-handed
		return 360 - result;
	return result;
}

double Max(double a, double b) {
	return a > b ? a : b;
}

double Max(double a, double b, double c) {
	return a > Max(b, c) ? a : Max(b, c);
}

double Min(double a, double b) {
	return a < b ? a : b;
}

double Min(double a, double b, double c) {
	return a < Min(b, c) ? a : Min(b, c);
}

