#include "AdvancingFront.h"
using namespace std;

void Triangulation::GetNewPoint(void) {
	fit = Front.begin();
	list<int>::iterator itp    = Plus(fit, -1),
                            itn    = Plus(fit, +1),
                            result = fit;
	double minAngle = GetAngle(Nodes[*itp],
                               Nodes[*fit],
                               Nodes[*itn]),
                               curAngle;
	if(minAngle != minAngle){
        minAngle = 361;
	}
	fit++;
	for (;fit != Front.begin(); Plus()) {
		itp = Plus(fit, -1);
		itn = Plus(fit, +1);
		if(FindDist(Nodes[*fit],Nodes[*itp])>4*hmesh||
           FindDist(Nodes[*fit],Nodes[*itn])>4*hmesh)
           continue;
		curAngle = GetAngle(Nodes[*itp],
                            Nodes[*fit],
                            Nodes[*itn]);
		if (curAngle < minAngle) {
			minAngle = curAngle;
			result = fit;
		}
	}
	fit = result;
}

bool Triangulation::isFit(Triangle t,double S){
	double s = t.area() / S;//
	double q = 0.1;
    if (s > 1.0+q || s < 1.0-q)
        return false;
	return true;
}

bool Triangulation::isIntersect(Triangle t){
    for(list<int>::iterator it = Front.begin();it!=Front.end(); it++)
	{
	    if(IsIntersectNotStrict(t,Nodes[*it]))
	    {
	        return true;
	    }
	}
	for(list<int>::iterator it = Front.begin();it!=Front.end(); it++)
	{
	    if(IsIntersect(t.p1,t.p3,Nodes[*it],Nodes[*(Plus(it,1))]))
	    {
            return true;
	    }
//	    if(IsIntersect(t.p2,t.p3,Nodes[*it],Nodes[*(Plus(it,1))]))
//	    {
//            return true;
//	    }
	}
	return false;
}

void Triangulation::FindPoints(double S)
{
    TPoint2d temp;
	TPoint2d cur = Nodes[*fit],
             next = Nodes[*Plus(fit,1)],
             prev = Nodes[*Plus(fit,-1)];
    //double ro = sqrt(2) * hmesh;
    double ro = sqrt(8.0*S/sqrt(3.0));
    for (auto cp : CircleFront)
    {
        temp = Nodes[cp];
        if(FindDist(cur ,temp) <= ro &&
           FindDist(next,temp) <= ro)
        {
            double max_angle = GetAngle(prev,cur,next),
                   cur_angle = GetAngle(prev,cur,temp),
                   p = 0.2, q = 1-p;
            bool is = cur_angle < Min(100,q * max_angle)
                      &&
                      cur_angle > Max(30,p * max_angle);
            if(is)
            {
                cpoints.push_back(cp);
            }
        }
    }
}

void Triangulation::FindPoints2(double S)
{
    TPoint2d temp;
	TPoint2d cur = Nodes[*fit],
             next = Nodes[*Plus(fit,1)],
             prev = Nodes[*Plus(fit,-1)];
    double ro = sqrt(1.5*8.0*S/sqrt(3.0));
    for (auto fp = Plus(fit,+3); fp!= Plus(fit,-1); fp = Plus(fp,1))
    {
        temp = Nodes[*fp];
        if(FindDist(cur ,temp) <= ro &&
           FindDist(next,temp) <= ro)
        {
            double max_angle = GetAngle(prev,cur,next),
                   cur_angle = GetAngle(prev,cur,temp),
                   p = 0.3, q = 1-p;
            bool is = cur_angle < Min(100,q * max_angle)
                      &&
                      cur_angle > Max(30,p * max_angle);
            if(is)
            {
                cpoints.push_back(*fp);
            }
        }
    }
}

bool Triangulation::isValid(Triangle t,double S) {
	if (t.area() <1e-10) return false;

	return isFit(t,S)&&(!isIntersect(t));
}


