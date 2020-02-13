#include "CoordinatTranslators.h"
#define _USE_MATH_DEFINES
#include <math.h>
#define M_PI 3.1415926535

double GetRadius(double x, double y, double z){
	return sqrt(x*x+y*y+z*z);
}

double GetPolarRadius(double x, double y){
	return sqrt(x*x+y*y);
}

double GetAngle(double x, double y, double z){
	if ((x != 0) || (y != 0) || (z != 0)){
		return acos(z/sqrt(x*x+y*y+z*z));
	}
	else{
		return 0;
	}
}

double GetPolarAngle(double x, double y){
	if (x > 0){
		if (y >= 0) return acos(x/sqrt(x*x+y*y)); //вычисление полярного угла, если проекция точки лежит в первой четверти
		if (y < 0) return 2*M_PI-acos(x/sqrt(x*x+y*y)); //вычисление полярного угла, если проекция точки лежит в четвёртой четверти
	}
	if (x < 0){
		if (y >= 0) return acos(x/sqrt(x*x+y*y)); //вычисление полярного угла, если проекция точки лежит в третьей четверти
		if (y < 0) return 2*M_PI-acos(x/sqrt(x*x+y*y)); //вычисление полярного угла, если проекция точки лежит во второй  четверти
	}
	if (x == 0){
		if (y > 0) return M_PI/2; //запись полярного угла, если проекция точки лежит на положительной части оси OY
		if (y < 0) return 3/2*M_PI; //запись полярного угла, если проекция точки лежит на отрицательной части оси OY
		if (y == 0) return 0; //в случае если проекция расматриваемой точки - начало координат, то функция возвращает ноль
	}
	return 0;
}

double GetDecX(double r, double theta, double phi){
	return r*cos(phi)*sin(theta);
}

double GetDecY(double r, double theta, double phi){
	return r*sin(phi)*sin(theta);
}

double GetDecZ(double r, double theta, double phi){
	return r*cos(theta);
}
