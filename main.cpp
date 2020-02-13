#include "AdvancingFront.h"
#include "Draw.h"
using namespace std;

int    WinWidth  = 1080.0,
	   WinHeight = 607.5,
	   WinDepth  = 10.0;
Triangulation* trian;
bool start = false;
int TriIndex=-1;

void init(void);
void display(void);
void func(unsigned char, int, int);
void mouseButton(int button, int state, int x, int y);
void init(void) {
	glClearColor(1, 1, 1, 1);
	gluOrtho2D(-WinWidth/2, WinWidth/2, -WinHeight/2, WinHeight/2);
}

void mouseButton(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON)
	{
        if(state == GLUT_UP)
        {
            TriIndex=0;
            for(;TriIndex<trian->Triangles.size();TriIndex++)
            {
                Triangle t(trian->Nodes[trian->Triangles[TriIndex].Ver[0]],
                        trian->Nodes[trian->Triangles[TriIndex].Ver[1]],
                        trian->Nodes[trian->Triangles[TriIndex].Ver[2]]);
                if(IsIntersect(t,TPoint2d(x-WinWidth/2,WinHeight/2-y)))
                    break;
            }
        }
	}
	glutPostRedisplay();
}


void func(unsigned char key, int x, int y) {
	switch (key)
	{
		case (int)'Q':case (int)'q':
			exit(0);
		break;
		case (int)'d':case (int)'D':
			trian->Plus();
		break;

		case (int)'a':case (int)'A':
			trian->Plus(-1);
		break;

		case (int)'f':case (int)'F':
			trian->MinusNode();
		break;

		case (int)'h':case (int)'H':
			trian->PlusNode();
		break;

		case VK_SPACE:
		    trian->AdvancingFrontIter();
        break;

        case (int)'s':
            start = !start;
        break;

		case(int)'j':
		    if(trian->mod_==SQUARE)
                trian->mod_=CIRCLE;
            else
                trian->mod_ = SQUARE;
            trian->VoidInit();
        break;

        case(int)'k':
            trian->Split();
        break;
        case (int)'1':
            TriIndex++;
//            trian->CirclePlus();
//            cout << *trian->cfit << endl;
		break;

		case (int)'2':
            TriIndex--;
//            trian->CircleMinus();
//            cout << *trian->cfit << endl;
		break;

		case (int)'3':
            TriIndex=0;
		break;

		case (int)'4':
            TriIndex = trian->Triangles.size();
		break;

		case (int)'5':
            trian->factor = 16;
            trian->VoidInit();
		break;

		case (int)'6':
            trian->factor = 12;
            trian->VoidInit();
		break;

        case (int)'+':
        case (int)'=':
            trian->h +=2.5;
            trian->VoidInit();
		break;

		case (int)'-':
            if(trian->h>3.5)
            {
                trian->h -=2.5;
                trian->VoidInit();
            }
		break;

		case (int)'u':case (int)'U':
			if(trian->r>15 && trian->mod_ == CIRCLE)
            {
                trian->r -=2.5;
                trian->VoidInit();
            }
		break;

		case (int)'i':case (int)'I':
			if(trian->r<trian->a/2 && trian->mod_ == CIRCLE)
            {
                trian->r +=2.5;
                trian->VoidInit();
            }
		break;

		case (int)'r':case (int)'R':
            trian->VoidInit();
            start = false;
		break;

		case(int)'z':
		    trian->Laplace2();
        break;

        case(int)'x':
		    trian->Laplace2();
        break;

        case(int)'m':
		    trian->AdvancingFront();
        break;
	}
	glutPostRedisplay();
}
void display(void){
	glClear(GL_COLOR_BUFFER_BIT);
    Fill(trian);
    //FillRecursion(trian);
	DrawNeib(trian,TriIndex);
	Draw(trian);
	//DrawFront(trian);
	DrawEdges(trian,trian->it_node);
	DrawNodes(trian);
    char buf[1024];
	sprintf(buf, "a = %.2f,r = %.2f,h = %.2f, size = %d, quasi = %.3f, min= %.3f, max = %.3f avar = %.3f",
            trian->a, trian->r, trian->h, trian->Triangles.size(),
            trian->GetQuasi(TriIndex),trian->GetQuasiMin(),trian->GetQuasiMax(),trian->GetQuasi());
	glWrite(-WinWidth / 2, WinHeight / 2 - 24,buf, -1);

    int num = 100;
	if(start&&trian->flag)
    {
        pause(0.0);
        for(int i = 0; i < num; i++)
            trian->AdvancingFrontIter();
        glutPostRedisplay();
    }

    glFlush();
}
int main(int argc, char **argv) {
    setlocale(LC_ALL, "Russian");
	srand(time(0));
	trian = new Triangulation;
	trian->a = 500; trian->r = 100; trian->h = 50; trian->factor = 3;
	trian->mod_ = SQUARE;
	trian->VoidInit();

	glutInit(&argc, argv);
	glutInitWindowSize(WinWidth, WinHeight);
	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
	glutCreateWindow("My Window");

	init();

    glutKeyboardFunc(func);
    glutMouseFunc(mouseButton);

	glutDisplayFunc(display);

	glutMainLoop();
}
