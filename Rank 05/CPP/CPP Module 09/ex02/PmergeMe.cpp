#include "PmergeMe.hpp"
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <iomanip>

PmergeMe::PmergeMe(void)
{
}

PmergeMe::PmergeMe(PmergeMe const &src)
{
	*this = src;
}

PmergeMe::~PmergeMe(void)
{
}

PmergeMe &PmergeMe::operator=(PmergeMe const &rhs)
{
	if (this != &rhs)
	{
		this->_vector = rhs._vector;
		this->_deque = rhs._deque;
	}
	return (*this);
}

void PmergeMe::parseInput(int argc, char **argv)
{
	for (int i = 1; i < argc; i++)
	{
		std::string arg = argv[i];
		
		// Vérifier que c'est un nombre positif
		for (size_t j = 0; j < arg.length(); j++)
		{
			if (!isdigit(arg[j]))
				throw std::runtime_error("Error: invalid input");
		}
		
		long num = atol(arg.c_str());
		if (num < 0 || num > 2147483647)
			throw std::runtime_error("Error: number out of range");
		
		_vector.push_back(static_cast<int>(num));
		_deque.push_back(static_cast<int>(num));
	}
	
	if (_vector.empty())
		throw std::runtime_error("Error: no input provided");
}

template <typename Container>
void PmergeMe::insertionSort(Container &container, int left, int right)
{
	for (int i = left + 1; i <= right; i++)
	{
		int key = container[i];
		int j = i - 1;
		
		while (j >= left && container[j] > key)
		{
			container[j + 1] = container[j];
			j--;
		}
		container[j + 1] = key;
	}
}

template <typename Container>
void PmergeMe::merge(Container &container, int left, int mid, int right)
{
	Container temp;
	int i = left;
	int j = mid + 1;
	
	while (i <= mid && j <= right)
	{
		if (container[i] <= container[j])
		{
			temp.push_back(container[i]);
			i++;
		}
		else
		{
			temp.push_back(container[j]);
			j++;
		}
	}
	
	while (i <= mid)
	{
		temp.push_back(container[i]);
		i++;
	}
	
	while (j <= right)
	{
		temp.push_back(container[j]);
		j++;
	}
	
	for (size_t k = 0; k < temp.size(); k++)
	{
		container[left + k] = temp[k];
	}
}

template <typename Container>
void PmergeMe::mergeInsertSort(Container &container, int left, int right)
{
	if (right - left <= 10)
	{
		insertionSort(container, left, right);
		return;
	}
	
	if (left < right)
	{
		int mid = left + (right - left) / 2;
		
		mergeInsertSort(container, left, mid);
		mergeInsertSort(container, mid + 1, right);
		merge(container, left, mid, right);
	}
}

void PmergeMe::sortVector(void)
{
	if (_vector.size() <= 1)
		return;
	
	mergeInsertSort(_vector, 0, _vector.size() - 1);
}

void PmergeMe::sortDeque(void)
{
	if (_deque.size() <= 1)
		return;
	
	mergeInsertSort(_deque, 0, _deque.size() - 1);
}

void PmergeMe::displayBefore(void) const
{
	std::cout << "Before: ";
	for (size_t i = 0; i < _vector.size() && i < 5; i++)
	{
		std::cout << _vector[i];
		if (i < _vector.size() - 1 && i < 4)
			std::cout << " ";
	}
	if (_vector.size() > 5)
		std::cout << " [...]";
	std::cout << std::endl;
}

void PmergeMe::displayAfter(void) const
{
	std::cout << "After:  ";
	for (size_t i = 0; i < _vector.size() && i < 5; i++)
	{
		std::cout << _vector[i];
		if (i < _vector.size() - 1 && i < 4)
			std::cout << " ";
	}
	if (_vector.size() > 5)
		std::cout << " [...]";
	std::cout << std::endl;
}

std::vector<int> const &PmergeMe::getVector(void) const
{
	return (_vector);
}

std::deque<int> const &PmergeMe::getDeque(void) const
{
	return (_deque);
}
