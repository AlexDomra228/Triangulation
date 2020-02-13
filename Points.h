#ifndef POINTS_H
#define POINTS_H

class TPoint2d{
	protected:
		double fx, fy;
	public:
		inline double X() const;
		inline double Y() const;
		inline void X(double);
		inline void Y(double);
		TPoint2d();
		TPoint2d(const double x, const double y);
		friend TPoint2d operator+(const TPoint2d& a, const TPoint2d& b);
		friend TPoint2d operator-(const TPoint2d& a, const TPoint2d& b);
		friend double operator*(const TPoint2d& a, const TPoint2d& b);
		friend TPoint2d operator*(const TPoint2d& a, const double b);
		friend TPoint2d operator*(const double a, const TPoint2d& b);
		void SetPolar(const double r, const double phi);
		inline void SetDec(const double x, const double y);
		double R() const;
		double Phi() const;
		void Normalize();
		//функция нахождения расстояния между двумя точками
		friend double FindDist(const TPoint2d& p1, const TPoint2d& p2);
		//функция нахождения векторного произведения радиус векторов, заданных введёнными точками (направление ez)
		friend double Cross(const TPoint2d& a, const TPoint2d& b);
		
};

double TPoint2d::X() const{
	return fx;
}

double TPoint2d::Y() const{
	return fy;
}

void TPoint2d::X(const double value){
	fx = value;
}

void TPoint2d::Y(const double value){
	fy = value;
}

void TPoint2d::SetDec(const double x, const double y){
	fx = x;
	fy = y;
}

double FindArea(const TPoint2d& a, const TPoint2d& b, const TPoint2d& c);

class TPoint3d:public TPoint2d{
	protected:
		double fz;
	public:
		inline double Z() const;
		inline void Z(const double);
		TPoint3d();
		TPoint3d(const double x, const double y, const double z);
		friend TPoint3d operator+(const TPoint3d& a, const TPoint3d& b);
		friend TPoint3d operator-(const TPoint3d& a, const TPoint3d& b);
		friend double operator*(const TPoint3d& a, const TPoint3d& b);
		friend TPoint3d operator*(const TPoint3d& a, const double b);
		friend TPoint3d operator*(const double a, const TPoint3d& b);
		void SetSpherical(const double r, const double phi, const double theta);
		inline void SetDec(const double x, const double y, const double z);
		double R() const;
		double Theta() const;
		void Normalize();
		//функция нахождения расстояния между двумя точками
		friend double FindDist(const TPoint3d& p1, const TPoint3d& p2);
		//функция нахождения векторного произведения радиус векторов, заданных введёнными точками
		friend TPoint3d Cross(const TPoint3d& a, const TPoint3d& b);
};

double TPoint3d::Z() const{
	return fz;
}

void TPoint3d::Z(const double value){
	fz = value;
}

void TPoint3d::SetDec(const double x, const double y, const double z){
	fx = x;
	fy = y;
	fz = z;
}

double FindArea(const TPoint3d& a, const TPoint3d& b, const TPoint3d& c);
double FindVolume(const TPoint3d& a, const TPoint3d& b, const TPoint3d& c, const TPoint3d& d);

#endif