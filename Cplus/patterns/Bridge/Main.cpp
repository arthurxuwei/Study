//main.cpp
#include "Abstraction.h"
#include "AbstractionImp.h"
#include <iostream>
using namespace std;


int main()
{
	AbstractionImp* imp = new ConcreteAbstractionImpA();

	Abstraction* abs = new RefinedAbstraction(imp);

	abs->Operation();

	return 0;
}