void Triangulation::GetTriangle(void) {
    int cur = *fit,
        next  = *(Plus(fit, 1)),
        prev  = *(Plus(fit, -1));
    TPoint2d
        pcur = Nodes[cur],
        pnext = Nodes[next],
        pprev = Nodes[prev];

        double phi = GetAngle(pprev,pcur,pnext),
               S0 = hmesh*hmesh*sqrt(3)/4,
               r1 = FindDist(pcur,TPoint2d(-a/4,-a/4)),
               r2 = FindDist(pcur,TPoint2d(a/4,a/4)),
               ro = FindDist(pcur,TPoint2d()),
               S=S0;
        ro = Min(r1,r2);
//        if(ro>r)
//            S*=pow((ro/a),1.0);
//        else
//            S*=pow((r/a),1.0);

        cpoints.clear();
        FindPoints(S);
        vector<Triangle> triangles;

        for(auto cp:cpoints)
        {
            Triangle t(pcur,pnext,Nodes[cp],cur,next,cp);
            if(isValid(newt,S))
                triangles.push_back(t);

        }
        if(triangles.size()){
            sort(triangles.begin(),triangles.end());
            newt = triangles.front();
            merge=true;
            return;
        }

        cpoints.clear();
        FindPoints2(S);
        triangles.clear();

        for(auto cp:cpoints)
        {
            Triangle t(pcur,pnext,Nodes[cp],cur,next,cp);
            if(isValid(newt,S))
                triangles.push_back(t);

        }
        if(triangles.size()){
            sort(triangles.begin(),triangles.end());
            newt = triangles.front();
            split=true;
            return;
        }

        newt = Triangle(pcur,pnext,pprev,cur,next,prev);
        if(phi <= 85.01)
        {
            return;
        }

        phi = phi * M_PI / 180.0;
        phi /= 2.0;
        double l1 = FindDist(pprev,pcur),
               l2 = FindDist(pcur,pnext),
               l = 4*S0/sin(phi)/(l1+l2);
        if(l2>=l1){
            l = 2 * S / l2 / sin(phi);
            TPoint2d p = pnext - pcur;
            p = p * (l / l2);
            TPoint2d p_(p.X()*cos(phi)-p.Y()*sin(phi),
                        p.X()*sin(phi)+p.Y()*cos(phi));
            p_ = pcur + p_;
            newt = Triangle(pcur,pnext,p_,cur,next,Nodes.size());
           }
        else{
            l = 2 * S / l1 / sin(phi);
            TPoint2d p = pprev - pcur;
            p = p * (l / l1);
            TPoint2d p_(p.X()*cos(phi)+p.Y()*sin(phi),
                        -p.X()*sin(phi)+p.Y()*cos(phi));
            p_ = pcur + p_;
            newt = Triangle(pprev,pcur,p_,prev,cur,Nodes.size());
        }
        if(!isIntersect(newt))
            return;
        newt = Triangle(pcur,pnext,pprev,cur,next,prev);
        if(!isIntersect(newt))
            return;
        else flag = false;
        return;
}

