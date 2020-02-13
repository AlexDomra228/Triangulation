#include "AdvancingFront.h"
void Triangulation::Split(void){
    split++;
    return;
    int size = Triangles.size();
    for(int i = 0; i < size;i++){
        TPoint2d p1 = Triangles[i].p1, p2 = Triangles[i].p2, p3 = Triangles[i].p3;
        TPoint2d q1 = (Triangles[i].p2 + Triangles[i].p1)/2.0,
                q2 = (Triangles[i].p3 + Triangles[i].p2)/2.0,
                q3 = (Triangles[i].p1 + Triangles[i].p3)/2.0;
        if(q1.onCircle)
        {
            q1*=r/q1.length();
        }
        if(q2.onCircle){
            q2*=r/q2.length();
        }
        if(q3.onCircle){
            q3*=r/q3.length();
        }
        TTriangle t1 = TTriangle(p1,q1,q3),
                 t2 = TTriangle(q1,p2,q2),
                 t3 = TTriangle(p3,q2,q3);
        t1.onCircle = q1.onCircle || q3.onCircle;
        t2.onCircle = q1.onCircle || q2.onCircle;
        t3.onCircle = q2.onCircle || q3.onCircle;
        Triangles.push_back(t1);
        Triangles.push_back(t2);
        Triangles.push_back(t3);
        Triangles[i]=TTriangle(q1,q2,q3);
    }
}

void Triangulation::Split(TTriangle tt, int j){
    currentTriangles.clear();
    currentTriangles.push_back(tt);
    for(int i = 0; i < j; i++)
    {
        int size = currentTriangles.size();
        for(int k = 0; k < size;k++)
        {
            TTriangle t = currentTriangles[k];
            TPoint2d p1 = t.p1, p2 = t.p2, p3 = t.p3;
            TPoint2d q1 = (p2 + p1)/2.0,
                    q2 = (p3 + p2)/2.0,
                    q3 = (p1 + p3)/2.0;
            if(q1.onCircle){
                q1*=r/q1.length();
            }
            if(q2.onCircle)
            {
                q2*=r/q2.length();
            }
            if(q3.onCircle){
                q3*=r/q3.length();
            }
            TTriangle t1 = TTriangle(p1,q1,q3),
                     t2 = TTriangle(q1,p2,q2),
                     t3 = TTriangle(p3,q2,q3);

            t1.onCircle = q1.onCircle || q3.onCircle;
            t2.onCircle = q1.onCircle || q2.onCircle;
            t3.onCircle = q2.onCircle || q3.onCircle;
            currentTriangles.push_back(t1);
            currentTriangles.push_back(t2);
            currentTriangles.push_back(t3);
            currentTriangles[k]=TTriangle(q1,q2,q3);
        }
    }
}

double Triangulation::Integral(void){
    double result = 0;
    for(int i = 0;i < Triangles.size(); i++){
        //result += foo(Triangles[i].center())*Triangles[i].area();
        Split(Triangles[i],split);
        for(int j = 0; j < currentTriangles.size(); j++)
        {
            result += foo(currentTriangles[j].center())
                      *currentTriangles[j].area();
        }
    }
    return result;
}

double Triangulation::Integral1(void){
    double result = 0;
    for(int i = 0;i < Triangles.size(); i++){
        result += foo(Triangles[i].center())*Triangles[i].area();
    }
    return result;
}

double Triangulation::Integral2(void)
{
    double result = 0;
    for(int i = 0; i < Triangles.size(); i++)
    {
        TTriangle t = Triangles[i];
        TPoint2d p1 = t.p1, p2 = t.p2, p3 = t.p3,
                p12 = p2 - p1, p13 = p3 - p1,
                a = p12 / pow(2,split), b = p13 / pow(2,split);
        for(int j = 0; j < pow(2,split); j++)
        {
            for(int k = 0; k + j < pow(2,split); k++)
            {
                TPoint2d p1_ = p1 + a*j + b*k,
                        p2_ = p1 + a*(j+1) + b*k,
                        p3_ = p1 + a*j + b*(k+1),
                        p4_ = p1 + a*(j+1) + b*(k+1);
                TTriangle t1(p1_,p2_,p3_), t2(p4_,p2_,p3_);
                result += foo(t1.center())*t1.area();
                if(k + j < pow(2,split)-1)
                    result += foo(t2.center())*t2.area();
            }
        }
    }
    return result;
}

void Triangulation::Richardson(void){
    int t = clock();
    double integ = 2 * sinh(0.5);
    //cout << integ << endl;
    const int N = 9, r_ = 2, q_= 2, s_ = 2;
    double U[N][N] = {},
        P[N][N] = {},
        R[N][N] = {};
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            U[i][j] = P[i][j] = R[i][j] = 0.0;
        }
    }
    fout << "hi\n";
    cout.precision(32);
    for(int i = 0; i < N; i++)
    {
        cout << "now im here: N == " << i << endl;
        U[i][0] = Integral2();
        cout << U[i][0] << endl;
        for(int j = 1; j <= i; j++)
        {
           R[i][j] = (U[i][j-1]-U[i-1][j-1])/(pow(r_,(s_+q_*(j-1)))-1);
           U[i][j] = U[i][j-1] + R[i][j];
           if (j>1)
               P[i-2][j-2] = log(abs(R[i-1][j-1]/R[i][j-1]))/log(r_);
        }
        Split();
    }
    cout.precision(16);
    //cout.width(16);
    fout.precision(32);
    cout << endl << endl;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(U[i][j])
                cout << (integ - U[i][j]) << "\t";
            if(U[j][i] && j > 0)
            {
                fout << fabs(integ - U[j][i]) << "\n";
            }
        }
        cout << endl;
        fout << endl;
    }
    cout << endl;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(R[i][j]){
                cout << R[i][j] << "\t";

            }
            if(R[j][i])
            {
                fout << abs(R[j][i]) << "\n";
            }
        }
        cout << endl;
        fout << endl<< endl;
    }
    cout << endl;
    cout.precision(4);
    for(int i = 0; i < N-2; i++){
        for(int j = 0; j < N; j++){
            if(P[i][j]){
                cout << P[i][j] << "\t";
            }
        }
        cout << endl;
    }
    cout << endl;
    cout << "time:\n";
    cout << clock() - t << endl;
}

double Triangulation::foo(TPoint2d p){
    //return p.y*p.y*p.y;
    return exp(-p.x/a)/a/a;
    return p.length2() < r*r?exp(-(p.length2())/r/r):exp(-1);
}
