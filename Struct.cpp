#include "AdvancingFront.h"

bool intersect(TTriangle t, int n)
{
    return t.Ver[0]==n||t.Ver[1]==n||t.Ver[2]==n;
}
void Triangulation::GetNeib(void)
{
    if(Triangles[0].Neigh[0]>=0)
        return;
    for(int i = 0; i < Triangles.size();i++)
    {
        int Ver[] = {Triangles[i].Ver[0],
                     Triangles[i].Ver[1],
                     Triangles[i].Ver[2]};
        //смотрим в нулевую вершину
        int n0 = Ver[0], n1 = Ver[1], n2 = Ver[2];
        vector<int> trians = Nodest[n0];
        if(trians.size()==2&&trians[0]==-2)
            Triangles[i].Neigh[1]=Triangles[i].Neigh[2]=-2;
        else
            for(auto t:trians)
            {
                if(t!=i && t >= 0)
                {
                    if(intersect(Triangles[t],n1))
                        Triangles[i].Neigh[2]=t;
                    else if(intersect(Triangles[t],n2))
                        Triangles[i].Neigh[1]=t;
                }
            }
        trians = Nodest[n1];
        if(trians.size()==2&&trians[0]==-2)
            Triangles[i].Neigh[0]=-2;
        else
            for(auto t:trians)
            {
                if(t!=i && t >= 0)
                {
                    if(intersect(Triangles[t],n2))
                    {
                        Triangles[i].Neigh[0]=t;
                        break;
                    }
                }
            }

    }
}