void Triangulation::UpdateFront(void) {
    if(!flag) return;
    int cur = *fit,
        next  = *(Plus(fit, 1)),
        prev  = *(Plus(fit, -1)),
        size = Nodes.size();

    int Ver[]={newt.Ver[0],newt.Ver[1],newt.Ver[2]};
    if(Front.size()==3)
    {
        Nodest[cur].push_back(Triangles.size()-1);
        Nodest[prev].push_back(Triangles.size()-1);
        Nodest[next].push_back(Triangles.size()-1);
        Front.erase(fit);
        int edge0,edge1,edge2;
        for(int i = 0; i < NodesEdges[cur].size(); i++)
        {
            if(Edges[NodesEdges[cur][i]].Ver[0]==prev)
                edge1 = NodesEdges[cur][i];
            if(Edges[NodesEdges[cur][i]].Ver[1]==next)
                edge2 = NodesEdges[cur][i];
        }
        for(int i = 0; i < NodesEdges[next].size(); i++)
        {
            if(Edges[NodesEdges[next][i]].Ver[1]==prev)
                edge0 = NodesEdges[next][i];
        }
        Edges[edge1].tr[1]=Triangles.size()-1;
        Edges[edge2].tr[0]=Triangles.size()-1;
        Edges[edge0].tr[0]=Triangles.size()-1;
        Triangles[Triangles.size()-1].Edges[0] = edge0;
        Triangles[Triangles.size()-1].Edges[1] = edge1;
        Triangles[Triangles.size()-1].Edges[2] = edge2;
        return;
    }
    if(merge)
    {
        merge = false;
        MergeFront(newt.Ver[2]);
        Nodest[cur].push_back(Triangles.size()-1);
        Nodest[Ver[2]].push_back(Triangles.size()-1);
        Nodest[next].push_back(Triangles.size()-1);
        return;
    }
    else if(split)
    {
        split = false;
        SplitFront(newt.Ver[2]);
        Nodest[cur].push_back(Triangles.size()-1);
        Nodest[Ver[2]].push_back(Triangles.size()-1);
        Nodest[next].push_back(Triangles.size()-1);

        int edge2, edge1, edge0;
        for(int i = 0; i < NodesEdges[cur].size(); i++)
        {
            if(Edges[NodesEdges[cur][i]].Ver[1]==next)
            {
                edge2 = NodesEdges[cur][i];
                break;
            }
        }
        Edges[edge2].tr[0]=Triangles.size()-1;
        edge1 = Edges.size();
        Edges.push_back(TEdge(cur,Ver[2],-1,Triangles.size()-1));
        edge0 = Edges.size();
        Edges.push_back(TEdge(Ver[2],next,-1,Triangles.size()-1));
        Triangles[Triangles.size()-1].Edges[0] = edge0;
        Triangles[Triangles.size()-1].Edges[1] = edge1;
        Triangles[Triangles.size()-1].Edges[2] = edge2;
        NodesEdges[cur].push_back(edge1);
        NodesEdges[next].push_back(edge0);
        NodesEdges.push_back(vector<int>());
        NodesEdges[Ver[2]].push_back(edge0);
        NodesEdges[Ver[2]].push_back(edge1);
        return;
    }
    if(Ver[0] == cur)//curnext
    {
        if(Ver[2] == prev)
        {
            Nodest[cur].push_back(Triangles.size()-1);
            Nodest[prev].push_back(Triangles.size()-1);
            Nodest[next].push_back(Triangles.size()-1);
            Front.erase(fit);
            int edge1, edge2;
            for(int i = 0; i < NodesEdges[cur].size(); i++)
            {
                if(Edges[NodesEdges[cur][i]].Ver[0]==prev)
                {
                    edge1 = NodesEdges[cur][i];
                }
                else if(Edges[NodesEdges[cur][i]].Ver[1]==next)
                {
                    edge2 = NodesEdges[cur][i];

                }
            }
            Edges[edge1].tr[1]=Triangles.size()-1;
            Edges[edge2].tr[0]=Triangles.size()-1;
            Triangles[Triangles.size()-1].Edges[0] = Edges.size();
            Triangles[Triangles.size()-1].Edges[1] = edge1;
            Triangles[Triangles.size()-1].Edges[2] = edge2;
            NodesEdges[prev].push_back(Edges.size());
            NodesEdges[next].push_back(Edges.size());
            Edges.push_back(TEdge(prev,next,-1,Triangles.size()-1));
            return;
        }
        else if(Ver[2] == size)
        {
            Front.insert(Plus(fit,1),size);
            Nodest.push_back(vector<int>());
            Nodest[cur].push_back(Triangles.size()-1);
            Nodest[next].push_back(Triangles.size()-1);
            Nodest[size].push_back(Triangles.size()-1);
            int edge2, edge1, edge0;
            for(int i = 0; i < NodesEdges[cur].size(); i++)
            {
                if(Edges[NodesEdges[cur][i]].Ver[1]==next)
                {
                    edge2 = NodesEdges[cur][i];
                    break;
                }
            }
            Edges[edge2].tr[0]=Triangles.size()-1;
            edge1 = Edges.size();
            Edges.push_back(TEdge(cur,size,-1,Triangles.size()-1));
            edge0 = Edges.size();
            Edges.push_back(TEdge(size,next,-1,Triangles.size()-1));
            Triangles[Triangles.size()-1].Edges[0] = edge0;
            Triangles[Triangles.size()-1].Edges[1] = edge1;
            Triangles[Triangles.size()-1].Edges[2] = edge2;
            NodesEdges[cur].push_back(edge1);
            NodesEdges[next].push_back(edge0);
            NodesEdges.push_back(vector<int>());
            NodesEdges[size].push_back(edge0);
            NodesEdges[size].push_back(edge1);
            Nodes.push_back(newt.p3);
            return;
        }
        else
        {
            MergeFront(Ver[2]);
            return;
        }
    }
    else//prevcur
    {
        Front.insert(fit,size);
        Nodest.push_back(vector<int>());
        Nodest[prev].push_back(Triangles.size()-1);
        Nodest[cur].push_back(Triangles.size()-1);
        Nodest[size].push_back(Triangles.size()-1);

        int edge2, edge1, edge0;
        for(int i = 0; i < NodesEdges[prev].size(); i++)
        {
            if(Edges[NodesEdges[prev][i]].Ver[0]==prev)
            {
                edge2 = NodesEdges[prev][i];
                break;
            }
        }
        Edges[edge2].tr[0]=Triangles.size()-1;
        edge1 = Edges.size();
        Edges.push_back(TEdge(prev,size,-1,Triangles.size()-1));
        edge0 = Edges.size();
        Edges.push_back(TEdge(size,cur,-1,Triangles.size()-1));

        Triangles[Triangles.size()-1].Edges[0] = edge0;
        Triangles[Triangles.size()-1].Edges[1] = edge1;
        Triangles[Triangles.size()-1].Edges[2] = edge2;
        NodesEdges[prev].push_back(edge1);
        NodesEdges[cur].push_back(edge0);
        NodesEdges.push_back(vector<int>());
        NodesEdges[size].push_back(edge0);
        NodesEdges[size].push_back(edge1);
        Nodes.push_back(newt.p3);
        return;
    }
}

