#ifndef ARRAY_TPP
# define ARRAY_TPP

// Implémentation des méthodes de la classe Array
// Constructeur par défaut
template <typename T>
Array<T>::Array(void) : _elements(NULL), _size(0)
{
}

// Constructeur avec taille
template <typename T>
Array<T>::Array(unsigned int n) : _elements(new T[n]()), _size(n)
{
}

// Constructeur de copie
template <typename T>
Array<T>::Array(Array const &src) : _elements(NULL), _size(0)
{
	*this = src;
}

// Opérateur d'affectation
template <typename T>
Array<T> &Array<T>::operator=(Array const &rhs)
{
	if (this != &rhs)
	{
		delete[] _elements;
		_size = rhs._size;
		if (_size > 0)
		{
			_elements = new T[_size];
			for (unsigned int i = 0; i < _size; i++)
				_elements[i] = rhs._elements[i];
		}
		else
			_elements = NULL;
	}
	return *this;
}

// Destructeur
template <typename T>
Array<T>::~Array(void)
{
	delete[] _elements;
}


// Opérateur d'accès
template <typename T>
T &Array<T>::operator[](unsigned int index)
{
	if (index >= _size)
		throw OutOfBoundsException();
	return _elements[index];
}

// Opérateur d'accès constant
template <typename T>
T const &Array<T>::operator[](unsigned int index) const
{
	if (index >= _size)
		throw OutOfBoundsException();
	return _elements[index];
}

// Getter de la taille
template <typename T>
unsigned int Array<T>::size(void) const
{
	return _size;
}

#endif
