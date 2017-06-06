// Array.h: interface for the Array class.
//
//////////////////////////////////////////////////////////////////////
#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
using std::ostream;
using std::istream;

class Array  
{
	friend ostream &operator<<( ostream &, const Array & );
	friend istream &operator>>( istream &, Array & );

public:
	Array( int = 10 );//default constructor
	Array( const Array & );//copy constructor
	~Array();
	
	int getSize() const;

	const Array &operator=( const Array & );//assignment operator
	bool operator==( const Array & ) const;//equality operator

	//inequality operator; returns opposite of == operator
	bool operator!=( const Array &right ) const
	{
		return !( *this == right );//invokes Array::operator==
	}

	//subscript operator for non-const objects returns modifiable lvalue
	int &operator[]( int );
	//subscript operator for const objects returns rvalue
	int operator[]( int ) const;

private:
	int size; //pointer-based array size
	int *ptr; //pointer to first element of pointer-based array
};

#endif


