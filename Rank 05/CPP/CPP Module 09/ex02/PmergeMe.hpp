#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <vector>
# include <deque>
# include <iostream>
# include <cstdlib>
# include <iomanip>

class PmergeMe
{
	private:
		std::vector<int>	_vector;
		std::deque<int>		_deque;
		
		PmergeMe(PmergeMe const &src);
		PmergeMe &operator=(PmergeMe const &rhs);
		
		// Génère les indices de Jacobsthal pour l'ordre d'insertion
		std::vector<size_t> generateJacobsthalSequence(size_t n);
		
		// Recherche binaire pour l'insertion
		template <typename Container>
		typename Container::iterator binarySearchInsert(Container &container,
			typename Container::iterator end, int value);
		
		// Algorithme Ford-Johnson (merge-insertion sort)
		template <typename Container>
		void fordJohnsonSort(Container &container);

	public:
		PmergeMe(void);
		~PmergeMe(void);
		
		void		parseInput(int argc, char **argv);
		void		sortVector(void);
		void		sortDeque(void);
		void		displayBefore(void) const;
		void		displayAfter(void) const;
		
		std::vector<int> const	&getVector(void) const;
		std::deque<int> const	&getDeque(void) const;
};

#endif
