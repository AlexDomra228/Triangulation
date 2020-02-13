#include "Draw.h"

void Draw(Triangle t,int LineWidth)
{
    glColor3d(0,0,0);
	glBegin(GL_LINE_LOOP);
	glLineWidth(LineWidth);
	 glVertex2d(t.p1.X(),t.p1.Y());
     glVertex2d(t.p2.X(),t.p2.Y());
	 glVertex2d(t.p3.X(),t.p3.Y());
	glEnd();
}

void Fill(Triangle t)
{
	glBegin(GL_TRIANGLES);
	 glVertex2d(t.p1.X(),t.p1.Y());
     glVertex2d(t.p2.X(),t.p2.Y());
	 glVertex2d(t.p3.X(),t.p3.Y());
	glEnd();
}

void DrawSquare(double a, int LineWidth)
{
	glColor3d(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glLineWidth(LineWidth);
	glVertex2d(+a / 2, +a / 2);
	glVertex2d(-a / 2, +a / 2);
	glVertex2d(-a / 2, -a / 2);
	glVertex2d(+a / 2, -a / 2);
	glEnd();
}

void DrawCircle(double r, int LineWidth)
{
    int num = 200;
    glColor3d(0, 0, 0);
    glBegin(GL_LINE_LOOP);
    glLineWidth(LineWidth);
    for (int i = 0; i <= num; i++) {
        double phi = 2 * i * M_PI / num;
        glVertex2d(r*cos(phi), r * sin(phi));
    }
    glEnd();
}

void DrawNeinb(Triangulation *trian)
{
    glColor3d(1.0,0.0,1.0);
    glBegin(GL_TRIANGLES);
    for(auto i:trian->Nodest[trian->it_node])
    {
        if (i>=0)
        {
            Triangle t(trian->Nodes[trian->Triangles[i].Ver[0]],
                       trian->Nodes[trian->Triangles[i].Ver[1]],
                       trian->Nodes[trian->Triangles[i].Ver[2]]);

             glVertex2d(t.p1.X(),t.p1.Y());
             glVertex2d(t.p2.X(),t.p2.Y());
             glVertex2d(t.p3.X(),t.p3.Y());
        }
    }
    glEnd();
    glColor3d(0,0,0);
    glPointSize(5);
    glBegin(GL_POINTS);
    if(trian->Nodes.size())
        glVertex2d(trian->Nodes[trian->it_node].X(),
                   trian->Nodes[trian->it_node].Y());
    glEnd();
}

void DrawNeib(Triangulation *trian,int n)
{
//    glColor3d(0.0,0.0,0.0);
//    glBegin(GL_TRIANGLES);
//    for(auto t:trian->Triangles)
//    {
//        if(t.Neigh[0]==-2||t.Neigh[1]==-2||t.Neigh[2]==-2)
//        {
//            Triangle tt(trian->Nodes[t.Ver[0]],
//                       trian->Nodes[t.Ver[1]],
//                       trian->Nodes[t.Ver[2]]);
//            glVertex2d(tt.p1.X(),tt.p1.Y());
//            glVertex2d(tt.p2.X(),tt.p2.Y());
//            glVertex2d(tt.p3.X(),tt.p3.Y());
//        }
//    }
//    glEnd();
//    return;


/////////////////////////////////////////////////////////////////////////////////
    if(n>trian->Triangles.size() || n < 0)
        return;

    glBegin(GL_TRIANGLES);
    Triangle t(trian->Nodes[trian->Triangles[n].Ver[0]],
               trian->Nodes[trian->Triangles[n].Ver[1]],
               trian->Nodes[trian->Triangles[n].Ver[2]]);
    glVertex2d(t.p1.X(),t.p1.Y());
    glVertex2d(t.p2.X(),t.p2.Y());
    glVertex2d(t.p3.X(),t.p3.Y());
    glColor3d(1.0,0.0,1.0);
    for(int i = 0; i < 3; i++)
    {
        if (trian->Triangles[n].Neigh[i]>=0)
        {
            Triangle t(trian->Nodes[trian->Triangles[trian->Triangles[n].Neigh[i]].Ver[0]],
                       trian->Nodes[trian->Triangles[trian->Triangles[n].Neigh[i]].Ver[1]],
                       trian->Nodes[trian->Triangles[trian->Triangles[n].Neigh[i]].Ver[2]]);

             glVertex2d(t.p1.X(),t.p1.Y());
             glVertex2d(t.p2.X(),t.p2.Y());
             glVertex2d(t.p3.X(),t.p3.Y());
        }
    }
    glEnd();
    glColor3d(0,0,0);
    Fill(trian,n);
}

void Draw(Triangulation *trian)
{
    //if (trian->mod_ == CIRCLE)
    //    DrawCircle(trian->r, 2);
	DrawSquare(trian->a, 2);
	//if(trian->Triangles.size()>10000) return;
	for (unsigned int i = 0; i < trian->Triangles.size(); i++) {
        Triangle t(trian->Nodes[trian->Triangles[i].Ver[0]],
                   trian->Nodes[trian->Triangles[i].Ver[1]],
                   trian->Nodes[trian->Triangles[i].Ver[2]]);
        Draw(t,5);
	}
}

void DrawFront(Triangulation *trian) {
	if (!trian->Front.size()) return;
	glPointSize(2);
	glColor3d(1,0,0);
	glBegin(GL_POINTS);
	for (auto p:trian->Front)
    {
        glVertex2d(trian->Nodes[p].X(),trian->Nodes[p].Y());
	}
	for (auto p:trian->CircleFront)
    {
        glVertex2d(trian->Nodes[p].X(),trian->Nodes[p].Y());
    }
	glEnd();

//	glPointSize(2);
//	glColor3d(0,0,0);
//	glBegin(GL_POINTS);
//        glVertex2d(trian->Nodes[*trian->fit].X(),trian->Nodes[*trian->fit].Y());
//    glEnd();
//
//    if(trian->CircleFront.size() && trian->cfit!=trian->CircleFront.end()){
//    glPointSize(2);
//	glColor3d(0,0,0);
//	glBegin(GL_POINTS);
//        glVertex2d(trian->Nodes[*trian->cfit].X(),trian->Nodes[*trian->cfit].Y());
//    glEnd();
//    }
}

void DrawNodes(Triangulation *trian)
{
    glPointSize(3);
	glColor3d(0,0,0);
	glBegin(GL_POINTS);
	for(auto p:trian->Nodes)
    {
        glVertex2d(p.X(),p.Y());
    }
    glEnd();
}

void DrawEdges(Triangulation *trian)
{
    glColor3d(0,0,0);
    glBegin(GL_LINES);
    int i = 0;
    for(auto edge:trian->Edges)
    {
        glVertex2d(trian->Nodes[edge.Ver[0]].X(),
                   trian->Nodes[edge.Ver[0]].Y());
        glVertex2d(trian->Nodes[edge.Ver[1]].X(),
                   trian->Nodes[edge.Ver[1]].Y());
    }
    glEnd();
}

void DrawEdges(Triangulation *trian, int n)
{
    if(n<0||n>=trian->NodesEdges.size())
    {
        return;
    }
    glColor3d(0,0,0);
    glPointSize(7);
    glBegin(GL_POINTS);
    glVertex2d(trian->Nodes[n].X(),trian->Nodes[n].Y());
    glEnd();
    glBegin(GL_LINES);
    for(auto e:trian->NodesEdges[n])
    {
        glVertex2d(trian->Nodes[trian->Edges[e].Ver[0]].X(),
               trian->Nodes[trian->Edges[e].Ver[0]].Y());
        glVertex2d(trian->Nodes[trian->Edges[e].Ver[1]].X(),
               trian->Nodes[trian->Edges[e].Ver[1]].Y());
    }
    glEnd();
}

void Fill(Triangulation *trian) {
    //if(trian->Triangles.size()>10000) return;
    glColor3d(1.0,160.0/255.0,0);
    for (unsigned int i = 0; i < trian->Triangles.size(); i++) {
        Triangle t(trian->Nodes[trian->Triangles[i].Ver[0]],
                   trian->Nodes[trian->Triangles[i].Ver[1]],
                   trian->Nodes[trian->Triangles[i].Ver[2]]);
        Fill(t);
	}
}

vector<bool> is_draw;
void FillRecursion(Triangulation *trian)
{
   if(trian->Triangles.size()==0)
        return;
   is_draw = vector<bool>(trian->Triangles.size(),false);
   FillRecursion(trian, 0);
}

void FillRecursion(Triangulation *trian, int tr)
{
    if(tr<0 || tr>=trian->Triangles.size() || is_draw[tr])
        return;
    is_draw[tr]=true;
    glColor3d(1.0,160.0/255.0,0);
    Fill(trian,tr);
    //glutPostRedisplay();
    //pause(0.5);
    for(int j = 0; j < 3; j++)
    {
        int neigh = trian->Triangles[tr].Neigh[j];
        FillRecursion(trian,neigh);
    }
}

void Fill(Triangulation* trian, int tr)
{
    if(tr<0 || tr>=trian->Triangles.size())
        return;
    Triangle t(trian->Nodes[trian->Triangles[tr].Ver[0]],
               trian->Nodes[trian->Triangles[tr].Ver[1]],
               trian->Nodes[trian->Triangles[tr].Ver[2]]);
    Fill(t);
}

void glWrite(float x, float y, char text[256], int kls, int* font)
{//печать текста на экран
	if (kls == -1) {
		kls = 0;
		while (text[kls])
			kls++;
	}
    glColor3d(0,0,0);
	glRasterPos2f(x, y);
	for (int i = 0; i<kls; i++)
		glutBitmapCharacter(font, (int)text[i]);
}

void pause(double tau)
{
    int t = clock(),dt = 0;
    while(dt < 1000*tau)
        dt = clock() - t;
    return;
}
