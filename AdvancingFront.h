#pragma once
#include "Points.h"
#include "PointsUnions.h"
#include "Headers.h"
#include "Triangle.h"
using namespace std;

struct TEdge{
    int tr[2];
    int Ver[2];
    bool onCircle;

    TEdge(void)
    {
        tr[0]=tr[1]=-2;
        Ver[0]=Ver[1]=-2;
        onCircle = false;
    }
    TEdge(int p1, int p2, int t1 = -1, int t2 = -2, bool oncircle = false)
    {
        tr[0]=t1,tr[1]=t2;
        Ver[0]=p1,Ver[1]=p2;
        onCircle = oncircle;
    }
};
class Triangulation {
public:
	vector <TTriangle> Triangles;
	vector <bool> is_splited;

	vector <TPoint2d> Nodes;

	vector <TEdge> Edges;

	vector <vector<int>> Nodest;
	vector <vector<int>> NodesEdges;

	vector <list<int>> Fronts;//��������������

    list <int> Front;
    list <int> CircleFront;
    vector <list<int>> CircleFronts;
    vector<int> cpoints;

    int it_node;

    Triangle newt;
    int InitSize;
	double a, r, h, hmesh;
	unsigned int num, factor, Count;
	list<int>::iterator fit, cfit;
	bool flag, merge, split;
	int mod_;
	//�������������
	void VoidInit(void);
    void FrontInit(void);
    void FrontInitCircle(void);
    void FrontInitTrian(void);
    void FrontInitDouble(void);
    //���������
	void GetNewPoint(void);
	void FindPoints(double S);
	void FindPoints2(double S);
	void GetTriangle(void);
	void UpdateFront(void);
	void UpdateTrian(void);
	bool isValid (Triangle,double);
	bool isFit(Triangle,double);
	bool isIntersect(Triangle);
    void AdvancingFrontIter(void);
	void AdvancingFront(void);
    void CircleTriangulation(void);
    void MergeFront(int c);
    void SplitFront(int f);
	//������ ��������
    double GetArea(void);
    double GetArea(int t);
    double GetQuality(void);
    double GetMinQuality(void);
    double GetQuasi(void);
	double GetQuasi(int t);
	double GetQuasiMin(void);
	double GetQuasiMax(void);
    //����������� �����
    void Laplace(void);
	void Laplace2(void);
	void GetNeib(void);
    //���������
    void Split(void);
    void Split(int tr);


    //������������ �� ������
    void Plus(int k = 1);//����������� �������� �� k �������, ���� ������� �� ������, �������� �����
	list<int>::iterator Plus(const list<int>::iterator &it, int k = 1);
    void CirclePlus(void);
    void CircleMinus(void);
	void PlusNode();
	void MinusNode();
};
