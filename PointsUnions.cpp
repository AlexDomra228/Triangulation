#include "PointsUnions.h"

int TTriangle::GetVerIndex(int NumberOfNode){
	int i;
	for (i = 0; i < 3; i++)
		if (Ver[i] == NumberOfNode){
			return i;
		}
    return -1;
}

//************************************************************************************

TRibe::TRibe(int V0, int V1, int NElement0, int NRibe0){
	Ver[0] = V0;
	Ver[1] = V1;
	NElement = NElement0;
	NRibe = NRibe0;
}

TRibe& TRibe::operator =(const TRibe& a){
	int i;
	for (i = 0; i < 2; i++) Ver[i] = a.Ver[i];
	NElement = a.NElement;
	NRibe = a.NRibe;
	return *this;
}

bool operator ==(const TRibe& a, const TRibe& b){
	return (a.Ver[0] == b.Ver[0]) && (a.Ver[1] == b.Ver[1]);
}

bool operator <(const TRibe& a, const TRibe& b){
	if (a.Ver[0] == b.Ver[0]) return (a.Ver[1] < b.Ver[1]);
	return (a.Ver[0] < b.Ver[0]);
}

bool operator >(const TRibe& a, const TRibe& b){
	if (a.Ver[0] == b.Ver[0]) return (a.Ver[1] > b.Ver[1]);
	return (a.Ver[0] > b.Ver[0]);
}

//***************************************************************************************

int TTetrahedron::GetVerIndex(int NumberOfNode){
	int i;
	for (i = 0; i < 4; i++)
		if (Ver[i] == NumberOfNode){
			return i;
		}
    return -1;
}

//***************************************************************************************

TSurface::TSurface(int V0, int V1, int V2, int NElement0, int NElement1, int NSurf0){
	Ver[0] = V0;
	Ver[1] = V1;
	Ver[2] = V2;
	NElement[0] = NElement0;
	NElement[1] = NElement1;
	NSurf[0] = NSurf0;
}

TSurface& TSurface::operator =(const TSurface& a){
	int i;
	for (i = 0; i < 3; i++) Ver[i] = a.Ver[i];
	for (i = 0; i < 2; i++){
		NElement[i] = a.NElement[i];
		NSurf[i] = a.NSurf[i];
	}
	return *this;
}

bool operator ==(const TSurface& a, const TSurface& b){
	return (a.Ver[0] == b.Ver[0]) && (a.Ver[1] == b.Ver[1]) && (a.Ver[2] == b.Ver[2]);
}

bool operator <(const TSurface& a, const TSurface& b){
	if (a.Ver[0] == b.Ver[0]){     
		if (a.Ver[1] == b.Ver[1]) return (a.Ver[2] < b.Ver[2]);
		return (a.Ver[1] < b.Ver[1]);
	}
	return (a.Ver[0] < b.Ver[0]);
}

bool operator >(const TSurface& a, const TSurface& b){
	if (a.Ver[0] == b.Ver[0]){     
		if (a.Ver[1] == b.Ver[1]) return (a.Ver[2] > b.Ver[2]);
		return (a.Ver[1] > b.Ver[1]);
	}
	return (a.Ver[0] > b.Ver[0]);
}
