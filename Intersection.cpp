#include "Triangle.h"
bool IsEqual(TPoint2d a, TPoint2d b)
{
    double eps = 1e-16;
    return fabs(a.X()-b.X())<eps && fabs(a.Y()-b.Y())<eps;
}
bool IsIntersect(TPoint2d a,TPoint2d b,TPoint2d c,TPoint2d d)
{
    double eps = pow(10,-8);
    if(IsEqual(a,c) && IsEqual(b,d)|| IsEqual(a,d)&& IsEqual(b,c)) return false;
    double q = Cross(b-a,c-a),
           w = Cross(b-a,d-a),
           e = Cross(d-c,a-c),
           r = Cross(d-c,b-c);
    if((abs(q)<eps && abs(w)>eps)||(abs(w)<eps && abs(q)>eps)){
        if((abs(e)<eps && abs(r)>eps)||(abs(r)<eps && abs(e)>eps)){
            return false;
        }
    }
    if(abs(q)+abs(w)+abs(e)+abs(r) < 4*eps){
        if (abs(a.X()-b.X()) > 2*eps){
            double mmin = Min(Max(a.X(),b.X()),Max(c.X(),d.X())),
                   mmax = Max(Min(a.X(),b.X()),Min(c.X(),d.X()));
            if(mmin <= mmax) return false;
            else {
                //std::cout<<"intersect\n";
                return true;
            }
        }
        else {
            double mmin = Min(Max(a.Y(),b.Y()),Max(c.Y(),d.Y())),
                   mmax = Max(Min(a.Y(),b.Y()),Min(c.Y(),d.Y()));
            if(mmin <= mmax) return false;
            else {
                //std::cout<<"intersect\n";
                return true;
            }
        }
    }
    bool result = q*w<eps&&e*r<eps;
    //if(result) std::cout<<"intersect\n";
    return result;
}
/*
    возвращает true, если точка внутри треугольника или на его границе.
    если точка совпадает с вершиной треугольника, тоже возвращает true
*/
bool IsIntersect(Triangle T, TPoint2d p) {
	TPoint2d B = T.p2 - T.p1, C = T.p3 - T.p1, P = p - T.p1;
	double m, l;
    double denom = (B.X()*C.Y() - B.Y()*C.X());
	m = -(P.X()*B.Y() - P.Y()*B.X())/denom;
	double eps = pow(10,-8);
	if (m >= -eps && m - 1 <= eps) {
		l = (P.X()*C.Y() - P.Y()*C.X())/denom;
		if (l >= -eps && m + l - 1 <= 2*eps) {
			return true;
		}
	}
	return false;
}

//qwe
bool IsIntersectNotStrict(Triangle T, TPoint2d p) {
    if(T==p) return false;
    return IsIntersect(T,p);
}

bool IsIntersect(Triangle t, TPoint2d p1, TPoint2d p2)
{
    return IsIntersect(t.p1,t.p2,p1,p2) ||
           IsIntersect(t.p2,t.p3,p1,p2) ||
           IsIntersect(t.p1,t.p1,p1,p2);
}
