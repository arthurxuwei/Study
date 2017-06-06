//main.cpp

#include "Product.h"
#include "Factory.h"

#include <IOSTREAM>
using std::cout;

int main()
{
	Factory* fac = new ConcreteFactory();

	Product* p = fac->CreteProduct();

	delete p;
	delete fac;

	return 0;
}