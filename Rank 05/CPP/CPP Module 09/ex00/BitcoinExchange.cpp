#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

BitcoinExchange::BitcoinExchange(void)
{
}

BitcoinExchange::BitcoinExchange(BitcoinExchange const &src)
{
	*this = src;
}

BitcoinExchange::~BitcoinExchange(void)
{
}

BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange const &rhs)
{
	if (this != &rhs)
		this->_data = rhs._data;
	return (*this);
}

static std::string trim(std::string const &str)
{
	size_t start = str.find_first_not_of(" \t\n\r");
	if (start == std::string::npos)
		return ("");
	size_t end = str.find_last_not_of(" \t\n\r");
	return (str.substr(start, end - start + 1));
}

bool BitcoinExchange::isValidDate(std::string const &date) const
{
	if (date.length() != 10)
		return (false);
	if (date[4] != '-' || date[7] != '-')
		return (false);
	
	for (size_t i = 0; i < date.length(); i++)
	{
		if (i == 4 || i == 7)
			continue;
		if (!isdigit(date[i]))
			return (false);
	}
	
	int year = atoi(date.substr(0, 4).c_str());
	int month = atoi(date.substr(5, 2).c_str());
	int day = atoi(date.substr(8, 2).c_str());
	
	if (year < 2009 || year > 2022)
		return (false);
	if (month < 1 || month > 12)
		return (false);
	if (day < 1 || day > 31)
		return (false);
	
	// Vérification simplifiée des jours par mois
	if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
		return (false);
	if (month == 2)
	{
		bool isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
		if ((isLeap && day > 29) || (!isLeap && day > 28))
			return (false);
	}
	
	return (true);
}

bool BitcoinExchange::isValidValue(double value) const
{
	return (value >= 0.0 && value <= 1000.0);
}

double BitcoinExchange::findClosestRate(std::string const &date) const
{
	std::map<std::string, double>::const_iterator it = _data.lower_bound(date);
	
	// Si on trouve la date exacte
	if (it != _data.end() && it->first == date)
		return (it->second);
	
	// Si on est au début, prendre la première valeur
	if (it == _data.begin())
	{
		if (it != _data.end())
			return (it->second);
		return (0.0);
	}
	
	// Sinon prendre la valeur précédente
	--it;
	return (it->second);
}

void BitcoinExchange::loadDatabase(std::string const &filename)
{
	std::ifstream file(filename.c_str());
	if (!file.is_open())
		throw std::runtime_error("Error: could not open database file.");
	
	std::string line;
	std::getline(file, line); // Sauter l'en-tête
	
	while (std::getline(file, line))
	{
		size_t comma = line.find(',');
		if (comma == std::string::npos)
			continue;
		
		std::string date = trim(line.substr(0, comma));
		std::string valueStr = trim(line.substr(comma + 1));
		
		if (!isValidDate(date))
			continue;
		
		double value = atof(valueStr.c_str());
		_data[date] = value;
	}
	
	file.close();
	
	if (_data.empty())
		throw std::runtime_error("Error: database is empty.");
}

void BitcoinExchange::processLine(std::string const &line)
{
	// Ignorer les lignes vides
	if (trim(line).empty())
		return;
	
	size_t pipe = line.find('|');
	if (pipe == std::string::npos)
	{
		std::cout << "Error: bad input => " << line << std::endl;
		return;
	}
	
	std::string date = trim(line.substr(0, pipe));
	std::string valueStr = trim(line.substr(pipe + 1));
	
	// Validation de la date
	if (!isValidDate(date))
	{
		std::cout << "Error: bad input => " << date << std::endl;
		return;
	}
	
	// Conversion de la valeur
	char *endptr;
	double value = strtod(valueStr.c_str(), &endptr);
	
	// Vérifier si la conversion a réussi
	if (*endptr != '\0' && *endptr != '\n' && *endptr != '\r')
	{
		std::cout << "Error: bad input => " << valueStr << std::endl;
		return;
	}
	
	// Validation de la valeur
	if (value < 0)
	{
		std::cout << "Error: not a positive number." << std::endl;
		return;
	}
	
	if (!isValidValue(value))
	{
		std::cout << "Error: too large a number." << std::endl;
		return;
	}
	
	// Trouver le taux de change et calculer
	double rate = findClosestRate(date);
	double result = value * rate;
	
	std::cout << date << " => " << value << " = " << result << std::endl;
}

void BitcoinExchange::processInput(std::string const &filename)
{
	std::ifstream file(filename.c_str());
	if (!file.is_open())
		throw std::runtime_error("Error: could not open input file.");
	
	std::string line;
	std::getline(file, line); // Sauter l'en-tête
	
	while (std::getline(file, line))
	{
		processLine(line);
	}
	
	file.close();
}
