#include "Points.h"
#include "CoordinatTranslators.h"
#define _USE_MATH_DEFINES
#include <math.h>

//Определение методов класса TPoint2d

TPoint2d::TPoint2d(){
	fx = fy = 0.0;
}

TPoint2d::TPoint2d(const double x, const double y){
	fx = x;
	fy = y;
}

TPoint2d operator+(const TPoint2d& a, const TPoint2d& b){
	return TPoint2d(a.fx + b.fx, a.fy + b.fy);
}

TPoint2d operator-(const TPoint2d& a, const TPoint2d& b){
	return TPoint2d(a.fx - b.fx, a.fy - b.fy);
}

double operator*(const TPoint2d& a, const TPoint2d& b){
	return a.fx*b.fx + a.fy*b.fy;
}

TPoint2d operator*(const TPoint2d& a, const double b){
	return TPoint2d(a.fx*b, a.fy*b);
}

TPoint2d operator*(const double a, const TPoint2d& b){
	return TPoint2d(a*b.fx, a*b.fy);
}

void TPoint2d::SetPolar(const double r, const double phi){
	fx = GetDecX(r, M_PI/2,phi);
	fy = GetDecY(r, M_PI/2,phi);
}

double TPoint2d::R() const{
	return GetRadius(fx, fy, 0);
}

double TPoint2d::Phi() const{
	return GetPolarAngle(fx, fy);
}

void TPoint2d::Normalize(){
	double l;
	l = GetRadius(fx, fy, 0);
	fx /= l;
	fy /= l;
}

//функция нахождения расстояния между двумя точками
double FindDist(const TPoint2d& p1, const TPoint2d& p2){
	double x = p1.fx - p2.fx;
	double y = p1.fy - p2.fy;
	return sqrt(x*x + y*y);
}

//функция нахождения векторного произведения радиус векторов, заданных введёнными точками (направление ez)
double Cross(const TPoint2d& a, const TPoint2d& b){
	return a.fx*b.fy - b.fx*a.fy;
}

double FindArea(const TPoint2d& a, const TPoint2d& b, const TPoint2d& c){
	return fabs(Cross(b-a, c-a));
}

//Определение методов класса TPoint3d

TPoint3d::TPoint3d():TPoint2d(){
	fz = 0.0;
}

TPoint3d::TPoint3d(const double x, const double y, const double z):TPoint2d(x, y){
	fz = z;
}

TPoint3d operator+(const TPoint3d& a, const TPoint3d& b){
	return TPoint3d(a.fx + b.fx, a.fy + b.fy, a.fz + b.fz);
}

TPoint3d operator-(const TPoint3d& a, const TPoint3d& b){
	return TPoint3d(a.fx - b.fx, a.fy - b.fy, a.fz - b.fz);
}

double operator*(const TPoint3d& a, const TPoint3d& b){
	return a.fx*b.fx + a.fy*b.fy + a.fz*b.fz;
}

TPoint3d operator*(const TPoint3d& a, const double b){
	return TPoint3d(a.fx*b, a.fy*b, a.fz*b);
}

TPoint3d operator*(const double a, const TPoint3d& b){
	return TPoint3d(a*b.fx, a*b.fy, a*b.fz);
}

void TPoint3d::SetSpherical(const double r, const double theta, const double phi){
	fx = GetDecX(r, theta,phi);
	fy = GetDecY(r, theta,phi);
	fz = GetDecZ(r, theta,phi);
}

double TPoint3d::R() const{
	return GetRadius(fx, fy, fz);
}

double TPoint3d::Theta() const{
	return GetAngle(fx, fy, fz);
}

void TPoint3d::Normalize(){
	double l;
	l = GetRadius(fx, fy, fz);
	fx /= l;
	fy /= l;
	fz /= l;
}

//функция нахождения расстояния между двумя точками
double FindDist(const TPoint3d& p1, const TPoint3d& p2){
	double x = p1.fx - p2.fx;
	double y = p1.fy - p2.fy;
	double z = p1.fz - p2.fz;
	return sqrt(x*x + y*y + z*z);
}

//функция нахождения векторного произведения радиус векторов, заданных введёнными точками
TPoint3d Cross(const TPoint3d& a, const TPoint3d& b){
	return TPoint3d(a.fy*b.fz-a.fz*b.fy, a.fz*b.fx-a.fx*b.fz, a.fx*b.fy-a.fy*b.fx);
}

double FindArea(const TPoint3d& a, const TPoint3d& b, const TPoint3d& c){
	return Cross(b-a, c-a).R();
}

double FindVolume(const TPoint3d& a, const TPoint3d& b, const TPoint3d& c, const TPoint3d& d){
	return fabs(Cross(b-a, c-a) * (d-a));
}
