#include "PmergeMe.hpp"

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

// Génère la séquence d'indices basée sur Jacobsthal pour l'ordre d'insertion
std::vector<size_t> PmergeMe::generateJacobsthalSequence(size_t n)
{
	std::vector<size_t> jacobsthal;
	std::vector<size_t> insertOrder;
	
	// Générer les nombres de Jacobsthal jusqu'à dépasser n
	// J(0) = 0, J(1) = 1, J(n) = J(n-1) + 2*J(n-2)
	jacobsthal.push_back(0);
	jacobsthal.push_back(1);
	while (jacobsthal.back() < n)
	{
		size_t next = jacobsthal[jacobsthal.size() - 1] + 2 * jacobsthal[jacobsthal.size() - 2];
		jacobsthal.push_back(next);
	}
	
	// Construire l'ordre d'insertion basé sur Jacobsthal
	// On insère d'abord J(k), puis on descend jusqu'à J(k-1) + 1
	std::vector<bool> inserted(n + 1, false);
	
	for (size_t i = 1; i < jacobsthal.size(); i++)
	{
		size_t curr = jacobsthal[i];
		size_t prev = jacobsthal[i - 1];
		
		// Ajouter curr s'il est dans la plage
		if (curr <= n && !inserted[curr])
		{
			insertOrder.push_back(curr);
			inserted[curr] = true;
		}
		
		// Descendre de curr-1 jusqu'à prev+1
		for (size_t j = curr - 1; j > prev; j--)
		{
			if (j <= n && !inserted[j])
			{
				insertOrder.push_back(j);
				inserted[j] = true;
			}
		}
	}
	
	return insertOrder;
}

// Recherche binaire pour trouver la position d'insertion
template <typename Container>
typename Container::iterator PmergeMe::binarySearchInsert(Container &container,
	typename Container::iterator end, int value)
{
	typename Container::iterator begin = container.begin();
	
	while (begin < end)
	{
		typename Container::iterator mid = begin + (end - begin) / 2;
		if (*mid > value)
			end = mid;
		else
			begin = mid + 1;
	}
	return begin;
}