void Triangulation::Split(void)
{
    if(Triangles.size()==0)
        return;
    int size = Nodes.size();
    int tsize = Triangles.size();
    int esize = Edges.size();
    auto temp = Triangles;
    vector <TEdge> newedges(esize*2+3*tsize);
    Triangles.resize(4*tsize);
    for(int i = 0; i < Edges.size();i++)
    {
        TPoint2d p = (Nodes[Edges[i].Ver[0]]+Nodes[Edges[i].Ver[1]])*0.5;
        Nodes.push_back(p);
    }
    cout << "hi\n";
    for(int i = 0; i < tsize; i++)
    {
        int p0 = temp[i].Ver[0],
            p1 = temp[i].Ver[1],
            p2 = temp[i].Ver[2],
            e0 = temp[i].Edges[0],
            e1 = temp[i].Edges[1],
            e2 = temp[i].Edges[2],
            q0 = size+e0,
            q1 = size+e1,
            q2 = size+e2;
        //cout << e0 << "\t" << e1 << "\t" << e2 << endl;
        TTriangle t;
        t.Ver[0]=p0,t.Ver[1]=q2,t.Ver[2]=q1;
        t.Neigh[0]=4*i+3;
        if(temp[i].Neigh[1]<0)
        {
            t.Neigh[1]=-2;
        }else
        {
            int neigh_p = 0;
            for(;temp[temp[i].Neigh[1]].Ver[neigh_p]!=p0;neigh_p++)
            {}
            t.Neigh[1]=temp[i].Neigh[1]*4+neigh_p;
        }
        if(temp[i].Neigh[2]<0)
        {
            t.Neigh[2]=-2;
        }else
        {
            int neigh_p = 0;
            for(;temp[temp[i].Neigh[2]].Ver[neigh_p]!=p0;neigh_p++)
            {}
            t.Neigh[2]=temp[i].Neigh[2]*4+neigh_p;
        }
        t.Edges[0] = 2*esize + 3*i + 0;
        t.Edges[1] = Edges[e1].Ver[0]==p0?2*e1:2*e1+1;
        t.Edges[2] = Edges[e2].Ver[0]==p0?2*e2:2*e2+1;
        Triangles[4*i+0] = t;
        t = TTriangle();
        t.Ver[0]=p1,t.Ver[1]=q0,t.Ver[2]=q2;
        t.Neigh[1]=4*i+3;
        if(temp[i].Neigh[0]<0)
        {
            t.Neigh[0]=-2;
        }else
        {
            int neigh_p = 0;
            for(;temp[temp[i].Neigh[0]].Ver[neigh_p]!=p1;neigh_p++)
            {}
            t.Neigh[0]=temp[i].Neigh[0]*4+neigh_p;
        }
        if(temp[i].Neigh[2]<0)
        {
            t.Neigh[2]=-2;
        }else
        {
            int neigh_p = 0;
            for(;temp[temp[i].Neigh[2]].Ver[neigh_p]!=p1;neigh_p++)
            {}
            t.Neigh[2]=temp[i].Neigh[2]*4+neigh_p;
        }
        t.Edges[1] = 2*esize + 3*i + 1;
        t.Edges[2] = Edges[e2].Ver[0]==p1?2*e2:2*e2+1;
        t.Edges[0] = Edges[e0].Ver[0]==p1?2*e0:2*e0+1;
        Triangles[4*i+1] = t;
        t = TTriangle();
        t.Ver[0]=p2,t.Ver[1]=q1,t.Ver[2]=q0;
        t.Neigh[2]=4*i+3;
        if(temp[i].Neigh[0]<0)
        {
            t.Neigh[0]=-2;
        }else
        {
            int neigh_p = 0;
            for(;temp[temp[i].Neigh[0]].Ver[neigh_p]!=p2;neigh_p++)
            {}
            t.Neigh[0]=temp[i].Neigh[0]*4+neigh_p;
        }
        if(temp[i].Neigh[1]<0)
        {
            t.Neigh[1]=-2;
        }else
        {
            int neigh_p = 0;
            for(;temp[temp[i].Neigh[1]].Ver[neigh_p]!=p2;neigh_p++)
            {}
            t.Neigh[1]=temp[i].Neigh[1]*4+neigh_p;
        }
        t.Edges[2] = 2*esize + 3*i + 2;
        t.Edges[1] = Edges[e1].Ver[0]==p2?2*e1:2*e1+1;
        t.Edges[0] = Edges[e0].Ver[0]==p2?2*e0:2*e0+1;
        Triangles[4*i+2] = t;
        t = TTriangle();
        t.Ver[0]=q0,t.Ver[1]=q1,t.Ver[2]=q2;
        TEdge edges[3] = {TEdge(q1,q2),TEdge(q0,q2),TEdge(q0,q1)};
        for(int j = 0; j < 3; j++)
        {
            t.Neigh[j] = 4*i+j;
            t.Edges[j] = 2*esize + 3*i + j;
            newedges[2*esize + 3*i + j] = edges[j];
        }
        Triangles[4*i+3] = t;
        t = TTriangle();
    }
    Nodest.clear();
    NodesEdges.clear();
    for(int i = 0; i<esize;i++)
    {
        newedges[2*i]  =  TEdge(Edges[i].Ver[0],size+i);
        newedges[2*i+1]=  TEdge(size+i,Edges[i].Ver[1]);
    }
    Edges = newedges;
    Nodest.resize(Nodes.size());
    for(int i = 0; i < 4*tsize;i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(find(Nodest[Triangles[i].Ver[j]].begin(),
                    Nodest[Triangles[i].Ver[j]].end(),i)
                  ==Nodest[Triangles[i].Ver[j]].end())
            {
                Nodest[Triangles[i].Ver[j]].push_back(i);
            }
        }
    }

    cout << "---------------------------------------\n";

}

void Triangulation::Split(int tr)
{
    if(tr<0 || tr>=Triangles.size() || is_splited[tr])
        return;
    is_splited[tr]=true;
    TPoint2d p = Nodes[Triangles[tr].Ver[0]]+
                 Nodes[Triangles[tr].Ver[1]]+
                 Nodes[Triangles[tr].Ver[2]];
    for(int j = 0; j < 3; j++)
    {
        int neigh = Triangles[tr].Neigh[j];
        if((neigh>=0 && is_splited[neigh] == false) || neigh < 0)
        {
            Nodes.push_back((p-Nodes[Triangles[tr].Ver[j]])*0.5);
        }
    }
    for(int j = 0; j < 3; j++)
    {
        int neigh = Triangles[tr].Neigh[j];
        Split(neigh);
    }
}

double Triangulation::GetArea(void)
{
    double S = hmesh*hmesh*sqrt(3)/4;
    double res = 0;
    for(auto t:Triangles)
    {
        double s = Triangle(Nodes[t.Ver[0]],
                      Nodes[t.Ver[1]],
                      Nodes[t.Ver[2]]).area() / S;
        if(res<s)
            res = s;
    }
    return res;
}

