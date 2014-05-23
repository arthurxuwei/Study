// Factory.cpp: implementation of the Factory class.
//
//////////////////////////////////////////////////////////////////////

#include "Factory.h"
#include "Product.h"

#include <IOSTREAM>
using namespace std;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Factory::Factory()
{

}

Factory::~Factory()
{

}

ConcreteFactory::ConcreteFactory()
{
	cout << "ConcreteFactory....." << endl;
}
ConcreteFactory::~ConcreteFactory()
{
	cout << "~ConcreteFactory....." << endl;

}

Product* ConcreteFactory::CreteProduct()
{
	cout << "CreteProduct..." << endl;
	return new ConcreteProduct();
}