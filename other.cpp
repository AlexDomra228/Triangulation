#include "AdvancingFront.h"
void Triangulation::Plus(int k)
{//передвижение по фронту
	if (k >= 0) {
		for (int i = 0; i < k; i++) {
			if (fit == Front.end()) {
				fit = Front.begin();
			}
			fit++;
		}
	}
	else {
		for (int i = 0; i < -k; i++) {
			if (fit == Front.begin()) {
				fit = Front.end();
				fit--;
			}
			else fit--;
		}
	}
	if (fit == Front.end()) fit = Front.begin();
}

void Triangulation::CirclePlus(void)
{
    cfit++;
    if(cfit == CircleFront.end())
    {
        cfit = CircleFront.begin();
        cout << "suck\n";
    }
}

void Triangulation::CircleMinus(void)
{
    if(cfit == CircleFront.begin())
    {
        cfit = CircleFront.end();
        cout << "suck\n";
    }
    cfit--;
}

void Triangulation::PlusNode()
{
    it_node++;
    if(it_node==Nodes.size())
        it_node = 0;
}
void Triangulation::MinusNode()
{
    if(it_node == 0)
        it_node=Nodes.size();
    it_node--;
}

list<int>::iterator Triangulation::Plus(const list<int>::iterator &it,int k)
{
	list<int>::iterator iter = it;
	if (k >= 0) {
		for (int i = 0; i < k; i++) {
			if (iter == Front.end()) {
				iter = Front.begin();
			}
			iter++;
		}
	}
	else {
		for (int i = 0; i < -k; i++) {
			if (iter == Front.begin()) {
				iter = Front.end();
				iter--;
			}
			else iter--;
		}
	}
	if (iter == Front.end()) iter = Front.begin();
	return iter;
}
