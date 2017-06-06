//cannot use zero array in c++ standard
//only use in GUN C
#include <iostream>
using namespace std;

struct A{
	int size;
	char o;
	int size2;
	char data[0];
};

main() {
	cout << sizeof(A) << endl;
	A a;
	cout << "a addr: " << &a << endl;
	cout << "data[0]: " << a.data << endl;
	cout << "data[0] addr: " << &a.data[0] << endl;
	
}