double Triangulation::GetQuality(void)
{
    double res = 0;
    for(auto t:Triangles)
    {
        res+=Triangle(Nodes[t.Ver[0]],
                      Nodes[t.Ver[1]],
                      Nodes[t.Ver[2]]).quality();
    }
    return res>0?(res/Triangles.size()):0;
}

double Triangulation::GetMinQuality(void)
{
    double res = 1,q;
    for(auto t:Triangles)
    {
        q = Triangle(Nodes[t.Ver[0]],
                     Nodes[t.Ver[1]],
                     Nodes[t.Ver[2]]).quality();
        if(res>q&&q>0)
            res = q;
    }
    return res;
}

double Triangulation::GetArea(int t)
{
    if(t<0)
        return -1;
    Triangle tr(Nodes[Triangles[t].Ver[0]],
                Nodes[Triangles[t].Ver[1]],
                Nodes[Triangles[t].Ver[2]]);
    return tr.area();
}

double Triangulation::GetQuasi(void)
{
    double res = 0;
    for(auto t:Triangles)
    {
        double s0 = GetArea(t.Neigh[0]),
               s1 = GetArea(t.Neigh[1]),
               s2 = GetArea(t.Neigh[2]),
               s = Triangle(Nodes[t.Ver[0]],
                            Nodes[t.Ver[1]],
                            Nodes[t.Ver[2]]).area();
        double k = 0.0;
        if(s0>0) k++;
        if(s1>0) k++;
        if(s2>0) k++;
        if(k)
        res += sqrt((s0*s0+s1*s1+s2*s2)/k)/s;
    }
    return res==0?res:res/Triangles.size();
}

double Triangulation::GetQuasi(int t)
{
    if(t<0||t>=Triangles.size())
        return 0;
    double s0 = GetArea(Triangles[t].Neigh[0]),
           s1 = GetArea(Triangles[t].Neigh[1]),
           s2 = GetArea(Triangles[t].Neigh[2]),
           s = Triangle(Nodes[Triangles[t].Ver[0]],
                        Nodes[Triangles[t].Ver[1]],
                        Nodes[Triangles[t].Ver[2]]).area();
    double k = 0.0;
    if(s0>0) k++;
    if(s1>0) k++;
    if(s2>0) k++;
    if(k)
    return sqrt((s0*s0+s1*s1+s2*s2)/k)/s;
}

double Triangulation::GetQuasiMin(void)
{
    double res = 2;
    for(int i = 0; i < Triangles.size();i++)
    {
        double cur = GetQuasi(i);
        if(cur<res)
            res = cur;
    }
    return res;
}

double Triangulation::GetQuasiMax(void)
{
    double res = 0;
    for(int i = 0; i < Triangles.size();i++)
    {
        double cur = GetQuasi(i);
        if(cur>res)
            res = cur;
    }
    return res;
}


void Triangulation::Laplace(void)
{
    for(int i = 0; i <Nodes.size();i++)
    {
        int l = 0; double x = 0, y = 0;
        if(!Nodest[i].size()||Nodest[i][0]==-2)
            continue;
        for(auto tr:Nodest[i])
        {
            for(int j = 0; j < 3; j++)
            {
                if(Triangles[tr].Ver[j]!=i)
                {
                    l++;
                    x+=Nodes[Triangles[tr].Ver[j]].X();
                    y+=Nodes[Triangles[tr].Ver[j]].Y();
                }
            }
        }
        if(l)
            Nodes[i]=TPoint2d(x/l,y/l);
    }
}

void Triangulation::Laplace2(void)
{
    vector <pair<double,double>> new_nodes(Nodes.size(),{0,0});
    vector <int> l(Nodes.size());
    for(int i = 0; i <Nodes.size();i++)
    {
        l[i] = 0; double x = 0, y = 0;
        if(!Nodest[i].size()||Nodest[i][0]==-2)
            continue;
        for(auto tr:Nodest[i])
        {
            for(int j = 0; j < 3; j++)
            {
                if(Triangles[tr].Ver[j]!=i)
                {
                    l[i]++;
                    new_nodes[i].first+=Nodes[Triangles[tr].Ver[j]].X();
                    new_nodes[i].second+=Nodes[Triangles[tr].Ver[j]].Y();
                }
            }
        }
    }
    for(int i = 0; i < Nodes.size();i++)
    {
        if(l[i])
        {
            Nodes[i].X(new_nodes[i].first/l[i]);
            Nodes[i].Y(new_nodes[i].second/l[i]);
        }
    }
}

