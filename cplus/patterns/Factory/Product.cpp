// Product.cpp: implementation of the Product class.
//
//////////////////////////////////////////////////////////////////////

#include "Product.h"

#include <IOSTREAM>
using namespace std;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Product::Product()
{

}

Product::~Product()
{
	
}

ConcreteProduct::ConcreteProduct()
{
	cout << "ConcreteProduct..." << endl;
}

ConcreteProduct::~ConcreteProduct()
{
	cout << "~ConcreteProduct..." << endl;
}