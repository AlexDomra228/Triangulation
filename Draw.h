#pragma once
#include "AdvancingFront.h"
#include "gl\glut.h"
#include "Windows.h"

void Draw(Triangle t,int LineWidth);

void DrawNeinb(Triangulation *trian);

void DrawNeib(Triangulation *trian, int n);

void Fill(Triangle t);

void Fill(Triangulation* trian, int tr);

void pause(double tau);

void DrawSquare(double a, int LineWidth);

void DrawCircle(double r, int LineWidth);

void Draw(Triangulation *trian);

void DrawFront(Triangulation *trian);

void DrawNodes(Triangulation *trian);

void DrawEdges(Triangulation *trian);

void DrawEdges(Triangulation *trian, int n);

void Fill(Triangulation *trian);

void FillRecursion(Triangulation *trian);

void FillRecursion(Triangulation *trian, int tr);

void glWrite(float x, float y, char text[256], int kls, int* font = (int*)GLUT_BITMAP_TIMES_ROMAN_24);
