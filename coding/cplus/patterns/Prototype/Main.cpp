//main.cpp
#include "Prototype.h"
#include <iostream>
using namespace std;

int main()
{
	Prototype* p = new ConcretePrototype();

	Prototype* p1 = p->Clone();

	return 0;
}