// Array.cpp: implementation of the Array class.
//
//////////////////////////////////////////////////////////////////////

#include "Array.h"
#include <iostream>
using std::cerr;
using std::cout;
using std::cin;
using std::endl;

#include <iomanip>
using std::setw;

#include <cstdlib>

//default constructor for class Array ( default size 10 )
Array::Array( int arraySize )
{
	size = ( arraySize > 0 ? arraySize : 10 ); // validate arraySize
	ptr = new int[ size ];//create space for pointer-based array

	for ( int i = 0; i < size; i++ )
		ptr[ i ] = 0;//set pointer-based array element
}//end default constructor

//copy constructor for class Array
//must receive a reference to prevent infinite recursion
Array::Array( const Array &arrayToCopy )
	: size( arrayToCopy.size )
{
	ptr = new int[ size ]; //create space for pointer-based array

	for ( int i = 0; i < size; i++ )
		ptr[ i ] = arrayToCopy.ptr[ i ];//copy
	
}//end copy constructor

//destructor for class Array
Array::~Array()
{
	delete [] ptr;//release space
}

//return number of elements of Array
int Array::getSize() const
{
	return size;
}

//overloaded assignment operator
//const return avoids: ( a1 = a2 ) = a3
const Array &Array::operator=( const Array &right )
{
	if ( &right != this )//avoid self-assignment
	{
		//for Arrays of different sizes, deallocate original
		//left-side array, then allocate new left-side array
		if ( size != right.size )
		{
			delete [] ptr;//release
			size = right.size;
			ptr = new int[ size ];//create new space
		}//end inner if
		
		for ( int i = 0; i < size; i++ )
			ptr[ i ] = right.ptr[ i ];//copy
	}//end outer if

	return *this;
}//end operator =

//determine of two Arrays are equal and
//return true, otherwise return fales
bool Array::operator==( const Array &right ) const
{
	if ( size != right.size )
		return false;

	for ( int i = 0; i < size; i++ )
		if ( ptr[ i ] != right.ptr[ i ] )
			return false;
	
	return true;
}//end operator ==

//overloaded subscript operator for non-const Arrays;
//reference return creates a modifiable lvalue
int &Array::operator []( int subscript )
{
	//check for subscript out-of-range error
	if ( subscript < 0 || subscript >= size )
	{
		cerr << "\nError: Subscript " << subscript << "out of range" <<endl;
		exit( 1 );
	}//end if

	return ptr[ subscript ];//reference return;
}//end operator[]

//overloaded subscript operator for const Arrays;
//const reference return creates an rvalue
int Array::operator []( int subscript) const
{
	//check for subscript out-of-range error
	if ( subscript < 0 || subscript >= size )
	{
		cerr << "\nError: Subscript " << subscript << "out of range" <<endl;
		exit( 1 );
	}//end if

	return ptr[ subscript ];//reference return;
}//end operator[]

//overloaded input operator for class Array
//inputs values for entire Array
istream &operator>>( istream &input, Array &a )
{
	for ( int i = 0; i < a.size; i++ )
		input >> a.ptr[ i ];

	return input;
}//end operator>>

//overloaded output operator for class Array
ostream &operator<<( ostream &output, const Array &a )
{
	int i;

	//output private ptr-based array
	for ( i = 0; i < a.size ; ++i )
	{
		output << setw( 12 ) << a.ptr[ i ];

		if ( ( i + 1) % 4 == 0 )//4 numbers per rpw of output
			output << endl;
	}//end for

	if ( i % 4 != 0 )//end ast line of output
		output << endl;

	return output;
}//end operator<<