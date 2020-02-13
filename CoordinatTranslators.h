#ifndef COORDINAT_TRANSLATOR_DEFINED

#define COORDINAT_TRANSLATOR_DEFINED
#define M_PI 3.1415926535
double GetRadius(double x, double y, double z);

double GetPolarRadius(double x, double y);

double GetAngle(double x, double y, double z);

double GetPolarAngle(double x, double y);

double GetDecX(double r, double theta, double phi);

double GetDecY(double r, double theta, double phi);

double GetDecZ(double r, double theta, double phi);

#endif
