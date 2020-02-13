#include "AdvancingFront.h"

void Triangulation::VoidInit(void){
    system("cls");
    Triangles.clear();
	Front.clear();
	Fronts.clear();
	Nodes.clear();
	Nodest.clear();
	NodesEdges.clear();
	cpoints.clear();
	CircleFront.clear();
    merge = false, split = false;
	num = (a / h + 1); if(num%2) num++;
	hmesh = a / num;
	Count = 0;
	flag = true;
    if(mod_ == SQUARE)
    {
        FrontInit();
    }else
    {
        FrontInitCircle();
    }
	fit = Front.begin();
    it_node = 0;

    int size1 = Front.size(),
        size2 = CircleFront.size(),
        size = size1+size2;
    Edges.resize(size);
    /////
    NodesEdges.resize(size);
    NodesEdges[0] = vector<int>(2);
    NodesEdges[0][0] = 0;
    NodesEdges[0][1] = size1-1;
    /////
    Edges[0]=TEdge(0,1);
    for(int i = 1; i < size1-1; i++)
    {
        NodesEdges[i]=vector<int>(2);
        NodesEdges[i][0] = i;
        NodesEdges[i][1] = i-1;
        Edges[i] = TEdge(i,i+1);
    }
    NodesEdges[size1-1]=vector<int>(2);
    NodesEdges[size1-1][0] = size1-1;
    NodesEdges[size1-1][1] = size1-2;
    Edges[size1-1] = TEdge(size1-1,0);
    if(size2)
    {
        Edges[size1]=TEdge(size1,size1+1);
        for(int i = size1+1; i < size-1; i++)
        {
            NodesEdges[i]=vector<int>(2);
            NodesEdges[i][0] = i;
            NodesEdges[i][1] = i-1;
            Edges[i] = TEdge(i,i+1);
        }
        Edges[size-1] = TEdge(size-1,size1);

        NodesEdges[size1] = vector<int>(2);
        NodesEdges[size1][0] = size1;
        NodesEdges[size1][1] = size-1;
    }
}

void Triangulation::FrontInit(void) {
	TPoint2d temp(-a/2,-a/2);
    vector<int> vec(1,-2);

	for (unsigned int i = 0;i < num;i++) {//инициализируем фронт границей квадрата
		temp.X(-a/2 + i * hmesh);
		Front.push_back(Nodes.size());
		Nodes.push_back(temp);
		Nodest.push_back(vec);
	}
	temp.X(a/2);

	for (unsigned int i = 0;i < num;i++) {
		temp.Y(-a/2 + i * hmesh);
		Front.push_back(Nodes.size());
		Nodes.push_back(temp);
		Nodest.push_back(vec);
	}
	temp.Y(a/2);

	for (unsigned int i = 0;i < num;i++) {
		temp.X(a/2 - i * hmesh);
		Front.push_back(Nodes.size());
		Nodes.push_back(temp);
		Nodest.push_back(vec);
	}
	temp.X(-a/2);

	for (unsigned int i = 0;i < num;i++) {
		temp.Y(a/2 - i * hmesh);
		Front.push_back(Nodes.size());
		Nodes.push_back(temp);
		Nodest.push_back(vec);
	}
}

void Triangulation::FrontInitCircle(void) {
    TPoint2d temp(-a/2,-a/2);
    int j = 0;
    vector<int> vec1(1,-2), vec2;
    FrontInit();

	double phi0 = 6.0 * M_PI / 4.0;
	int cnum = r / hmesh + 1;
	cnum*=6;
	int num2 = (a/2 - r)/hmesh + 1;
	//cnum*=2;

    for(int i = 0; i < cnum;i++)
    {
        double phi = phi0 - (i) * 2 * M_PI/cnum;
        temp.X(r*cos(phi));
        temp.Y(r*sin(phi));
        CircleFront.push_back(Nodes.size());
		Nodes.push_back(temp);
		Nodest.push_back(vec1);
    }
    cfit = CircleFront.begin();
}

void Triangulation::FrontInitTrian(void)
{
    TPoint2d temp(-a/2,-a/2);
    vector<int> vec(1,-2);
	for (unsigned int i = 0;i <= num/2;i++) {//инициализируем фронт границей квадрата
		temp.X(-a/2 + i * hmesh);
		Front.push_back(Nodes.size());
		Nodes.push_back(temp);
		Nodest.push_back(vec);
	}
	temp.X(0);
	for (unsigned int i = 1;i <= num/2;i++) {
		temp.Y(-a/2 + i * hmesh);
		Front.push_back(Nodes.size());
		Nodes.push_back(temp);
		Nodest.push_back(vec);
	}
	for (unsigned int i = 1;i < num/2;i++) {
		temp.Y(0-i*hmesh);
		temp.X(i*hmesh);
		Front.push_back(Nodes.size());
		Nodes.push_back(temp);
		Nodest.push_back(vec);
	}
	temp.X(a/2);

	for (unsigned int i = 0;i < num;i++) {
		temp.Y(-a/2 + i * hmesh);
		Front.push_back(Nodes.size());
		Nodes.push_back(temp);
		Nodest.push_back(vec);
	}
	temp.Y(a/2);

	for (unsigned int i = 0;i < num;i++) {
		temp.X(a/2 - i * hmesh);
		Front.push_back(Nodes.size());
		Nodes.push_back(temp);
		Nodest.push_back(vec);
	}
	temp.X(-a/2);

	for (unsigned int i = 0;i < num;i++) {
		temp.Y(a/2 - i * hmesh);
		Front.push_back(Nodes.size());
		Nodes.push_back(temp);
		Nodest.push_back(vec);
	}
}
