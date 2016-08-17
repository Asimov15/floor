template <class T>
class audax
{
	private:
		vector<T> fortis;		
	
	public:		
		audax(T, T, T);
		audax();
		audax(const audax<T> &obj);				
		~audax();		
		vector<T> getvec();		
		T &       operator[](int);		
		audax<T>  operator+(audax<T>);
		audax<T>  operator-(audax<T>);
		audax<T>  operator*(double);
		audax<T>  operator/(double);
		void      operator+=(audax<T>);
		double    magnitude();
		audax<T>  unitize();
		void      clear();
		double    dot_product(audax<T>);
};

template <class T>
audax<T>::audax(T x, T y, T z)
{	
	fortis.push_back(x);
	fortis.push_back(y);
	fortis.push_back(z);
}

template <class T>
audax<T>::audax()
{	
	fortis.push_back(0);
	fortis.push_back(0);
	fortis.push_back(0);
}

template <class T>
audax<T>::audax(const audax<T> &obj)
{		
	fortis = obj.fortis;
}

template <class T>
audax<T>::~audax()
{}	

template <class T>
vector<T> audax<T>::getvec()
{
	return fortis;
}

template <class T>
T &audax<T>::operator[](int index)
{
	return fortis[index];
}

template <class T>
audax<T> audax<T>::operator+(audax<T> a)
{
	int i;
	audax<T> c;
	
	for (i = 0; i < 3; i++)
	{
		c[i] = (*this)[i] + a[i];
	}
	return c;
}
template <class T>
audax<T> audax<T>::operator-(audax<T> a)
{
	int i;
	audax<T> c;
	
	for (i = 0; i < 3; i++)
	{
		c[i] = (*this)[i] - a[i];
	}
	return c;
}

template <class T>
audax<T> audax<T>::operator*(double a)
{
	int i;
	audax<T> b;
	
	for (i = 0; i < 3; i++)
	{
		b[i] = (*this)[i] * a;
	}
	return b;
}

template <class T>
audax<T> audax<T>::operator/(double a)
{
	int i;
	audax<T> b;
	
	for (i = 0; i < 3; i++)
	{
		b[i] = (*this)[i] / a;
	}
	return b;
}

template <class T>
double audax<T>::magnitude()
{
	return pow (pow((*this)[0],2) + pow((*this)[1],2) + pow((*this)[2],2), 0.5 );
}

template <class T>
audax<T> audax<T>::unitize()
{
	return (*this) / (*this).magnitude();
}

template <class T>
void audax<T>::clear()
{
	int i;
	for (i = 0; i < 3; i++)
	{
		(*this)[i] = 0;
	}
}

template <class T>
void audax<T>::operator+=(audax<T> a)
{
	int i;	
	
	for (i = 0; i < 3; i++)
	{
		(*this)[i] = (*this)[i] + a[i];
	}
}

template <class T>
double audax<T>::dot_product(audax<T> v2)
{
	double g;
	g = (*this)[0] * v2[0] + (*this)[1] * v2[1] + (*this)[2] * v2[2];
	
	return g;
}
