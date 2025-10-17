#ifndef ARRAY_TPP
# define ARRAY_TPP

template <typename T>
Array<T>::Array(void) : _elements(NULL), _size(0)
{
}

template <typename T>
Array<T>::Array(unsigned int n) : _elements(new T[n]()), _size(n)
{
}

template <typename T>
Array<T>::Array(Array const &src) : _elements(NULL), _size(0)
{
	*this = src;
}

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

template <typename T>
Array<T>::~Array(void)
{
	delete[] _elements;
}

template <typename T>
T &Array<T>::operator[](unsigned int index)
{
	if (index >= _size)
		throw OutOfBoundsException();
	return _elements[index];
}

template <typename T>
T const &Array<T>::operator[](unsigned int index) const
{
	if (index >= _size)
		throw OutOfBoundsException();
	return _elements[index];
}

template <typename T>
unsigned int Array<T>::size(void) const
{
	return _size;
}

#endif
