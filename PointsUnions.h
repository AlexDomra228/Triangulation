struct TTriangle{
    int Ver[3]; //номер точки - вершины
    int Neigh[3]; //номер соседнего ттреугольника
    int NeighRibe[3]; //номер общего ребра в соседнем треугольнике
    int Edges[3];
    int GetVerIndex(int NumberOfNode);

    TTriangle(void)
    {
        Ver[0]=Ver[1]=Ver[2]=Neigh[0]=Neigh[1]=Neigh[2]=Edges[0]=Edges[1]=Edges[2]=-1;
    }
};

struct TRectangle{
    int Ver[4];
    bool Trues[4];
};

struct TRibe{
	int Ver[2];
    int NElement;
    int NRibe;
    TRibe(int vNElement0, int vNRibe0, int v0, int v1);
	TRibe& operator =(const TRibe& a);
    friend bool operator ==(const TRibe& a, const TRibe& b);
	friend bool operator <(const TRibe& a, const TRibe& b);
	friend bool operator >(const TRibe& a, const TRibe& b);
};

struct TTetrahedron{
    int Ver[4]; //номер точки - вершины
    int Neigh[4]; //номер соседнего тетраэдра
    int NeighSurf[4]; //номер общей грани в соседнем тетраэдре
    int GetVerIndex(int NumberOfNode);
};

struct TPolyhedron{
    int Ver[8];
    bool Trues[8];
};

struct TSurface{
	int Ver[3];
    int NElement[2];
    int NSurf[2];
    TSurface(int V0, int V1, int V2, int NElement0, int NElement1, int NSurf0);
	TSurface& operator =(const TSurface& a);
    friend bool operator ==(const TSurface& a, const TSurface& b);
	friend bool operator <(const TSurface& a, const TSurface& b);
	friend bool operator >(const TSurface& a, const TSurface& b);
};
