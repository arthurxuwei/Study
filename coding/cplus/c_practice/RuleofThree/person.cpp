/**
 *  the rule of three: if you need to explicitly declare either the destructor,
 *  copy constructor or copy assignment operator yourself, you probably need to 
 *  explicitly declare all three of them.
 *
 */
class person
{
	char* name;
	int age;

public:
	//the constructor acquires a resource:
	//in this case, dynamic memory obtained via new[]
	person(const char* the_name, int the_age)
	{
		name = new char[strlen(the_name) + 1];
		strcpy(name, the_name);
		age = the_age;
	}

	//the destructor must release this resource via delete[]
	~person()
	{
		delete[] name;
	}

	//copy constructor
	person(const person& that)
	{
		name = new char[strlen(that.name) + 1];
		strcpy(name, that.name);
		age = that.age;
	}

	//copy assignment operator
	person& operator=(const person& that)
	{
		if (this != &that)
		{
			delete[] name;
			//this is dangerous point in the flow of execution
			//we have temporarily invalidated the class invariants,
			//and the next statement might throw an exception,
			//leaving the object in an invalid state :(
			name = new char[strlen(that.name) + 1];
			strcpy(name, that.name);
			age = that.age;
		}
		return *this;
	}
	
	//exception safety version
	//person& operator=(const person& that)
	//{
	//	char* local_name = new char[strlen(that.name) + 1];
	//	//if the above statement throws,
	//	// the object is still in the same state as before.
	//	// Noen of the following statements will throw an exception :)
	//	strcpy(local_name, that.name);
	//	delete[] name;
	//	name = local_name;
	//	age = that.age;
	//	return *this;
	//}

}
