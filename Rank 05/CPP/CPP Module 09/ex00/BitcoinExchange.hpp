#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <map>
# include <string>

class BitcoinExchange
{
	private:
		std::map<std::string, double> _data;
		
		BitcoinExchange(BitcoinExchange const &src);
		BitcoinExchange &operator=(BitcoinExchange const &rhs);
		
		bool		isValidDate(std::string const &date) const;
		bool		isValidValue(double value) const;
		double		findClosestRate(std::string const &date) const;
		void		processLine(std::string const &line);

	public:
		BitcoinExchange(void);
		~BitcoinExchange(void);
		
		void		loadDatabase(std::string const &filename);
		void		processInput(std::string const &filename);
};

#endif
