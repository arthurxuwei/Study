// Factory.h: interface for the Factory class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _FACTORY_H_
#define _FACTORY_H_

class Product;

class Factory  
{
public:
	virtual ~Factory() = 0;
	virtual Product* CreteProduct() = 0;
protected:
	Factory();

};

class ConcreteFactory : public Factory
{
public:
	ConcreteFactory();
	~ConcreteFactory();

	Product* CreteProduct();
};

#endif // !defined
