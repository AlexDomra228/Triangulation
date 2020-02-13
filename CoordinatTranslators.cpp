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
		if (y >= 0) return acos(x/sqrt(x*x+y*y)); //���������� ��������� ����, ���� �������� ����� ����� � ������ ��������
		if (y < 0) return 2*M_PI-acos(x/sqrt(x*x+y*y)); //���������� ��������� ����, ���� �������� ����� ����� � �������� ��������
	}
	if (x < 0){
		if (y >= 0) return acos(x/sqrt(x*x+y*y)); //���������� ��������� ����, ���� �������� ����� ����� � ������� ��������
		if (y < 0) return 2*M_PI-acos(x/sqrt(x*x+y*y)); //���������� ��������� ����, ���� �������� ����� ����� �� ������  ��������
	}
	if (x == 0){
		if (y > 0) return M_PI/2; //������ ��������� ����, ���� �������� ����� ����� �� ������������� ����� ��� OY
		if (y < 0) return 3/2*M_PI; //������ ��������� ����, ���� �������� ����� ����� �� ������������� ����� ��� OY
		if (y == 0) return 0; //� ������ ���� �������� �������������� ����� - ������ ���������, �� ������� ���������� ����
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