// Algorithme Ford-Johnson (merge-insertion sort)
template <typename Container>
void PmergeMe::fordJohnsonSort(Container &container)
{
	size_t size = container.size();
	
	if (size <= 1)
		return;
	
	// Étape 1: Créer des paires et trier chaque paire (larger, smaller)
	// DEBUG START
	std::cout << "\n=== ETAPE 1: Creation des paires ===\n";
	std::cout << "Input: ";
	for (size_t i = 0; i < size; i++)
		std::cout << container[i] << " ";
	std::cout << "\n";
	// DEBUG END
	
	std::vector<std::pair<int, int> > pairs;
	int straggler = -1;
	bool hasStraggler = (size % 2 != 0);
	
	for (size_t i = 0; i + 1 < size; i += 2)
	{
		int a = container[i];
		int b = container[i + 1];
		if (a > b)
			pairs.push_back(std::make_pair(b, a));
		else
			pairs.push_back(std::make_pair(a, b));
		// DEBUG START
		std::cout << "Pair " << (i/2 + 1) << ": (" << pairs.back().first << ", " << pairs.back().second << ") [smaller, larger]\n";
		// DEBUG END
	}
	
	// Gérer l'élément "straggler" s'il existe
	if (hasStraggler)
	{
		straggler = container[size - 1];
		// DEBUG START
		std::cout << "Straggler (element impair): " << straggler << "\n";
		// DEBUG END
	}
	// DEBUG START
	std::cout << "Total pairs: " << pairs.size() << "\n";
	std::cout << "=====================================\n";
	// DEBUG END
	
	// Étape 2: Trier récursivement les paires selon leur élément "larger"
	// On utilise une approche récursive sur les "larger" elements
	if (pairs.size() > 1)
	{
		// Créer un conteneur avec les éléments "larger"
		Container largerElements;
		// DEBUG START
		std::cout << "\n=== ETAPE 2: Tri recursif des larger ===\n";
		std::cout << "Larger elements avant tri recursif: ";
		// DEBUG END
		for (size_t i = 0; i < pairs.size(); i++)
		{
			largerElements.push_back(pairs[i].second);
			// DEBUG START
			std::cout << pairs[i].second << " ";
			// DEBUG END
		}
		// DEBUG START
		std::cout << "\n";
		std::cout << ">>> DEBUT RECURSION >>>\n";
		// DEBUG END
		
		// Trier récursivement
		fordJohnsonSort(largerElements);
		
		// DEBUG START
		std::cout << "<<< FIN RECURSION <<<\n";
		std::cout << "Larger elements apres tri recursif: ";
		for (size_t i = 0; i < largerElements.size(); i++)
			std::cout << largerElements[i] << " ";
		std::cout << "\n";
		// DEBUG END
		
		// Réorganiser les paires selon l'ordre trié des "larger"
		std::vector<std::pair<int, int> > sortedPairs;
		for (size_t i = 0; i < largerElements.size(); i++)
		{
			for (size_t j = 0; j < pairs.size(); j++)
			{
				if (pairs[j].second == largerElements[i])
				{
					sortedPairs.push_back(pairs[j]);
					pairs[j].second = -1; // Marquer comme utilisé
					break;
				}
			}
		}
		pairs = sortedPairs;
		
		// DEBUG START
		std::cout << "Pairs reordonnees: ";
		for (size_t i = 0; i < pairs.size(); i++)
			std::cout << "(" << pairs[i].first << "," << pairs[i].second << ") ";
		std::cout << "\n";
		std::cout << "========================================\n";
		// DEBUG END
	}
	
	// Étape 3: Construire la chaîne principale (main chain)
	// Le premier élément "smaller" (a1) est inséré en premier car il est <= b1
	Container mainChain;
	Container pend;
	
	if (!pairs.empty())
	{
		// a1 va en premier, puis b1
		mainChain.push_back(pairs[0].first); // a1
		mainChain.push_back(pairs[0].second);  // b1
		
		// Ajouter le reste des "larger" à la mainChain
		for (size_t i = 1; i < pairs.size(); i++)
			mainChain.push_back(pairs[i].second);
		
		// Les éléments "smaller" restants vont dans pend
		for (size_t i = 1; i < pairs.size(); i++)
			pend.push_back(pairs[i].first);
	}
	
	// DEBUG START
	std::cout << "\n=== ETAPE 3: Construction mainChain et pend ===\n";
	std::cout << "mainChain: ";
	for (size_t i = 0; i < mainChain.size(); i++)
		std::cout << mainChain[i] << " ";
	std::cout << "\npend: ";
	for (size_t i = 0; i < pend.size(); i++)
		std::cout << pend[i] << " ";
	std::cout << "\n";
	if (hasStraggler)
		std::cout << "straggler: " << straggler << "\n";
	std::cout << "===============================================\n\n";
	// DEBUG END
	
	// Étape 4: Insérer les éléments de pend en utilisant l'ordre de Jacobsthal
	if (!pend.empty())
	{
		std::vector<size_t> insertOrder = generateJacobsthalSequence(pend.size());
		
		// DEBUG START
		std::cout << "\n=== ETAPE 4: Insertion avec Jacobsthal ===\n";
		std::cout << "Ordre d'insertion Jacobsthal: ";
		for (size_t i = 0; i < insertOrder.size(); i++)
			std::cout << insertOrder[i] << " ";
		std::cout << "\n";
		// DEBUG END
		
		for (size_t i = 0; i < insertOrder.size(); i++)
		{
			size_t idx = insertOrder[i] - 1; // Convertir en index 0-based
			if (idx < pend.size())
			{
				int value = pend[idx];
				
				// DEBUG START
				std::cout << "Insertion de pend[" << idx << "] = " << value << "\n";
				std::cout << "  mainChain avant: ";
				for (size_t k = 0; k < mainChain.size(); k++)
					std::cout << mainChain[k] << " ";
				std::cout << "\n";
				// DEBUG END

				typename Container::iterator pos = binarySearchInsert(mainChain, mainChain.end(), value);
				
				// DEBUG START
				size_t insertPos = pos - mainChain.begin();
				// DEBUG END

				mainChain.insert(pos, value);
				
				// DEBUG START
				std::cout << "  Position inseree: " << insertPos << "\n";
				std::cout << "  mainChain apres:  ";
				for (size_t k = 0; k < mainChain.size(); k++)
					std::cout << mainChain[k] << " ";
				std::cout << "\n";
				// DEBUG END
			}
		}
		// DEBUG START
		std::cout << "==========================================\n\n";
		// DEBUG END
	}
	
	// Étape 5: Insérer le straggler s'il existe
	if (hasStraggler)
	{
		// DEBUG START
		std::cout << "\n=== ETAPE 5: Insertion du straggler ===\n";
		std::cout << "straggler = " << straggler << "\n";
		std::cout << "mainChain avant: ";
		for (size_t k = 0; k < mainChain.size(); k++)
			std::cout << mainChain[k] << " ";
		std::cout << "\n";
		// DEBUG END
		
		typename Container::iterator pos = binarySearchInsert(mainChain, mainChain.end(), straggler);

		// DEBUG START
		size_t insertPos = pos - mainChain.begin();
		// DEBUG END

		mainChain.insert(pos, straggler);
		
		// DEBUG START
		std::cout << "Position inseree: " << insertPos << "\n";
		std::cout << "mainChain apres:  ";
		for (size_t k = 0; k < mainChain.size(); k++)
			std::cout << mainChain[k] << " ";
		std::cout << "\n";
		std::cout << "=======================================\n\n";
		// DEBUG END
	}
	
	// Copier le résultat
	container = mainChain;
}

void PmergeMe::sortVector(void)
{
	if (_vector.size() <= 1)
		return;
	
	fordJohnsonSort(_vector);

	// DEBUG START
	std::cout << "==============================================\n";
	std::cout << "==============================================\n";
	std::cout << "==============================================\n";
	std::cout << "=== Résultat du tri Ford-Johnson sur vector ===\n";
	std::cout << "Sorted vector: ";
	for (size_t i = 0; i < _vector.size(); i++)
		std::cout << _vector[i] << " ";
	std::cout << "\n";
	std::cout << "==============================================\n";
	std::cout << "==============================================\n";
	std::cout << "==============================================\n";
	std::cout << "==============================================\n\n";
	// DEBUG END
}

void PmergeMe::sortDeque(void)
{
	if (_deque.size() <= 1)
		return;
	
	fordJohnsonSort(_deque);

	// DEBUG START
	std::cout << "=============================================\n";
	std::cout << "=============================================\n";
	std::cout << "=============================================\n";
	std::cout << "=== Résultat du tri Ford-Johnson sur deque ===\n";
	std::cout << "Sorted deque: ";
	for (size_t i = 0; i < _deque.size(); i++)
		std::cout << _deque[i] << " ";
	std::cout << "\n";
	std::cout << "=============================================\n";
	std::cout << "=============================================\n";
	std::cout << "=============================================\n";
	std::cout << "=============================================\n\n";
	// DEBUG END
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
