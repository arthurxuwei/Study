#include <IOSTREAM>
using std::cout;
using std::endl;

char *Reverse( char *str)
{
	int i = 0;
	int nNum = strlen( str ) ;
	int j = nNum - i - 1;
	while( j > i )
	{
		str[ nNum ] = str[ i ];
		str[ i ] = str[ j ];
		str[ j ] = str[ nNum ];
		i++;
		j = nNum - i - 1;
	}

	str[ nNum ] = '\0';
	return str;
}

int main()
{
	char str[] = "abcd";
	cout << str << endl;
	strcpy( str, Reverse( str ) );
	cout << str << endl;
	return 0;
}