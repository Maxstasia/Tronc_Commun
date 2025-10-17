#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <vector>
# include <deque>
# include <string>

class PmergeMe
{
	private:
		std::vector<int>	_vector;
		std::deque<int>		_deque;
		
		PmergeMe(PmergeMe const &src);
		PmergeMe &operator=(PmergeMe const &rhs);
		
		// Tri par insertion pour petites séquences
		template <typename Container>
		void insertionSort(Container &container, int left, int right);
		
		// Algorithme Ford-Johnson (merge-insertion sort)
		template <typename Container>
		void mergeInsertSort(Container &container, int left, int right);
		
		template <typename Container>
		void merge(Container &container, int left, int mid, int right);

	public:
		PmergeMe(void);
		~PmergeMe(void);
		
		void		parseInput(int argc, char **argv);
		void		sortVector(void);
		void		sortDeque(void);
		void		displayBefore(void) const;
		void		displayAfter(void) const;
		double		getVectorTime(void) const;
		double		getDequeTime(void) const;
		
		std::vector<int> const	&getVector(void) const;
		std::deque<int> const	&getDeque(void) const;
};

#endif
