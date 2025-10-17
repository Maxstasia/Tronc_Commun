#ifndef ARRAY_HPP
# define ARRAY_HPP

# include <exception>
# include <cstddef>

template <typename T>
class Array
{
	private:
		T				*_elements;
		unsigned int	_size;

	public:
		// Constructeur par défaut
		Array(void);

		// Constructeur avec taille
		Array(unsigned int n);

		// Constructeur de copie
		Array(Array const &src);

		// Opérateur d'affectation
		Array &operator=(Array const &rhs);

		// Destructeur
		~Array(void);

		// Opérateur d'accès
		T &operator[](unsigned int index);
		T const &operator[](unsigned int index) const;

		// Getter de la taille
		unsigned int size(void) const;

		// Exception pour les indices hors limites
		class OutOfBoundsException : public std::exception
		{
			public:
				virtual const char *what() const throw()
				{
					return "Index out of bounds";
				}
		};
};

# include "Array.tpp"

#endif