void Triangulation::UpdateTrian(void) {
    if (!flag) return;
	else
	{
        TTriangle t;
        t.Ver[0] = newt.Ver[0];
        t.Ver[1] = newt.Ver[1];
        t.Ver[2] = newt.Ver[2];
        Triangles.push_back(t);
	}
	if(Front.size() == 2 && Fronts.size()==0) {
        flag = false;
        std::cout<<"End of triangulation\n";
    }
}

void Triangulation::AdvancingFrontIter(void) {
    if(flag)
    {
        if(Front.size() <= 3)
        {
            fit = Front.begin();
            TTriangle t;
            t.Ver[0] = *fit;
            t.Ver[1] = *Plus(fit,1);
            t.Ver[2] = *Plus(fit,2);
            newt = Triangle(Nodes[*fit],
                            Nodes[*Plus(fit,1)],
                            Nodes[*Plus(fit,2)],
                            *fit,
                            *Plus(fit,1),
                            *Plus(fit,2));
            UpdateTrian();
            UpdateFront();
            //Triangles.push_back(t);
            if(Fronts.size())
            {
                Front = Fronts.back();
                Fronts.pop_back();
                AdvancingFrontIter();
                return;
            }
            else
            {
                flag = false;
                return;
            }
        }
        GetNewPoint();
        GetTriangle();
        UpdateTrian();
        UpdateFront();
    }
   // else GetNeib();
    fit = Front.begin();
}

void Triangulation::AdvancingFront(void)
{
    while(flag)
        AdvancingFrontIter();
    GetNeib();
}

void Triangulation::MergeFront(int c)
{
    cfit = CircleFront.begin();
    auto next = Plus(fit,1);
    while((*cfit)!=c)
    {
        CirclePlus();
    }
    Front.insert(next,c);
    CirclePlus();
    for(;(*cfit)!=c;CirclePlus())
    {
        //cout << *cfit <<"\n";
        Front.insert(next,*cfit);

    }
    Front.insert(next, *cfit);
    CircleFront.reverse();
    Fronts.push_back(CircleFront);
    CircleFront.clear();
    fit = Front.begin();
}

void Triangulation::SplitFront(int f)
{
    auto it = fit, next = Plus(fit,1);
    while(*(fit)!=f)
        Plus();
    auto newp = fit;
    list <int> front1,front2;
    while(fit!=it)
    {
        front1.push_back(*fit);
        Plus();
    }
    front1.push_back(*fit);
    Plus();
    while(fit!=newp)
    {
        front2.push_back(*fit);
        Plus();
    }
    front2.push_back(*fit);

    Front.clear();
    Front = front2;
    Fronts.push_back(front1);
    fit = Front.begin();
    return;

}

void Triangulation::CircleTriangulation(void){
    return;
}
