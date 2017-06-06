template <class T> class SmartPointer {
public:
	SmartPointer(T *ptr) {
		ref = ptr;
		ref_count = (unsigned *)malloc(sizeof(unsigned));
		*ref_count = 1;
	}

	SmartPointer(SmartPointer<T> & sptr) {
		ref = sptr.ref;
		ref_count = sptr.ref_count;
		++*ref_count;
	}

	SmartPointer<T> &operator=(SmartPointer<T> &sptr) {
		if (this != &sptr) {
			ref = sptr.ref;
			ref_count = sptr.ref_count;
			++*ref_count;
		}
		return *this;
	}

	~SmartPointer() {
		--*ref_count;
		if (*ref_count == 0) {
			delete ref;
			free(ref_count);
			ref = NULL;
			ref_count = NULL;
		}
	}

	T getValue() {return *ref;}

protect:
	T *ref;
	unsigned *ref_count;
};
